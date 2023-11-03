#include "main.h"

Timer g_t;
BufferedSerial g_pc(USBTX, USBRX, 115200);

Scheduler g_scheduler;

uint8_t g_state_1 = 0;
uint8_t g_state_2 = 0;
uint8_t g_state_3 = 0;
uint8_t g_state_4 = 0;

DigitalOut g_myled(LED1);
DigitalOut g_myled2(LED2);
DigitalOut g_myled3(LED3);
DigitalOut g_myled4(LED4);

// system is initially in UNSET state
alarm_state_t g_alarm_state = UNSET_STATE;

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