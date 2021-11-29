#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
 //Menentukan Fungsionalitas dari PIN pada Microcontroller
 Serial.begin(115200); //baudrate yang digunakan untuk komunikasi microcontroller dengan komputer
 lcd.begin();
}

void loop() {
 //Program yang akan dijalankan berulang-ulang
 float suhu=random(27.1,35.10);
 
 lcd.clear(); //Untuk Menghapus karakter pada LCD
 lcd.setCursor(1,0); lcd.print("Suhu Saat Ini: ");
 lcd.setCursor(5,1); lcd.print(suhu);
 delay(1000); //Jeda waktu perulagan seama 1000 mili detik
}
