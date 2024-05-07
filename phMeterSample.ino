//////////////////////////////////Sensor de Humedad y Temperatura Exterior/////////////////////////////////// 
//#include <DHT.h>

//#include <DHT_U.h>
//int SENSOR = 22; //Señal DHT 22 en el pin digital 3
//int TEMPERATURA;
//int HUMEDAD;
//DHT dht(SENSOR, DHT22);
#define ArrayLenth  40    //times of collection
//int TexArray[ArrayLenth];   //Store the average value of the sensor feedback
//int HArray[ArrayLenth];
int Index;
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); //DIR, E, RW, RS, D4, D5, D6, D7
#include <OneWire.h>
int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
OneWire ds(DS18S20_Pin);  // on digital pin 2

/////////////////////////////////////Temperatura Interior/////////////////////////////////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 2 // Signal pin on digital 21
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
int TinArray[ArrayLenth];

////////////////////////////////////////pH///////////////////////////////////////////////////////////
#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define LED 13
#define samplingInterval 40
#define printInterval 800
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
float b = 1.2422;  //Intercepto u offset
float m = 0.316;   //Pendiente 
float T = 20;   //Temperatura entorno
float Tc = 17;  //Temperatura de calibración
float pHiso = 7; //pH de la isopotencial que se asume 7 

void setup(void)
{
  Serial.begin(9600);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
  lcd.clear();
   
//  dht.begin();
}
void loop(void)

{
//////////////////////////////////// Recolección de Datos/////////////////////////////////////////
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage,aux,pHcorr,Tempex,Humex,temperature;
  
  if(millis()-samplingTime > samplingInterval)
  {   
      DS18B20.requestTemperatures();
      Index = Index + 1; 
      pHArray[Index]= analogRead(SensorPin);
      //TexArray[Index]= dht.readTemperature();
      //HArray[Index]= dht.readHumidity();
      TinArray[Index]= DS18B20.getTempCByIndex(0);
      if(Index >= ArrayLenth)Index= 0;
      voltage = avergearray(pHArray, ArrayLenth)*3.3/1024;
      temperature = avergearray(TinArray, ArrayLenth);
      //Tempex = avergearray(TexArray, ArrayLenth);
      //Humex = avergearray(HArray, ArrayLenth);
      samplingTime= millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical.
  {
///////////////////////////Corrección de Temperatura///////////////////////////////////////////////////////////
  T = temperature;
  aux = 1/(m*((T+273.15)/(Tc+273.15)));
  pHcorr = aux*(voltage-b)+pHiso;

//////////////////////////////////////Envio de Datos//////////////////////////////////////////////////////////
  Serial.print("pH: ");
  Serial.print(pHcorr,2);
  Serial.print(" Temp.Liq.: ");
  Serial.println(temperature);
  lcd.setCursor(0,1);
  lcd.print("PH: ");
  lcd.setCursor(4,1);
  lcd.print(pHcorr);
  lcd.setCursor(0,0);
  lcd.print("Volt:");
  lcd.setCursor(6,0);
  lcd.print(voltage);
  lcd.setCursor(9,1);
  lcd.print("T: ");
  lcd.setCursor(12,1);
  lcd.print(temperature);
  
  //Serial.print("°C Temp.Ext.: ");
  //Serial.print(Tempex);
  //Serial.print("°C Hum.Ext.: ");
  //Serial.print(Humex);
  //Serial.println("%");
  printTime=millis();
  }
}

////////////////////////////Función para suavizar datos recolectados///////////////////////////
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
