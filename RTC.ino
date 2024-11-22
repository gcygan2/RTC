#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <DIYables_4Digit7Segment_74HC595.h>

#define ADR_DS1302 0x68
#define PRZYCISK 7

LiquidCrystal_I2C lcd(0x27,16,2);
//DIYables_4Digit7Segment_74HC595 display(7, 6, 5);

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
    Wire.beginTransmission(ADR_DS1302);
    Wire.write(adr);
    Wire.endTransmission();
    
    Wire.requestFrom(ADR_DS1302, 1);
    return Wire.read();
  }
};

Zegarek z;

void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  lcd.init();
  pinMode(PRZYCISK, INPUT_PULLUP);

  //display.printInt(-132, false);
/*
    ustaw minuty
    Wire.beginTransmission(ADR_DS1302);
    Wire.write(1);
    Wire.write(0x15);
    Wire.endTransmission();
*/
}

void loop()
{
  //display.loop();
  z.print();
  uint8_t c = z.Sekundy();   
  if (!digitalRead(PRZYCISK)) {
    Serial.println(c,HEX);
    while (!digitalRead(PRZYCISK));
  }
  //delay(500);
}
