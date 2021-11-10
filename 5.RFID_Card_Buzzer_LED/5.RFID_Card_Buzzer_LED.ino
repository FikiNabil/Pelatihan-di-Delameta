//Inisialisasi pembuatan variable
#include <SPI.h>
#include <MFRC522.h>
String uidString;
int Buzzer=4;
int R=2;
int G=3;
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
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
 readRFID();
 Serial.print("Tag UID:");
 Serial.println(uidString);
 Serial.println();
 Serial.print("Message : ");

 //LOGIKA
 if (uidString=="C79D884A"){
 Serial.println("Selamat datang BRO!!!");
 BuzzerOKE();
 }
 else if(uidString=="EA 06D580"){
 Serial.println("Selamat datang GAN!!!");
 BuzzerOKE();
 }
 else{
 Serial.println("Kartu Belum Terdaftar!");
 BuzzerGagal();
 }
 Serial.println("Tempelkan Kartu!");
 delay(500); //Jeda waktu perulagan seama 500 mili detik
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
