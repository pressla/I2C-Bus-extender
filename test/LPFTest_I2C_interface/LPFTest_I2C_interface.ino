// I2C slave sample code
// send bytes to I2C bus

#include <Wire.h>
//MCP23008 registers:
#define IODIR   0x00
#define GPINTEN 0x02
#define IOCON   0x05
#define INTCAP  0x08
#define GPIO    0x0A

//Arduino nano pins:
//SDA pin A4
//SCL pin A5
//Espressif ESP-32 Pins:
//SDA pin G21
//SCL pin G22

const int pSDA1 = 21;
const int pSCL1 = 22;
const int I2Cspeed = 400000; //100 or 400kHz are standard
const byte IO = 0x20; //MCP address

byte x = 0;
byte y = 0;
byte buffer[32];  //wire.h has 32byte buffer
unsigned long errorCount = 0;

void setup() {
  Wire.begin(pSDA1, pSCL1,I2Cspeed);  // join i2c bus as master
  Serial.begin(115200);             // start serial for output
  Serial.println("Hello HL2 I2C sender");
  setI2CReg(IODIR, 0x80);
  setI2CReg(GPINTEN, 0x80);
  setI2CReg(IOCON, 0x22);
}

void loop() {
  byte chck = 0;
  buffer[0] = 0x0A;   //gpio write mask
  buffer[1] = 1 << x; //shift left bit by x bits
  
  for (int n=0;n<31;n++) chck += buffer[n];
  buffer[31] = chck;
  Wire.beginTransmission(IO); // transmit to device #
  Wire.write(buffer,2); // sends 2 bytes
  byte error = Wire.endTransmission(); // stop transmitting
  String snd = "n=";
  snd = snd+buffer[1]+" errorcount:";
  snd += errorCount;
  Serial.println(snd);

  
  x++;
  if (x>7) {x=0;y++;}

  if (error!=0) {
      //Serial.println("error connect to slave");
      errorCount++;
  }
  
  
  delay(1000);
}

void setI2CReg(byte reg, byte val)
{
  Wire.beginTransmission(IO);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
