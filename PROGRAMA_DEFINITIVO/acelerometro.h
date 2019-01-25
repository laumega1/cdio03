/*-------- ACELERÓMETRO --------*/
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

#define interruptPin  4 //decimos que el pin de interrupcion sera el 4

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIONES GENERALES --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
volatile int _interrupcion=0;

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN AUXILIAR DE LECTURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.endTransmission();

   Wire.requestFrom(Address, Nbytes);
   uint8_t index = 0;
   while (Wire.available())
      Data[index++] = Wire.read();
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN AUXILIAR DE ESCRITURA --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- FUNCIÓN DE LA INTERRUPCIÓN --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void handleInterrupt()
{
  uint8_t intStatus[1];

  I2Cread(MPU9250_ADDRESS, 0x3A, 1, intStatus); //leemos de intStatus para desactivar la interrupcion

  Serial.println("          DETECTADO MOVIMIENTO. Estado de la Interrupción: ");
  Serial.println(intStatus[1], HEX);
  _interrupcion=1;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- SETUP --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void setup_acelerometro ()
{
  Serial.println("Conectando...");
  
  pinMode(interruptPin, INPUT_PULLUP); //ponemos el pin a nivel alto por defecto
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  Wire.begin(); //Inicializo I2C

  // configuro el Wake on Motion
  I2CwriteByte(MPU9250_ADDRESS, 0x1C, ACC_FULL_SCALE_2_G);
  I2CwriteByte(MPU9250_ADDRESS, 0X6B, 0);
  I2CwriteByte(MPU9250_ADDRESS, 0X6C, 7);
  I2CwriteByte(MPU9250_ADDRESS, 0X1D, 5);
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x80);
  I2CwriteByte(MPU9250_ADDRESS, 0X38, 64);
  I2CwriteByte(MPU9250_ADDRESS, 0X69, 192);
  I2CwriteByte(MPU9250_ADDRESS, 0X1F, 2);//2
  I2CwriteByte(MPU9250_ADDRESS, 0X1E, 1);//1
  I2CwriteByte(MPU9250_ADDRESS, 0X6B, 32);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                                           /*-------- BUCLE --------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void loop_acelerometro ()
{
   uint8_t Buf[14]; //Lectura acelerometro y giroscopio
   int FS_ACC = 16;
   int FS_GYRO = 2000;

   I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

   float ax = (Buf[0] << 8 | Buf[1]); //Convertir registros acelerometro
   float ay = (Buf[2] << 8 | Buf[3]);
   float az = Buf[4] << 8 | Buf[5];

   ax = (ax*FS_ACC/32768)-0.36 ;
   ay = (ay*FS_ACC/32768)-31.56 ;
   az = (az*FS_ACC/32768)-0.69 ;
   
   Serial.println("Lectura Acelerometro"); //mostrar valores
   Serial.print("AX=");
   Serial.print(ax, 2);
   Serial.print("g");
   Serial.print("\t");
   Serial.print("AY=");
   Serial.print(ay, 2);
   Serial.print("g");
   Serial.print("\t");
   Serial.print("AZ=");
   Serial.print(az, 2);
   Serial.println("g");
}
