#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char ssid[]           = "ARRIS-4A9A"; //nombre de red
char password[]       = "ECA9404D4A9A"; //contraseña de red
//direccion para hacer post de los datos
String serverNamePost = "http://192.168.0.6:8080/postData?";
//direccion para obtener los datos
String serverNameGet  = "http://192.168.0.6:8080/getData";
int PIN_LED = 16, PIN_BUZZER = 15;

//definicion de pines e iniciazion de WiFi y puerto serial
void setup() {
    pinMode(PIN_LED,    OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
}

void sendDataHttp(String dataString) {
  //metodo para enviar los datos al servidor que aloja la pagina web
  if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverNamePost + dataString;
      http.begin(client, serverPath);
      int httpResponseCode = http.GET();
    
      if (httpResponseCode>0) {
          String payload = http.getString();
          Serial.println(payload);
      }
    
      http.end();
  } else {
      Serial.println("WiFi Disconnected");
  }
}

String getHttpData() {
  //metodo para obtener el estado del led y del buzzer del servidor que aloja la pagina web
  String dataHttp = "{}";
  if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverNameGet);
      int httpResponseCode = http.GET();
    
      if (httpResponseCode > 0) {
          dataHttp = http.getString();
      }
   
      http.end();
  } else {
      Serial.println("WiFi Disconnected");
  }

  return dataHttp;
}


void loop() {
  String httpInputs = getHttpData(); // se trae el String con la informacion de los switches
  if(!httpInputs.equals("{}")){
      DynamicJsonDocument jsonBuffer(1024); // Se pasa JSON 
      deserializeJson(jsonBuffer, httpInputs);
      boolean isBuzzerActive = jsonBuffer["isBuzzerActive"];
      boolean isLedActive    = jsonBuffer["isLedActive"];

      digitalWrite(PIN_BUZZER, isBuzzerActive);            
      digitalWrite(PIN_LED,    isLedActive);
  }

  String stringArduinoData;
  if (Serial.available() > 0) {                   //si el puerto serial esta disponible
    while (Serial.available() > 0) {              //mientras que el puerto serial este disponible
      char charArduinoData = (char)Serial.read(); //leer el mensaje recibido
      stringArduinoData += charArduinoData;       //guardar en String cada char del mensaje recibido
    }
    sendDataHttp(stringArduinoData); //envia los datos al servidor
  }

  delay(300);
}
