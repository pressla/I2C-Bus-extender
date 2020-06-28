// I2C slave sample code
// send bytes to I2C bus

#include <Wire.h>
//Arduino nano pins:
//SDA pin A4
//SCL pin A5
//Espressif ESP-32 Pins: ESP32 again poorly implemented can be Master only. need a standard arduino type for Wire.h to receive I2C

//SDA pin G21
//SCL pin G22

const int pSDA1 = 21;
const int pSCL1 = 22;
const int I2Cspeed = 400000; //100 or 400kHz are standard

byte x = 0;
byte y = 0;
byte buffer[32];  //wire.h has 32byte buffer
unsigned long errorCount = 0;

void setup() {
  Wire.begin(pSDA1, pSCL1,I2Cspeed);  // join i2c bus as master
  Serial.begin(115200);             // start serial for output
  Serial.println("Hello HL2 I2C sender");
}

void loop() {
  byte chck = 0;
  buffer[0] = y;
  buffer[1] = x;
  buffer[x]=y;
  for (int n=0;n<31;n++) chck += buffer[n];
  buffer[31] = chck;
  Wire.beginTransmission(0x20); // transmit to device #
  Wire.write(buffer,32); // sends 32 bytes
  byte error = Wire.endTransmission(); // stop transmitting
  String snd = "n=";
  snd = snd+buffer[31]+" errorcount:";
  snd += errorCount;
  Serial.println(snd);

  
  x++;
  if (x>30) {x=0;y++;}

  if (error!=0) {
      //Serial.println("error connect to slave");
      errorCount++;
  }
  
  
  delay(10);
}
