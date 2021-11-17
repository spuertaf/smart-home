# Smart-Home
---
El siguiente repositorio contiene el proyecto final de Teoría de la Conmutación elaborado por Juan Manuel Muñoz y Santiago Puerta.

## Introducción 
---
El proyecto Smart-Home consiste en la captura de variables tanto análogas como digitales, las cuales son comunes en un hogar. 
En concreto las variables que se medirán serán: temperatura, humedad, iluminación de la sala, porcentaje en la que están abiertas dos canillas y por ultimo la calidad del aire presente.

### Microcontroladores
---
Hay que tener presente que para la elaboración de este proyecto hicimos uso de dos microcontroladores: Arduino Mega o Uno y el Node MCU v2; las razones del porque requerimos de dos microcontroladores se encuentran expuestas en el manual técnico del proyecto, presente en este mismo repositorio o presionando el siguiente [enlace](https://github.com/spuertaf/smart-home/blob/main/Manual%20SmartHome.pdf).

### Código
---
La presente sección dará especificaciones sobre el código usado para el correcto funcionamiento del proyecto; para mayor referencia diríjase al manual técnico de este proyecto o visite el siguiente [enlace](https://github.com/spuertaf/smart-home/blob/main/Manual%20SmartHome.pdf).

- **Arduino** <br/>*Consideraciones previas a la ejecución de los archivos .ino* del proyecto: <br/>La siguiente es una tabla que contiene: nombre de la librería que se uso, una breve descripción, nombre del modulo donde se uso, y finalmente un enlace en donde se podrá encontrar mayor referencia.<br/>

| Librería | Descripción | Modulo en que se uso | Mayor referencia |
|----------| ------------|----------------------|------------------|
|DHT.h     |Liberia para uso de sensor de temperatura y humedad DHT11. |[master.ino](https://github.com/spuertaf/smart-home/blob/main/master.ino) | [programarfacil.com](https://programarfacil.com/blog/arduino-blog/sensor-dht11-temperatura-humedad-arduino/)|
|ESP8266WiFi.h |Rutinas del ESP8266 para conectarse a la red. | [slave.ino](https://github.com/spuertaf/smart-home/blob/main/slave.ino) | [esp8266-arduino](https://github.com/spuertaf/smart-home/blob/main/slave.ino) |
|ArduinoJson.h |Librería para uso de JSON, serialización, deserializacion y más. |[slave.ino](https://github.com/spuertaf/smart-home/blob/main/slave.ino) |[arduinolibraries.info](https://www.arduinolibraries.info/libraries/arduino-json) |  

<br/><br/>

- **Servidor y pagina web** <br/>*Consideraciones previas a la ejecución del servidor y la pagina web* del proyecto: <br/>La siguiente es una tabla que contiene: nombre de la librería que se uso, una breve descripción, nombre del modulo donde se uso, y finalmente un enlace en donde se podrá encontrar mayor referencia.<br/>

| Liberia | Descripción | Modulo en que se uso | Mayor referencia |
|---------|-------------|----------------------|------------------|
|Flask    |Framework para la construcción de aplicaciones web. | [HTTP_connection.py](https://github.com/spuertaf/smart-home/blob/main/python_server/HTTP_connection.py) | [pypi.org](https://pypi.org/project/Flask/) |
|json |Serializado de Json. | [HTTP_connection.py](https://github.com/spuertaf/smart-home/blob/main/python_server/HTTP_connection.py) |[pypi.org](https://pypi.org/project/jsonlib/) |
|time |Acceso a tiempos y conversiones. | [HTTP_connection.py](https://github.com/spuertaf/smart-home/blob/main/python_server/HTTP_connection.py) | [docs.python.org](https://docs.python.org/3/library/time.html)| 
---
La siguiente es una descripción del como implementamos tanto el servidor como la pagina web del proyecto, la cual contendrá el lenguaje de programación del que hicimos uso, y que en particular implementamos en dicho lenguaje.

- *Python:* <br/>En particular, en este lenguaje, elaboramos la implementación del servidor con la ayuda del framework Flask, además de la implementación de comandos y rutinas para el envío de la información capturada por los sensores y la recolección del estado tanto del led como del buzzer de la pagina web, asimismo, el desarrollo de la conexión HTTP con el servidor; véase [HTTP_connection.py](https://github.com/spuertaf/smart-home/blob/main/python_server/HTTP_connection.py). A su vez en este mismo lenguaje se desarrollo un objeto para el manejo de la información captada por los sensores y la obtención y modificación del estado actual del led y del buzzer; véase [DataHandler.py](https://github.com/spuertaf/smart-home/blob/main/python_server/DataHandler.py).<br/>
- *HTML:* <br/>En este lenguaje de etiquetas de hipertexto se dio el desarrollo de las bases de la pagina web; en que lugar iría el encabezado, como se dividiría la pagina web, entre otros aspectos de la pagina se encuentran resueltos en este módulo; véase [index.html](https://github.com/spuertaf/smart-home/blob/main/python_server/templates/index.html).<br/>
- *CSS:* <br/>En este lenguaje de diseño grafico se dan las guías, colores y estilos que usara la pagina web en sus diferentes componentes; véase [styles.css](https://github.com/spuertaf/smart-home/blob/main/python_server/static/css/styles.css).<br/>
- *JavaScript:* <br/>En este lenguaje de programación se encuentran implementadas las funcionalidades para obtener los datos captados por los sensores, redondear, graficar en la pagina web y convertir dichos datos a texto; véase [js](https://github.com/spuertaf/smart-home/tree/main/python_server/static/js).<br/>
<br/><br/>

