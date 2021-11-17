from flask import Flask,render_template,request, make_response
import json
from time import time
from DataHandler import DataHandler

dataHandler = DataHandler(0,0,0,0,0,0, False, False)
app = Flask(__name__) #servidor donde estara alojada la pagina web


@app.route('/', methods=["GET", "POST"]) #comando, cada vez que lo ejecuto se ejecutan las fuciones que el comando posee
def main():
    return render_template('index.html') #retorna plantilla html de la pagina web


@app.route('/data', methods=["GET", "POST"])
def data():
    '''metodo para hacer una peticion (get o post) al servidor de la pagina web, que retorna el contenido de la respuesta'''
    #diccionario de datos que seran graficados en la pagina web
    dataJson =  {
        'time':         time()*1000,
        'temperature':  dataHandler.getTemperature(),
        'humidity':     dataHandler.getHumidity(),
        'illumination': dataHandler.getIllumination(),
        'water1':       dataHandler.getWater1(),
        'water2':       dataHandler.getWater2(),
        'gas':          dataHandler.getGas()
    }
    
    response = make_response(json.dumps(dataJson)) 
    response.content_type = 'application/json' #contenido de la respuesta del servidor
    return response 


@app.route('/postData')
def readData() -> str:
    '''metodo para mandar los datos captados por los sensores a la pagina web'''
    dataHandler.setIllumination(request.args.get('ill'))
    dataHandler.setTemperature(request.args.get('tem'))
    dataHandler.setHumidity(request.args.get('hum'))
    dataHandler.setWater2(request.args.get('wa2'))
    dataHandler.setGas(request.args.get('gas'))
    dataHandler.setWater1(request.args.get('wa1'))
    return str(dataHandler)


@app.route('/getData')
def getData() -> dict:
    '''metodo para obtener el estado del led y del buzzer'''
    return {
        'isBuzzerActive':  dataHandler.getIsBuzzerActive(),
        'isLedActive'   :  dataHandler.getIsLedActive()
    }


@app.route('/sendSwitchsData', methods=['POST'])
def sendSwitchsData() -> str:
    '''metodo para enviar a la pagina web el estado del led y del buzzer'''
    dataHandler.setIsBuzzerActive(request.form['buzzer'] == 'true')
    dataHandler.setIsLedActive(request.form['led'] == 'true')
    return ""

if __name__ == '__main__':
   app.run(host='0.0.0.0', port=8080, debug=True)
