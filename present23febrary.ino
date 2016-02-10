#include <Pino.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

// Экран
#include "LCDwrapper.h"

// Управление светодиодами
#include "MyRGB.h"


// Bmp180 датчик температоуры и давления
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Состаяние аккомулятора
#include "Battery.h"

// Все настройки в.т.ч номера пинов в Configs.h
#include "Configs.h"

    
// Кнопка 
RBD::Button button(Configs::button);

// Измерение значения на вольтметре
Battery bat(Configs::voltagePin);


// Инициализируем объект-экран, передаём использованные 
LCDwrapper lcd(Configs::lcdRS, Configs::lcdE, Configs::lcdDB4, Configs::lcdDB5, Configs::lcdDB6, Configs::lcdDB7, Configs::lcdLight);



// Инициализируем погодный датчик
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
Adafruit_BMP085 bmp;

// Timer
// Таймер для имзмерения интервала проведения замеров данных с BMP180
RBD::Timer MesureTimer;

// Rgb leds
MyRGB led1(Configs::led1R, Configs::led1G, Configs::led1B), 
      led2(Configs::led2R, Configs::led2G, Configs::led2B), 
      led3(Configs::led3R, Configs::led3G, Configs::led3B);




 
void setup() 
{
    // Настраиваем кнопку в соответствии с нашей схемой подключения
    button.invertReading();
    
    
    if (!bmp.begin()) {
        lcd.setCursor(0, 0);
        // печатаем вторую строку
        lcd.print("Could not find a valid BMP085 sensor, check wiring!");
        while(1);
    }

    MesureTimer.setTimeout(Configs::MesureTimeout);
    MesureTimer.restart();


    // Стартовое отображение информации о погодных данных и состоянии аккомклятора
    lcd.show(bmp, bat);


    led1.off().onR();
    led2.off().onG();
    led3.off().onB();

}
 
void loop() 
{

    if(button.onPressed()) {
    }
   
    if(button.onReleased()) {
        lcd.turnLight();
    }

    
    if(MesureTimer.onRestart()) {
        // Печатаем погодные данные
        lcd.show(bmp, bat);
    }
}


