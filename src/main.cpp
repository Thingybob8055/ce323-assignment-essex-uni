#include "main.h"

Timer g_t;
BufferedSerial g_pc(USBTX, USBRX, 115200);

Scheduler g_scheduler;

DigitalOut g_alarm_led(LED1);

// system is initially in UNSET state
alarm_state_t g_alarm_state = UNSET_STATE;

KeypadControl g_keypad_control;

BusOut cols_out(p26, p25, p24); 
BusIn rows_in(p14, p13, p12, p11);

TextLCD g_lcd(p15, p16, p17, p18, p19, p20);

int main() {
    g_t.start();
    
    if(INIT_Tasks() == INIT_FAIL) {
        printf("INIT_Tasks() failed :-(");
        while(1);
    }
    
    while(1) {
        g_scheduler.Run(chrono::duration_cast<chrono::milliseconds>(g_t.elapsed_time()).count());
        wait_us(10000);
    }
}