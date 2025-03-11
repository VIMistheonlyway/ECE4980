#include <Wire.h>

const float Vtrip = 3.0; // Trip voltage level
int trip_flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); // Digital PWM 2, relay switch
  pinMode(A1, INPUT); // Line voltage check
  pinMode(A3, INPUT); // Trip voltage check
}

void loop() {

  // Read actual analog values
  int VlineRaw = analogRead(A1);
  float voltage_line = VlineRaw * (5.0 / 1023.0);

  int VinRaw = analogRead(A3);
  float voltage_in = VinRaw * (5.0 / 1023.0);;

  if (voltage_in <= Vtrip) {
    unsigned long trstart = micros(); // Start trip timer
    digitalWrite(2, LOW); // Trip line
    
    while (trip_flag == 0) {
      voltage_in = analogRead(A0) * (5.0 / 1023.0); // Continuously read new values
      if (voltage_in < 0.1) { // Check if voltage dropped near zero
        unsigned long trcurrent = micros(); // End trip timer
        unsigned long trtotal = trcurrent - trstart; // Calculate elapsed time
        Serial.println("Relay Tripped");
        Serial.print("Time Elapsed: ");
        Serial.println(trtotal);
        trip_flag = 1;
      }
    }
  } else {
    digitalWrite(2, HIGH); // RELAY SWITCH ON NORMALLY
    Serial.println("Normal Operation");
  }

  trip_flag = 0;
  delay(5000); // Reasonable delay
}
