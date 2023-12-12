#ifndef KEYPAD_CONTROL_H
#define KEYPAD_CONTROL_H

#include <cstdint>
#include "mbed.h"

extern BusOut cols_out;
extern BusIn rows_in;

class KeypadControl
{
private:
    /* data */
const char keytable[4][4] = {
    {'1', '2', '3', 'F'},
    {'4', '5', '6', 'E'},
    {'7', '8', '9', 'D'},
    {'A', '0', 'B', 'C'}
};

public:
char get_key();
uint16_t enter_number();

};

#endif /* KEYPAD_CONTROL_H */