/*
 *
 * class LCDwrapper
 * Обертка над LiquidCrystal для удобного отображения на экране
 * и избежания засорения кода 
 *
 */
#pragma once

#include <LiquidCrystal.h>
//#include <Pino.h>

#include <math.h>

 // Дополнительные символы для LCD
#include "PicBat.h"

// Bmp180 датчик температоуры и давления
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Состаяние аккомулятора
#include "Battery.h"



class LCDwrapper
{
public:
    // Constructors
    LCDwrapper(uint8_t rs,uint8_t e,uint8_t db4,uint8_t db5,uint8_t db6,uint8_t db7, uint8_t led):
        _lcd(rs, e, db4, db5, db6, db7),
        _lcdLight(led, Pino::Mode::out),
        _glyps(_lcd)
    {
        // устанавливаем размер (количество столбцов и строк) экрана
        _lcd.begin(16, 2);
        _lcd.clear();

        // Сразу же включаем подсветку
        _lcdLight.on();
    }

    // Copy constructor
    LCDwrapper( const LCDwrapper& ) = default;
    // Move constructor
    LCDwrapper ( LCDwrapper && ) = default;

    // Отображает необходимую информацию
    void show(Adafruit_BMP085 &bmp, Battery &bat);

    LCDwrapper& setCursor(uint8_t row, uint8_t col)
    {
        _lcd.setCursor(row, col);
        return *this;
    }

    LCDwrapper& print(const char * str)
    {
        _lcd.print(str);
        return *this;
    }

    void turnLight()
    {
        _lcdLightState = !_lcdLightState;
        _lcdLight.turn(_lcdLightState);
    }



private:

    void printFract(float val);


    // объект-экран
    LiquidCrystal _lcd;
    
    // Подсветка экрана (включает подсветку через транзистор КТ3102АМ)
    Pino _lcdLight;
    
    // Статус подсветки
    bool _lcdLightState = false;
    
    // Дополнительные символы для LCD
    PicBat _glyps;
};