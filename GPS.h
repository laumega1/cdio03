/******************************************************************************

GPS A2235H
Conectar RXI al pin 12 del ESP8266
Conectar TXO al pin 13 del ESP8266
Usamos el pin 15 para inicializar el GPS
ATENCION: no poner el GPS sobre el Sparkfun

******************************************************************************/

#include <TinyGPS++.h>                                                                                                   //Librería del GPS.
#include <SoftwareSerial.h>                                                                                              //Librería que nos permite crear un software ya que el nuestro posee solo una salida UART

#define RX_PIN  12                                                                                                       // GPS RXI.
#define TX_PIN  13                                                                                                       // GPS TX0.
#define PIN_INICIO 15                                                                                                    // Pin para inicializar el GPS.

#define GPS_VELOCIDAD  4800                                                                                              //Velocidad de comunicación serie.

TinyGPSPlus gps;                                                                                                         // Definimos el objeto gps.

SoftwareSerial ss(RX_PIN,TX_PIN);                                                                                        // Creamos una UART software para comunicación con el GPS.

/////////////////////////////////////////////////////////////////////////////////////////
//                                      FUNCIONES                                      //
/////////////////////////////////////////////////////////////////////////////////////////

static void esperar(unsigned long ms){                                                                                   // Función que espera 1s para leer el GPS.

  unsigned long inicio = millis();                                                                                       //Devuelve los segundos de inicialización.
  do{
    while(ss.available()){

      gps.encode(ss.read());                                                                                             // Lee el gps mientras que esté disponible la UART software.
    }
  } while(millis() - inicio < ms);

                                                                                                                         //Termina el bucle cuando el número de milisegundos desde que la placa comenzó a ejecutar el programa menos los segundos de inicialización sea mayor a ms.
}

void encender_apagar(){                                                                                                  // Función para encender/apagar mediante un pulso.

                                                                                                                         // Enciende el pulso.

  digitalWrite(PIN_INICIO,LOW);                                                                                          //Declara la señal que envía el pin de inicio como bajo.
  delay(200);                                                                                                            //Espera 0.2s
  digitalWrite(PIN_INICIO,HIGH);                                                                                         //Declara la señal que envía el pin de inicio como alta.
  delay(200);                                                                                                            //Espera 0.2s
  digitalWrite(PIN_INICIO,LOW);                                                                                          //Declara la señal que envía el pin de inicio como bajo.
 }


/////////////////////////////////////////////////////////////////////////////////////////
//                                  CONFIGURACIÓN                                      //
/////////////////////////////////////////////////////////////////////////////////////////

void setup_GPS () {

//  Serial.begin(9600);                                                                                                   // Inicializa la comunicación con el monitor serie.
  ss.begin(GPS_VELOCIDAD); // Inicializa la comunicación con el GPS.

  pinMode(PIN_INICIO,OUTPUT);                                                                                             //Hace que el pin de inicio se comporte como salida.
  encender_apagar();                                                                                                      // Pulso para encender el GPS.

  //Serial.println("Fecha      Hora       Latitud   Longitud   Alt    Rumbo   Velocidad");
  //Serial.println("(MM/DD/YY) (HH/MM/SS)     (deg)       (deg)  (ft)                   (mph)");
  //Serial.println("-------------------------------------------------------------------------");

//Imprime la posición, velocidad y rumbo del satélite en la x fecha y x hora.
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                          BUCLE                                      //
/////////////////////////////////////////////////////////////////////////////////////////

void loop_GPS () {
  /*char gpsDate[10];//Inicia una variable tipo char formada por 10 espacios de tamaño que guarde la fecha.
  char gpsTime[10];//Inicia una variable tipo char formada por 10 espacios de tamaño que guarde el tiempo.
*/
  if(gps.location.isValid()){ // Si el GPS está recibiendo los mensajes NMEA.
/*
    sprintf(gpsDate,"%d/%d/%d", gps.date.month(),gps.date.day(),gps.date.year()); // Construimos una string de los datos de fecha.
    sprintf(gpsTime,"%d/%d/0%d", gps.time.hour(),gps.time.minute(),gps.time.second());  // Construimos string de los datos de hora.

    Serial.print(gpsDate);//Imprime por pantalla la fecha.
    Serial.print('\t');
    Serial.print(gpsTime);//Imprime por pantalla la hora.
    Serial.print('\t');
    */
    Serial.print("La latitud es: ");
    Serial.print(gps.location.lat(),6);                                                                                      //Imprime por pantalla la latitud.
    Serial.print('\t');
    Serial.print("La longitud es: ");
    Serial.print(gps.location.lng(),6);                                                                                      //Imprime por pantalla la longitud
    Serial.print('\t');
    /*Serial.print(gps.altitude.feet());//Imprime por pantalla la altura en pies.
    Serial.print('\t');
    Serial.print(gps.course.deg(),2);//Imprime por pantalla el rumbo en grados.
    Serial.print('\t');
    Serial.println(gps.speed.mph(),2);//Imprime por pantalla la velocidad.*/
  }
  else                                                                                                                        // Si no recibe los mensajes muestra los satelites conectados.
  {

    Serial.print("Satelites conectados: ");
    Serial.println(gps.satellites.value());
  }
  //esperar(1000); //Espera 1s.
}
# cdio03
