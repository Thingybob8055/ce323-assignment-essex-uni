#include "tasks.h"

std::string input_buffer = "____"; // buffer to store the input from the keypad

// buffer to store the top and bottom line of the lcd display
std::string top_lcd_line_buffer = "\0";
std::string bottom_lcd_line_buffer = "\0";

uint8_t incorrect_attempts_counter = 0; // counter to keep track of the number of incorrect attempts

uint8_t stored_error_value = 0; // store the error value when the alarm is triggered (switches)

// reset the input buffer
void reset_input_buffer() {
    input_buffer = "____";
}

static bool is_alarm_led_on = true; // flag to keep track of the alarm led state
bool reset_previous_time = false; // reset the previous time in the alarm state

// set the initial alarm state conditions
void set_intial_alarm_state() {
    g_alarm_led = 1;
    is_alarm_led_on = true;
    reset_previous_time = true;
}

bool reset_exit_state_previous_time = false; // reset the previous time in the exit state

bool reset_entry_state_previous_time = false; // reset the previous time in the entry state

uint8_t switches = 0; // read the switches value (polling)

bool has_entered_entry_state = false; // flag to keep track when the system has entered the entry state

int state_handler(unsigned long now) {
    switch (g_alarm_state) {
        case UNSET_STATE:
            g_alarm_led = 0;  // turn off the alarm led
            break;
        case ALARM_STATE:
            static long previous_time = now;

            // reset the previous time in the alarm state
            if (reset_previous_time == true) {
                previous_time = now;
                reset_previous_time = false;
            }

            // non blocking delay to turn off the alarm led after a certain interval
            if(now - previous_time >= ALARM_LED_ON_INTERVAL_MS && is_alarm_led_on) {
                g_alarm_led = !g_alarm_led;
                previous_time = now;
                is_alarm_led_on = false;
            }

            break;
        case EXIT_STATE:

            if (switches > 0) {
                set_intial_alarm_state(); // set the initial alarm state conditions
                stored_error_value = switches;
                g_alarm_state = ALARM_STATE; // change the state to alarm state
                break;
            }

            static long exit_previous_time = now;

            if (reset_exit_state_previous_time == true) {
                exit_previous_time = now;
                reset_exit_state_previous_time = false;
            }

            // non blocking delay to change the state to set state after a certain interval
            // and if no switches are activated
            if(now - exit_previous_time >= EXIT_INTERVAL_MS) {
                if(switches == 0)
                    g_alarm_state = SET_STATE;
                exit_previous_time = now;
            }

            g_alarm_led = !g_alarm_led; // blink the alarm led
            break;
        case SET_STATE:
            g_alarm_led = 0;  // turn off the alarm led

            // if the switches are greater than 128 (first switch is activated)
            if (switches >= 128) {
                reset_entry_state_previous_time = true;
                has_entered_entry_state = true;
                g_alarm_state = ENTRY_STATE;
            
            // else if the switches are between 64 and 127 (last 7 switches)
            } else if (switches > 0 && switches < 128) {
                set_intial_alarm_state();
                stored_error_value = switches;
                g_alarm_state = ALARM_STATE;
            }
            break;

        case ENTRY_STATE:
            // if just entered the entry state and switches are greater than 0
            if (switches > 0 && has_entered_entry_state == false) {
                set_intial_alarm_state();
                stored_error_value = switches;
                g_alarm_state = ALARM_STATE;
                break;
            }

            // if already in entry state and switches are greater than 128
            if (switches > 128 && has_entered_entry_state == true) {
                set_intial_alarm_state();
                stored_error_value = switches;
                g_alarm_state = ALARM_STATE;
                break;
            }
            // door is closed after in entry state
            if(switches == 0 && has_entered_entry_state == true) {
                has_entered_entry_state = false;
            }

            static long entry_previous_time = now;

            if (reset_entry_state_previous_time == true) {
                entry_previous_time = now;
                reset_entry_state_previous_time = false;
            }

            // non blocking delay to change the state to set state after a certain interval
            if(now - entry_previous_time >= ENTRY_INTERVAL_MS) {
                set_intial_alarm_state();
                stored_error_value = 0;
                g_alarm_state = ALARM_STATE;
                break;
            }

            g_alarm_led = !g_alarm_led; // blink the alarm led
            break;

        case REPORT_STATE:
            g_alarm_led = 0; // turn off the alarm led
            break;
        default:
            break;
    }
    return 1;
}

// utility function to get the triggered zones by bitshifting the stored error value
std::string get_triggered_zones() {
    std::vector<int> indices;
    for (unsigned int i = 0; i < 8; i++) {
        if (stored_error_value & (1 << i)) {
            indices.push_back(i+1);
        }
    }
    // convert vector to a comma separated string
    std::string indices_str = "";
    for (unsigned int i = 0; i < indices.size(); i++) {
        indices_str += std::to_string(indices[i]);
        if (i != indices.size() - 1) {
            indices_str += ",";
        }
    }
    // return the string
    if(indices_str == "")
        return "Invalid Code";
    else
        return indices_str;
}

// switch the alarm state based on the password entered
void keypad_state_switch(bool is_password_correct) {
    if(is_password_correct) {
       if(g_alarm_state == UNSET_STATE) {
            reset_exit_state_previous_time = true;
            g_alarm_state = EXIT_STATE;
        } else if(g_alarm_state == ALARM_STATE) {
            g_alarm_state = REPORT_STATE;
        } else if(g_alarm_state == EXIT_STATE || g_alarm_state == ENTRY_STATE) {
            g_alarm_state = UNSET_STATE;
        } else if (g_alarm_state == REPORT_STATE) {
            g_alarm_state = UNSET_STATE;
        }
    } else {
        if(g_alarm_state == UNSET_STATE || g_alarm_state == EXIT_STATE || g_alarm_state == ENTRY_STATE) {
            set_intial_alarm_state();
            stored_error_value = 0;
            g_alarm_state = ALARM_STATE;
        }
    }
}

// utility function to count the number of digits in a string
uint8_t no_of_digits_in_string(std::string str) {
    int count = 0;
    for(unsigned int i = 0; i < str.length(); i++) {
        if(isdigit(str[i]))
            count++;
    }
    return count;
}

// utility function to replace the digits in a string with '*'
std::string replace_with_asterisk(std::string str) {
    for(unsigned int i = 0; i < str.length(); i++) {
        if(isdigit(str[i]))
            str[i] = '*';
    }
    return str;
}

// update the bottom lcd line buffer based on the alarm state
void bottom_lcd_line_buffer_update() {
    if(g_alarm_state != REPORT_STATE) {
        int count = no_of_digits_in_string(input_buffer);
        if(count == 0) {
            bottom_lcd_line_buffer = "\0";
        } else if (count < 4) {
            bottom_lcd_line_buffer = replace_with_asterisk(input_buffer);
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
    if(g_alarm_state != SET_STATE) {
        key = g_keypad_control.get_key();
        if(key != ' ' && isdigit(key)) {
            //the key gets shifted into the input buffer from right to left
            printf("key: %c\n", key);
            if(input_buffer_index < 4)
                input_buffer[input_buffer_index++] = key;
        } else if(key == 'C') {
            // delete the last character in the input buffer and replace it with '_'
            if (g_alarm_state == REPORT_STATE) {
                keypad_state_switch(true);
            } 
            else if (input_buffer_index > 0) {
                input_buffer[--input_buffer_index] = '_'; // replace the last character with '_'
            }
        } else if(key == 'B') {
            //check if there are any '_' in the input buffer
            if(input_buffer.find('_') != std::string::npos) {
                printf("incomplete code\n");
            } else {
                input_buffer_index = 0; // reset the input buffer index
                printf("complete code\n");
                code = std::stoi(input_buffer);
                printf("code: %d\n", code);
                if (code == atoi(password.c_str())) {
                    keypad_state_switch(true);
                    reset_input_buffer(); // reset the input buffer if correct password
                    incorrect_attempts_counter = 0; // reset the incorrect attempts counter
                } else {
                    reset_input_buffer();
                    if(g_alarm_state != ENTRY_STATE && g_alarm_state != ALARM_STATE)
                        incorrect_attempts_counter++; // increment the incorrect attempts counter
                    if(incorrect_attempts_counter == 3) {
                        keypad_state_switch(false);
                        reset_input_buffer();
                        incorrect_attempts_counter = 0; // reset the incorrect attempts counter
                    }
                }
            }
        }
    }
    return 1;
}

// update the top lcd line buffer based on the alarm state and the number of incorrect attempts
// along with calculating the number of spaces to be added to the end of the alarm state string
void top_lcd_line_buffer_update() {
    if(g_alarm_state != REPORT_STATE) {
        unsigned int length = alarm_state_map[g_alarm_state].length();
        // calculate the number of spaces to be added to the end of the alarm state string
        unsigned int no_of_spaces = (total_no_of_char - length) - 2;
        // add the spaces to the end of the alarm state string
        top_lcd_line_buffer = alarm_state_map[g_alarm_state] + std::string(no_of_spaces, ' ');
        if (g_alarm_state == UNSET_STATE || g_alarm_state == EXIT_STATE) {
            top_lcd_line_buffer = alarm_state_map[g_alarm_state] + std::string(no_of_spaces, ' ') + 
            std::string("x") + std::to_string(incorrect_attempts_counter);
        }
    } else {
        top_lcd_line_buffer = "E:" + get_triggered_zones();
    }
}

// update the lcd display based on the top and bottom lcd line buffers
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

// convert the switch value to the led combination value for the red/green leds
int led_convert(int switch_val) //takes parameter the switch value calculated from the teachers switch code
{
    int led_out = 0; //led output value
    for(int i = 7; i>=0; i--) {
        led_out = (led_out << 2) + 2 - ((switch_val>>i) & 1);
    }
    return led_out; //returns the led_out for led combination value.
}

// task to read the switches value using polling and SPI
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