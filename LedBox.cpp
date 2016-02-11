
#include "LedBox.h"

// Приветственное моргание светодиодами при включении
void LedBox::hello()
{
    uint16_t timeout = 500;

    _led1.on();
    _led2.on();
    _led3.on();
    delay(timeout);
    _led1.off().onR();
    delay(timeout);
    _led1.offB().onR().onG();
    _led2.off().onR();
    delay(timeout);
    _led1.off().onG();
    _led2.offB().onR().onG();
    _led3.off().onR();
    delay(timeout);
    _led1.off().onB();
    _led2.off().onG();
    _led3.offB().onR().onG();
    delay(timeout);
    _led1.offG().onR().onB();
    _led2.off().onB();
    _led3.off().onG();
    delay(timeout);
    _led1.off();
    _led2.offG().onR().onB();
    _led3.off().onB();
    delay(timeout);
    _led2.off();
    _led3.offG().onR().onB();
    delay(timeout);
    _led3.off();
    delay(timeout);
    _led1.on();
    _led2.on();
    _led3.on();

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
        _led1.orange();
        _led2.red();
        _led3.red();
    } else if (percent < 42 ) {
        _led1.orange();
        _led2.orange();
        _led3.red();
    } else if (percent < 58 ) {
        _led1.orange();
        _led2.orange();
        _led3.orange();
    } else if (percent < 74 ) {
        _led1.green();
        _led2.orange();
        _led3.orange();
    } else  { //if (percent < 90 )
        _led1.green();
        _led2.green();
        _led3.orange();
    }

}



