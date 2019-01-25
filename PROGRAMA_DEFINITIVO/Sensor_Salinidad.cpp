/*-------- SENSOR SALINIDAD --------*/
#include "SensoresPrograma.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- CONSTRUCTOR --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
Sensor_Salinidad::Sensor_Salinidad (int _pin,int _power_pin, Adafruit_ADS1115 * _adc, int _ValorConSal, int _ValorSinSal) //declaramos el constructor y sus parámetros
{                                 
  pin = _pin; //objeto pin
  adc = _adc; //objeto adc
  power_pin = _power_pin; //pin digital
  (*this).ValorConSal = _ValorConSal; //obejto variable agua
  (*this).ValorSinSal = _ValorSinSal; //objeto variable aire
  pinMode (_power_pin,OUTPUT); //declaramos el pin digital
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN DE LECTURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Sensor_Salinidad::leer_canal () //funcion para leer el canal
{                                                                                                                        
  digitalWrite((*this).power_pin, HIGH ); //encendemos el sensor                                                                                                                    
  int lectura_digital = (*adc).readADC_SingleEnded(pin); //lectura del adc del pin analogico se mete en una variable                                                                                                   
  digitalWrite((*this).power_pin, LOW ); //apagamos el sensor                                                                                                    
  return lectura_digital; //devolvemos esa variable                                                                                                                                 
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN CALCULO --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Salinidad::calcular_Salinidad (int lectura_digital) //funcion para calcular la humedad pasandole la lectura del adc
{                                                                                          
 double salinidad = 100*  (*this).ValorSinSal/((*this).ValorSinSal-(*this).ValorConSal)-lectura_digital*100/((*this).ValorSinSal-(*this).ValorConSal); //formula para el calculo

  if (salinidad>100){
    salinidad=100;
  }

  if (salinidad<0){
    salinidad=0;
  }

  return salinidad; //devuelve el valor calculado almacenado en la variable salinidad
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN PANTALLA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

double Sensor_Salinidad::get_Salinidad () // funcion para sacar el valor calculado preiamente por pantalla
{                                                                                                                   
  int valor = leer_canal(); //llamamos a la funcion leer para alamcenar el valor que retornaba en la variable valor                                                                                                                                  
  double salinidad = calcular_Salinidad (valor); //calculamos el valor de salinidad con la variable que guardaba la lectura del adc                                                                                                         
  return salinidad; //ese calculo se mmete en una variable llamada salinidad que luego devolvemos                                                                                                                                      
}
