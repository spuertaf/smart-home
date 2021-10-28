#include <ESP8266WiFi.h> //libreria para funciones WiFi de ESP8266 para envio de datos
#include <BlynkSimpleEsp8266.h> //libreria para funciones de blynk para el envio de datos a la plataforma 
#define BLYNK_TEMPLATE_ID "TMPLe1W_aHMQ";
#define BLYNK_DEVICE_NAME "Smart room"; //nombre de espacio donde se graficaran los datos
#define BLYNK_AUTH_TOKEN "-PnWppOXrzrRrV_7sL_M-_X4ghUN7uEk"; //token de comunicacion con blynk
#define BLYNK_PRINT Serial //imprimir mensajes Blynk por medio del puerto serial
char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Room01"; //nombre de red
char password[] = "spuertaf"; //contraseña de red


void setup() {
  //definicion de pines y comunicacion serial
  Blynk.begin(auth, ssid, password);
  Serial.begin(9600); //inicio comunicacion a 9600 baudios
  while(!Serial){;} //esperar la comunicacion con el puerto serial
}

void loop() {
  Blynk.run(); 
  String stringArduinoData; //mensaje recibido de Arduino
  if (Serial.available() > 0){ //si el puerto serial esta disponible
    while(Serial.available() > 0){ //mientras que el puerto serial este disponible
      char charArduinoData = (char)Serial.read(); //leer el mensaje recibido
      stringArduinoData += charArduinoData; //guardar en String cada char del mensaje recibido
      delay(30);
    }
    getSensorsDataAndSendBlynk(stringArduinoData); 
  }
}

void getSensorsDataAndSendBlynk(String arduinoMessage){
  /*metodo que procesa el mensaje recibido de Arduino para posteriormente ser enviado a Blynk
  cada mensaje es de la forma tem:8.00*/
  int oneSensorAndValueStart = 0; //incio de un mensaje
  while(arduinoMessage.indexOf(',') > 0){ //mientras que se capten comas en el mensaje
    String oneSensorAndValue = arduinoMessage.substring(oneSensorAndValueStart, arduinoMessage.indexOf(',')); //capturo el mensaje desde el inicio del mensaje hasta donde se capte una coma
    arduinoMessage = arduinoMessage.substring(arduinoMessage.indexOf(',')+1); //actualizo el mensaje para quitar el dato ya capturado
    sendBlynk(oneSensorAndValue); //envio el dato capturado del mensaje de Arduino a Blynk
  }
}

void sendBlynk(String oneSensorAndValue){
  /*metodo para enviar los datos recibidos a Blynk
  cada mensaje es de la forma tem:8.00*/
  int startSensorName = 0;
  int endSensorName = 3;
  int startSensorValue = 4;
  int endSensorValue = 8;
  String sensorName = oneSensorAndValue.substring(startSensorName , endSensorName);
  float sensorValue = (oneSensorAndValue.substring(startSensorValue , endSensorValue)).toFloat();
  Serial.print(sensorName + "   ");
  Serial.println(sensorValue);
  if(sensorName == "hum"){ //caso: humedad DHT11
    Blynk.virtualWrite(V0, sensorValue);
  } else if (sensorName == "tem"){ //caso: temperatura DHT11
    Blynk.virtualWrite(V1, sensorValue);
  } else if (sensorName == "wa1"){ //caso: potenciometro 1
    Blynk.virtualWrite(V2, sensorValue);
  } else if (sensorName == "wa2"){ //caso: potenciometro 2
    Blynk.virtualWrite(V3, sensorValue);
  } else if (sensorName == "gas"){ //caso: gas
    Blynk.virtualWrite(V4, sensorValue);
  } else if (sensorName == "lum"){ //caso: luminocidad captada por la fotoresistencia
    Blynk.virtualWrite(V5, sensorValue);
  } else if (sensorName == "per"){ //caso: personas en la habitacion
    Blynk.virtualWrite(V6, sensorValue);
  }
}
