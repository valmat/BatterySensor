#include <Pino.h>

// Все настройки в.т.ч номера пинов в Configs.h
#include "Configs.h"


#include <RBD_Timer.h>
#include <RBD_Button.h>

// Управление светодиодами
#include "MyRGB.h"
#include "LedBox.h"


// Bmp180 датчик температоуры и давления
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Состаяние аккомулятора
#include "Battery.h"

using MyBattery = Battery<Configs::batLastCount>;

// Экран
#include <LiquidCrystal.h>

 // Дополнительные символы для LCD
#include "MyGlyps.h"

#include "LCDwrapper.h"

