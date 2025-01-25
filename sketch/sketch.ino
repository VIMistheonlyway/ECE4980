uint32_t i = 0;

void setup() {
  // Here's some code, doesn't do much

  // Gotta make it do something
  Serial.begin(9600);
}

void loop() {
  /* lets count, cuz why not.
   * might wrap around at 4,294,967,295
   * might crash
   * maybe bet on it
   */
  Serial.println(i++);
}
