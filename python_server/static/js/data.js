var chartTemperature, chartHumidity, chartGas, chartIllumination, chartWater1, chartWater2;

$(document).ready(function(){
     //plantilla de las diferentes graficas a usar para representar las variables captadas por los sensores

    chartTemperature = new Highcharts.Chart({
        chart: { renderTo: 'temperatureTable', defaultSeriesType: 'area', events: {  }},
        title: { text: 'Temperatura'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Temperature', data: []}]
    });

    chartHumidity = new Highcharts.Chart({
        chart: { renderTo: 'humidityTable', defaultSeriesType: 'area', events: {  }},
        title: { text: 'Humedad'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Humidity', data: []}]
    });

    chartGas = new Highcharts.Chart({
        chart: { renderTo: 'gasTable', defaultSeriesType: 'area', events: {  }},
        title: { text: 'Gas'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Gas', data: []}]
    });

    chartIllumination = new Highcharts.Chart({
        chart: { renderTo: 'illuminationTable', defaultSeriesType: 'area', events: {  }},
        title: { text: 'Iluminacion'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Iluminacion', data: []}]
    });

    chartWater1 = new Highcharts.Chart({
        chart: { renderTo: 'water1Table', defaultSeriesType: 'area', events: {  }},
        title: { text: 'Llave de agua 1'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Llave de agua 1', data: []}]
    });

    chartWater2 = new Highcharts.Chart({
        chart: { renderTo: 'water2Table', defaultSeriesType: 'area', events: { }},
        title: { text: 'Llave de agua 2'}, xAxis: {type: 'datetime', tickPixelInterval: 150, maxZoom: 20 * 1000 },
        yAxis: { minPadding: 0.2, maxPadding: 0.2, title: { text: 'Value',margin: 80 }},
        series: [{color : '#c23d23',lineColor: '#303030',  name: 'Llave de agua 2', data: []}]
    });

    requestData();
});

function requestData() {
    var requests = $.get('/data'); //obtiene el diccionario con los datos captados por los sensores
    var tm = requests.done(function (result){
        //obtener y quitar cifras decimales a las variables obtenidas por los sensores
        var time         = Math.round(result.time);
        var temperature  = Math.round(result.temperature);
        var humidity     = Math.round(result.humidity);
        var water1       = Math.round(result.water1);
        var water2       = Math.round(result.water2);
        var gas          = Math.round(result.gas);
        var illumination = Math.round(result.illumination);
       
        //graficar los datos añadiendo una referencia temporal a la grafica
        chartHumidity.series[0].addPoint(    [time, humidity],     true, false);   
        chartTemperature.series[0].addPoint( [time, temperature],  true, false);
        chartGas.series[0].addPoint(         [time, gas],          true, false);   
        chartIllumination.series[0].addPoint([time, illumination], true, false);
        chartWater1.series[0].addPoint(      [time, water1],       true, false);   
        chartWater2.series[0].addPoint(      [time, water2],       true, false);

        //convertir a String las variables obtenidas para enviarlas al servidor 
        $(".sensorTemperature").text(temperature);
        $(".sensorHumidity").text(humidity);
        $(".sensorGas").text(result.gas);
        $(".sensorIllumination").text(illumination);
        $(".sensorWater2").text(result.water2);
        $(".sensorWater1").text(result.water1);

        setTimeout(requestData, 2000);
    });
}