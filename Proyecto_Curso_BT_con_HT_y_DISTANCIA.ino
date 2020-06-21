#include <LiquidCrystal.h>//Librería pantalla
#include <SimpleDHT.h> // librería que tenemos que incluir
#include <SoftwareSerial.h>
#include <hcsr04.h> //Librería del sensor de distancia

#define TRIG_PIN A0 //Pines del sensor de distancia
#define ECHO_PIN A1

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);//Valores del sensor

SoftwareSerial BT1(3,4); // Sensor BT. Pines 3 y 4 OJO: RX, TX recordar que se cruzan

SimpleDHT11 sensor;     // Se usa para decir el tipo de sensor, dht11 <-- ÉSTE. o dht22
                        // Constante del sensor y su pin
int SensorHT=2;         // Sensor Humedad y Temperatura "HT" en Pin2

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12); //Pantalla y pines. 

int BluetoothData; //Variable para el BT

void setup() 
{
pinMode (SensorHT,INPUT); //pin2 y de enrtada.
  Serial.begin(9600); //Iniciamos monitor serie
  lcd.begin(16, 2); //Iniciamos la pantalla
lcd.print("X Distancia");// Escribe en la primera línea y columna

lcd.setCursor(0,1);//Segunda linea y primera columna
  
  lcd.print("O Humed.Temp. ");//Escribe Humedad(%): Segunda linea primera columna  
  
  BT1.begin(9600);

}

void loop()
{
  
  //Aquí definimos las variables
 
  byte temperature = 0; 
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  byte data[40] = {0};
  
  //Que hace Arduino si encuentra algún tipo de error
  
  if(sensor.read(SensorHT,&temperature,&humidity, data)) 
  
  {
    Serial.print("No reading , err="); Serial.println(err);delay(1000);
    return;
  }
   if (BT1.available()) //Para emparejar los dispositivos BT
   {
     BluetoothData=BT1.read();//Leemos valores del BT
     
     if(BluetoothData=='O') //Al presionar "O"
      {
  lcd.clear();

  
  lcd.setCursor(0,0);//Primera linea y columna
  
  lcd.print("Temperatura:");//Escribe Temp:º En la primera linea
  
  lcd.print((int)temperature);//Escribe el valor de  "Temp: " 
  
  lcd.setCursor(0,1);//Segunda linea y primera columna
  
  lcd.print("Humedad(%): ");//Escribe Humedad(%): Segunda linea primera columna
  
  lcd.print((int)humidity);//TEscribe el valor después de Humedad(%): "
 delay(750);


      }
   if(BluetoothData=='X')
{
 lcd.clear();


  Serial.println(hcsr04.distanceInMillimeters());// Configura distancia en mm

     
    Serial.println(hcsr04.ToString());// Información del dispositivo, driver, y distancia en formato JSON
    
    
  lcd.setCursor(0,0);//Primera linea y columna
  
  lcd.print("Distancia en mm ");//Escribe en primera linea.
  
 lcd.setCursor(0,1); //Cambia de línea.
  lcd.print(hcsr04.distanceInMillimeters()); //Escribe la distancia en mm
  
   delay(750);
}
}

   }
