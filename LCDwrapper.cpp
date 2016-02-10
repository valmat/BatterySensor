#include "LCDwrapper.h"


void LCDwrapper::printFract(float val)
{
    val = round(val*10)/10;
    uint8_t fract = round(10*(val - (int)val));

    _lcd.print( (int)val );
    _lcd.print( '.' );
    _lcd.print( (int)fract );
}

void LCDwrapper::show(Adafruit_BMP085 &bmp, Pino &rawVoltage)
{
    //
    // Печатаем погодные данные
    //
    _lcd.setCursor(0, 0);

    auto temperature = bmp.readTemperature();
    auto pressure = bmp.readPressure()/133.322368421;
    
    _lcd.print("T:");
    printFract(temperature);
    _lcd.print("\xDF");
    _lcd.print("C    ");

    _lcd.setCursor(9, 0);
    //printFract(pressure);
    _glyps.picD();
    _lcd.print(":");
    _lcd.print(round(pressure));
    //_lcd.println(" MM PT.CT.");
    _lcd.print("MM  ");  

    
    //
    // Отображаем состояние аккомулятора
    //
    //lcd.clear();
    _lcd.setCursor(0, 1);
    
    _lcd.print("raw:");
    _lcd.print( rawVoltage.read() );
    _lcd.print("    ");
    
    /*
    //auto pic_nom = millis()%7;
    auto pic_nom = TMPVAR%8;
    
    _lcd.setCursor(11, 1);
    _lcd.print(pic_nom);

    _lcd.setCursor(14, 1);
    glyps.pic(pic_nom);
    TMPVAR++;
    */
}
