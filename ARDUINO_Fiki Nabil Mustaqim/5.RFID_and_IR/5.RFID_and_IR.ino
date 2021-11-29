//Inisialisasi pembuatan variable
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

String uidString;
int Buzzer=4;
int R=2;
int G=3;
int IR=5;
int flag=0;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); //Create MFRC522 instance.

void setup() {
 Serial.begin(9600); //baudrate yang digunakan untuk komunikasi microcontroller dengan komputer
 SPI.begin(); // Initiate SPI bus
 mfrc522.PCD_Init(); // Initiate MFRC522
 pinMode(Buzzer, OUTPUT);
 pinMode(R, OUTPUT);
 pinMode(G, OUTPUT);
 pinMode(IR, INPUT);
 lcd.begin();
 lcd.setCursor(1,0);lcd.print("Tempelkan Kartu!");
 digitalWrite(R, HIGH);
 digitalWrite(G, LOW);
}

void BuzzerOKE(){
 digitalWrite(G, HIGH);
 digitalWrite(R, LOW);
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
 digitalWrite(R, HIGH);
 digitalWrite(G, LOW);
 digitalWrite(Buzzer, HIGH);
 delay(1000);
 digitalWrite(Buzzer, LOW);
 delay(100);
}

void loop() {
 int bacaIR=digitalRead(IR);
 if (mfrc522.PICC_IsNewCardPresent() and flag==0) {
 readRFID();
 lcd.clear();
 lcd.setCursor(0,0); lcd.print("Tag UID:");
 lcd.setCursor(8,0); lcd.print(uidString);
 lcd.setCursor(1,1); lcd.print("Message : ");
 delay(1000);
 if (uidString=="199-157-136-74"){
  flag=1;
  lcd.setCursor(1,0); lcd.print("Success");
  delay(1000);
  lcd.setCursor(1,0); lcd.print("Gate Opened!");
  delay(1000);
  BuzzerOKE();
  }
  else {
  flag=0;
  lcd.setCursor(1,0); lcd.print("Failed");
  BuzzerGagal();
  }
}
  if (bacaIR==0 and flag==1){
    flag=0;
    lcd.setCursor(1,0); lcd.print("Please Go");
    delay(1000);
    lcd.setCursor(1,0); lcd.print("Gate Closed!");
    delay(1000);
    BuzzerOKE();
    }
}

void readRFID(){
 mfrc522.PICC_ReadCardSerial();
 //Pembatas bisa dirubah sesuai keinginan, disini yang digunakan "-"
 uidString = String(mfrc522.uid.uidByte[0]) + "-" +
             String(mfrc522.uid.uidByte[1]) + "-" + 
             String(mfrc522.uid.uidByte[2]) + "-" +
             String(mfrc522.uid.uidByte[3]);
 }
