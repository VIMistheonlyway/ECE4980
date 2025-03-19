#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Project Brystol//

LiquidCrystal_I2C lcd(0x27, 16, 2); //figure out how to use LCD

const float Itrip = 0.060; //9V and 200 Ohm resistance as normal line conditions

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(2, OUTPUT); //digital pwm 2, relay switch
  pinMode(4, OUTPUT); //digital pwm 4, trip system
  pinMode(A1, INPUT); //sensor input
  pinMode(A2, INPUT); //button input
}

void loop() {
//Voltage from current sensor in
const float Vin = analogRead(A1); //value from the current sensor
int B = analogRead(A2); //analog input of button
float voltage = Vin*(5/1023.0); 
float current = (voltage - 2.5) / 66; //conversion of the read voltage to current
float Iline = current; //multiplied by the load resistance to get vline
//Serial.println(Iline);
float trip = Iline > Itrip; //compares the vline to the trip voltage set

if(trip) {
  unsigned long trstartt = micros();
  digitalWrite(2, LOW); //trips the relay
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
  //Serial.println("Relay Tripped");
  delay(10000);
}

else if(B < 0.5) {//checks the ripple of the voltage
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
  //Serial.println("Relay Reset");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reset Achieved");
  Serial.println("Reset Achieved");
  delay(10000);
}

if(!trip || B > 0.5) { //Normal Operation
  digitalWrite(2, HIGH); //digital relay  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Normal Operation");
  //Serial.println("Normal Operation");
}

delay(1000);
return;
}

