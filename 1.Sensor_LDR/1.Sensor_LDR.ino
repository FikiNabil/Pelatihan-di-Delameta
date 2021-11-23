//INISIALIASI
int pinLDR=A0;

void setup() {
 Serial.begin(9600);
}

void loop() {
  //BACA DATA
  int bacaLDR=analogRead(pinLDR);

  //PRINT TO SERIAL
  Serial.print("NILAI :");
  Serial.print(bacaLDR);
  Serial.println();
  delay(500);
}
