//INISIALISASI
int pinFlame=A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //BACA DATA
  int bacaFlame=analogRead(pinFlame);
  bacaFlame=map(bacaFlame,1000,0,0,100);
  

  //PRINT TO SERIAL
  Serial.print("NILAI SENSOR :");
  Serial.print(bacaFlame);
  Serial.println();
}

  
