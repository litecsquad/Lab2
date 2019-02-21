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
	for (turn = 0; turn < 7; ++turn) //goes on to build rest of the sequence
	{
		while (button) //when pushbutton released, light up corresponding LED for 1 second
        {
            blinks_LED(led, 1);
        }

        while(counts < 674) //wait 1 second for potentiometer to determine number of blinks
        {
            while (PB0 & PB1 & PB2 & PB3) //if NO pushbutton is pressed, determine # of blinks with potentiometer
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
		
		game[turn] = {led, blinks};
		
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
    }
    while(counts < 674) //turn on all LEDs for one second to confirm that sequences has been created
    {
        LED0 = 1; LED1 = 1; LED2 = 1; LED3 = 1;
    }
}
