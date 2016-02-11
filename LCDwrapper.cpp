#include "LCDwrapper.h"


void LCDwrapper::printFract(float val)
{
    val = round(val*10)/10;
    uint8_t fract = round(10*(val - (int)val));

    _lcd.print( (int)val );
    _lcd.print( '.' );
    _lcd.print( fract );
}

void LCDwrapper::show(Adafruit_BMP085 &bmp, Battery &bat)
{
    //
    // Печатаем погодные данные
    //
    _lcd.setCursor(0, 0);

    auto temperature = bmp.readTemperature();
    auto pressure = bmp.readPressure()/133.322368421;
    
    _lcd.print("T:");
    printFract(temperature);
    // °C
    _lcd.print("\xDF");
    _lcd.print("C    ");

    _lcd.setCursor(9, 0);
    _glyps.picD();
    _lcd.print(":");
    _lcd.print(round(pressure));
    //_lcd.println(" MM PT.CT.");
    _lcd.print("MM  ");  

    
    //
    // Отображаем состояние аккомулятора
    //
    auto batState    = bat.state();
    // измеряемое напряжение на пине
    auto mesVoltage  = batState.mesVoltage();
    // Вычисляемое напряжение батареи
    auto calcVoltage = batState.calcVoltage();
    // Проценты
    auto percent     = batState.percent();


    //lcd.clear();
    _lcd.setCursor(0, 1);
    
    // Выводим значек батареи
    picBat(percent);

    _lcd.print(":");
    _lcd.print( batState.raw() );

    _lcd.print(":");
    _lcd.print(percent );

    _lcd.print(":");
    //_lcd.print( mesVoltage );
    printFract(mesVoltage);

    _lcd.print(":");
    //_lcd.print( calcVoltage );
    printFract(calcVoltage);


    _lcd.print("    ");
    
}

void LCDwrapper::picBat(uint8_t percent)
{
    if(percent >= 90) {
        // full
        _glyps.pic(6);
    } else if (percent < 10) {
        // empty
        _glyps.pic(0);
        
    } else if (percent < 26 ) {
        _glyps.pic(1);
    } else if (percent < 42 ) {
        _glyps.pic(2);
    } else if (percent < 58 ) {
        _glyps.pic(3);
    } else if (percent < 74 ) {
        _glyps.pic(4);
    } else { // if (percent < 90 )
        _glyps.pic(5);
    }
}
