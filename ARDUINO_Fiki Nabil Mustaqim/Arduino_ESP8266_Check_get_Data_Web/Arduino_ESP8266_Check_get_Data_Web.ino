#include <WiFiEsp.h>
#include <SoftwareSerial.h>

char ssid[]        = "delameta";            // your network SSID (name)
char pass[]        = "bilano1407";        // your network password
int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "test.iot-go.click"; // change to your PC's IP address
String PATH_NAME   = "/index.php";
String getData;
int status = WL_IDLE_STATUS;     // the Wifi radio's status

SoftwareSerial Serialesp(2,3);

WiFiEspClient client;

void setup() {
  Serial.begin(115200);
  Serialesp.begin(9600);
  WiFi.init(&Serialesp);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield Tidak terdeteksi");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Menghubungkan ke SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("Terhubung ke jaringan!");
  printWifiStatus();
  Serial.println();
  Serial.println("Mengubungkan ke Server...");
  // if you get a connection, report back via serial
  if (client.connect(HOST_NAME, HTTP_PORT)) {
    Serial.println("Berhasil terhubung ke Server!");
  }
}

void loop() {
    client.connect(HOST_NAME, HTTP_PORT);
    client.println(HTTP_METHOD + " " + PATH_NAME +  
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
      }      
    }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
