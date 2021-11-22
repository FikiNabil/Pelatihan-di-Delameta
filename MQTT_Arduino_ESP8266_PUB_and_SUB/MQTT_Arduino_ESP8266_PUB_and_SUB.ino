#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"
#include <PubSubClient.h>

//Initialize PIN
int Relay = 2;
int LDR   = A0;
int Flame = A1;

char ssid[]        = "delameta";            // your network SSID (name)
char pass[]        = "bilano1407";        // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status
unsigned long lastSend;

// Initialize the Ethernet client object
WiFiEspClient espClient;
PubSubClient client(espClient);

SoftwareSerial Serialx(2,3); // RX, TX   //ESP8266 RX,TX connected to these pins

void setup() {
// initialize serial for debugging
Serial.begin(115200);
// initialize serial for ESP module
Serialx.begin(9600);
// initialize ESP module
WiFi.init(&Serialx);

//initialize Relay
pinMode(Relay, OUTPUT);

// check for the presence of the shield
if (WiFi.status() == WL_NO_SHIELD) {
Serial.println("WiFi shield not present");
// don't continue
while (true);
}

// attempt to connect to WiFi network
while ( status != WL_CONNECTED) {
Serial.print("Attempting to connect to WPA SSID: ");
Serial.println(ssid);
// Connect to WPA/WPA2 network
status = WiFi.begin(ssid, pass);
lastSend = 0;
}

// you're connected now, so print out the data
Serial.println("You're connected to the network");

//connect to MQTT server
client.setServer("broker.hivemq.com", 1883);
client.setCallback(callback);
}

//print any message received for subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Pesan diterima [");
  Serial.print(topic);
  Serial.println("] ");
  //==============================================================
  if (strcmp(topic, "fikinabil14/lampu1") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == '1'){
       //Jalankan Perintah1
       Serial.println("JALANKAN PERINTAH 1");
       digitalWrite(Relay, HIGH);
       delay(1000);
    }
    if (receivedChar == '0'){
       //Jalankan Perintah0
       Serial.println("JALANKAN PERINTAH 2");
       digitalWrite(Relay, LOW);
       delay(1000);
    }
  }
  }
  //==============================================================
    //==============================================================
  if (strcmp(topic, "fikinabil14/LDR") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == '1'){
       //Jalankan Perintah1
       Serial.println("JALANKAN PERINTAH 3");
    }
    if (receivedChar == '0'){
       //Jalankan Perintah0
       Serial.println("JALANKAN PERINTAH 4");
    }
  }
  }
  //==============================================================
    //==============================================================
  if (strcmp(topic, "fikinabil14/Flame") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == '1'){
       //Jalankan Perintah1
       Serial.println("JALANKAN PERINTAH 5");
    }
    if (receivedChar == '0'){
       //Jalankan Perintah0
       Serial.println("JALANKAN PERINTAH 6");
    }
  }
  }
  //==============================================================
  
}

void pushdata(){
  //Ambil Data / Baca Sensor
  //char msgBuffer[20];
  int datax=random(10,100);
  int bacaLDR=analogRead(LDR);
      bacaLDR=map(bacaLDR,3,973,0,100);
  int bacaFlame=analogRead(Flame);
      bacaFlame=map(bacaFlame,5,1015,100,0);
  
  //POST TO SERIAL
  Serial.print("Sensor 1 :");Serial.print(datax);
  Serial.print("| Sensor LDR :");Serial.print(bacaLDR);
  Serial.print("| Sensor Flame :");Serial.print(bacaFlame);
  Serial.println();
  
  //POST TO MQTT
  //client.publish("fikinabil14/datax", dtostrf(datax, 6, 2, msgBuffer)); //Convert to String 
  client.publish("fikinabil14/datax", String(datax).c_str());
  client.subscribe("fikinabil14/bacaLDR", String(bacaLDR).c_str());
  client.subscribe("fikinabil14/bacaFlame", String(bacaFlame).c_str());
}

void loop() {
// put your main code here, to run repeatedly:
if (!client.connected()) {
reconnect();
}
if ( millis() - lastSend > 3000 ) { // Update and send only after 1 seconds
    pushdata();
    lastSend = millis();
 }
client.loop();
}

void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
// Attempt to connect, just a name to identify the client
if (client.connect("fikinabil")) {
Serial.println("connected");

//client.publish("outpic","Hello World");
client.subscribe("fikinabil14/lampu1",0);
client.publish("fikinabil14/LDR",0);
client.publish("fikinabil14/Flame",0);

} else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
}
}
}
