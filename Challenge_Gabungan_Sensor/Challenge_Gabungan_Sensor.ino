//INISIALISASI
int flame=A0;
int LDR=A1;
int R=3;
int Y=6;
int G=7;
int Buzzer=5;
int PIR=4;

void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  //BACA DATA
  int bacaFlame=analogRead(flame);
      bacaFlame=map(bacaFlame,5,1015,100,0);
  int bacaLDR=analogRead(LDR);
      bacaLDR=map(bacaLDR,3,1015,0,100);
  int bacaPIR=digitalRead(PIR);

  //SENSOR LDR
  analogWrite(R, bacaLDR);

  //SENSOR FLAME
  if(bacaFlame == 0){
    Serial.println("AMAN BANGET");
    digitalWrite(Buzzer, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(Y, LOW);
  }
  else if(bacaFlame >=25 and bacaFlame<=50){
    Serial.println("WARNING SILAHKAN PERIKSA");
    digitalWrite(Y, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
    delay(500);
  }
  else if(bacaFlame >=50){
    Serial.println("WASPADA HARAP MENGUNGSI");
    digitalWrite(G, HIGH);
    digitalWrite(Y, HIGH);
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(200);
  }
}
