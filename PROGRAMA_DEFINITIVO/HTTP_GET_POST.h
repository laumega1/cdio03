/*-------- WIFI --------*/
#include <ESP8266WiFi.h>

#define PRINT_DEBUG_MESSAGES

// Comentar/Descomentar para conexion Fuera/Dentro de UPV
//LO HE COMENTADO PORQUE NO ESTAMOS DENTRO DE LA UPV
//#define WiFi_CONNECTION_UPV

#define REST_SERVER_THINGSPEAK //Selecciona tu canal para ver los datos en la web

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- WIFI DEFINITIONS --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifdef WiFi_CONNECTION_UPV //Conexion UPV
  const char WiFiSSID[] = "GTI1";
  const char WiFiPSK[] = "1PV.arduino.Toledo";
#else //Conexion fuera de la UPV
  const char WiFiSSID[] = "laura20400"; //LAURA METE AQUI TU WIFI
  const char WiFiPSK[] = "holacaracola"; //LAURA METE AQUI LA CONTRASEÑA DE TU WIFI
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- SERVER DEFINITIONS --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#if defined(WiFi_CONNECTION_UPV) //Conexion UPV
  const char Server_Host[] = "proxy.upv.es";
  const int Server_HttpPort = 8080;
#elif defined(REST_SERVER_THINGSPEAK) //Conexion fuera de la UPV
  const char Server_Host[] = "api.thingspeak.com";
  const int Server_HttpPort = 80;
#endif

WiFiClient client;

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- HTTP REST CONECTION --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifdef REST_SERVER_THINGSPEAK
  const char Rest_Host[] = "api.thingspeak.com";
  String MyWriteAPIKey="9TBC5KM1DFAP8DKI"; // ESTA ES LA CLAVE OBTENIDA
#else
  const char Rest_Host[] = "dweet.io";
  String MyWriteAPIKey="cdiocurso2018gXX"; // Escribe la clave de tu canal Dweet
#endif

#define NUM_FIELDS_TO_SEND 8

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- PIN DEFINITIONS --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const int LED_PIN = 5; //Thing's onboard, green LED

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- WIFI CONECTION --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void connectWiFi()
{
  byte ledStatus = LOW;

  #ifdef PRINT_DEBUG_MESSAGES
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
  #endif

  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_PIN, ledStatus); //Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
    #ifdef PRINT_DEBUG_MESSAGES
       Serial.println(".");
    #endif
    delay(500);
  }
  #ifdef PRINT_DEBUG_MESSAGES
     Serial.println( "WiFi Connected" );
     Serial.println(WiFi.localIP()); //Print the IP address
  #endif
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- HTTP POST THINGSPEAK --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void HTTPPost(String fieldData[], int numFields)
{
    if (client.connect( Server_Host , Server_HttpPort ))
    {
        String PostData= "api_key=" + MyWriteAPIKey ;
        for ( int field = 1; field < (numFields + 1); field++ ){
            PostData += "&field" + String( field ) + "=" + fieldData[ field ];
        }

        // POST data via HTTP
        #ifdef PRINT_DEBUG_MESSAGES
            Serial.println( "Connecting to ThingSpeak for update..." );
        #endif
        client.println( "POST http://" + String(Rest_Host) + "/update HTTP/1.1" );
        client.println( "Host: " + String(Rest_Host) );
        client.println( "Connection: close" );
        client.println( "Content-Type: application/x-www-form-urlencoded" );
        client.println( "Content-Length: " + String( PostData.length() ) );
        client.println();
        client.println( PostData );
        #ifdef PRINT_DEBUG_MESSAGES
            Serial.println( PostData );
            Serial.println();
            //Para ver la respuesta del servidor
            #ifdef PRINT_HTTP_RESPONSE
              delay(500);
              Serial.println();
              while(client.available()){String line = client.readStringUntil('\r');Serial.print(line); }
              Serial.println();
              Serial.println();
            #endif
        #endif
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- SETUP --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void setup_HTPP() {

  #ifdef PRINT_DEBUG_MESSAGES
    Serial.begin(9600);
  #endif

  connectWiFi();
  digitalWrite(LED_PIN, HIGH);

  #ifdef PRINT_DEBUG_MESSAGES
      Serial.print("Server_Host: ");
      Serial.println(Server_Host);
      Serial.print("Port: ");
      Serial.println(String( Server_HttpPort ));
      Serial.print("Server_Rest: ");
      Serial.println(Rest_Host);
  #endif
 }



void loop_HTTP(double _humedad,double _salinidad,double _temperatura,double _luminosidad) 
{
    String data[ NUM_FIELDS_TO_SEND + 1]; //Podemos enviar hasta 8 datos

    data[ 1 ] = String( _humedad ); //enviamos el valor de la humedad
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "HUMEDAD = " );
        Serial.println( data[ 1 ] );
    #endif

    data[ 2 ] = String( _salinidad ); //enviamos el valor de la salinidad
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "SALINIDAD = " );
        Serial.println( data[ 2 ] );
    #endif

    data[ 3 ] = String( _temperatura ); //enviamos el valor de la temperatura
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "TEMPERATURA = " );
        Serial.println( data[ 3 ] );
    #endif

    data[ 4 ] = String(_luminosidad ); //enviamos el valor de la luminosidad
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "LUMINOSIDAD = " );
        Serial.println( data[ 4 ] );
    #endif

    data[ 5 ] = String( P ); //enviamos el valor de la presión
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "PRESIÓN = " );
        Serial.println( data[ 5 ] );
    #endif
 
    data[ 6 ] = String( gps.location.lat() ); //enviamos la latitud de nuestro sensor
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "LATITUD = " );
        Serial.println( data[ 6 ] );
    #endif

    data[ 7 ] = String( gps.location.lng() ); //enviamos la longitud de nuestro sensor
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "LONGITUD = " );
        Serial.println( data[ 7 ] );
    #endif

    data[ 8 ] = String( _interrupcion ); //enviamos si hay alguna interrupción en nuestro sensor
    #ifdef PRINT_DEBUG_MESSAGES
        Serial.print( "INTERRUPCIÓN = " );
        Serial.println( data[ 8 ] );
    #endif

    HTTPPost( data, NUM_FIELDS_TO_SEND );
    delay( 15000 );
}
