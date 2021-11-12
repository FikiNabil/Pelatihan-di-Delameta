//INISIALISASI
int PIR=PA5;
int LEDRed=PA2;
int LEDGreen=PA4;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaPIR=digitalRead(PIR); //Sensor PIR

  //PRINT TO SERIAL
  Serial.print("| Nilai PIR: "); Serial.print(bacaPIR);
  Serial.println();
  delay(500);

  //LOGIKA PROGRAM
   //Program Sensor PIR
   if(bacaPIR == 1){
    digitalWrite(LEDRed, HIGH);
    digitalWrite(LEDGreen, LOW);
   }
   else if(bacaPIR == 0){
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDGreen, HIGH);
   }
}
