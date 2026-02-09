//TO SIMULATE MOVEMENT IN THIS WOKWI PROJECT, CLICK ON THE PIR SENSOR
//WHILE THE SIMULATION IS RUNNING AND CLICK "SIMULATE MOTION" IN THE POPUP-BOX

#include <LiquidCrystal_I2C.h>

// set pin numbers
const int pirPin = 14;  // the number of the pir pin
const int ledPin = 26;     // LED pin

// variable for storing the pir status
int pirState = 0;

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  // initialize the pir pin as an input
  pinMode(pirPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Start the LCD
  lcd.clear();
  lcd.init();
  lcd.backlight();
}

void loop() {
  // read the state of the pir value
  pirState = digitalRead(pirPin);
  Serial.println(pirState);
  delay(1000);

  // if the pir is pressed, the pirState is HIGH
  if (pirState == HIGH) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Motion Detected          ");

  } else {
    // turn LED off
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("All Clear                ");
  }
}
