#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    uint8_t boosterS1history = 1;
    uint8_t boosterS2history = 1;
    // Declare the variables that main uses to interact with your state machine.
    bool boosterS1state = false;
    bool boosterS2state = false;


    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired())
        {
            count0 ++;
        }
        // If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if(timer1Expired())
        {
            boosterS1history = boosterS1history << 1;
            boosterS1history |= checkStatus_BoosterpackS1();
            boosterS2history = boosterS2history << 1;
            boosterS2history |= checkStatus_BoosterpackS2();
        }


        // Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        boosterS1state = fsmBoosterpackButtonS1(boosterS1history);
        boosterS2state = fsmBoosterpackButtonS1(boosterS2history);
        // If a completed, debounced button press has occurred, increment count1.
        if(boosterS1state == true)
        {
            count1 ++;
        }
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    switch(count % 8)
    {
    case 0:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 1:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 2:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 3:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 4:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 5:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 6:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case 7:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    default:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    }
}

// Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    switch(count % 8)
        {
        case 0:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 1:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 2:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 3:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 4:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 5:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 6:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        case 7:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        default:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
            break;
        }
}

// Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(uint8_t buttonhistory)
{
    bool pressed = false;
    if(buttonhistory == 0x00)
    {
        return pressed;
    }
    if(buttonhistory == 0xff)
    {
        return pressed;
    }
    pressed = true;
    return pressed;
}
