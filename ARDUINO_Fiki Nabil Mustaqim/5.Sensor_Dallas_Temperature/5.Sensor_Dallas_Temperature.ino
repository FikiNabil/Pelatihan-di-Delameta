//Inisialisasi pembuatan variable
#include <OneWire.h>
#include <DallasTemperature.h>
int Buzzer =3;
int sensorSuhu =2;
OneWire oneWire(sensorSuhu);
DallasTemperature sensors(&oneWire);

void setup() {
 Serial.begin(9600); //baudrate yang digunakan untuk komunikasi microcontroller dengan komputer
 sensors.begin(); //Memanggil fungsi
 pinMode(Buzzer, OUTPUT);
}

void loop() {
 //BACA SENSOR
 sensors.requestTemperatures();
 float bacaSuhu = sensors.getTempCByIndex(0); //Membaca data di index 0 pada one wire

 //PRINT TO SERIAL
 Serial.print("SUHU :");
 Serial.print(bacaSuhu);
 Serial.print("C");
 Serial.println();

 //LOGIKA
 if(bacaSuhu >=31){
  digitalWrite(Buzzer, HIGH);
  delay(100);
  digitalWrite(Buzzer, LOW);
  delay(100);
 }
 else {
  digitalWrite(Buzzer, LOW);
 }
}
