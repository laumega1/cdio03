/*-------- SENSOR DE HUMEDAD --------*/
#include "SensoresPrograma.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- CONSTRUCTOR --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
Sensor_Humedad::Sensor_Humedad (int _pin, Adafruit_ADS1115 * _adc, int _ValorAire, int _ValorAgua) //declaramos el constructor y sus parámetros
{                                       
  pin = _pin; //objeto pin analógico
  adc = _adc; //objeto adc
  (*this).ValorAire = _ValorAire; //obejto variable aire
  (*this).ValorAgua = _ValorAgua; //objeto variable agua
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN DE LECTURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Sensor_Humedad::leer_canal () //funcion para leer el canal
{                                                                                                        
  int lectura_digital = (*adc).readADC_SingleEnded(pin); //lectura del adc del pin analogico se mete en una variable
  Serial.println(lectura_digital);
  return lectura_digital; //devolvemos esa variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN CÁLCULO --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Humedad::calcular_Humedad (int lectura_digital) //funcion para el calculo de la ecuacion pasandole la lectura del adc
{                                                                           
 double humedad = 100*(*this).ValorAire/((*this).ValorAire-(*this).ValorAgua)-lectura_digital*100/((*this).ValorAire-(*this).ValorAgua); //el calculo del valor se alamcena en una variable que posteriormente retornamos

  if (humedad>100) //se ajustan los valores maximos y minimos
  {                                                                                                                       
    humedad=100;
  }
  
  if (humedad<0)
  {
    humedad=0;
  }
  return humedad; //devuelve el valor calculado almacenado en la variable
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN PANTALLA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
double Sensor_Humedad::get_Humedad () //funcion para sacar el valor calculado preiamente por pantalla
{                                                                                                   
  int valor = leer_canal(); //llamamos a la funcion leer para alamcenar el valor que retornaba en la variable valor
  double humedad = calcular_Humedad (valor); //calculamos el valor de humedad con la variable que guardaba la lectura del adc
  return humedad; //ese calculo se mmete en una variable llamada humedad que luego devolvemos
}
