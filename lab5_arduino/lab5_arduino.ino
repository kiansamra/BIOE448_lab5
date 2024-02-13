const int trigPin = 8;
const int echoPin = 10;
// const int ledPin1 = 3; 
// const int ledPin2 = 4; 
long duration;
float distanceCm, distanceInch;
// const float R1 = 1/58;
// const float R2 = 1/148;
const int C = 10;

#include <ArduinoBLE.h>
BLEService newService("180A"); // creating the service
BLEByteCharacteristic readChar("2A57", BLERead);
BLEByteCharacteristic writeChar("2A58", BLEWrite);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(ledPin1, OUTPUT); 
  // pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);

  while(!Serial);
  if (!BLE.begin()){
  Serial.println("Waiting for ArduinoBLE");
  while(1);
  }

  BLE.setDeviceName("KianAndKate");
  BLE.setAdvertisedServiceUuid("1234abcd1234abcd");
  BLE.setAdvertisedService(newService);
  newService.addCharacteristic(readChar);
  newService.addCharacteristic(writeChar);
  BLE.addService(newService);

  readChar.writeValue(0);
  writeChar.writeValue(0);

  BLE.advertise();
  Serial.println("Bluetooth device active");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(C);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 1/58;
  distanceInch = duration * 1/148;
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm/");
  Serial.print(distanceInch);
  Serial.println(" in");

  readChar.writeValue(distanceCm);

  // if (distanceCm < 5) {
  //   digitalWrite(ledPin1, HIGH); 
  //   digitalWrite(ledPin2, LOW);  
  // } else {
  //   digitalWrite(ledPin1, LOW);   
  //   digitalWrite(ledPin2, HIGH);  
  // }

  delay(1);
}


