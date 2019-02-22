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


else if(mode == 2) //enact mode 2 for 8 turns
{
	while(1)
	{
		TurnOff(); //MAKE SURE ALL LEDs turned off
		printf("\r\nMode 2 Selected");
		printf("\r\nPlayer 1 creates game sequence for Player 2.\r\nPush any button to begin your sequence\r\n");
		
		while(1)
		{
			result = read_AD_input(1); //returns ADC1 from 0 - 255
		}
		
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
		for (i = 0; i< 7; i++) //goes on to build rest of the sequence
		{
			counts = 0;
			TR0 = 0;
			TR0 = 1;
			TMR0 = 0;
			//BOUNCE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
			while (!button);
			while (button) //ONCE pushbutton released, light up corresponding LED for 1 second
			{
				blink_LED(led, 1);
			}
			while(counts < 674) //wait 1 second for potentiometer to determine number of blinks
			{
				//BOUNCE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!//
				while (!PB0 && !PB1 && !PB2 && !PB3);
				while (PB0 && PB1 && PB2 && PB3) //if NO pushbutton is pressed, determine # of blinks with potentiometer
				{
					(result)%= 3;
					if(result == 0)
					{
						blink_LED(0,1);
						blinks = 1;
					}
					else if(result == 1)
					{
						blink_LED(0, 1); blink_LED(1,1); /* MAKE FUNCTION FOR MULTIPLE LEDs??? */
						blinks = 2;
					}
					else if(result == 2)
					{
						blink_LED(0, 1); blink_LED(1,1); blink_LED(2,1);
						blinks = 3;
					}
				}
			}
			counts = 0;
			TR0 = 0;
			TR0 = 1;
			TMR0 = 0;
			
			game_sequence[i][0] = led;
			game_sequence[i][1] = blinks;
			
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
		/* END OF for LOOP*/
		while(counts < 674) //turn on all LEDs for one second to confirm that sequences has been created.
		{
			LED0 = 0; LED1 = 0; LED2 = 0; LED3 = 0;
		}
		for(x = 0; x <= 8; x++)
		{
			printf("%u %u \r\n",game_sequence[x][0], game_sequence[x][1]);
		}

	}//end while loop
} //end mode 2 loop
/*END OF MODE 2*/
				
				
