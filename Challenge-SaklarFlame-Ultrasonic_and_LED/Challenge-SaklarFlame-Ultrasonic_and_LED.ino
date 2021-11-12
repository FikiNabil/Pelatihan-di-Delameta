//INISIALISASI
#include <NewPing.h>
int Flame=PA0;
int triger=PA1;
int echo=PA2;
int batas=400;
int LEDRed=PA3;
int LEDYellow=PA4;
int LEDGreen=PA5;
int flag=0;

NewPing cm(triger, echo, batas);

void setup(){
  Serial.begin(9600);
  pinMode(Flame, INPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop(){
  //BACA DATA
  int bacaFlame=digitalRead(Flame);
  delay(500);
  int bacaJarak=cm.ping_cm();

  //SERIAL TO PRINT
  Serial.print("Nilai Flame: "); Serial.print(bacaFlame);
  Serial.print("| Data Jarak: "); Serial.print(bacaJarak);
  Serial.print("| NilaiFlag :"); Serial.print(flag);
  Serial.println();

  //LOGIKA PROGRAM
  if(bacaFlame == 0 and flag == 0){
    flag=1;
    delay(500);
  }
  else if(bacaFlame == 0 and flag == 1){
    delay(500);
    flag=0;
  }

  

  if(flag==1){
    if(bacaJarak <=10){
      digitalWrite(LEDRed, HIGH);
      digitalWrite(LEDYellow, HIGH);
      digitalWrite(LEDGreen, HIGH);
      delay(100);
      digitalWrite(LEDRed, LOW);
      digitalWrite(LEDYellow, LOW);
      digitalWrite(LEDGreen, LOW);
      delay(100);
    }
    else if(bacaJarak >=10 and bacaJarak <=30){
      digitalWrite(LEDRed, HIGH);
      digitalWrite(LEDYellow, HIGH);
      digitalWrite(LEDGreen, HIGH);
      delay(1000);
      digitalWrite(LEDRed, LOW);
      digitalWrite(LEDYellow, LOW);
      digitalWrite(LEDGreen, LOW);
      delay(1000);
    }
    else if(bacaJarak >=30){
      digitalWrite(LEDRed, HIGH);
      delay(200);
      digitalWrite(LEDRed, LOW);
      delay(200);
      digitalWrite(LEDYellow, HIGH);
      delay(200);
      digitalWrite(LEDYellow, LOW);
      delay(200);
      digitalWrite(LEDGreen, HIGH);
      delay(200);
      digitalWrite(LEDGreen, LOW);
      delay(200);
      digitalWrite(LEDYellow, HIGH);
      delay(200);
      digitalWrite(LEDYellow, LOW);
      delay(200);
      digitalWrite(LEDRed, HIGH);
      delay(200);
      digitalWrite(LEDRed, LOW);
    }
  }
 else if(flag==0){
   digitalWrite(LEDRed, LOW);
   digitalWrite(LEDYellow, LOW);
   digitalWrite(LEDGreen, LOW);
  }
}
