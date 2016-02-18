#include "LCDwrapper.h"


uint16_t LCDwrapper::pow10(uint8_t pow)
{
    if(1 == pow) {
        return 10;
    } else if(pow > 1) {
        return 10 * pow10(pow-1);
    } else {
        return 1;
    }
}

void LCDwrapper::printFract(float val, uint8_t pow)
{
    uint16_t intact = (int)val;
    uint8_t fract = (uint8_t)( pow10(pow) * ( val - (float)intact ) + 0.5 );

    _lcd.print( intact );
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

    // значёк батареи
    _lcd.setCursor(0, 1);
    picBat(percent);

    // %
    _lcd.print(" ");
    _lcd.print(percent );
    _lcd.print("%   ");

    // Напряжение
    if(calcVoltage < 10.0) {
        _lcd.setCursor(10, 1);
    } else {
        _lcd.setCursor(9, 1);
    }
    printFract(calcVoltage, 2);
    _lcd.print(" B");
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
