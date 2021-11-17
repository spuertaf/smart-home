$(document).ready(function() {
    //listeners de la pagina web para poder saber es el estado del switchs que representan el led y el buzzer de la pagina web (prendido - apagado)
    $('input[name=switchBuzzer]').change(function() {
        sendSwitchsData();
    });

    $('input[name=switchLed]').change(function() {
        sendSwitchsData();
    });

    
});

function sendSwitchsData () {
    var buzzerValue = $(".switchBuzzer").is(":checked"); //obtiene el estado del buzzer (prendido - apagado)
    var ledValue    = $(".switchLed").is(":checked"); //obtiene el estado del led (prendido - apagado)
    
    $.post(
        "/sendSwitchsData", { //envia el estado del buzzer y del led al servidor
            "buzzer": buzzerValue,
            "led":    ledValue
    });
}