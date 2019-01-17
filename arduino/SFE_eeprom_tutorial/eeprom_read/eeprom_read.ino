//Include the Wire I2C Library
#include <Wire.h>

/*This address is determined by the way your address pins are wired.
In the diagram from earlier, we connected A0 and A1 to Ground and 
A2 to 5V. To get the address, we start with the control code from 
the datasheet (1010) and add the logic state for each address pin
in the order A2, A1, A0 (100) which gives us 0b1010100, or in 
Hexadecimal, 0x54*/

#define EEPROM_ADR 0x50
#define MEMSIZE   0x7D00
#define READSIZE  0x10

void setup()
{

//Start the I2C Library
  Wire.begin();
  Wire.setClock(400000); 

//Start the serial port
  Serial.begin(115200);

  //Output raw bytes to terminal
  //In this case we're going to read all of the bytes
  //which is 32000, or in hex, 0x7D00
  for (long x = 0 ; x < READSIZE ; x++) //Read all 131,071 bytes from EERPOM
  {
    byte val = readEEPROM(x);
    Serial.write(val);
  }
}

void loop()
{
  //Nothing to do, just hang out.
}

/* This is the 3 step memory reading procedure that
we talked about. First we send the MSB of the address. 
Then we send the LSB of the address. Then we ask for the 
number of bytes that we want to receive. Here, we're 
going 1 byte at a time*/

byte readEEPROM(long eeaddress)
{
  Wire.beginTransmission(EEPROM_ADR);

  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADR, 1);

  byte rdata = 0xFF;
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}
