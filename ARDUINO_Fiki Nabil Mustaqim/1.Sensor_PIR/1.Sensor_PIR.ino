//INISIALISASI
int pinPIR=2;
int pinBuzzer=5;

void setup() {
  Serial.begin(9600);
  pinMode(pinPIR, INPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  //BACA SENSOR
  int bacaPIR=digitalRead(pinPIR);

  //PRINT TO SERIAL
  Serial.print("PIR");
  Serial.print(bacaPIR);
  Serial.println(); //UNTUK ENTER

  //LOGIKA
  if(bacaPIR==1){
    Serial.println("AWAS ADA MALING!!!");
    digitalWrite(pinBuzzer, HIGH);
    delay(100);
    digitalWrite(pinBuzzer, LOW);
    delay(100);
  }
  else {
    Serial.println("AMAN BOS QUE...");
    digitalWrite(pinBuzzer, LOW);
  }
}
