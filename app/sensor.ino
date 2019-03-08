#include <ESP8266WiFi.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 0 //D3
DHT dht(dht_dpin, DHTTYPE); 

const char* ssid = "infocus"; 
const char* password = "hariharan";
const char* host = "192.168.43.183";


void setup() {
 dht.begin();
 Serial.begin(115200);
 delay(100);
 
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);

           while (WiFi.status() != WL_CONNECTED) {
                                                   delay(500);
                                                   Serial.print(".");
                                                   }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());

}

void loop() {

 float h = dht.readHumidity();
 float t = dht.readTemperature();      
 
 Serial.print("connecting to ");
 Serial.println(host);
 WiFiClient client;
 const int httpPort = 5000;
 if (!client.connect(host, httpPort)) {
                                       Serial.println("connection failed");
                                       return;
                                       }

     // We now create a URI for the request
     //String url = "/projects/index.html";
     String url = "/";
     
     url +="?hum=";
     url +=h;
     url +="&temp=";
     url +=t;
     url +="&device=";
     url +="esp";
     
     Serial.print("Requesting URL: ");
     Serial.println(url);

     // This will send the request to the server
     client.print(String("GET ") + url + " HTTP/1.1\r\n" +
     "Host: " + host + "\r\n" +
     "Connection: close\r\n\r\n");
     delay(500);

     // Read all the lines of the reply from server and print them to Serial
     while(client.available()){
                                String line = client.readStringUntil('\r');
                                Serial.print(line);
                             }

 Serial.println();
 Serial.println("closing connection");

}
