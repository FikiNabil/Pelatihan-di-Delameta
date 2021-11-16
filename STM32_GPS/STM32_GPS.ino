/*/
 * A9  to RX USBTTL (Serial TX)
 * A10 to TX USBTTL (Serial1 RX)
 * A2  to RX GPS  (Serial2 TX)
 * A3  to TX GPS  (Serial2 RX)
 * Tekan Reset sebelum Upload
 * Pilih Board    :fake STM32;[pF10 
 * Upload methode :Serial
 */
 
#include <TinyGPS++.h>

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;
String latitude, longitude,km_ph;

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  Serial2.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    km_ph = String(gps.speed.kmph());
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) + " | " + String(km_ph) ;
    Serial.println(link);
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}
