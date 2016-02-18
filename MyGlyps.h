/*
 *
 * Класс для удобного рисования символа заполненности батареи
 *
 */
#pragma once

#include <LiquidCrystal.h>

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
        if(nom < 7) _lcd.write(nom);
    }

    // Выводит русскую букву "Д"
    void picD() const
    {
        _lcd.write(7);
    }

private:
    LiquidCrystal &_lcd;

    static uint8_t pics[8][8];
};