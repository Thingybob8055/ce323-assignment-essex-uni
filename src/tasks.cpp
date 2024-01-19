#include "tasks.h"

std::string input_buffer = "____";

uint8_t incorrect_attempts_counter = 0;

void reset_input_buffer() {
    input_buffer = "____";
}

static bool is_alarm_led_on = true;

// TODO: Set count library
int alarm_led_blink(unsigned long now) {
    // long time_now = chrono::duration_cast<chrono::milliseconds>(g_timer.elapsed_time()).count();
    switch (g_alarm_state) {
        case UNSET_STATE:
            g_alarm_led = 0;
            break;
        case ALARM_STATE:
            // g_alarm_led = 1;
            
            static long previous_time = now;
           //print the now
            printf("now: %ld\n", now);
            //print the previous time
            printf("previous_time: %ld\n", previous_time);
        
            if(now - previous_time >= ALARM_LED_ON_INTERVAL_MS && is_alarm_led_on) {
                g_alarm_led = !g_alarm_led;
                previous_time = now;
                is_alarm_led_on = false;
            }

            break;
        case EXIT_STATE:
            g_alarm_led = !g_alarm_led;
            break;
        default:
            break;
    }

    // pc.write("testFunction called!\n", 21);
    return 1;
}

void keypad_state_switch(bool is_password_correct) {
    if(is_password_correct) {
       if(g_alarm_state == UNSET_STATE) {
            g_alarm_state = EXIT_STATE;
        } else if(g_alarm_state == ALARM_STATE) {
            g_alarm_state = REPORT_STATE;
        }
    } else {
        if(g_alarm_state == UNSET_STATE) {
            g_alarm_led = 1;
            g_alarm_state = ALARM_STATE;
        }
    }
}

int enter_code(unsigned long now) {
    char key = ' ';
    int code = 0;
    if(g_alarm_state == UNSET_STATE || g_alarm_state == ALARM_STATE) {
        key = g_keypad_control.get_key();
        if(key != ' ' && isdigit(key)) {
            //the key gets shifted into the input buffer from right to left
            printf("key: %c\n", key);
            input_buffer[0] = input_buffer[1];
            input_buffer[1] = input_buffer[2];
            input_buffer[2] = input_buffer[3];
            input_buffer[3] = key;
        } else if(key == 'D') {
            reset_input_buffer();
        } else if(key == 'B') {
            //check if there are any '_' in the input buffer
            if(input_buffer.find('_') != std::string::npos) {
                printf("incomplete code\n");
            } else {
                printf("complete code\n");
                code = std::stoi(input_buffer);
                printf("code: %d\n", code);
                if (code == atoi(password.c_str())) {
                    // g_alarm_state = EXIT_STATE;
                    keypad_state_switch(true);
                    reset_input_buffer();
                    incorrect_attempts_counter = 0;
                } else {
                    reset_input_buffer();
                    incorrect_attempts_counter++;
                    if(incorrect_attempts_counter == 3) {
                        keypad_state_switch(false);
                        reset_input_buffer();
                        incorrect_attempts_counter = 0;
                    }
                }
            }
        }
    }
    return 1;
}

int lcd_display(unsigned long now) {
    g_lcd.cls();
    g_lcd.locate(0, 0);
    g_lcd.printf("%s   x%d", alarm_state_map[g_alarm_state], incorrect_attempts_counter);
    g_lcd.locate(0, 1);
    g_lcd.printf("%s", input_buffer.c_str());
    return 1;
}