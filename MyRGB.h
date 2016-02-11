/*
 *
 * MyRGB.h - библиотека для управления RGB светодиодом с общим анодом.
 * Функционал в пределах необходимого мне.
 *
 */

#pragma once

#include <Pino.h>


class MyRGB
{
public:
    // Constructors
    MyRGB(const Pino &r, const Pino &g, const Pino &b) : _r(r), _g(g), _b(b) {}
    MyRGB(Pino &&r, Pino &&g, Pino &&b) : _r(r), _g(g), _b(b) {}
    MyRGB(uint8_t rn, uint8_t gn, uint8_t bn) : _r(rn, Pino::Mode::out), _g(gn, Pino::Mode::out), _b(bn, Pino::Mode::out) {}

    // Copy constructor
    MyRGB( const MyRGB& ) = default;
    // Move constructor
    MyRGB ( MyRGB && ) = default;

    // Turn on Red
    MyRGB& onR()
    {
        // commands are inverted, because my RGB led has common anode
        _r.off();
        _is_on_r = true;
        // You can use commands chain
        return *this;
    }
    // Turn on Green
    MyRGB& onG()
    {
        _g.off();
        _is_on_g = true;
        return *this;
    }
    // Turn on Blue
    MyRGB& onB()
    {
        _b.off();
        _is_on_b = true;
        return *this;
    }

    // Turn off Red
    MyRGB& offR()
    {
        _r.on();
        _is_on_r = false;
        return *this;
    }
    // Turn off Green
    MyRGB& offG()
    {
        _g.on();
        _is_on_g = false;
        return *this;
    }
    // Turn off Blue
    MyRGB& offB()
    {
        _b.on();
        _is_on_b = false;
        return *this;
    }

    // Turn off all colors
    MyRGB& off()
    {
        return offR().offG().offB();
    }
    
    // Turn on all colors
    MyRGB& on()
    {
        return onR().onG().onB();
    }

    // turn Red to value
    MyRGB& turnR(bool value)
    {
        // commands are inverted, because my RGB led has common anode
        _r.turn(!value); 
        _is_on_r = value;
        return *this;
    }
    // turn Green to value
    MyRGB& turnG(bool value)
    {
        _g.turn(!value);
        _is_on_g = value;
        return *this;
    }
    // turn Blue to value
    MyRGB& turnB(bool value)
    {
        _b.turn(!value);
        _is_on_b = value;
        return *this;
    }

    // toogle Red
    MyRGB& toogleR()
    {
        _is_on_r = !_is_on_r;
        return turnR(_is_on_r);
    }
    // toogle Green
    MyRGB& toogleG()
    {
        _is_on_g = !_is_on_g;
        return turnG(_is_on_g);
    }
    // toogle Blue
    MyRGB& toogleB()
    {
        _is_on_b = !_is_on_b;
        return turnB(_is_on_b);
    }

    //
    // показывать только определенный цвет
    //
    MyRGB& red()
    {
        return onR().offG().offB();
    }
    MyRGB& green()
    {
        return offR().onG().offB();
    }
    MyRGB& blue()
    {
        return offR().offG().onB();
    }
    MyRGB& yellow()
    {
        return onR().onG().offB();
    }
    MyRGB& purple()
    {
        return onR().offG().onB();
    }
    


private:
    
    bool _is_on_r = true;
    bool _is_on_g = true;
    bool _is_on_b = true;

    const Pino _r;
    const Pino _g;
    const Pino _b;

};



