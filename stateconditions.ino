#define aipincs A1
#define aopinr A2
#define aopints A3


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
unsigned long starttime = micros();



unsigned long currenttime = micros();
unsigned long totaltime = currenttime - starttime;
Serial.println(totaltime);
}

void loop() {
  // put your main code here, to run repeatedly:
while(aipincs)

}
