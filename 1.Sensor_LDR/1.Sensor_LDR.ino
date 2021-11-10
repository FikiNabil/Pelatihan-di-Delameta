//INISIALIASI
int pinLDR=A0;
int LEDRed=2;

void setup() {
 Serial.begin(9600);
}

void loop() {
  //BACA DATA
  int bacaLDR=analogRead(pinLDR);
  pinMode(LEDRed, OUTPUT);

  //PRINT TO SERIAL
  Serial.print("NILAI :");
  Serial.print(bacaLDR);
  Serial.println();

  //LOGIKA
  if(bacaLDR <=500){
    digitalWrite(LEDRed, HIGH);
  }
  else {
    digitalWrite(LEDRed, LOW);
  }
}
