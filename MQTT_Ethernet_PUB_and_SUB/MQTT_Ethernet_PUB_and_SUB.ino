#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

void subscribeReceive(char* topic, byte* payload, unsigned int length); //Untuk Subscribe Topic
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192, 168, 137, 111); //IP Address Static (Aktifkan jika ingin menggunakan ip static)

const char* server = "192.168.1.23"; //IP Address / Domain MQTT Broker
 
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void setup()
{
  Serial.begin(115200);
  //IP Static
  //Ethernet.begin(mac, ip);   //Aktifkan jika ingin digunakan
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
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
  delay(3000);  
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());                        
  mqttClient.setServer(server, 1883);   
 
  if (mqttClient.connect("fikinabil_client1"))  //Unix Cient ID
  {
    Serial.println("Koneksi berhasil!");
    mqttClient.setCallback(subscribeReceive);
  }else {
    Serial.println("Gagal Koneksi ke server!");
  }
}

void loop()
{
  //Ambil Data / Baca Sensor
  char msgBuffer[20];
  int datax=random(10,100);

  //MQTT LOOP
  mqttClient.loop(); //Looping MQTT
  mqttClient.subscribe("lampu1");

  //POST TO SERIAL
  Serial.print("Sensor 1 :");Serial.print(datax);
  Serial.println();
  
  //POST TO MQTT
  mqttClient.publish("datax", dtostrf(datax, 6, 2, msgBuffer)); //Convert to String 
  delay(1000);
}

void subscribeReceive(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Pesan diterima [");
  Serial.print(topic);
  Serial.println("] ");
  //==============================================================
  if (strcmp(topic, "lampumerah19") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == '1')
       //Jalankan Perintah1
       Serial.println("JALANKAN PERINTAH 1");
       digitalWrite(13, HIGH);
    if (receivedChar == '0')
       //Jalankan Perintah0
       Serial.println("JALANKAN PERINTAH 0");
       digitalWrite(13, LOW);
    }
  }
  //==============================================================
  
}
