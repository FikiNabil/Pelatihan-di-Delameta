//INISIALISASI
int LDR = PA0;
int LEDRed = PA1;

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(LEDRed, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaldr=analogRead(LDR);
  bacaldr=map(bacaldr, 0, 4095, 0, 255);
  
  //PRINT TO SERIAL
  Serial.println("Kondisi Lampu : " + String(bacaldr));

  //LOGIKA
  analogWrite(LEDRed, bacaldr);
  delay(100);
}
