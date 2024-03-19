#ifndef PIN_MAP_H
#define PIN_MAP_H

//Pin definitions go here

/*
                                +----------------------------+
                                |[GND]                 [VOUT]|
                                |[VIN]                   [VU]|
                                |[VB]                   [IF-]|
                                |[NR]                   [IF+]|
                     LEDS_SPI - |[P5]                   [RD-]|
                     LEDS_SPI - |[P6]                   [RD+]|
                     LEDS_SPI - |[P7]                   [TD-]|
                   LEDS_LATCH - |[P8]                   [TD+]|
                                |[P9]                    [D-]|
                                |[P10]                   [D+]|
SWITCH_READING/KEYPAD_ROWS_IN - |[P11]                  [P30]|
SWITCH_READING/KEYPAD_ROWS_IN - |[P12]                  [P29]|
SWITCH_READING/KEYPAD_ROWS_IN - |[P13]                  [P28]|
SWITCH_READING/KEYPAD_ROWS_IN - |[P14]                  [P27]|
                       LCD_RS - |[P15]                  [P26]| - KEYPAD_COLS_OUT/SWITCH_CS
                        LCD_E - |[P16]                  [P25]| - KEYPAD_COLS_OUT/SWITCH_CS
                      LCD_DB4 - |[P17]                  [P24]| - KEYPAD_COLS_OUT/SWITCH_CS
                      LCD_DB5 - |[P18]                  [P23]|
                      LCD_DB6 - |[P19]                  [P22]|
                      LCD_DB7 - |[P20] [L1][L2][L3][L4] [P21]|
                                +----------------------------+
                                     ALARM_LED      
*/

#define ALARM_LED       LED1
#define KEYPAD_COLS_OUT p26, p25, p24
#define KEYPAD_ROWS_IN  p14, p13, p12, p11
#define LCD_PINS        p15, p16, p17, p18, p19, p20
#define SWITCH_CS       p26, p25, p24
#define SWITCH_READING  p14, p13, p12, p11
#define LEDS_SPI        p5, p6, p7
#define LEDS_LATCH      p8

#endif /* PIN_MAP_H */