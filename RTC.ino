#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ARD_PCF8583 0x68

LiquidCrystal_I2C lcd(0x27,16,2);

struct Czas
{
    uint8_t s;
    uint8_t m;
    uint8_t h;   
};


class Zegarek
{
  public:

  
  uint8_t print()
  {
    lcd.clear();
    lcd.print (Odczyt(2), HEX);
    lcd.print(":");
    lcd.print (Odczyt(1), HEX);
    lcd.print(" ");
    lcd.print (Odczyt(0), HEX);
  }
  
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

Zegarek z;

  
void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  lcd.init();
/*
    Wire.beginTransmission(ARD_PCF8583);
    Wire.write(0);
    Wire.write(0x11);
    Wire.write(0x23);
    Wire.endTransmission();
    Wire.write(0);
*/
}

void loop()
{
  z.print();

  uint8_t c = z.Sekundy();   
  Serial.println(c,HEX);
  delay(1000);
}
