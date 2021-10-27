#include "DHT.h" //libreria para uso de metodos de sensor temperatura y humedad DHT11
#define DHTPIN A4
#define DHTTYPE DHT11 //tipo de sensor DHT: DHT11

DHT dht(DHTPIN, DHTTYPE); //inicializacion objeto DHT11, sensor temperatura y humedad

int pot1Pin = A0;
int pot2Pin = A1;
int fotoResistorPin = A5;
int entranceSensorEchoPin = 13; 
int entranceSensorTriggerPin = 12;
int exitSensorEchoPin = 10; 
int exitSensorTriggerPin = 11; 
int gasSensorPin = A4;
float dhtHumidity, dhtTemperature; 
String messageToNodeMcu; //mensaje que el Arduino enviara al NodeMCU
int numberOfPeopleInRoom = 0; 

void setup() {
  
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(fotoResistorPin, INPUT);
  pinMode(gasSensorPin, INPUT);
  pinMode(entranceSensorEchoPin, INPUT);
  pinMode(entranceSensorTriggerPin, OUTPUT);
  digitalWrite(entranceSensorTriggerPin, LOW);
  pinMode(exitSensorEchoPin, INPUT);
  pinMode(exitSensorTriggerPin, OUTPUT);
  digitalWrite(exitSensorTriggerPin, LOW);
  dht.begin();
  Serial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  messageToNodeMcu = ""; //mensaje que el Arduino enviara al NodeMCU
  dhtHumidity = getDhtHumidity();
  dhtTemperature = getDhtTemperature();
  //por convencion usamos 3 letras para definir los nombres de los sensores
  messageToNodeMcu = floatToString("hum",dhtHumidity); 
  messageToNodeMcu += floatToString("tem",dhtTemperature);
  messageToNodeMcu += floatToString("wa1",getPotPercentage(pot1Pin));
  messageToNodeMcu += floatToString("wa2",getPotPercentage(pot2Pin));
  messageToNodeMcu += floatToString("gas", analogRead(gasSensorPin));
  messageToNodeMcu += floatToString("lum", analogRead(fotoResistorPin));
  messageToNodeMcu += floatToString ("per", detectPeopleInRoom());
  Serial.println(messageToNodeMcu);
  delay(100);
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
  float exitSensorDistance = getDistanceSensorDistance(exitSensorEchoPin, exitSensorTriggerPin);
  if (entranceSensorDistance < 10.00){ //alguien entro en la estacion ya que la distancia sensada se acorta
    numberOfPeopleInRoom += 1;
  } else if ((exitSensorDistance < 10.00) and (numberOfPeopleInRoom > 0)){ //alguien salio de la habitacion ya que la distancia sensada se acorta
    numberOfPeopleInRoom -= 1;
  }
  return numberOfPeopleInRoom;
}
