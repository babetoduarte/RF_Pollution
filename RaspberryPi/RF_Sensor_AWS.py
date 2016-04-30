import paho.mqtt.client as mqtt
import ssl
import jsonpickle

awsClient=mqtt.Client()
awsClient.tls_set("rootCA.pem", certfile="ca6601c61a-certificate.pem.crt", keyfile="ca6601c61a-private.pem.key", cert_reqs=ssl.CERT_REQUIRED,
    tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)
awsClient.connect("A21KN5F6UZ417N.iot.us-east-1.amazonaws.com", 8883, 60)

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    payload = {"state": {"desired": {"signal": msg.payload}}}
    aws_payload = jsonpickle.encode(payload)
    awsClient.publish('$aws/things/emf_sensor_2/shadow/update', payload=aws_payload, qos=0, retain=False)

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed to "+str(mid))

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    localClient.subscribe("RFMeasurements")

localClient = mqtt.Client()
localClient.on_connect = on_connect
localClient.on_message = on_message
localClient.on_subscribe = on_subscribe
localClient.connect("localhost",1883, 60)

#awsClient.loop_forever()
localClient.loop_forever(timeout=1.0, max_packets=1, retry_first_connection=True)
