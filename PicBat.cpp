/*
 *
 * Класс для удобного рисования символа заполненности батареи
 *
 */

//#include <stdint.h>
#include "PicBat.h"

// Constructors
PicBat::PicBat(LiquidCrystal &lcd) : _lcd(lcd)
{
    lcd.createChar(0, pics[0]);
    lcd.createChar(1, pics[1]);
    lcd.createChar(2, pics[2]);
    lcd.createChar(3, pics[3]);
    lcd.createChar(4, pics[4]);
    lcd.createChar(5, pics[5]);
    lcd.createChar(6, pics[6]);
    lcd.createChar(7, pics[7]);
}

uint8_t PicBat::pics[8][8] = {
    {
        // 0
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b11111,
    },{
        // 1
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b11111,
        0b11111,
    },{
        // 2
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b11111,
        0b11111,
        0b11111,
    },{
        // 3
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
    },{
        // 4
        0b01110,
        0b10001,
        0b10001,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
    },{
        // 5
        0b01110,
        0b10001,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
    },{
        // 6
        0b01110,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
    },{
        //////////////
        // Дополнительные глифы
        // 7
        // Д
        0b00110,
        0b01010,
        0b01010,
        0b01010,
        0b01010,
        0b01010,
        0b11111,
        0b10001,
    }
};
