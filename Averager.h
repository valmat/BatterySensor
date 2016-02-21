/*
 *
 * Averager - усреднитель
 *
 */

#pragma once

template<uint16_t total>
class Averager
{
public:
    // Constructors
    Averager() {}

    // Copy constructor
    Averager( const Averager& ) = delete;
    // Move constructor
    Averager ( Averager && ) = delete;

    // Добавляет новый элемент
    void add(uint16_t val)
    {
        if(total == _count) {
            // Когда массив заполнен полностью
            // Сдвигаем все влево
            for(uint8_t i = 0; i < total-1; i++) {
                _arr[i] = _arr[i+1];
            }
            _arr[total-1] = val;
        } else {
            // На стадии заполнения
            _arr[_count] = val;
            _count++;
        }
    }

    // Возвращает среднее
    uint16_t get() const
    {
        if (0 == _count) {
            return 0;
        }
        uint32_t sum = 0;
        for(uint8_t i = 0; i < _count; i++) {
            sum +=_arr[i];
        }
        // Возвращаем округленное до целого среднее
        return (uint16_t)(0.5 + 1.0*sum/_count);
    }

private:
    uint8_t _count =0;
    uint16_t _arr[total];
};