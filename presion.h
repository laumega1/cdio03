//#include <Wire.h> // Incluye la libreria Wire.h, que es la que nos permite imprimir en pantalla.
#include <SFE_BMP180.h> // Incluye la libreria FE_BMP180.h, que es la que nos permite programar el BMP180.
//#include <Adafruit_ADS1015.h>//Incluye la libreria Adafruit_ADS1015.h, que es la que nos permite programar el ADS.

/////////////////////////////////////////
/*        VARIABLES GLOBALES           */
/////////////////////////////////////////

/*Adafruit_ADS1115 ads(0x48);//
float Voltage = 0.0; //Declara el valor de la variable real "Voltage" a 0.0
double temperatura; // Declara la variable real "temperatura".
int16_t adc2; // Declara la variable entera adc2.

SFE_BMP180 bmp180; // Declara el objeto bmp180.
char status; // Declaramos status.
double P; // Declaramos la variable real P.*/

/////////////////////////////////////////
/*        SETUP(CONFIGURACIÓN)         */
/////////////////////////////////////////


  SFE_BMP180 bmp180; // Declara el objeto bmp180.
  char status; // Declaramos status.
  double P; // Declaramos la variable real P.


void setup_presion(void) { //


  if (bmp180.begin()){ // Si se inicia el BMP180 imprime en pantalla que se ha iniciado.

    Serial.println("BMP180 iniciado");

  }else{ // Si no, repite en bucle que ha habido un error al iniciarlo.

    Serial.println("Error al iniciar BMP180");
    while(1);
  }

}

/////////////////////////////////////////
/*            FUNCIONES                */
/////////////////////////////////////////

/*void leerTemperatura(){

  adc2 = ads.readADC_SingleEnded(2); // Le da el valor que le el ADS en el pin A0 a la variable adc0.
  Voltage = (adc2 * 0.1875)/1000; // Le da valor al voltage.
  temperatura=(-0.97)+((Voltage-0.75)/0.036); //Le da valor a la temperatura.
}*/



/////////////////////////////////////////
/*               LOOP                  */
/////////////////////////////////////////

void loop_presion(double temperatura){



  status = bmp180.startPressure(3); // Inicio de la lectura de presión.

  if (status != 0){ // Si  la lectura de la presión es distinta a cero.

    delay(status); //Pausa para que finalice la lectura.
    status = bmp180.getPressure(P,temperatura); //Obtenemos la presión.

  }

    Serial.println("Presion: ");
    Serial.print(P,2);
    Serial.println(" mb");
  /*leerTemperatura();//Llama a la función "leerTemperatura()".

  Serial.print("AIN0: ");
  Serial.println();
  Serial.println(adc2); //
  Serial.print("tVoltage: ");
  Serial.println(Voltage, 7);
  Serial.println();
  Serial.print("tTemperatura: ");
  Serial.println(temperatura);
  Serial.println();*/

//Imprime por pantalla el valor del AIN0, el voltage y la temperatura.

  //delay(1000); //Esperar 1s.



//Imprime por pantalla el valor de la presión en milibares.

  //delay(2000); //Esperar 1s.
}
# cdio03
