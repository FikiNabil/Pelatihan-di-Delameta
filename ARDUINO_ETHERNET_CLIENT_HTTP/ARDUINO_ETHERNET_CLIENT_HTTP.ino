#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h> //6.17.3

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192, 168, 137, 46);

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "192.168.1.23"; // change to your PC's IP address
String PATH_NAME   = "/iot/data-api.php";
String getData;

int flame  = A1;
int ldr    = A0;
int R      = 4; 
int Y      = 5;
int G      = 6;

void setup() {
  Serial.begin(115200);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(flame, INPUT);
  pinMode(ldr, INPUT);

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

  // initialize the Ethernet Setting
  //Ethernet.begin(mac, ip);
  //Serial.println("Menghubungkan...");
  delay(5000);  
  client.connect(HOST_NAME, HTTP_PORT);
}

void loop() {
  //Baca data
  String namadevice="fikinabil";
  float sensor1=analogRead(flame);
  float sensor2=analogRead(ldr);
  float sensor3=random(50,200);
  
// make a HTTP request:
    // send HTTP header
    client.connect(HOST_NAME, HTTP_PORT);
    client.println(HTTP_METHOD + " " + PATH_NAME + 
                   "?namadevice=" + String(namadevice) + 
                   "&sensor1=" + String(sensor1) + 
                   "&sensor2=" + String(sensor2) + 
                   "&sensor3=" + String(sensor3) + 
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
        Serial.println(getData);

        //AMBIL DATA JSON
        const size_t capacity = JSON_OBJECT_SIZE(8) + 130; //cari dulu nilainya pakai Arduino Json 5 Asisten
        DynamicJsonDocument doc(capacity);
        //StaticJsonDocument<192> doc;
        DeserializationError error = deserializeJson(doc, getData);
      
        const char* waktu_dibaca      = doc["waktu"]; // "2021-10-12 09:18:55"
        const char* namadevice_dibaca = doc["namadevice"]; // "iwancilibur"
        const char* sensor1_dibaca    = doc["sensor1"]; // "44"
        const char* sensor2_dibaca    = doc["sensor2"]; // "42"
        const char* sensor3_dibaca    = doc["sensor3"]; // "40"
        const char* control1_dibaca   = doc["control1"]; // "0"
        const char* control2_dibaca   = doc["control2"]; // "0"
        const char* control3_dibaca   = doc["control3"]; // "0"
        
       //POST TO SERIAL
       Serial.print("Waktu      = ");Serial.println(waktu_dibaca);
       Serial.print("Nama Device= ");Serial.println(namadevice_dibaca);
       Serial.print("Sensor 1   = ");Serial.println(sensor1_dibaca);
       Serial.print("Sensor 2   = ");Serial.println(sensor2_dibaca);
       Serial.print("Sensor 3   = ");Serial.println(sensor3_dibaca);
       Serial.print("Control 1  = ");Serial.println(control1_dibaca);
       Serial.print("Control 2  = ");Serial.println(control2_dibaca);
       Serial.print("Control 3  = ");Serial.println(control3_dibaca);
       Serial.println();
      
       //LOGIKA
       if(String(control1_dibaca)=="1"){
        Serial.println("CONTROL 1 ON");
        digitalWrite(R, HIGH);
       }else{
        Serial.println("CONTROL 1 OFF");
        digitalWrite(R,LOW);
       }
       if(String(control2_dibaca)=="1"){
        Serial.println("CONTROL 2 ON");
        digitalWrite(Y, HIGH);
       }else{
        Serial.println("CONTROL 2 OFF");
        digitalWrite(Y,LOW);
       }
       if(String(control3_dibaca)=="1"){
        Serial.println("CONTROL 3 ON");
        digitalWrite(G, HIGH);
       }else{
        Serial.println("CONTROL 3 OFF");
        digitalWrite(G,LOW);
       }
       //if(sensor2 >= 100){
        //digitalWrite(5, LOW);
        //digitalWrite(6, HIGH);
        //digitalWrite(7, LOW);
       //}
       //else if(sensor2 >= 300 and sensor2<=700){
        //digitalWrite(6, LOW);
        //digitalWrite(5, LOW);
        //digitalWrite(7, HIGH);
       //}
       //else{
        //digitalWrite(7, LOW);
        //digitalWrite(6, LOW);
        //digitalWrite(5, HIGH);
       //}
      }
    }
    delay(1000);
}
