//INISIALISASI
int Flame=PA6;;
int LEDRed=PA2;
int LEDGreen=PA4;


void setup() {
  Serial.begin(9600);
  pinMode(Flame,INPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaFlame=digitalRead(Flame); //Sensor Flame

  //PRINT TO SERIAL
  Serial.print("Nilai Flame: "); Serial.print(bacaFlame);
  Serial.println();
  delay(500);

  //LOGIKA PROGRAM
   //Program Sensor Flame
   if(bacaFlame == 1){
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDGreen, HIGH);
   }
   else if(bacaFlame == 0){
    digitalWrite(LEDRed, HIGH);
    digitalWrite(LEDGreen, LOW);
   }
}
