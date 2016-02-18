#include <Pino.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

// Экран
#include "LCDwrapper.h"

// Управление светодиодами
#include "MyRGB.h"
#include "LedBox.h"


// Bmp180 датчик температоуры и давления
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Состаяние аккомулятора
#include "Battery.h"

// Все настройки в.т.ч номера пинов в Configs.h
#include "Configs.h"

    
// Кнопка 
RBD::Button button(Configs::button);
// Время, когда кнопка была нажата
uint32_t buttonStart = 0;

// Измерение значения на вольтметре
Battery bat(Configs::voltagePin);


// Инициализируем объект-экран, передаём использованные 
LCDwrapper lcd(Configs::lcdRS, Configs::lcdE, Configs::lcdDB4, Configs::lcdDB5, Configs::lcdDB6, Configs::lcdDB7, Configs::lcdLight);


// Инициализируем погодный датчик BMP180
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
Adafruit_BMP085 bmp;

// Таймер для имзмерения интервала проведения замеров данных с BMP180
RBD::Timer MesureTimer;

// Таймер для имзмерения интервала обновления индикации светодиодов
RBD::Timer LedTimer;

// Rgb leds
MyRGB led1(Configs::led1R, Configs::led1G, Configs::led1B),
      led2(Configs::led2R, Configs::led2G, Configs::led2B),
      led3(Configs::led3R, Configs::led3G, Configs::led3B);

LedBox leds(led1, led2, led3);


void setup() 
{
    // Настраиваем кнопку в соответствии с нашей схемой подключения
    button.invertReading();
    button.setDebounceTimeout(Configs::buttonDebounce);
    
    if (!bmp.begin()) {
        lcd.setCursor(0, 0);
        lcd.print("Could not find a valid BMP085 sensor, check wiring!");
        while(1);
    }

    // Таймеры для обновления отображаемой информации
    MesureTimer.setTimeout(Configs::MesureTimeout);
    MesureTimer.restart();
    
    LedTimer.setTimeout(Configs::LedTimeout);
    LedTimer.restart();


    // Стартовое отображение информации о погодных данных и состоянии аккомклятора
    lcd.show(bmp, bat);

    // Приветственное моргание светодиодами при включении
    leds.hello();
    leds.on();
    leds.showBat(bat.state().percent());
}

void loop() 
{
    if(button.onPressed()) {
        buttonStart = millis();
    }

    // If was pressed and released
    // Из-за глюка в RBD::Button нужно проверять была ли кнопка предварительно нажата
    if(buttonStart > 0 && button.onReleased()) {
        if( millis() - buttonStart < Configs::longPressTime) {
            lcd.toogleLight();
        } else {
           leds.toogle();
        }
        // Сбрасываем флаг нажатости
        buttonStart = 0;
    }

    if(MesureTimer.onRestart()) {
        // Печатаем погодные данные
        lcd.show(bmp, bat);
    }
    
    if(LedTimer.onRestart()) {
        // Индикация состояния батареи на светодиодах
        leds.showBat(bat.state().percent());
    }
}


