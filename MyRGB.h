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
/*    const*/ MyRGB& onR() /*const*/
    {
        // commands are inverted, because my RGB led has common anode
        _r.off();
        _is_on_r = true;
        // You can use commands chain
        return *this;
    }
    // Turn on Green
    /*const*/ MyRGB& onG() /*const*/
    {
        _g.off();
        _is_on_g = true;
        return *this;
    }
    // Turn on Blue
    /*const*/ MyRGB& onB() /*const*/
    {
        _b.off();
        _is_on_b = true;
        return *this;
    }

    // Turn off Red
    /*const*/ MyRGB& offR() /*const*/
    {
        _r.on();
        _is_on_r = false;
        return *this;
    }
    // Turn off Green
    /*const*/ MyRGB& offG() /*const*/
    {
        _g.on();
        _is_on_g = false;
        return *this;
    }
    // Turn off Blue
    /*const*/ MyRGB& offB() /*const*/
    {
        _b.on();
        _is_on_b = false;
        return *this;
    }

    // Turn off all colors
    /*const*/ MyRGB& off() /*const*/
    {
        return offR().offG().offB();
    }
    
    // Turn on all colors
    /*const*/ MyRGB& on() /*const*/
    {
        return onR().onG().onB();
    }

    // turn Red to value
    /*const*/ MyRGB& turnR(bool value) /*const*/
    {
        _r.turn(!value); // commands are inverted, because my RGB led has common anode
        _is_on_r = value;
        return *this;
    }
    // turn Green to value
    /*const*/ MyRGB& turnG(bool value) /*const*/
    {
        _g.turn(!value);
        _is_on_g = value;
        return *this;
    }
    // turn Blue to value
    /*const*/ MyRGB& turnB(bool value) /*const*/
    {
        _b.turn(!value);
        _is_on_b = value;
        return *this;
    }

    // toogle Red
    /*const*/ MyRGB& toogleR() /*const*/
    {
        _is_on_r = !_is_on_r;
        return turnR(_is_on_r);
    }
    // toogle Green
    /*const*/ MyRGB& toogleG() /*const*/
    {
        _is_on_g = !_is_on_g;
        return turnG(_is_on_g);
    }
    // toogle Blue
    /*const*/ MyRGB& toogleB() /*const*/
    {
        _is_on_b = !_is_on_b;
        return turnB(_is_on_b);
    }


private:
    
    bool _is_on_r = true;
    bool _is_on_g = true;
    bool _is_on_b = true;

    const Pino _r;
    const Pino _g;
    const Pino _b;

};



