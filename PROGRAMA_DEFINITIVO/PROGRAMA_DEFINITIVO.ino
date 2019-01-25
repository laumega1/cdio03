
/*-------- PROGRAMA FINAL --------*/
/*-------- Por Fabio Hernandez, Laura Melero, Laura Pons, David Jiménez y Pablo Lampentzam --------*/

#include <SFE_BMP180.h>
#include <Wire.h>

#include "SensoresPrograma.h"
#include "GPS_A2235.h"
#include "acelerometro.h"
#include "presion.h"
#include "HTTP_GET_POST.h"

Adafruit_ADS1115 adc(0x48); //declaramos el adc

Sensor_Humedad S_H (0,&adc,30034.14,15864.86); //declaramos el constructor de humedad con sus parámetros
Sensor_Salinidad S_S (1,5,&adc,17093.90,11891); //declaramos el constructor de salinidad con sus parámetros       
Sensor_Temperatura S_T (2,&adc,0.75,0.036,-221.6); //declaramos el constructor de temperatura con sus parámetros
Sensor_Iluminacion S_I (3,&adc,0.01,0.13); //declaramos el constructor de iluminación con sus parámetros

const int tiempoSegundos=10; //declaramos una variable para el tiempo que dormirá nuestro nuestros sensores de 900segundos (15 min)

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- SETUP --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void setup() 
{                                                                       
  adc.setGain(GAIN_ONE); //ajuste de la ganancia                                                                                                

  setup_HTPP(); //llamamos a la función set up del WIFI
  setup_GPS(); //llamamos a la función set up del GPS                                                                                                       
  setup_acelerometro(); //llamamos a la función set up del acelerómetro
  setup_presion(); //llamamos a la función set up del sensor de presión
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- BUCLE --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void loop()
{
 double _humedad = S_H.get_Humedad(); //llamamos a la funcion con el valor de humedad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de humedad es: ");
  Serial.print (_humedad);
  Serial.println (" %");
  Serial.println (" ");

  double _salinidad = S_S.get_Salinidad(); //llamamos a la funcion con el valor de salinidad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de salinidad es: ");
  Serial.print (_salinidad);
  Serial.println (" %");
  Serial.println (" ");

  double _temperatura = S_T.get_Temperatura(); //llamamos a la funcion con el valor de temperatura y la variable donde se almacena sale por pantalla
  Serial.print ("Hay ");
  Serial.print (_temperatura);
  Serial.println (" ºC");
  Serial.println (" ");

  double _luminosidad = S_I.get_Luminosidad(); //llamamos a la funcion con el valor de luminosidad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de luminosidad es: ");
  Serial.print (_luminosidad);
  Serial.println (" %");
  Serial.println (" ");
  
  loop_GPS(); //llamamos a la funcion loop del 
  Serial.begin(9600); //iniciar el programa a 9600ms
  adc.begin(); //inicializamos adc                  GPS
  Serial.println (" ");

  loop_acelerometro(); //llamamos a la funcion loop del acelerómetro
  Serial.println (" ");

  loop_presion(_temperatura); //llamamos a la funcion loop del sensor de presión dandole el valor de la temperatura
  Serial.println (" ");

  loop_HTTP(_humedad, _salinidad, _temperatura, _luminosidad); //llamamos a la funcion loop del WIFI, dandole la humedad, la salinidad, la temperatura y la luminosidad

  ESP.deepSleep(tiempoSegundos*10000); //dormimos a nuestro dispositivo para evitar que consuma energia
}
