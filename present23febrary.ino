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


    
    // Кнопка 
    RBD::Button button(2);

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
    LCDwrapper lcd(4, 7, 8, 12, 14, 15, 13);


    
    // Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
    // Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
    Adafruit_BMP085 bmp;

    // Timer
    // Таймер для имзмерения интервала проведения замеров данных с BMP180
    RBD::Timer MesureTimer;

    // Rgb leds
    MyRGB led1(3,9,0), led2(5,10,16), led3(6,11,1);

    // Измерение значения на вольтметре
    Pino rawVoltage(A6);

     
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

        MesureTimer.setTimeout(3000);
        MesureTimer.restart();


        led1.off().onR();
        led2.off().onG();
        led3.off().onB();
        //delay(2000);




        lcd.show(bmp ,rawVoltage);


    }
     
    void loop() 
    {
        
        // печатаем вторую строку
        //lcd.print("button presed");
        //lcd.setCursor(0, 0);

        if(button.onPressed()) {
          
          //lcd.clear();
          //lcd.print("Button Pressed");
        }
       
        if(button.onReleased()) {
          //lcd.clear();
          //lcd.print("Button Released");


          lcd.turnLight();
        }







        
        if(MesureTimer.onRestart()) {
            // Печатаем погодные данные
            lcd.show(bmp ,rawVoltage);
        }



    
    }


