#include "DHT.h" //libreria para uso de metodos de sensor temperatura y humedad DHT11
#define DHTPIN A4
#define DHTTYPE DHT11 //tipo de sensor DHT: DHT11

DHT dht(DHTPIN, DHTTYPE);

int gasSensorPin             = A0;
int pot1Pin                  = A1;
int pot2Pin                  = A2;
int fotoResistorPin          = A3;
int entranceSensorEchoPin    = 13; //Digital
int entranceSensorTriggerPin = 12; //Digital
int exitSensorEchoPin        = 10; //Digital
int exitSensorTriggerPin     = 11; //Digital
int numberOfPeopleInRoom     = 0;

void setup() {
  //definicion de pines como input o output
  pinMode(pot1Pin,                  INPUT);
  pinMode(pot2Pin,                  INPUT);
  pinMode(fotoResistorPin,          INPUT);
  pinMode(gasSensorPin,             INPUT);
  pinMode(entranceSensorEchoPin,    INPUT);
  pinMode(entranceSensorTriggerPin, OUTPUT);
  pinMode(exitSensorEchoPin,        INPUT);
  pinMode(exitSensorTriggerPin,     OUTPUT);
  
  digitalWrite(entranceSensorTriggerPin, LOW);
  digitalWrite(exitSensorTriggerPin,     LOW);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  String messageToNodeMcu = ""; //mensaje que el Arduino enviara al NodeMCU
  
  //para convencion usar 3 letras para definir los nombres de los sensores
  messageToNodeMcu =  floatToString("hum",  getDhtHumidity()); 
  messageToNodeMcu += floatToString("tem",  getDhtTemperature());
  messageToNodeMcu += floatToString("agu",  getPotPercentage(pot1Pin));
  messageToNodeMcu += floatToString("agu2", getPotPercentage(pot2Pin));
  messageToNodeMcu += floatToString("per",  detectPeopleInRoom());
  messageToNodeMcu += floatToString("gas",  getGas());
  messageToNodeMcu += floatToString("lum",  getIllumination());
  Serial.println(messageToNodeMcu);
  delay(1000);
}

float getIllumination(){
  return analogRead(fotoResistorPin);
}

float getGas(){
  return analogRead(gasSensorPin);
}

float getDhtHumidity(){
  //este metodo retorna en flotante el valor de la humedad captado por el sensor DHT11
  return dht.readHumidity(); 
}

float getDhtTemperature(){
  //este metodo retorna en flotante el valor de la temperatura cpatado por el sensor DHT11
  return dht.readTemperature();
}

String floatToString(String sensorName, float value){
  /*este metodo recibe el nombre del sensor y el valor que capta dicho sensor y 
  retorna un string en forma de llave:valor para ser enviado al NodeMCU*/
  return sensorName + ":" + value + ",";
}

int getPotPercentage(int potPin){
  //este metodo calcula y retorna el porcentaje de 0 a 100 que emite el potenciometro
  int potValue = analogRead(potPin);
  int potPercentage = map(potValue, 0, 1023, 0, 100);
  return potPercentage;
}

float getDistanceSensorDistance(int sensorEchoPin, int sensorTriggerPin){
  //metodo para obtener la distancia captada por un sensor ultrasonido
  float timeToGetEcho;
  float cmDistance;
  digitalWrite(sensorTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTriggerPin, LOW);
  timeToGetEcho = pulseIn(sensorEchoPin, HIGH); //obtener el ancho del pulso
  cmDistance = timeToGetEcho/59;
  return cmDistance; 
}

int detectPeopleInRoom(){
  //metodo para poder detectar cuantas personas se encuentran en la estancia en el momento
  float entranceSensorDistance = getDistanceSensorDistance(entranceSensorEchoPin, entranceSensorTriggerPin);
  float exitSensorDistance     = getDistanceSensorDistance(exitSensorEchoPin, exitSensorTriggerPin);
  if (entranceSensorDistance < 10.00){ //alguien entro en la habitacion
    numberOfPeopleInRoom += 1;
  } else if ((exitSensorDistance < 10.00) and (numberOfPeopleInRoom > 0)){ //alguien salio de la habitacion
    numberOfPeopleInRoom -= 1;
  }
  return numberOfPeopleInRoom;
}
