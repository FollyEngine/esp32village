

// https://www.play-zone.ch/en/st-l293d-motor-treiber-push-pull-4-channel-driver-mit-dioden.html
// https://techtutorialsx.com/2016/09/12/esp8266-controlling-a-motor-with-the-uln2803a/

int motorPin1 = 5; //Pin that will control the motor
int motorPin2 = 22; //Pin that will control the motor

void setup() {
  while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");
  
  pinMode(motorPin1, OUTPUT);  //Initialize the pin as output pin
  pinMode(motorPin2, OUTPUT);  //Initialize the pin as output pin
}

void loop() {
  Serial.printf("Off\n");

  digitalWrite(motorPin1,HIGH);  //Turn off the motor
  digitalWrite(motorPin2,HIGH);  //Turn off the motor
  delay(2000);

  Serial.printf("On one way\n");
  digitalWrite(motorPin1,LOW);  //Turn on the motor at full speed
  digitalWrite(motorPin2,HIGH);  //Turn on the motor at full speed
  delay(2000);

  Serial.printf("On other way\n");
  digitalWrite(motorPin1,HIGH);  //Turn on the motor at full speed
  digitalWrite(motorPin2,LOW);  //Turn on the motor at full speed
  delay(2000);

}

