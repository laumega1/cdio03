
/*-------- PROGRAMA FINAL --------*/

//#include <Adafruit_ADS1015.h>
//#include <SFE_BMP180>
#include <Wire.h>
#include "SensoresPrograma.h"

/*#include "Sensor_Humedad.h"
#include "Sensor_Salinidad.h"
#include "Sensor_Temperatura.h"
#include "Sensor_Iluminacion.h"*/
#include "GPS.h"
#include "acelerometro.h"
#include "presion.h"
#include "HTTP_GET_POST.h"

Adafruit_ADS1115 adc(0x48);                                                                                            //declaramos el adc

Sensor_Humedad S_H (0,&adc,20500,9763);                                                                                //declaramos el constructor de humedad con sus parámetros
Sensor_Salinidad S_S (1,5,&adc,20200,12800);                                                                           //declaramos el constructor de salinidad con sus parámetros
Sensor_Temperatura S_T (2,&adc,0.75,0.036,-25.97);                                                                     //declaramos el constructor de temperatura con sus parámetros
Sensor_Iluminacion S_I (3,&adc,0.40);                                                                                  //declaramos el constructor de iluminación con sus parámetros

const int tiempoSegundos=15;                                                                                          //declaramos una variable para el tiempo de 900segundos (15 min)

void setup(){

  Serial.begin(9600);                                                                                                  //iniciar el programa a 9600ms
  adc.begin();                                                                                                         //inicializamos adc
  adc.setGain(GAIN_ONE);                                                                                               //ajuste de la ganancia

  setup_GPS();                                                                                                         //llamamos a la función set up del GPS
  setup_acelerometro();                                                                                                //llamamos a la función set up del acelerómetro

}

void loop(){

  double _humedad = S_H.get_Humedad();                                                                                 //llamamos a la funcion con el valor de humedad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de humedad es: ");
  Serial.print (_humedad);
  Serial.println (" %");
  Serial.println (" ");
  delay(2000);

  double _salinidad = S_S.get_Salinidad();                                                                             //llamamos a la funcion con el valor de salinidad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de salinidad es: ");
  Serial.print (_salinidad);
  Serial.println (" %");
  Serial.println (" ");
  delay(2000);

  double _temperatura = S_T.get_Temperatura();                                                                         //llamamos a la funcion con el valor de temperatura y la variable donde se almacena sale por pantalla
  Serial.print ("Hay ");
  Serial.print (_temperatura);
  Serial.println (" ºC");
  Serial.println (" ");
  delay(2000);

  double _luminosidad = S_I.get_Luminosidad();                                                                         //llamamos a la funcion con el valor de luminosidad y la variable donde se almacena sale por pantalla
  Serial.print ("El porcentaje de luminosidad es: ");
  Serial.print (_luminosidad);
  Serial.println (" %");
  Serial.println (" ");
  delay(2000);

  loop_GPS();                                                                                                          //llamamos a la funcion loop del GPS
  Serial.println (" ");
  delay(2000);

  loop_acelerometro();                                                                                                 //llamamos a la funcion loop del GPS
  Serial.println (" ");
  delay(2000);                                                                                                        //delay de 2s entre cada tandada de valores

  loop_presion(_temperatura);                                                                                                 //llamamos a la funcion loop del GPS
  Serial.println (" ");
  delay(2000);   

  loop_HTTP(_humedad, _salinidad, _temperatura, _luminosidad);
  
  ESP.deepSleep(tiempoSegundos*1000000);
}
# cdio03
