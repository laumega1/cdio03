/*-------- SENSOR DE HUMEDAD --------*/
#ifndef HUMEDAD_YA_INCLUIDA
#define HUMEDAD_YA_INCLUIDA
#include <Adafruit_ADS1015.h>

class Sensor_Humedad 
{
  private:
    int pin; // pin analogico
    Adafruit_ADS1115 * adc; // puntero al objeto adc
    int ValorAire;
    int ValorAgua;
    int leer_canal(); // funcion para leer la entrada
    double calcular_Humedad(int lectura_digital); // funcion para calcular el valor de humedad

  public:
    Sensor_Humedad(int pin,Adafruit_ADS1115 * adc,int ValorAire,int ValorAgua); // constructor
    double get_Humedad(); // funcion para mostrar el valor de humedad
};
#endif

/*-------- SENSOR DE ILUMINACION --------*/

#ifndef ILUMINACION_YA_INCLUIDA
#define ILUMINACION_YA_INCLUIDA

class Sensor_Iluminacion 
{
  private:
    int pin; // pin analogico
    Adafruit_ADS1115 * adc; // puntero al objeto adc
    double a; // variable a con el valor del divisor
    double b; // variable a con el valor del divisor
    int leer_canal(); // funcion para leer la entrada
    double calcular_Voltaje(int lectura_digital); // funcion para calcular el valor del voltaje
    double calcular_Luminosidad(double valor_voltaje); // funcion para calcular el valor de luminosidad

  public:
    Sensor_Iluminacion(int pin,Adafruit_ADS1115 * adc,double a, double b); //constructor
    double get_Luminosidad(); //funcion para mostrar el valor de luminosidad
};
#endif

/*-------- SENSOR DE SALINIDAD --------*/

#ifndef SALINIDAD_YA_INCLUIDA
#define SALINIDAD_YA_INCLUIDA

class Sensor_Salinidad 
{
  private:
    int pin; // pin analogico
    int power_pin; // pin digital
    Adafruit_ADS1115 * adc; // puntero al objeto adc
    int ValorConSal;
    int ValorSinSal;
    int leer_canal(); // funcion para leer la entrada
    double calcular_Salinidad(int lectura_digital); // funcion para calcular el valor de salinidad

  public:
    Sensor_Salinidad(int pin,int power_pin,Adafruit_ADS1115 * adc,int ValorConSal,int ValorSinSal); // constructor
    double get_Salinidad(); // funcion para mostrar el valor de salinidad
};
#endif

/*-------- SENSOR DE TEMPERATURA --------*/

#ifndef TEMPERATURA_YA_INCLUIDA
#define TEMPERARURA_YA_INCLUIDA

class Sensor_Temperatura 
{
  private:
    int pin; // pin analogico
    Adafruit_ADS1115 * adc; // puntero al objeto adc
    double a; // variables de la ecuacion
    double b; // variables de la ecuacion
    double cal; //calibra la temperatura
    int leer_canal(); // funcion para leer la entrada
    double calcular_Voltaje(int lectura_digital); // funcion para calcular el valor del voltaje
    double calcular_Temperatura(double valor_voltaje); // funcion para calcular el valor de temperatura

  public:
    Sensor_Temperatura(int pin,Adafruit_ADS1115 * adc,double a,double b,double cal); // constructor
    double get_Temperatura(); // funcion para mostrar el valor de temperatura
};
#endif
