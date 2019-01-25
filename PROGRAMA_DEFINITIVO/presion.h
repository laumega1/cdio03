/*-------- SENSOR DE DE PRESIÓN --------*/

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- VARIABLES GLOBALES --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  SFE_BMP180 bmp180; // Declara el objeto bmp180.
  char status; // Declaramos status.
  double P; // Declaramos la variable real P.
  double T;

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- SETUP --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void setup_presion(void) 
{ 
  if (bmp180.begin()) // Si se inicia el BMP180 imprime en pantalla que se ha iniciado.
  { 
    Serial.println("BMP180 iniciado");
  }
  else // Si no, repite en bucle que ha habido un error al iniciarlo.
  { 
    Serial.println("Error al iniciar BMP180");
    while(1);
  }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- BUCLE --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void loop_presion(double temperatura)
{
  T=temperatura;
  
  status = bmp180.startPressure(2); //Inicio de la lectura de presión.

  if (status != 0) // Si  la lectura de la presión es distinta a cero.
  { 
    delay(status); //Pausa para que finalice la lectura.
    status = bmp180.getPressure(P,T); //Obtenemos la presión.
  }
    Serial.println("Presion: ");
    Serial.print(P,2);
    Serial.println(" mb");
}
