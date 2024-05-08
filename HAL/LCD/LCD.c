#include "LCD.h"


void LCD_init(void)
{
    DIO_vPORTINIT('B');
    DIO_vSETPINDIR('B',LCD_DB4_PIN_ID,DIO_OUTPUT);
    DIO_vSETPINDIR('B',LCD_DB5_PIN_ID,DIO_OUTPUT);
    DIO_vSETPINDIR('B',LCD_DB6_PIN_ID,DIO_OUTPUT);
    DIO_vSETPINDIR('B',LCD_DB7_PIN_ID,DIO_OUTPUT);

    DIO_vSETPINDIR('B',LCD_RS_PIN_ID,DIO_OUTPUT);
    DIO_vSETPINDIR('B',LCD_RW_PIN_ID,DIO_OUTPUT);
    DIO_vSETPINDIR('B',LCD_EN_PIN_ID,DIO_OUTPUT);
    SysTick_Wait(100);

    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
    LCD_sendCommand(LCD_CLEAR_COMMAND);
    LCD_sendCommand(LCD_CURSOR_OFF);

}

void LCD_sendCommand (uint8 command)
{
    DIO_vWRITEPIN('B',LCD_RS_PIN_ID,DIO_LOW);
    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_HIGH);
    SysTick_Wait(100);

    DIO_vWRITEPIN('B',LCD_DB4_PIN_ID,command >> 4 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB5_PIN_ID,command >> 5 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB6_PIN_ID,command >> 6 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB7_PIN_ID,command >> 7 & 0x01);

    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_LOW);

    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_HIGH);
    SysTick_Wait(100);

    command = command << 4;

    DIO_vWRITEPIN('B',LCD_DB4_PIN_ID,command >> 4 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB5_PIN_ID,command >> 5 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB6_PIN_ID,command >> 6 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB7_PIN_ID,command >> 7 & 0x01);


    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_LOW);
    SysTick_Wait(100);
}

void LCD_displayCharacter(uint8 data)
{
    DIO_vWRITEPIN('B',LCD_RS_PIN_ID,DIO_HIGH);
    DIO_vWRITEPIN('B',LCD_RW_PIN_ID,DIO_LOW);

    DIO_vWRITEPIN('B',LCD_DB4_PIN_ID,data >> 4 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB5_PIN_ID,data >> 5 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB6_PIN_ID,data >> 6 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB7_PIN_ID,data >> 7 & 0x01);

    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_HIGH);
    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_LOW);

    data = data << 4;

    DIO_vWRITEPIN('B',LCD_DB4_PIN_ID,data >> 4 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB5_PIN_ID,data >> 5 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB6_PIN_ID,data >> 6 & 0x01);
    DIO_vWRITEPIN('B',LCD_DB7_PIN_ID,data >> 7 & 0x01);


    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_HIGH);
    SysTick_Wait(100);
    DIO_vWRITEPIN('B',LCD_EN_PIN_ID,DIO_LOW);

}

void LCD_displayString(uint8 *str)
{
    uint8 i = 0;
    while (str[i] != '\0')
    {
        LCD_displayCharacter(str[i]);
        i++;
    }
    

}

void LCD_clearScreen(void)
{
    LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_integerToString(float64 data)
{
    uint8 i[11] = {0};
    int8 counter = 0;

    if (((int32)data) <0)
    {
        LCD_displayCharacter('-');
        data *= -1;
    }
    do
    {

        i[counter] = (uint32)data%10;
        data /= 10;
        counter++;


    } while ((uint32)data != 0);
    counter--;
    for (; counter >=0 ; counter--)
    {
        LCD_displayCharacter(i[counter]+48);
    }
    

}

void LCD_moveCursor(uint8 row,uint8 col)
{
    uint8 Address = 0;

    if ( (  (row == 0) || (row == 1)  ) && (  (col >=0 ) && (col <=15)  ))
    {
        switch (row)
        {
        case 0:
            Address = col;
            break;
        case 1:
            Address = col + 0x40;
            break;
        default:
            break;
        }
        LCD_sendCommand(Address + 128);
    }
}

