//INISIALIASI
int pinLDR=A0;
int LEDRed=3;

void setup() {
 Serial.begin(9600);
 pinMode(LEDRed, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaLDR=analogRead(pinLDR);
  bacaLDR=map(bacaLDR,3,973,0,255);

  //PRINT TO SERIAL
  Serial.print("NILAI :");
  Serial.print(bacaLDR);
  Serial.println();

  //LOGIKA
  analogWrite(LEDRed, bacaLDR);
}
