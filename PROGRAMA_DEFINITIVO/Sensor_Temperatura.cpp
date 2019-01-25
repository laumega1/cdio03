/*-------- SENSOR DE TEMPERATURA --------*/
#include "SensoresPrograma.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- CONSTRUCTOR --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
Sensor_Temperatura::Sensor_Temperatura (int _pin, Adafruit_ADS1115 * _adc, double _a, double _b, double _cal) //declaramos el constructor y sus parámetros
{                              
  pin = _pin; //objeto pin
  adc = _adc; //objeto adc
  (*this).a = _a; //obejto ecuacion
  (*this).b = _b; //objeto ecuacion
  (*this).cal = _cal; //objeto calibrado
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN LECTURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Sensor_Temperatura::leer_canal () //funcion para leer el canal
{                                                                                                       
  int lectura_digital = (*adc).readADC_SingleEnded(pin); //lectura del adc del pin analogico se mete en una variable
  return lectura_digital; //devolvemos esa variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN CÁLCULO --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Temperatura::calcular_Voltaje (int lectura_digital) //funcion para calcular wl voltaje pasandole la lectura del adc
{                                                                           
  double valor_voltaje = (lectura_digital * 0.1875)/1000;
  return valor_voltaje; //devuelve el valor calculado almacenado en la variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Temperatura::calcular_Temperatura (double valor_voltaje) //funcion para calcular la humedad pasandole la lectura del adc 
{                                                                      
 double valor_temperatura = ((*this).cal)+((valor_voltaje-(*this).a)/(*this).b); //ecuacion para la temperatura

   if (valor_temperatura>40)
   {
    valor_temperatura=40;
   }

 return valor_temperatura; //devuelve el valor calculado almacenado en la variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN PANTALLA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Temperatura::get_Temperatura () // funcion para sacar el valor calculado preiamente por pantalla
{                                                                                               
  int valor = leer_canal(); //llamamos a la funcion leer para alamcenar el valor que retornaba en la variable valor
  double voltaje = calcular_Voltaje (valor); //calculamos el valor del voltaje con la variable que guardaba la lectura del adc
  double temperatura = calcular_Temperatura (voltaje); //calculamos el valor de temperatura con la variable que guardaba el voltaje
  return temperatura; //ese calculo se mmete en una variable llamada temperatura que luego devolvemos
}
