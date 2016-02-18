/*
 *
 * class Configs
 * Все настройки в.т.ч номера пинов в Configs
 *
 */
#pragma once


struct Configs
{
    // Button pin nom
    constexpr static uint8_t button = 2;
    // Button Debounce Timeout
    constexpr static uint8_t buttonDebounce = 100;

    // Инициализируем объект-экран, передаём использованные 
    // для подключения контакты на Arduino в порядке:
    // RS, E, DB4, DB5, DB6, DB7
    // RS  --> 4
    // E   --> 7
    // DB4 --> 8
    // DB5 --> 12
    // DB6 --> 14
    // DB7 --> 15
    // lcdLight: 13
    constexpr static uint8_t lcdRS      = 4;
    constexpr static uint8_t lcdE       = 7;
    constexpr static uint8_t lcdDB4     = 8;
    constexpr static uint8_t lcdDB5     = 12;
    constexpr static uint8_t lcdDB6     = 14;   //A0
    constexpr static uint8_t lcdDB7     = 15;   //A1
    constexpr static uint8_t lcdLight   = 13;

    // Leds configs
    constexpr static uint8_t led1R = 3;
    constexpr static uint8_t led1G = 9;
    constexpr static uint8_t led1B = 0;
    
    constexpr static uint8_t led2R = 6;
    constexpr static uint8_t led2G = 11;
    constexpr static uint8_t led2B = 1;
    
    constexpr static uint8_t led3R = 5;
    constexpr static uint8_t led3G = 10;
    constexpr static uint8_t led3B = 16;    // A2

    // Raw voltage pin
    // See ~/opt/arduino-1.6.6/hardware/arduino/avr/variants/standard/pins_arduino.h
    // A6 = 20
    constexpr static uint8_t voltagePin = 20;

    // Интервал проведения измерений погодных данных
    // 3с = 3000 милисекунд
    constexpr static uint32_t MesureTimeout = 5000;

    // Интервал переиндикации светодиодами состояния батареи
    constexpr static uint32_t LedTimeout = 401;

    // Время долгого удержания кнопки
    // Удержание кнопки в течении этого времени считается долгим
    constexpr static uint16_t longPressTime = 750;

    // Количество хранимых в памяти последних значений с пина, снимающего напряжение на батареи
    // для их последующего усреднения
    constexpr static uint8_t batLastCount = 20;

};