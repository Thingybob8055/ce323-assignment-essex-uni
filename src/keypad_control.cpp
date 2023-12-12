#include "keypad_control.h"

char KeypadControl::get_key() {
int i,j;
    for (i = 0; i <= 3; i++) {
        cols_out = i;
        
        // for each bit in rows
        for (j = 0; j <= 3; j++) {
            
            // if j'th bit of "rows_in" is LOW
            if (~rows_in & (1 << j)) {
                return this->keytable[j][3-i];
            }
        }
    }
    return ' ';
}

uint16_t KeypadControl::enter_number() {
    
}