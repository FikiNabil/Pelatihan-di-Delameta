//INISIALISASI
int pinFlame=A0;
int pinBuzzer=4;

void setup() {
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaFlame=analogRead(pinFlame);
  bacaFlame=map(bacaFlame,5,1015,100,0);

  //PRINT TO SERIAL
  Serial.print("NILAI SENSOR :");
  Serial.print(bacaFlame);
  Serial.println(); //UNTUK ENTER

  //LOGIKA
  if(bacaFlame == 0) {
    Serial.println("AMAN!");
    digitalWrite(pinBuzzer, LOW);
  }
  else if(bacaFlame >=20 and bacaFlame <=50){
    Serial.println("WARNING SILAHKAN PERIKSA!!");
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
    digitalWrite(pinBuzzer, LOW);
    delay(1000);
  }
  else if(bacaFlame >=50){
    Serial.println("WASPADA HARAP MENGUNGSI!!!");
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
    digitalWrite(pinBuzzer, LOW);
    delay(200);
  }
}
