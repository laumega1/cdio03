/*-------- SENSOR DE ILUMINACION --------*/
#include "SensoresPrograma.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- CONSTRUCTOR --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
Sensor_Iluminacion::Sensor_Iluminacion (int _pin, Adafruit_ADS1115 * _adc, double _a, double _b) //declaramos el constructor y sus parámetros
{                     
  pin = _pin; //objeto pin
  adc = _adc; //objeto adc
  (*this).a = _a; //obejto variable valor mínimo de voltage
  (*this).b = _b; //objeto variable valor máximo de voltage
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN LECTURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Sensor_Iluminacion::leer_canal () //funcion para leer el canal
{                                                                     
  int lectura_digital = (*adc).readADC_SingleEnded(pin); //lectura del adc del pin analogico se mete en una variable
  return lectura_digital; //devolvemos esa variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIONES CALCULOS --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Iluminacion::calcular_Voltaje (int lectura_digital) //funcion para calcular el voltaje pasandole la lectura del adc
{                                        
 double valor_voltaje = (lectura_digital/((32768-1)/4.096));
 return valor_voltaje; //devuelve el valor calculado almacenado en la variable humedad
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Iluminacion::calcular_Luminosidad (double valor_voltaje) //funcion para calcular el porcentaje de luminosidad pasandole el voltaje
{                                     
 double valor_luminosidad = (valor_voltaje-(*this).a)*(100-0)/((*this).b-(*this).a);
  
  if(valor_luminosidad >100)
  {
    valor_luminosidad=100;
  }
  
  if (valor_luminosidad <0){
    valor_luminosidad=0;
  }
 
  return valor_luminosidad;//devuelve el valor calculado almacenado en la variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN PANTALLA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Iluminacion::get_Luminosidad () // funcion para sacar el valor calculado previamente por pantalla
{                                                               
  int valor = leer_canal(); //llamamos a la funcion leer para alamcenar el valor que retornaba en la variable valor
  double voltaje = calcular_Voltaje (valor); //calculamos el valor del voltaje con la variable que guardaba la lectura del adc
  double luminosidad = calcular_Luminosidad (voltaje); //calculamos el valor de luminosidad con la variable que guardaba el voltaje
  return luminosidad; //ese calculo se mmete en una variable llamada luminosidad que luego devolvemos
}
