//INISIALISASI
#include <NewPing.h>
int triger=PA0;
int echo=PA1;
int batas=400;
int LEDRed=PA2;
int LEDYellow=PA3;
int LEDGreen=PA4;

NewPing cm(triger, echo, batas);

void setup() {
  Serial.begin(9600);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaJarak=cm.ping_cm(); //Sensor Ultrasonik

  //PRINT TO SERIAL
  Serial.print(" | Data Jarak: "); 
  Serial.print(bacaJarak); 
  Serial.print("cm");
  Serial.println();
  delay(500);

  //LOGIKA PROGRAM
   //Program Sensor Ultrasonik
   if(bacaJarak <=20){
    digitalWrite(LEDRed, HIGH);
    digitalWrite(LEDYellow, LOW);
    digitalWrite(LEDGreen, LOW);
   }
   else if(bacaJarak >=20 and bacaJarak <=50){
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDYellow, HIGH);
    digitalWrite(LEDGreen, LOW);
   }
   else if(bacaJarak >=50){
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDYellow, LOW);
    digitalWrite(LEDGreen, HIGH);
   }
}
