//Inisialisasi pembuatan variable
#include <NewPing.h>
int Buzzer =3;
int triger =4;
int echo =5;
int R =6;
int Y =7;
int G =8;
int batas =400; //Maksimal 400 cm
NewPing cm(triger,echo,batas);

void setup() {
 Serial.begin(9600);
 pinMode(Buzzer, OUTPUT);
 pinMode(R, OUTPUT);
 pinMode(Y, OUTPUT);
 pinMode(G, OUTPUT);
}

void loop() {
  //BACA DATA
 int bacaJarak=cm.ping_cm();
 
 //Print ke Serial Monitor
 Serial.print("Data Jarak: ");
 Serial.print(bacaJarak);
 Serial.print(" cm");
 Serial.println();
 delay(500); 

 //LOGIKA
 if (bacaJarak <=20 and bacaJarak !=0){
  Serial.println("BERHENTI");
  digitalWrite(R, HIGH);
  digitalWrite(Y, LOW);
  digitalWrite(G, LOW);
  digitalWrite(Buzzer, HIGH);
  delay(50);
  digitalWrite(Buzzer, LOW);
  delay(50);
 }
 else if(bacaJarak >=21 and bacaJarak <=70){
  Serial.println("BAHAYA");
  digitalWrite(R, LOW);
  digitalWrite(Y, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(Buzzer, HIGH);
  delay(500);
  digitalWrite(Buzzer, LOW);
  delay(500);
 }
 else if(bacaJarak >=71 and bacaJarak <=200){
  Serial.println("AMAN");
  digitalWrite(R, LOW);
  digitalWrite(Y, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(Buzzer, LOW);
 }
}
