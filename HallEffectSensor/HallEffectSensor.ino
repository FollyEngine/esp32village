// Read the onboard hall effect senosr
// This is really there to tell you if a magnetic field
// is affecting your equipment... But you can also 
// Use it to notice if a magnet is nearby.
// This example is based on this web page tutorial: 
// https://alexkychen.wordpress.com/2017/11/13/control-led-using-esp32-hall-effect-sensor/
// I tried the magnets from my daughters' magnet set and if I held a couple of them about 
// 3 mm from the top of the chipI got a reading.
// But people with neodymium magnets were talking about big numbers - detects polarity.


int hall_reading=0;

void setup() {

  // set up serial
   Serial.begin(115200);

}

void loop() {
  // read hall effect sensor
  hall_reading = hallRead();

  Serial.print("Hall Reading:");
  Serial.println(hall_reading);

  delay(1000);

}
