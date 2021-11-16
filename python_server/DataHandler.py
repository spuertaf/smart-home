class DataHandler():
    #DataHandler object constructor
    def __init__(self, gas:float, temperature:float, humidity:float, water1:float, water2:float, illumination:float, isBuzzerActive:bool, isLedActive:bool):
        self._gas            = gas
        self._temperature    = temperature
        self._humidity       = humidity
        self._water1         = water1
        self._water2         = water2
        self._illumination   = illumination
        self._isBuzzerActive = isBuzzerActive
        self._isLedActive    = isLedActive
        
    '''atributes setters'''    
    def setIsBuzzerActive(self, isBuzzerActive:bool):
        self._isBuzzerActive = isBuzzerActive
        
        
    def setIsLedActive(self, isLedActive:bool):
        self._isLedActive = isLedActive
        
        
    def setGas(self, gas:float):
        self._gas = gas
        
        
    def setTemperature(self, temperature:float):
        self._temperature = temperature
        
        
    def setHumidity(self, humidity:float):
        self._humidity = humidity
        
        
    def setWater1(self, water1:float):
        self._water1 = water1
        
        
    def setWater2(self, water2:float):
        self._water2 = water2
        
        
    def setIllumination(self, illumination:float):
        self._illumination = illumination
       
    '''atributes getters'''    
    def getHumidity(self) -> float:
        return self._humidity
    
    
    def getGas(self) -> float:
        return self._gas
    
    
    def getTemperature(self) -> float:
        return self._temperature
    
    
    def getWater1(self) -> float:
        return self._water1
    
    
    def getWater2(self) -> float:
        return self._water2
    
    
    def getIllumination(self) -> float:
        return self._illumination
    
    
    def getIsBuzzerActive(self) -> bool:
        return self._isBuzzerActive
    
    
    def getIsLedActive(self) -> bool:
        return self._isLedActive