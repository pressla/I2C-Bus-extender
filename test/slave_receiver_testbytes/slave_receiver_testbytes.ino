// I2C slave sample code
// analog value for external Amp by arduino
// See Schematic: 
#include <Wire.h>

const int ledPin =  13;// the number of the LED pin
unsigned long dataLoss = 0;
unsigned long bytesPerSec = 0;
//SDA pin A4
//SCL pin A5
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated

void setup() {
  Wire.begin(0x20);                 // join i2c bus with address to listen
  Wire.onReceive(receiveEvent);     // register event
  Serial.begin(115200);             // start serial for output
  Serial.println("Hello HL2 I2C");
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
  //Serial.println(howMany);
  //Serial.print("BUS DATA:");
  //Serial.println(howMany);
  
  byte c[32];
  String rec;
  byte chck = 0;
  int i= 0;
  while (0 < Wire.available()) { // loop through all but the last
    c[i] = Wire.read(); // receive byte as a character
    if (i!=0) rec += ",";
    rec += c[i];
    chck += c[i];
    i++;
  }
  chck-=c[31];
  bytesPerSec += howMany;
Serial.println(rec);
  if (chck != c[31]) dataLoss++;
  String txt(c[1]);
  txt = txt+"n="+howMany+" "+"dataLossCount:"+dataLoss+" "+chck+"="+c[31];
  
  if (lifeblink(1000)) {
    txt = txt + "bytesPerSec="+bytesPerSec;
    bytesPerSec = 0;
    Serial.println(txt);
    digitalWrite(ledPin, ledState);

  }


  
}

bool lifeblink (int timeout) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= timeout) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
  
      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
  
      return true;
    }
    else return false;
    
}
