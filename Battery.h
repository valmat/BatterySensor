/*
 *
 * class Battery
 * Состаяние аккомулятора
 *
 */
#pragma once

#include <Pino.h>
#include <math.h>

// Forward declaration
class Battery;

// Все вычесленные данные батареи
class BatteryState
{
public:
    // Copy constructor
    BatteryState( const BatteryState& ) = default;
    // Move constructor
    BatteryState ( BatteryState && ) = default;

    // Возвращает сырые данные с пина
    uint16_t raw() const
    {
        return _rawValue;
    }

    // измеряемое напряжение на пине
    float mesVoltage() const
    {
        return _mesVoltage;
    }

    // Вычисляемое напряжение батареи
    float calcVoltage() const
    {
        return _calcVoltage;
    }

    // Проценты
    uint8_t percent() const
    {
        //
        // Расчеты ведутся в соответствии с предоставленным производителем графиком
        // зависимости уровня заряда от напряжения на аккомуляторе
        //
        if(_calcVoltage < 12.0) {
            return 0;
        } else if (_calcVoltage > 14.5) {
            return 100;
        }

        //
        // Далее считаем, что
        // 12.0 <= calcVoltage <= 14.5
        // 

        // Коэфициенты прямой
        float lA, lB;

        if(_calcVoltage < 12.4) {
            lA = linefunA(12.0, 12.4, 0, 10);
            lB = linefunB(12.0, 12.4, 0, 10);
        } else if (_calcVoltage < 12.8) {
            lA = linefunA(12.4, 12.8, 10, 20);
            lB = linefunB(12.4, 12.8, 10, 20);
        } else if (_calcVoltage < 12.9) {
            lA = linefunA(12.8, 12.9, 20, 30);
            lB = linefunB(12.8, 12.9, 20, 30);
        } else if (_calcVoltage < 13.0) {
            lA = linefunA(12.9, 13.0, 30, 40);
            lB = linefunB(12.9, 13.0, 30, 40);
        } else if (_calcVoltage < 13.1) {
            lA = linefunA(13.0, 13.1, 40, 50);
            lB = linefunB(13.0, 13.1, 40, 50);
        } else if (_calcVoltage < 13.2) {
            lA = linefunA(13.1, 13.2, 50, 60);
            lB = linefunB(13.1, 13.2, 50, 60);
        } else if (_calcVoltage < 13.3) {
            lA = linefunA(13.2, 13.3, 60, 70);
            lB = linefunB(13.2, 13.3, 60, 70);
        } else if (_calcVoltage < 13.4) {
            lA = linefunA(13.3, 13.4, 70, 80);
            lB = linefunB(13.3, 13.4, 70, 80);
        } else if (_calcVoltage < 14.0) {
            lA = linefunA(13.4, 14.0, 80, 90);
            lB = linefunB(13.4, 14.0, 80, 90);
        } else { //if (_calcVoltage <= 14.5)
            lA = linefunA(14.0, 14.5, 90, 100);
            lB = linefunB(14.0, 14.5, 90, 100);
        }

        return round(lA * _calcVoltage + lB);
    }


private:

    // priate constructor. Only Battery can create this object
    // @rawValue Значение на пине от 0 до 1024
    BatteryState(uint16_t rawValue):
        _rawValue(rawValue),
        // измеряемое напряжение на пине
        _mesVoltage(vvcVoltage * _rawValue / 1024.0),
        // Вычисляемое напряжение батареи
        _calcVoltage(diodeVoltage + resist * _mesVoltage)

    {
        // измеряемое напряжение на пине
        //_mesVoltage  = vvcVoltage * _rawValue / 1024.0;
        // Вычисляемое напряжение батареи
        //_calcVoltage = diodeVoltage + resist * _mesVoltage;
    }

    // Для вычисления процентов нам нужно будет уравнение прямой
    // y(x) = (y2-y1)/(x2-x1) * x + (y1*x2 - y2*x1)/(x2-x1)
    // и коэфициенты уравнения прямой:
    // y(x) = A *x + B
    // Вычисление коэфициентов на этапе компиляции намного эффективнее 
    constexpr static float linefunA(float x1, float x2, float y1, float y2)
    {
        return (y2-y1)/(x2-x1);
    }
    constexpr static float linefunB(float x1, float x2, float y1, float y2)
    {
        return (y1*x2 - y2*x1)/(x2-x1);
    }

    //
    // Константы:
    //
    // Напряжение питания ардуины.
    constexpr static float vvcVoltage = 5.0;

    // Напряжение питания ардуины.
    constexpr static uint16_t pinResolution = 1024;

    // Падение напряжения на защитном диоде
    // Расчетное значение 0.503
    // Путем колибровки получено значение 0.503
    constexpr static float diodeVoltage = 0.503;

    // Коэфициент преобразования определяемый резисторами делителя напряжения
    // Расчетное значение 3.0
    // Путем колибровки получено значение 3.0534
    constexpr static float resist = 3.0534;


    //
    // Переменные:
    //
    // Значение на пине от 0 до 1024
    uint16_t _rawValue;
    // измеряемое напряжение на пине
    float _mesVoltage;
    // Вычисляемое напряжение батареи
    float _calcVoltage;

    friend class Battery;
};


class Battery
{
public:
    // Constructors
    // @voltagePin номер пина, на котором производятся измерения
    Battery(uint8_t voltagePin): _pin(voltagePin)
    {}

    // Copy constructor
    Battery( const Battery& ) = default;
    // Move constructor
    Battery ( Battery && ) = default;

    BatteryState state() const
    {
        return BatteryState(_pin.read());
    }

private:

    Pino _pin;

};