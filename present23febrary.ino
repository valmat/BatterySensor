#include <Pino.h>
#include <LiquidCrystal.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

// Управление светодиодами
#include "MyRGB.h"


// Bmp180 датчик температоуры и давления
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Дополнительные символы для LCD
#include "PicBat.h"


#include <math.h>

    
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
    LiquidCrystal lcd(4, 7, 8, 12, 14, 15);

    // Подсветка экрана (включает подсветку через транзистор КТ3102АМ)
    Pino lcdLight(13, Pino::Mode::out);
    // Статус подсветки
    bool lcdLightState = false;

    // Дополнительные символы для LCD
    PicBat glyps(lcd);
    uint8_t TMPVAR = 0; // DEL mE

    
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

    void printFract(/*const*/ LiquidCrystal &lcd, float val)
    {
        val = round(val*10)/10;
        uint8_t fract = round(10*(val - (int)val));

        lcd.print( (int)val );
        lcd.print( '.' );
        lcd.print( (int)fract );
    }
      
     
    void setup() 
    {
        //lcdLight.off();

        button.invertReading();
        
        
        
        // устанавливаем размер (количество столбцов и строк) экрана
        lcd.begin(16, 2);
        // печатаем первую строку
        //lcd.print("\2\3    Time is");
        
                //"1234567890123456
        // устанавливаем курсор в колонку 0, строку 1. То есть на
        // самом деле это вторая строка, т.к. нумерация начинается с нуля
        lcd.setCursor(0, 1);
        lcd.clear();
        // печатаем вторую строку
        //lcd.print("\x14   non-existent!");

        if (!bmp.begin()) {
          lcd.setCursor(0, 0);
          // печатаем вторую строку
          lcd.print("Could not find a valid BMP085 sensor, check wiring!");
          while (1) {}
        }

        MesureTimer.setTimeout(3000);
        MesureTimer.restart();


        /*
        led1.off().onR();
        led2.off().onR();
        led3.off().onR();
        delay(700);
        led1.off().onG();
        led2.off().onG();
        led3.off().onG();
        delay(800);
        led1.off().onB();
        led2.off().onB();
        led3.off().onB();        
        delay(900);
        led1.offB().onR().onG();
        led2.offB().onR().onG();
        led3.offB().onR().onG();
        delay(1100);
        */
        led1.off().onR();
        led2.off().onG();
        led3.off().onB();
        //delay(2000);



            lcd.setCursor(0, 1);

            auto temperature = bmp.readTemperature();
            auto pressure = bmp.readPressure()/133.322368421;
            
            printFract(lcd, temperature);
            lcd.print("\xDF");
            lcd.print("C ");

            //printFract(lcd, pressure);
            lcd.print(round(pressure));
            //lcd.println(" MM PT.CT.");
            lcd.print("MM");


    }
     
    void loop() 
    {
        
        // печатаем вторую строку
        //lcd.print("button presed");
        lcd.setCursor(0, 0);

        if(button.onPressed()) {
          
          //lcd.clear();
          //lcd.print("Button Pressed");
        }
       
        if(button.onReleased()) {
          //lcd.clear();
          //lcd.print("Button Released");

          lcdLightState = !lcdLightState;
          lcdLight.turn(lcdLightState);
        }

        /*
        led1.off().onR();
        led2.off().onR();
        led3.off().onR();
        delay(700);
        led1.off().onG();
        led2.off().onG();
        led3.off().onG();
        delay(800);
        led1.off().onB();
        led2.off().onB();
        led3.off().onB();        
        delay(900);
        led1.offB().onR().onG();
        led2.offB().onR().onG();
        led3.offB().onR().onG();
        delay(1100);
        led1.off().onR();
        led2.off().onG();
        led3.off().onB();
        delay(2000);
        */


        /*
        auto temperature = bmp.readTemperature();
        temperature = round(temperature*10)/10;

        auto pressure = bmp.readPressure()/133.322368421;
        pressure = round(pressure*10)/10;
        
        lcd.setCursor(0, 1);
        //lcd.print("T:");
        lcd.print(temperature);
        lcd.print("*C ");
        
        //lcd.print("P: ");
        lcd.print(pressure);
        lcd.println(" MM PT.CT.");
        */


        
        if(MesureTimer.onRestart()) {

            //lcd.clear();
            // Отображаем состояние аккомулятора
            lcd.setCursor(0, 1);
            
            lcd.print("raw:");
            lcd.print( rawVoltage.read() );
            lcd.print("    ");
            
            //auto pic_nom = millis()%7;
            auto pic_nom = TMPVAR%8;
            
            lcd.setCursor(11, 1);
            lcd.print(pic_nom);

            lcd.setCursor(14, 1);
            glyps.pic(pic_nom);
            TMPVAR++;


            
            
            // Печатаем погодные данные
            lcd.setCursor(0, 0);

            auto temperature = bmp.readTemperature();
            auto pressure = bmp.readPressure()/133.322368421;
            
            lcd.print("T:");
            printFract(lcd, temperature);
            lcd.print("\xDF");
            lcd.print("C    ");

            lcd.setCursor(9, 0);
            //printFract(lcd, pressure);
            glyps.picD();
            lcd.print(":");
            lcd.print(round(pressure));
            //lcd.println(" MM PT.CT.");
            lcd.print("MM  ");
        }



    
    }


