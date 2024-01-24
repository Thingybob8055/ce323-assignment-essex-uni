#include "tasks.h"

std::string input_buffer = "____";

std::string top_lcd_line_buffer = "\0";
std::string bottom_lcd_line_buffer = "\0";

uint8_t incorrect_attempts_counter = 0;

void reset_input_buffer() {
    input_buffer = "____";
}

static bool is_alarm_led_on = true;
bool reset_previous_time = false;

void set_intial_alarm_state() {
    g_alarm_led = 1;
    is_alarm_led_on = true;
    reset_previous_time = true;
}

bool reset_exit_state_previous_time = false;

bool reset_entry_state_previous_time = false;

int switches = 0;
// long last_previous_time = 0;
bool has_entered_entry_state = false;

int state_handler(unsigned long now) {
    // long time_now = chrono::duration_cast<chrono::milliseconds>(g_timer.elapsed_time()).count();
    switch (g_alarm_state) {
        case UNSET_STATE:
            g_alarm_led = 0;
            break;
        case ALARM_STATE:
            // g_alarm_led = 1;
            
            static long previous_time = now;

            printf("now: %ld\n", now);

            printf("previous_time: %ld\n", previous_time);
            // printf("last_previous_time: %ld\n", last_previous_time);

            if (reset_previous_time == true) {
                previous_time = now;
                reset_previous_time = false;
            }

            if(now - previous_time >= ALARM_LED_ON_INTERVAL_MS && is_alarm_led_on) {
                g_alarm_led = !g_alarm_led;
                previous_time = now;
                // last_previous_time = now;
                is_alarm_led_on = false;
            }

            break;
        case EXIT_STATE:

            if (switches > 0) {
                set_intial_alarm_state();
                g_alarm_state = ALARM_STATE;
                break;
            }

            // non delay wait just like in the alarm state
            static long exit_previous_time = now;

            printf("now: %ld\n", now);

            printf("exit_previous_time: %ld\n", exit_previous_time);

            if (reset_exit_state_previous_time == true) {
                exit_previous_time = now;
                reset_exit_state_previous_time = false;
            }

            if(now - exit_previous_time >= EXIT_INTERVAL_MS) {
                if(switches == 0)
                    g_alarm_state = SET_STATE;
                exit_previous_time = now;
            }

            g_alarm_led = !g_alarm_led;
            break;
        case SET_STATE:
            g_alarm_led = 0;
            if (switches >= 128) {
                reset_entry_state_previous_time = true;
                has_entered_entry_state = true;
                g_alarm_state = ENTRY_STATE;
            } else if (switches >= 64 && switches < 128) {
                set_intial_alarm_state();
                g_alarm_state = ALARM_STATE;
            }
            break;

        case ENTRY_STATE:
            if (switches > 0 && has_entered_entry_state == false) {
                set_intial_alarm_state();
                g_alarm_state = ALARM_STATE;
                break;
            }

            if (switches > 128 && has_entered_entry_state == true) {
                set_intial_alarm_state();
                g_alarm_state = ALARM_STATE;
                break;
            }
            // door is closed after in entry state
            if(switches == 0 && has_entered_entry_state == true) {
                has_entered_entry_state = false;
            }

            static long entry_previous_time = now;

            printf("now: %ld\n", now);

            printf("entry_previous_time: %ld\n", entry_previous_time);

            if (reset_entry_state_previous_time == true) {
                entry_previous_time = now;
                reset_entry_state_previous_time = false;
            }

            if(now - entry_previous_time >= ENTRY_INTERVAL_MS) {
                set_intial_alarm_state();
                g_alarm_state = ALARM_STATE;
                break;
            }

            g_alarm_led = !g_alarm_led;            
            break;

        case REPORT_STATE:
            g_alarm_led = 0;
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
            reset_exit_state_previous_time = true;
            g_alarm_state = EXIT_STATE;
        } else if(g_alarm_state == ALARM_STATE) {
            g_alarm_state = REPORT_STATE;
        } else if(g_alarm_state == EXIT_STATE || g_alarm_state == ENTRY_STATE) {
            g_alarm_state = UNSET_STATE;
        }
    } else {
        if(g_alarm_state == UNSET_STATE || g_alarm_state == EXIT_STATE || g_alarm_state == ENTRY_STATE) {
            set_intial_alarm_state();
            g_alarm_state = ALARM_STATE;
        }
    }
}

uint8_t no_of_digits_in_string(std::string str) {
    int count = 0;
    for(unsigned int i = 0; i < str.length(); i++) {
        if(isdigit(str[i]))
            count++;
    }
    return count;
}

void bottom_lcd_line_buffer_update() {
    if(g_alarm_state != REPORT_STATE) {
        int count = no_of_digits_in_string(input_buffer);
        if(count == 0) {
            bottom_lcd_line_buffer = "\0";
        } else if (count < 4) {
            bottom_lcd_line_buffer = input_buffer;
        } else if (count == 4) {
            bottom_lcd_line_buffer = "Press B to set";
        }
    } else {
        bottom_lcd_line_buffer = "Press C to clear";
    }
}

int enter_code(unsigned long now) {
    static int input_buffer_index = 0;
    char key = ' ';
    int code = 0;
    if(g_alarm_state == UNSET_STATE || g_alarm_state == ALARM_STATE || g_alarm_state == EXIT_STATE || g_alarm_state == ENTRY_STATE) {
        key = g_keypad_control.get_key();
        if(key != ' ' && isdigit(key)) {
            //the key gets shifted into the input buffer from right to left
            printf("key: %c\n", key);
            if(input_buffer_index < 4)
                input_buffer[input_buffer_index++] = key;
        } else if(key == 'C') {
            // reset_input_buffer();
            // delete the last character in the input buffer and replace it with '_'
            if(input_buffer_index > 0) {
                input_buffer[--input_buffer_index] = '_';
            }
        } else if(key == 'B') {
            input_buffer_index = 0; // reset the input buffer index
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
                    if(g_alarm_state != ENTRY_STATE)
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

void top_lcd_line_buffer_update() {
    // g_lcd.printf("%s   x%d", alarm_state_map[g_alarm_state], incorrect_attempts_counter);
    // get string length of the alarm state string
    if(g_alarm_state != REPORT_STATE) {
        unsigned int length = alarm_state_map[g_alarm_state].length();
        // calculate the number of spaces to be added to the end of the alarm state string
        unsigned int no_of_spaces = (total_no_of_char - length) - 2;
        // add the spaces to the end of the alarm state string
        top_lcd_line_buffer = alarm_state_map[g_alarm_state] + std::string(no_of_spaces, ' ');
        if (g_alarm_state == UNSET_STATE || g_alarm_state == EXIT_STATE) {
            top_lcd_line_buffer = alarm_state_map[g_alarm_state] + std::string(no_of_spaces, ' ') + std::string("x") + std::to_string(incorrect_attempts_counter);
        }
    } else {
        top_lcd_line_buffer = "CODE ERROR: 1";
    }
}

int lcd_display(unsigned long now) {
    top_lcd_line_buffer_update();
    bottom_lcd_line_buffer_update();

    g_lcd.cls();
    g_lcd.locate(0, 0);
    g_lcd.printf("%s", top_lcd_line_buffer.c_str());

    g_lcd.locate(0, 1);
    g_lcd.printf("%s", bottom_lcd_line_buffer.c_str());
    return 1;
}

int led_convert(int switch_val) //takes parameter the switch value calculated from the teachers switch code
{
    int led_out = 0; //led output value
    for(int i = 7; i>=0; i--) {
        led_out = (led_out << 2) + 2 - ((switch_val>>i) & 1);
    }
    return led_out; //returns the led_out for led combination value.
}

int read_switches(unsigned long now) {
    g_switch_cs = 4;
    switches = g_switch_reading;
    g_switch_cs = 5;
    switches= (switches << 4) + g_switch_reading;
    printf("Switches = %d\r\n", switches);
    
    g_sw.write( ( led_convert(switches) ) ); 
    lat = 1;
    lat = 0;
    return 1;
}

// used to change the state of the system using the serial monitor for testing and debugging
int cmd_state_change(unsigned long now) {
    // take input from serial monitor
    char cmd = ' ';
    if(g_pc.readable()) {
        g_pc.read(&cmd, sizeof(cmd));
        printf("cmd: %c\n", cmd);
        if(cmd == '0') {
            g_alarm_state = UNSET_STATE;
        } else if(cmd == '1') {
            reset_exit_state_previous_time = true;
            g_alarm_state = EXIT_STATE;
        } else if(cmd == '2') {
            g_alarm_state = SET_STATE;
        } else if(cmd == '3') {
            reset_entry_state_previous_time = true;
            has_entered_entry_state = true;
            g_alarm_state = ENTRY_STATE;
        } else if(cmd == '4') {
            set_intial_alarm_state();
            g_alarm_state = ALARM_STATE;
        } else if(cmd == '5') {
            g_alarm_state = REPORT_STATE;
        } else if (cmd == '6') {
            switches = 1;
        }
    }
    return 1;
}