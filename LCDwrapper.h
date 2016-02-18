/*
 *
 * class LCDwrapper
 * Обертка над LiquidCrystal для удобного отображения на экране
 * и избежания засорения кода 
 *
 */
#pragma once


class LCDwrapper
{
public:
    // Constructors
    LCDwrapper(uint8_t rs,uint8_t e,uint8_t db4,uint8_t db5,uint8_t db6,uint8_t db7, uint8_t led):
        _lcd(rs, e, db4, db5, db6, db7),
        _lcdLight(led, Pino::Mode::out),
        _glyps(_lcd)
    {
        // устанавливаем размер (количество столбцов и строк) экрана
        _lcd.begin(16, 2);
        _lcd.clear();

        // Сразу же включаем подсветку
        _lcdLight.on();
    }

    // Copy constructor
    LCDwrapper( const LCDwrapper& ) = default;
    // Move constructor
    LCDwrapper ( LCDwrapper && ) = default;

    // Отображает необходимую информацию
    void show(Adafruit_BMP085 &bmp, MyBattery &bat);

    LCDwrapper& setCursor(uint8_t row, uint8_t col)
    {
        _lcd.setCursor(row, col);
        return *this;
    }

    // Печатает строку на экране
    template<typename T>
    LCDwrapper& print(T val)
    {
        _lcd.print(val);
        return *this;
    }

    // переключает подсветку экрана в другое состояние
    void toogleLight()
    {
        _lcdLightState = !_lcdLightState;
        _lcdLight.turn(_lcdLightState);
    }

    // Печатает значек батареи в зависимости от процента заряда
    void picBat(uint8_t percent);



private:

    void printFract(float val, uint8_t pow = 1);
    uint16_t pow10(uint8_t pow);


    // объект-экран
    LiquidCrystal _lcd;
    
    // Подсветка экрана (включает подсветку через транзистор КТ3102АМ)
    Pino _lcdLight;
    
    // Статус подсветки
    bool _lcdLightState = true;
    
    // Дополнительные символы для LCD
    MyGlyps _glyps;
};