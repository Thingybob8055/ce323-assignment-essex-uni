#include "keypad_control.h"

char KeypadControl::get_key() {
int i,j;
    for (i = 0; i <= 3; i++) {
        cols_out = i;
        
        // for each bit in rows
        for (j = 0; j <= 3; j++) {
            
            // if j'th bit of "rows_in" is LOW
            if (~rows_in & (1 << j)) {
                // wait till a key is pressed and released before returning
                while (~rows_in & (1 << j)){}
                return this->keytable[j][3-i];
            }
        }
    }
    return ' ';
}