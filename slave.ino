#define BLYNK_TEMPLATE_ID "TMPLUNimmFa_"
#define BLYNK_DEVICE_NAME "Quickstart Device"                  //nombre de espacio donde se graficaran los datos
#define BLYNK_AUTH_TOKEN  "OG8MWfTp35O18eHKFqL2ka2UHUxhxvUa";  //token de comunicacion con blynk
#define BLYNK_PRINT Serial                                     //imprimir mensajes Blynk por medio del puerto serial
#include <ESP8266WiFi.h>                                       //libreria para funciones WiFi de ESP8266 para envio de datos
#include <BlynkSimpleEsp8266.h>                                //libreria para funciones de blynk para el envio de datos a la plataforma 
char auth[]     = BLYNK_AUTH_TOKEN;
char ssid[]     = "IoT-B19";                                //nombre de red
char password[] = "lcontrol2020*";                              //contraseña de red

void setup() {
  // definicion comunicacion serial
  Serial.begin(9600); //inicio comunicacion a 9600 baudios
  Blynk.begin(auth, ssid, password);
  while(!Serial){;}   //esperar la comunicacion con el puerto serial
}

void getSensorsDataAndSendBlynk(String arduinoData){
   /*metodo que procesa el mensaje recibido de Arduino para posteriormente ser enviado a Blynk
  cada mensaje es de la forma tem:8.00*/
  while(arduinoData.indexOf(',') > 0){
    String oneSensorAndValue = arduinoData.substring(0, arduinoData.indexOf(',')); //capturo el mensaje desde el inicio del mensaje hasta donde se capte una coma
    arduinoData = arduinoData.substring(arduinoData.indexOf(',')+1); //actualizo el mensaje para quitar el dato ya capturado
    sendBlynk(oneSensorAndValue); //envio el dato capturado del mensaje de Arduino a Blynk
  }
}

void sendBlynk(String oneSensorAndValue){
  /*metodo para enviar los datos recibidos a Blynk
  cada mensaje es de la forma tem:8.00*/
  
  String sensorName  = oneSensorAndValue.substring(0, oneSensorAndValue.indexOf(':'));
  float  sensorValue = (oneSensorAndValue.substring(oneSensorAndValue.indexOf(':')+1)).toFloat();
  if(sensorName == "gas"){         //gas detectado
    Blynk.virtualWrite(V0, sensorValue);
  } else if (sensorName == "tem"){ //temperatura DHT11
    Blynk.virtualWrite(V1, sensorValue);
  } else if (sensorName == "hum"){ //humedad DHT11
    Blynk.virtualWrite(V2, sensorValue);
  } else if (sensorName == "agu"){ //nivel agua 1
    Blynk.virtualWrite(V3, sensorValue);
  } else if (sensorName == "agu2"){ //nivel agua 2
    Blynk.virtualWrite(V4, sensorValue);
  } else if (sensorName == "lum"){ //luminocidad captada por la fotoresistencia
    Blynk.virtualWrite(V5, sensorValue);
  }
}

void loop() {
  Blynk.run();
  String stringArduinoData;                            //mensaje recibido de Arduino
  if (Serial.available() > 0){                         //si el puerto serial esta disponible
    while(Serial.available() > 0){                     //mientras que el puerto serial este disponible
      char charArduinoData = (char)Serial.read();      //leer el mensaje recibido
      stringArduinoData += charArduinoData;            //guardar en String cada char del mensaje recibido
      delay(2);
    }
    getSensorsDataAndSendBlynk(stringArduinoData);
  }
}
