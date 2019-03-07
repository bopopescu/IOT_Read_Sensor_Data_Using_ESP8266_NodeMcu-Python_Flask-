#include <ESP8266WiFi.h>

const char* ssid = "infocus"; 
const char* password = "hariharan";
const char* host = "192.168.43.183";


void setup() {
// you can feed the sensor data to esp8266NodeMCU 

 pinMode(D0, INPUT);
 pinMode(A0, INPUT);
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

 int distance=digitalRead(D0);
 int weight=analogRead(A0);
 
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
     
     url +="?distance=";
     url +=distance;
     url +="&weight=";
     url +=weight;
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


 
  
 
