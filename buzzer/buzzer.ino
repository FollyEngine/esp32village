// https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/
// https://learn.sparkfun.com/tutorials/transistors - all about transistors


/*
 * Drive a passive piezo buzzer to make noises using sounds.
 * Use a transistor and some resistors as a switch  with an external battery to power the buzzer.
 * Play with the duty cycle and the frequency to change loudness and pitch.
 * 
 * S9013 Transistor
 * 1kOhm Resistor  - between pin 4 signal and base of transistor 
 * 460 Ohm Resistor - across the pins of the piezo buzzer
 * 100 Ohm Resisotr - between + of piezo buzzer and V+ - change this one to change how loud the buzzer is.
 * External battery - 4 pack AA - connect Ground to ground of ESP32 or faith the wrath of the disconnected ground fairy
 * 
 */

int freq = 2000;
int channel = 0;
int resolution = 8;

void setup() {

  Serial.begin(115200);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(4, channel);


}


void loop() {

  delay(1000);

   ledcWriteTone(channel, 2000);

 
   /* change loudness */
   for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle=dutyCycle+10){
 
    Serial.println(dutyCycle);
 
    ledcWrite(channel, dutyCycle);
    delay(100);
  }
  
   for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle=dutyCycle-10){
 
    Serial.println(dutyCycle);
 
    ledcWrite(channel, dutyCycle);
    delay(100);
  }

  /* change pitch */             
  ledcWriteTone(channel, 500);
  for (int freq = 255; freq < 10000; freq = freq + 250){
 
     Serial.println(freq);
 
     ledcWriteTone(channel, freq);
     delay(500);
  }

 

}
