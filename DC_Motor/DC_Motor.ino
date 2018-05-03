

// https://www.play-zone.ch/en/st-l293d-motor-treiber-push-pull-4-channel-driver-mit-dioden.html
// https://techtutorialsx.com/2016/09/12/esp8266-controlling-a-motor-with-the-uln2803a/

int motorPin1 = 21; //Pin that will control the motor
int motorPin2 = 22; //Pin that will control the motor

void setup() {
  while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");

  pwm_setup();
}

void loop() {
  pwm_loop();
}

void onoff_setup() {
  pinMode(motorPin1, OUTPUT);  //Initialize the pin as output pin
  pinMode(motorPin2, OUTPUT);  //Initialize the pin as output pin
}
void onoffloop() {
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

void pwm_setup() {
  ledcAttachPin(LED_BUILTIN, 3); // internal blue led (pin 5), led channel 0?
  ledcSetup(3, 12000, 8);


  ledcAttachPin(motorPin1, 1); // assign motor pins to channels
  ledcAttachPin(motorPin2, 2);
  
  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
}

//https://github.com/espressif/esp-idf/tree/master/examples/peripherals/mcpwm/mcpwm_brushed_dc_control
void pwm_loop() {
  Serial.printf("Off\n");

  ledcWrite(1, 255);  //Turn off the motor
  ledcWrite(2, 255);  //Turn off the motor
  ledcWrite(3, 0);  // TURN on the LED

  delay(2000);

/*
  Serial.printf("On one way\n");
  ledcWrite(1,0);  //Turn on the motor at full speed
  ledcWrite(2u,255);  //Turn on the motor at full speed
  delay(2000);

  Serial.printf("On other way\n");
  ledcWrite(1,255);  //Turn on the motor at full speed
  ledcWrite(2,0);  //Turn on the motor at full speed
  delay(2000);
*/

  Serial.printf("Sweep\n");
  for (int i=0; i<80; i++) {
    Serial.printf("Sweep %d\n", i);

    // NOTE: you write to the ledc channel, not the pin!
    ledcWrite(1, i);  //Turn on the motor at full speed
    ledcWrite(2, 255-i);  //Turn on the motor at full speed

    ledcWrite(3, i);  // Sweep the led to OFF

    delay(100);
  }
  Serial.printf("Sweep other way\n");
  for (int i=0; i<80; i++) {
    Serial.printf("Sweep %d\n", i);

    ledcWrite(2, i);  //Turn on the motor at full speed
    ledcWrite(1, 255-i);  //Turn on the motor at full speed

    ledcWrite(3, i);  // Sweep the led to OFF

    delay(100);
  }

}
