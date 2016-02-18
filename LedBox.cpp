
#include "LedBox.h"

// Приветственное моргание светодиодами при включении
void LedBox::hello()
{
    uint16_t timeout = 500;

    _led1.off();
    _led2.off();
    _led3.off(); 
    delay(timeout);
    _led1.red();
    delay(timeout);
    _led1.yellow();
    _led2.red();
    delay(timeout);
    _led1.green();
    _led2.yellow();
    _led3.red();
    delay(timeout);
    _led1.blue();
    _led2.green();
    _led3.yellow();
    delay(timeout);
    _led1.purple();
    _led2.blue();
    _led3.green();
    delay(timeout);
    _led1.off();
    _led2.purple();
    _led3.blue();
    delay(timeout);
    _led2.off();
    _led3.purple();
    delay(timeout);
    _led3.off();
    delay(timeout);
    _led1.off();
    _led2.off();
    _led3.off();

}

// отображает состояние батареи в зависимости от процента заряда
void LedBox::showBat(uint8_t percent)
{
    if(!_isOn) return;

    if(percent >= 99) {
        // Идет зарядка
        _led1.blue();
        _led2.blue();
        _led3.blue();
    } else if (percent == 0) {
        // Подано слишком низкое питание
        _led1.purple();
        _led2.purple();
        _led3.purple();
    } else if (percent >= 90) {
        // full
        _led1.green();
        _led2.green();
        _led3.green();
        
        
    } else if (percent < 10) {
        // empty
        _led1.red();
        _led2.red();
        _led3.red();
    } else if (percent < 26 ) {
        _led1.yellow();
        _led2.red();
        _led3.red();
    } else if (percent < 42 ) {
        _led1.yellow();
        _led2.yellow();
        _led3.red();
    } else if (percent < 58 ) {
        _led1.yellow();
        _led2.yellow();
        _led3.yellow();
    } else if (percent < 74 ) {
        _led1.green();
        _led2.yellow();
        _led3.yellow();
    } else  { //if (percent < 90 )
        _led1.green();
        _led2.green();
        _led3.yellow();
    }

}



