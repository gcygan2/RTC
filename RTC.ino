#include <Wire.h> 
#define ARD_PCF8583 0x68

struct Czas
{
    uint8_t s;
    uint8_t m;
    uint8_t h;   
};


class Zegarek
{
  public:

  
  uint8_t Sekundy()
  {
    return Odczyt(0);
  }

  
  private:
  uint8_t Odczyt(uint8_t adr)
  {
    Wire.beginTransmission(ARD_PCF8583);
    Wire.write(adr);
    Wire.endTransmission();
    
    Wire.requestFrom(ARD_PCF8583, 1);
    //while (Wire.available()) {
      return Wire.read();
  }

};

void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
}

void loop()
{
  Zegarek z;

  uint8_t c = z.Sekundy();   
  Serial.println(c,HEX);
  delay(1000);
}
