/*
 *
 * LedBox - управление группой RGB светодиодов с общим анодом.
 * Функционал в пределах необходимого мне.
 *
 */

#pragma once

#include "MyRGB.h"


class LedBox
{
public:
    // Constructors
    LedBox(MyRGB &led1, MyRGB &led2, MyRGB &led3) : _led1(led1), _led2(led2), _led3(led3) {}

    // Copy constructor
    LedBox( const LedBox& ) = default;
    // Move constructor
    LedBox ( LedBox && ) = default;

    // Приветственное моргание светодиодами при включении
    void hello();

    // отображает состояние батареи в зависимости от процента заряда
    void showBat(uint8_t percent);

private:

    MyRGB & _led1;
    MyRGB & _led2;
    MyRGB & _led3;
};