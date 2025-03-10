#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Project Brystol//

LiquidCrystal_I2C lcd(0x27, 16, 2); //figure out how to use LCD

const float Vtrip = 3; //3V to trip, test to see level to trip

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(2, OUTPUT); //digital pwm 2, relay switch
  pinMode(4, OUTPUT); //digital pwm 4, trip system
  pinMode(A1, INPUT);
}

void loop() {
//Voltage from current sensor in
const float Vin = analogRead(A1); //value from the current sensor Andrew makes
float voltage = Vin*(5/1024.0); 
float tripped = voltage < Vtrip;

if(tripped) {
  unsigned long trstartt = micros();
  digitalWrite(2, LOW); //trips the line
  digitalWrite(4, HIGH); //turns on the trip system LED

  unsigned long trcurrentt = micros();
  unsigned long trtotalt = trcurrentt - trstartt;

  lcd.clear();
  lcd.setCursor(1, 0); //overcurrent fault trip statement
  lcd.print(trtotalt);
  lcd.setCursor(3,0);
  lcd.print("us");
  lcd.setCursor(0,1);
  lcd.print("Relay Tripped");
  delay(10000);
}

else if(abs(voltage - Vtrip) < 0.1) {//change that value
  unsigned long rstartt = micros();
  digitalWrite(4, LOW); //turns off the trip system LED
  digitalWrite(2, HIGH); //resets the digital relay

  unsigned long rcurrentt = micros();
  unsigned long rtotalt = rcurrentt - rstartt;

  lcd.clear();
  lcd.setCursor(1, 0); //lcd print out for the normal condition
  lcd.print(rtotalt);
  lcd.setCursor(3,0);
  lcd.print("us");
  lcd.setCursor(0,1);
  lcd.print("Relay Reset");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reset Achieved");
  delay(10000);
}

if(!tripped) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Normal Operation");
}

delay(1000);
return;
}
