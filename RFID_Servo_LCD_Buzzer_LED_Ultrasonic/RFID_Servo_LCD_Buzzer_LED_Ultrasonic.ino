//INISIALISASI LIBRARY
#include <NewPing.h>
#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

//INISIALISASI PIN
int triger=7;
int echo=6;
int batas=15;
int Buzzer=3;
int LEDRed=4;
int LEDGreen=5;
int outServo=2;
int flag=0;

#define SS_PIN 10
#define RST_PIN 9

//INISIALIASI LIBRARY TO VARIABLE
MFRC522 mfrc522(SS_PIN, RST_PIN);
NewPing cm(triger, echo, batas);
LiquidCrystal_I2C lcd(0x27, 16, 2);
String uidString;
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(outServo);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(Buzzer, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
  lcd.begin();
  welcome();
}

void welcome(){
  lcd.clear();
  lcd.setCursor(1,0); lcd.print("SELAMAT DATANG");
  lcd.setCursor(0,1); lcd.print("TEMPELKAN KARTU!");
  myservo.write(0);
  delay(1000);
  digitalWrite(LEDRed, HIGH);
  digitalWrite(LEDGreen, LOW);
}


void BuzzerOKE(){
 digitalWrite(LEDGreen, HIGH);
 digitalWrite(LEDRed, LOW);
 digitalWrite(Buzzer, HIGH);
 delay(100);
 digitalWrite(Buzzer, LOW);
 delay(100);
 digitalWrite(Buzzer, HIGH);
 delay(100);
 digitalWrite(Buzzer, LOW);
 delay(100);
}

void BuzzerGagal(){
 digitalWrite(LEDRed, HIGH);
 digitalWrite(LEDGreen, LOW);
 digitalWrite(Buzzer, HIGH);
 delay(1000);
 digitalWrite(Buzzer, LOW);
 delay(100);
}

void readRFID(){
 mfrc522.PICC_ReadCardSerial();
 //Pembatas bisa dirubah sesuai keinginan, disini yang digunakan "-"
 uidString = String(mfrc522.uid.uidByte[0]) + "-" +
             String(mfrc522.uid.uidByte[1]) + "-" + 
             String(mfrc522.uid.uidByte[2]) + "-" +
             String(mfrc522.uid.uidByte[3]);
 }

void loop() {
  //BACA DATA
  int bacaJarak=cm.ping_cm();

  //PRINT TO SERIAL
  Serial.print("Data Jarak: ");
  Serial.print(bacaJarak);
  Serial.print(" cm");
  Serial.print("| Tag UID: ");
  Serial.print(uidString);
  Serial.println();
  delay(500); 

  //LOGIKA PROGRAM
  if(mfrc522.PICC_IsNewCardPresent() and flag==0){
  readRFID();
    if(uidString == "167-50-137-75"){
      flag=1;
      lcd.clear();
      lcd.setCursor(4,0); lcd.print("BERHASIL");
      lcd.setCursor(0,1); lcd.print("PALANG TERBUKA!");
      BuzzerOKE();
      myservo.write(90);
      delay(1000);
      }
     else {
      flag=0;
      lcd.clear();
      lcd.setCursor(6,0); lcd.print("GAGAL");
      lcd.setCursor(4,1); lcd.print("DIPROSES!");
      BuzzerGagal();
      delay(1000);
      welcome();
     }
   }

    if(bacaJarak !=0 and bacaJarak <=15 and flag==1){
      flag=0;
      lcd.clear();
      lcd.setCursor(2,0); lcd.print("TERIMAKASIH");
      lcd.setCursor(0,1); lcd.print("SELAMAT JALAN");
      BuzzerOKE();
      delay(300);
      lcd.setCursor(0,1); lcd.print("PALANG TERTUTUP!");
      myservo.write(0);
      delay(1000);
      welcome();
     }
}
