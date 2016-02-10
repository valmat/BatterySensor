/*
 *
 * Класс для удобного рисования символа заполненности батареи
 *
 */
#pragma once

#include <LiquidCrystal.h>

//#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h>
//#include "binary.h"


class MyGlyps
{
public:
    // Constructors
    MyGlyps(LiquidCrystal &lcd);

    // Copy constructor
    MyGlyps( const MyGlyps& ) = default;
    // Move constructor
    MyGlyps ( MyGlyps && ) = default;

    void pic(uint8_t nom) const
    {
        if(nom < 8) _lcd.write(nom);
        //if(nom < 8) _lcd.print(nom, BYTE);
    }

    void picD() const
    {
        _lcd.write(7);
    }

private:
    LiquidCrystal &_lcd;

    static uint8_t pics[8][8];
};