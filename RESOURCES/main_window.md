# APP.c

# Includes

# Functions 
    1-
    2-

# Main _ Initializations 
    gpio_portf_init
    systick_init
    uart0_pc_init
    uart1_gps_init
    EEPROM_init
    LCD_init


    lon_lat 2d array
    distance = 0 
    
# While 1 

    # if ((distance < 100) and (sw1 not pressed) and (pc donot send W)){
        gps get lon & lat > add to array
        Wait to next gps fix time
        harvsine (distance , lon , lat )   or harvsine (array)
    }else {
        save array to eeprom
        distance =0
    }
    
    if pc sent U { send array by uart 0 to pc }
