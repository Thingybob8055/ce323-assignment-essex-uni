#ifndef KEYPAD_CONTROL_H
#define KEYPAD_CONTROL_H

#include <cstdint>
#include "mbed.h"

// global variables from main.cpp
extern BusOut cols_out;
extern BusIn rows_in;

class KeypadControl
{
private:
// keytable to map the keys on the keypad
const char keytable[4][4] = {
    {'1', '2', '3', 'F'},
    {'4', '5', '6', 'E'},
    {'7', '8', '9', 'D'},
    {'A', '0', 'B', 'C'}
};

public:
char get_key(); // function to get the key pressed on the keypad

};

#endif /* KEYPAD_CONTROL_H */