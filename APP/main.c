#include "../HAL/SW/SW.h"





int main()
{
    while (1)
    {
        if(SW1_ispressed())
        {
            printf("True");
        }
        else  printf("False");
    }
    
}