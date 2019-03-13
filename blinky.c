#include<stdint.h>
#include<stdbool.h>
#include "driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include "inc/hw_memmap.h"

unsigned long counter;


int main()
{
    unsigned long PINJ1,PINJ0;

    /*set the system clock*/
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480 ,120000000);

    /*Enable clock to PORTN*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Enable and wait for the port to be ready for access
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    /*Enable clock to PORTJ*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    // Enable and wait for the port to be ready for access
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }
    /*CONFIGURE PIN0,1 PORTN AS OUTPUT*/
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_0 | GPIO_PIN_1  );
    /*CONFIGURE PIN0,1 PORTN AS INPUT*/
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
    /*SET UP PULL UP RESISTOR ON PINS 0,1 PORTJ*/
    GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1 , GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);

       /*WRITE ZERO TO PINS 0,1 , TWO LED ARE OFF IN THE BEGINNING*/
    GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 | GPIO_PIN_1,0x00);

    while(1)
    {
        /*READ THE SWITCH VALUE*/
        PINJ0=GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0);
        if(PINJ0 == 0x00)  // THE SWITCH PRESSED
        {
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 | GPIO_PIN_1,0x01); /* THE D1 LED IS ON*/
        }
        /*READ THE SWITCH VALUES*/
        PINJ1=GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1);

        if(PINJ1 == 0x00)// THE SWITCH PRESSED
        {

            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 | GPIO_PIN_1,0x02);/* THE D2 LED IS ON*/
        }

    }
}
