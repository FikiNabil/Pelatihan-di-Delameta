//INISIALISASI
int IR = PA0;
int Buzzer = PA1;
int LEDRed = PA2;
int flag=0;

void setup() {
  Serial.begin(9600);
  pinMode(IR, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LEDRed, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaIR=digitalRead(IR);
  
  //PRINT TO SERIAL
  Serial.println("Kondisi IR : " + String(bacaIR));

  //LOGIKA
  if(bacaIR == 0 and flag ==0){
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LEDRed, HIGH);
    delay(500);
    flag=1;
  }
  else if(bacaIR == 0 and flag ==1){
    digitalWrite(Buzzer, LOW);
    digitalWrite(LEDRed, LOW);
    delay(500);
    flag=0;
  }
}
