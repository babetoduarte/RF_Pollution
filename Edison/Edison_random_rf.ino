char* possibleMeasurements[] = {"0000","0001","0010","0011", "0100", "0101", "0110", "0111", "1000", "1001"}; 

void setup() {
  //Start Serial Console
  Serial.begin(9600);
  //Setup ditital pins as Outputs
  pinMode(13, OUTPUT); //This will flash a board led indicating transmission
  pinMode(2, OUTPUT); //This will be the most significant bit connectig to the NodeMCU's D1 pin
  pinMode(4, OUTPUT); //This will be the second most significant bit connectig to the NodeMCU's D2 pin
  pinMode(7, OUTPUT); //This will be the second least significant bit connectig to the NodeMCU's D3 pin
  pinMode(8, OUTPUT); //This will be the least significant bit connectig to the NodeMCU's D4 pin
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(100);
  char* rfMeasurement = possibleMeasurements[random(0,10)];
  //Serial.println(rfMeasurement);
  //Turn on indicator LED
  digitalWrite(13, HIGH);
  if(rfMeasurement=="0000"){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    Serial.println("No Measurement");
  }
  else if(rfMeasurement=="0001"){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    Serial.println("-70 dBm");
  }
  else if(rfMeasurement=="0010"){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    Serial.println("-60 dBm");
  }
  else if(rfMeasurement=="0011"){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("-50 dBm");
  }
  else if(rfMeasurement=="0100"){
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    Serial.println("-40 dBm");
  }
  else if(rfMeasurement=="0101"){
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    Serial.println("-30 dBm");
  }
  else if(rfMeasurement=="0110"){
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    Serial.println("-20 dBm");
  }
  else if(rfMeasurement=="0111"){
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("-10 dBm");
  }
  else if(rfMeasurement=="1000"){
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    Serial.println("0 dBm");
  }
  else if(rfMeasurement=="1001"){
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    Serial.println("+10 dBm");
  }
  else {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("ERROR");
  }
  
  delay(2000); //Wait 2s to generate another reading (keeping the current reading on)
  //Set all pins to low
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  //Turn of indicator LED
  digitalWrite(13, LOW);
}
