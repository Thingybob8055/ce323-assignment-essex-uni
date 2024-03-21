#include "main.h"

Timer g_timer;  //Timer object
BufferedSerial g_pc(USBTX, USBRX, 115200);  //Serial object

Scheduler g_scheduler; //Scheduler object

DigitalOut g_alarm_led(ALARM_LED);  //Alarm LED

// system is initially in UNSET state
alarm_state_t g_alarm_state = UNSET_STATE;  //global comtext to keep track of the system state

KeypadControl g_keypad_control;  //Keypad object

BusOut cols_out(KEYPAD_COLS_OUT); // coloums of the keypad
BusIn rows_in(KEYPAD_ROWS_IN); // read the rows of the keypad

TextLCD g_lcd(LCD_PINS);  //LCD display object

BusOut g_switch_cs(SWITCH_CS);  //chip select for switches, controlled using SPI
BusIn g_switch_reading(SWITCH_READING); //These two are for switches

// mosi, miso (unused really), sclk
SPI g_sw(LEDS_SPI); //For the LEDS, controlled using SPI

DigitalOut lat(LEDS_LATCH);

int main() {
    g_timer.start();  // start the timer
    
    // initialise the tasks and the red/green LEDs
    if(INIT_Tasks() == INIT_FAIL) {
        printf("INIT_Tasks() failed :-(");
        while(1);
    }

    INIT_GRLEDs();
    
    while(1) {
        // run the scheduler
        g_scheduler.Run(chrono::duration_cast<chrono::milliseconds>(g_timer.elapsed_time()).count());
        wait_us(10000);
    }
}