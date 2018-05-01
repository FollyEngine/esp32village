/*
  Blink

  This is the official Arduino blink example slightly adapated to drive
  3 LEDs with the ESP32.

  You need to attach a resistor in series between the I/O pin and Anode
  (the long leg of the LED).  Then attach the cathode (the short leg) to ground.

  If you hold it up standard LED to the light you can see a diagonal line 
  closer to the cathode like in the fritzing diagram.  
  
  Without the resistor, you might break the ESP32 or the LED.

  A 1k Ohm resistor works - you can go smaller eg 100 Ohm - 
  your LED will be brighter but you will be using more current.   

  This program will turn 3 LEDs on and off at the same time.  

  The on board blue LED will turn on and off with pin 5 - but it will 
  turn on when your LED turns off.  It has a resistor attached to Vc (3 V)
  (a pull up resistor) built onto the board.

  Original Comments:

  Turns an LED on for one second, then off for one second, repeatedly.  
  Adapted to drive external LEDs too.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // LED_BUILTIN is IO5
  pinMode(LED_BUILTIN, OUTPUT); 

  // pin IO2
  pinMode(2, OUTPUT);

  // pin IO4
  pinMode(4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  delay(1000);    // wait for a second
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  delay(1000);                       // wait for a second
}
