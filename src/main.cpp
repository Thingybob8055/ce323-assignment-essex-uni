#include "main.h"

Timer g_timer;
BufferedSerial g_pc(USBTX, USBRX, 115200);

Scheduler g_scheduler;

DigitalOut g_alarm_led(ALARM_LED);

// system is initially in UNSET state
alarm_state_t g_alarm_state = UNSET_STATE;

KeypadControl g_keypad_control;

BusOut cols_out(KEYPAD_COLS_OUT); 
BusIn rows_in(KEYPAD_ROWS_IN);

TextLCD g_lcd(LCD_PINS);

BusOut g_switch_cs(SWITCH_CS);
BusIn g_switch_reading(SWITCH_READING); //These two are for switches

// mosi, miso (unused really), sclk
SPI g_sw(LEDS_SPI); //For the LEDS, controlled using SPI

DigitalOut lat(LEDS_LATCH);

int main() {
    g_timer.start();
    
    if(INIT_Tasks() == INIT_FAIL) {
        printf("INIT_Tasks() failed :-(");
        while(1);
    }

    INIT_GRLEDs();
    
    while(1) {
        g_scheduler.Run(chrono::duration_cast<chrono::milliseconds>(g_timer.elapsed_time()).count());
        wait_us(10000);
    }
}