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


class PicBat
{
public:
    // Constructors
    PicBat(LiquidCrystal &lcd);

    // Copy constructor
    PicBat( const PicBat& ) = default;
    // Move constructor
    PicBat ( PicBat && ) = default;

    void pic(uint8_t nom)
    {
        if(nom < 8) _lcd.write(nom);
        //if(nom < 8) _lcd.print(nom, BYTE);
    }



private:
    LiquidCrystal &_lcd;

    static uint8_t pics[8][8];
};