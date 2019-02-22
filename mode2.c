//MODE 2 VARIABLES://

int game_sequence[8][2] =  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

unsigned int blinks; // assigned with potentiometer for game_sequence array
unsigned char led; // LED picked with PBs for game_sequence array
unsigned char button; // determines what PB pushed to light up corresponding LED


/**************
FUNCTIONS USED IN MODE 2:
TurnOff();
blink_LED();
***************/


/*********  MAIN MODE 2 CODE  ****************/

void main(void)
{
	Sys_Init();      // System Initialization
        Port_Init();     // Initialize ports 2 and 3 
        Interrupt_Init();
        Timer_Init();    // Initialize Timer 0 
	putchar(' ');    // the quote fonts may not copy correctly into SiLabs IDE
	//ADC Initialization included later on
	
    TurnOff(); //MAKE SURE ALL LEDs turned off
	// MODE 2 INSTRUCTIONS //
    printf("\r\nMode 2 Selected");
    printf("\r\nPlayer 1 creates game sequence for Player 2.\r\nPush any button to begin your sequence\r\n");

    //CHOOSE FIRST LED IN SEQUENCE//
    if(!PB0)
        {
            button = PB0;
            led = 0;
        }
    else if (!PB1)
        {
            button = PB1;
            led = 1;
        }
    else if (!PB2)
        {
            button = PB2;
            led = 2;
        }
    else if (!PB3)
        {
            button = PB3;
            led = 3;
		}
	for (turn = 0; turn < 7; turn++) //goes on to build rest of the sequence (TURN ++ OR ++TURN???)
	{
        counts = 0;
        TR0 = 0;
        TR0 = 1;
        TMR0 = 0;

        while (!button); 
		while (button) //ONCE pushbutton released, light up corresponding LED for 1 second
        {
            blinks_LED(led, 1);
        }

        while(counts < 674) //wait 1 second for potentiometer to determine number of blinks
        {
            while (!PB0 && !PB1 && !PB2 && !PB3);
            while (PB0 && PB1 && PB2 && PB3) //if NO pushbutton is pressed, determine # of blinks with potentiometer
            {
                ADC_Init(); //initiate potentiometer, returns ADC1 from 0 - 255
                (ADC1)%= 3;

                if(ADC1 == 0)
                {
                    blinks_LED(0,1);
                    blinks = 1;
                }
                else if(ADC1 == 1)
                {
                    blinks_LED(0, 1); blinks_LED(1,1); /* MAKE FUNCTION FOR MULTIPLE LEDs??? */
                    blinks = 2;
                }
                else if(ADC1 == 2)
                {
                    blinks_LED(0, 1); blinks_LED(1,1); blinks_LED(2,1);
                    blinks = 3;
                }
            }
        }
		
	TurnOff();	
        counts = 0;
        TR0 = 0;
        TR0 = 1;
        TMR0 = 0;

		game_sequence[turn] = {led, blinks};
		
		if (!PB0) //determine next LED in sequence
		{
			button = PB0;
			led = 0;
		}
		else if(!PB1)
		{
			button = PB1;
			led = 1;
		}
		else if(!PB2)
		{
			button = PB2;
			led = 2;
		}
		else if (!PB3)
		{
			button = PB3;
			led = 3;
		}
		TurnOff();
    }
    /* END OF for LOOP*/
    while(counts < 674) //turn on all LEDs for one second to confirm that sequences has been created.
    {

        LED0 = 0; LED1 = 0; LED2 = 0; LED3 = 0;

    }
TurnOff();
}
