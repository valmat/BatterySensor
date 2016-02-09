#include <Pino.h>
#include <LiquidCrystal.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

#include "MyRGB.h"


// Bmp180
#include <Wire.h>
#include <Adafruit_BMP085.h>


#include <math.h>
     
    // Инициализируем объект-экран, передаём использованные 
    // для подключения контакты на Arduino в порядке:
    // RS, E, DB4, DB5, DB6, DB7
    /*
    RS  4
    E   7
    DB4 8
    DB5 12
    DB6 14
    DB7 15
    */
    LiquidCrystal lcd(4, 7, 8, 12, 14, 15);

    RBD::Button button(2);

    Pino lcdLight(13, Pino::Mode::out);
    bool lcdLightState = false;

    
    // Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
    // Connect GND to Ground
    // Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
    // Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
    // EOC is not used, it signifies an end of conversion
    // XCLR is a reset pin, also not used here
    
    Adafruit_BMP085 bmp;

    // Timer
    // Таймер для имзмерения интервала проведения замеров данных с BMP180
    RBD::Timer MesureTimer;

    // Rgb leds
    MyRGB led1(3,9,0), led2(5,10,16), led3(6,11,1);

    byte mychr[8]   = {B00010,  B00100,  B01000,  B11111,  B00010,  B00100,  B01000,  B00000};
    byte rozha_l[8] = {B00000,  B01000,  B00000,  B00001,  B00000,  B01000,  B00110,  B00001};
    byte rozha_r[8] = {B00000,  B00010,  B00000,  B10000,  B00000,  B00010,  B01100,  B10000};


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
        
        lcd.createChar(1, mychr);
        lcd.createChar(2, rozha_l);
        lcd.createChar(3, rozha_r);

        
        
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
        lcd.print("\x14   non-existent!");

        if (!bmp.begin()) {
          lcd.setCursor(0, 0);
          // печатаем вторую строку
          lcd.print("Could not find a valid BMP085 sensor, check wiring!");
          while (1) {}
        }

        MesureTimer.setTimeout(3000);
        MesureTimer.restart();


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

            // Отображаем состояние аккомулятора
            lcd.setCursor(0, 1);
            
            // Печатаем погодные данные
            lcd.setCursor(0, 0);

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



    
    }


