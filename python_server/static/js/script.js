var chartTemperature, chartHumidity, chartGas, chartIllumination, chartWater1, chartWater2;
requestData();

$(document).ready(function(){
    //plantilla de las diferentes graficas a usar para representar las variables captadas por los sensores

    chartTemperature = new Highcharts.Chart({
        chart: { renderTo: 'temperatureTable', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Temperatura'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Temperature', data: []}]
    });

    chartHumidity = new Highcharts.Chart({
        chart: { renderTo: 'humidityTable', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Humedad'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Humidity', data: []}]
    });

    chartGas = new Highcharts.Chart({
        chart: { renderTo: 'gasTable', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Gas'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Gas', data: []}]
    });

    chartIllumination = new Highcharts.Chart({
        chart: { renderTo: 'illuminationTable', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Iluminacion'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Iluminacion', data: []}]
    });

    chartWater1 = new Highcharts.Chart({
        chart: { renderTo: 'water1Table', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Llave de agua 1'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Llave de agua 1', data: []}]
    });

    chartWater2 = new Highcharts.Chart({
        chart: { renderTo: 'water2Table', defaultSeriesType: 'area', events: { load: requestData }},
        title: { text: 'Llave de agua 2'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Llave de agua 2', data: []}]
    });
});

function requestData() {
    var requests = $.get('/data'); //obtiene el diccionario con los datos captados por los sensores
    var tm = requests.done(function (result){
        var buzzerValue = $(".switchBuzzer").is(":checked"); //obtiene el estado del buzzer (prendido - apagado)
        var ledValue    = $(".switchLed").is(":checked"); //obtiene el estado del led (prendido - apagado)

        $.post(
            "/sendSwitchsData", {
                "buzzer": buzzerValue,
                "led":    ledValue
            })
       
        //graficar los datos añadiendo una referencia temporal a la grafica
        chartHumidity.series[0].addPoint([result.time, result.humidity], true, false);    
        chartTemperature.series[0].addPoint([result.time, result.temperature], true, false);
        chartGas.series[0].addPoint([result.time, result.gas], true, false);   
        chartIllumination.series[0].addPoint([result.time, result.illumination], true, false);
        chartWater1.series[0].addPoint([result.time, result.water1], true, false);   
        chartWater2.series[0].addPoint([result.time, result.water2], true, false);
        
        //obtener y quitar cifras decimales a las variables obtenidas por los sensores
        $(".sensorTemperature").text(Math.round(result.temperature));
        $(".sensorHumidity").text(Math.round(result.humidity));
        $(".sensorGas").text(Math.round(result.gas));
        $(".sensorIllumination").text(Math.round(result.illumination));
        $(".sensorWater2").text(Math.round(result.water2));
        $(".sensorWater1").text(Math.round(result.water1));

        setTimeout(requestData, 2000);
    });
}