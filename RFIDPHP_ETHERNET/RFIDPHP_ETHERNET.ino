#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h> //6.17.3
#include <SPI.h>
#include <MFRC522.h>

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "192.168.1.63"; // change to your PC's IP address
String PATH_NAME   = "/rfid_fiki/data-api.php";
String getData;

#define SS_PIN 9
#define RST_PIN 8
#define buzzer 7

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(115200);
  pinMode (buzzer,OUTPUT);
  while(!Serial);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //delay(3000);
  //START IP DHCP
  Serial.println("Konfigurasi DHCP, Silahkan Tunggu!");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP Gagal!");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet Tidak tereteksi :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Hubungkan kabel Ethernet!");
    }
    while (true) {delay(1);}
  }  
  //End DHCP 
  delay(5000); 
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());  
  client.connect(HOST_NAME, HTTP_PORT);
  Serial.println("Siap Digunakan!");
}

void loop() {
  //Baca data
  
   //Program yang akan dijalankan berulang-ulang
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String uidString;
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     uidString.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "" : ""));
     uidString.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.print("Message : ");
  uidString.toUpperCase();
  Serial.println(uidString);
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);

  //POST TO WEB
    client.connect(HOST_NAME, HTTP_PORT);
    client.println(HTTP_METHOD + " " + PATH_NAME + 
                   "?rfid=" + String(uidString) +
                   "&tol=Bogor" +
                   //"&sensor1=" + String(sensor1) + 
                   //"&sensor2=" + String(sensor2) + 
                   " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header
  
    while(client.connected()) {
      if(client.available()){
        char endOfHeaders[] = "\r\n\r\n";
        client.find(endOfHeaders);
        getData = client.readString();
        getData.trim();
        
        //AMBIL DATA JSON
        const size_t capacity = JSON_OBJECT_SIZE(12) + 210; //cari dulu nilainya pakai Arduino Json 5 Asisten
        DynamicJsonDocument doc(capacity);
        //StaticJsonDocument<192> doc;
        DeserializationError error = deserializeJson(doc, getData);
      
        const char* id_dibaca       = doc["id"]; 
        const char* rfid_dibaca     = doc["rfid"]; 
        const char* nama_dibaca     = doc["nama"]; 
        const char* alamat_dibaca   = doc["alamat"]; 
        const char* telepon_dibaca  = doc["telepon"];
        const char* saldo_dibaca    = doc["saldo"]; 
        const char* tanggal_dibaca  = doc["tanggal"]; 
        const char* tol_dibaca      = doc["tol"];
        const char* harga_dibaca    = doc["harga"];
        const char* saldoawal_dibaca       = doc["saldoawal"];
        const char* saldoakhir_dibaca      = doc["saldoakhir"];
        const char* keterangan_dibaca      = doc["keterangan"];
      
       //LOGIKA
       if(String(nama_dibaca)!=""){
        buzzeroke();
        Serial.println("Kartu Terdaftar!");
        Serial.println(getData);
        //POST TO SERIAL
         Serial.print("ID       = ");Serial.println(id_dibaca);
         Serial.print("RFID     = ");Serial.println(rfid_dibaca);
         Serial.print("Nama     = ");Serial.println(nama_dibaca);
         Serial.print("Alamat   = ");Serial.println(alamat_dibaca);
         Serial.print("Telepon  = ");Serial.println(telepon_dibaca);
         Serial.print("Saldo   = ");Serial.println(saldo_dibaca);
         Serial.print("Waktu    = ");Serial.println(tanggal_dibaca);
         Serial.print("Nama tol    = ");Serial.println(tol_dibaca);
         Serial.print("Harga  = ");Serial.println(harga_dibaca);
         Serial.print("Saldo awal  = ");Serial.println(saldoawal_dibaca);
         Serial.print("Saldo akhir  = ");Serial.println(saldoakhir_dibaca);
         Serial.print("Keterangan  = ");Serial.println(keterangan_dibaca);
         Serial.println();
       }else{
        buzzergagal();
        Serial.println("Kartu Tidak terdaftar!");
        }
      } 
    }
    //delay(1000);
}

void buzzeroke(){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void buzzergagal(){
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(10);
}
