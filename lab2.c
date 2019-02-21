/*  Names: Reagan Wilcox, Julia Meissner, Galilea Olvera
    Section: 4
    Date: 2/1/2019
    File name: LAB 2
*/

#include <c8051_SDCC.h> //include files. This file is available online
#include <stdio.h>
#include <stdlib.h>
 
//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Port_Init(void);      // Initialize ports for input and output
void Timer_Init(void);     // Initialize Timer 0 
void Interrupt_Init(void); //Initialize interrupts
void Timer0_ISR(void) __interrupt 1; //Initialize Timer Interrupt Service 
int random(int n); //generates random number
int blinks(void); 
unsigned char leds(void);
void ADC_Init(void);
void TurnOff(void);
int read_and_scale(int n, unsigned char low, unsigned char high);
void blink_LED(int lednum, int times);
int a;
void game(void);
unsigned char read_AD_input(unsigned char n);




//###### Add all of our functions ########

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
//Port 1
/*MIDDLE PIN OF POTENTIOMETER MUST BE CONNECTED TO P1.1 = pin 13 #########*/

//Port 2
__sbit __at 0xA0 PB0; //29; Pushbutton 0
__sbit __at 0xA1 PB1; //30; Pushbutton 1
__sbit __at 0xA2 PB2; //27; Pushbutton 2
__sbit __at 0xA3 PB3; //28; Pushbutton 3
__sbit __at 0xA4 SS0; //24; Slide switch 0
__sbit __at 0xA5 SS1; //25; Slide switch 1
//__sbit __at 0xA6 POT; //22; Potentiometer **INCORRECTUMUNDO: should be in P1.1**

//Port 3
__sbit __at 0xB0 BILED0; //38; BILED 0
__sbit __at 0xB1 BILED1; //37;BILED 1
__sbit __at 0xB2 LED0; //35; LED0
__sbit __at 0xB3 LED1; //36; LED1
__sbit __at 0xB4 LED2; //33; LED2
__sbit __at 0xB5 LED3; //34; LED3

unsigned int counts;     //TIME
int turn;                //8 cycle sequences per game
unsigned int score;      //print at the end of each game
char game_sequence[8][2]; // OR we can do one "array" that repeats the LED # however many times it needs to blink
char responce[8][2];
unsigned int mode;      //keeps track of user-inputted mode
//unsigned char AD1_1;    //AD value on P1.1
unsigned int delay_counts; //counts per delay period
unsigned int blink_counts; //counts per blink period (50% on, 50% off)
unsigned char seed;
int blink_counter;
char scorer;
int i;
int index;
unsigned char answer;
char x;
char j;



/*************************/
void main(void)
{
    Sys_Init();      // System Initialization
    Port_Init();     // Initialize ports 2 and 3 
    Interrupt_Init();
    Timer_Init();    // Initialize Timer 0 
    putchar(' ');    // the quote fonts may not copy correctly into SiLabs IDE
    
 
    while (1)
    {
        printf("\r\nBrief description of game\r\n");
        printf("Start\r\n");
    
        //ensure initial conditions of LEDS and BILED
        TurnOff();
        
        //set random seed for each game
        printf("Press any Key for Randomization \r\n");
        seed = getchar();
        srand(seed);
        
        //AD1_1 = read_AD_input(1);  //Read  A/D value on P1.1
        
        
        /*SET DEFAULT VALUES*/
        blink_counts = 56;
        delay_counts = 337;
    
        //read switches to see what game mode the user chooses
        printf("Select a game mode by moving the slide switches\r\n");
        while (PB0) //loop cotinues until pushbutton0 is pressed
        {
			
            if (SS0 && !SS1)       //switch 0 flipped
            {
                printf("Mode 1 selected\r");
                mode = 1;
                if (!PB0)
				{
					break;
				} //Wait for PB0 to be released
			}
            
            else if (!SS0 && SS1)    //switch 1 flipped
			{
                printf("Mode 2 selected\r");
                mode = 2;
                if (!PB0)
				{
					break;
				} //Wait for PB0 to be released

            }
            
            else if (SS0 && SS1)    //switches 0 and 1 flipped
            {
                printf("Mode 3 selected\r");
                mode = 3;
                if (!PB0)
				{
					break;
				} //Wait for PB0 to be released

            }
            
            else                    //no switches flipped
            {
                printf("No mode selected\r");
                mode = 0;
                if (!PB0)
				{
					break; //Wait for PB0 to be released 
				}             
            }
		}

        /*if you're here, pushbotton0 was pressed*/
        
        if (mode == 0) //restart because no mode was selected
        {
            printf("No mode selected. Restart and select a game mode.");
        }
            //delay ?
        /***********MODE 1***********/
		else if (mode == 1) //enact mode 1 for 8 turns
		{
			while(1)
			{
	                printf("Mode 1:\r\n\rA random sequence will light LEDs. Match the sequence by\r\n\rpressing the corresponding pushbuttons\r\n\rHigh Score Wins!\r\n");
					printf("Press Push Button 0 to start\r\n");
	                i = 0;
					score = 0;
					TurnOff();
					game();
					if (!PB0)
					{
						printf("Loooooooooooooooool\r\n");
						while (i < 9)
						{
						index = 0;
							while (index <= i)
							{
								if (game_sequence[index][0] == 0)
								{
									blink_LED(0,game_sequence[index][1]);
								}

								else if (game_sequence[index][0] == 1)
								{
									blink_LED(1,game_sequence[index][1]);
								}

								else if (game_sequence[index][0] == 2)
								{
									blink_LED(2,game_sequence[index][1]);
								}

								else if (game_sequence[index][0] == 3)
								{
									blink_LED(3,game_sequence[index][1]);
								}

								index ++;

								BILED0 = 1;

							}
							index = 0;

							while (index <= i)
							{
								counts = 0;
						
							//responce = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
								for (x = 0; x < 8; ++x)
									{
										//responce[x] = 0;
										for (j = 0; j<2; ++j)
										{
											responce[x][j] = 0;
										}


									}
								if (!PB0 || !PB1 || !PB2 || !PB3)
								{
								blink_counter = 0;
									while (blink_counter <= game_sequence[index][1])
									{
										counts = 0;
										while (counts <= 667)
										{
											if (!PB0)
											{
											responce[index][0] = 0;
											responce[index][1] += 1;

											}
											if (!PB1)
											{
											responce[index][0] = 1;
											responce[index][1] += 1;

											}
											if (!PB2)
											{
											responce[index][0] = 2;
											responce[index][1] += 1;

											}
											if (!PB3)
											{
											responce[index][0] = 3;
											responce[index][1] += 1;

											}
										}
										counts = 0;
										while(counts <= 337)
										{
											LED0 = 1;
											LED1 = 1;
											LED2 = 1;
											LED3 = 1;
										}
										TurnOff();
										scorer = 0;
										while(scorer <= index)
										{
											if ((game_sequence[index][0] == responce[index][0]) && (game_sequence[index][1] == responce[index][1]))
											{
												score ++;
											}
											else
											{
												BILED1 = 1;
												counts = 0;
												while( counts <= 337 )
												{}
												BILED1 = 0;
											}

										scorer ++;
										}


										blink_counter ++;
								
								
									}
						
									
									
								  
								  	
								
							

								}

							}
							printf("Your score is %d /r/n", score);


						}
						printf("Do you want to play again? y if yes, n if no /r/n");
						answer = getchar('');
						if (answer == 110)
						{
							break;
						}
					}  
				}
			}
            
            /***********MODE 2***********/
            if (mode == 2) //enact mode 2 for 8 turns
            {
                printf("Mode 2:\r\n\rPlayer 1 will create a sequence by pressing pushbuttons. Then, the LEDs will \r\n\rbe lit, and Player 2 will match the sequence by pressing the corresponding pushbuttons");
             
            } //end mode 2
            
            /***********MODE 3***********/
            if (mode == 3) //enact mode 3 for 8 turns
            {
                printf("Mode 3:\r\n\rset the blink frequency by adjusting the potentiometer. When finished, press pushbutton0\r\n\rthen, set the delay period by adjusting the potentiometer.\r\n\r");
                TurnOff();
                counts = 0;
                while (1) //set blink rate
	
                {
					printf("%d", read_AD_input(1));
					
                    blink_counts = read_and_scale(1, 0.05, 1.0); //convert blink period from 0.05 to 1.0 seconds
					printf("%d", blink_counts);
                    while (counts <= blink_counts/2) //on for half of blink time
                    {
                        LED0 = 1;
                    }
                    
                    while (counts <= blink_counts) //off for half of blink time
                    {
                        LED0 = 0;
                    }
					if (!PB0)
					{
						break;
					}
                }
                blink_counts = blink_counts;
                counts = 0;

    
                while (PB0) //set delay time
                {
                    delay_counts = read_and_scale(1, 1, 8); //convert delay period from 1.0 to 8.0 seconds
                    while (counts <= 169) //LED on for 0.5 seconds
                    {
                        LED0 = 1;
                    }
                    
                    while (counts <= 169 + delay_counts) //led off for delay period
                    {
                        LED0 = 0;
                    }
                }
                delay_counts = delay_counts;
                
                blink_LED(LED0, 4);
                   
            } //end mode 3
        }
   
}

/***********************/
void Port_Init(void) //Do not touch
{
    P1MDIN &= ~0x02;     //Set analog pin 1.1 to 0 (0000 0010)
    P1MDOUT &= ~0x02;     //Set analog pin 1.1 to 0
    P1 |= 0x02;          //Set impedance of analog pin 1.1 to 1
    
    P2MDOUT &= 0xC0;    //Set Port 2 bits 0-6 to input (1100 0000)
    P2 |= ~0xC0;        //High impedance mode

    P3MDOUT |= 0x3F;    //Set Port 3 bits 0-5 to output (0011 1111)
}

/***********************/
void Interrupt_Init(void) //Do not touch
{
    IE |= 0x02;         // enable Timer0 Interrupt request (by masking)
    EA = 1;             // enable global interrupts (by sbit)
}

/***********************/
void Timer_Init(void) //Do not touch
{
    CKCON |= 0x08;      // Timer0 uses SYSCLK as source
    TMOD &= 0xFC;       // clear the 4 least significant bits
    //TMOD |= 0x01;     // Timer0 in mode 1 -> 16 bits
    TR0 = 0;            // Stop Timer0
    TMR0 = 0;           // Clear high & low byte of T0
}
 

/***********************/
void Timer0_ISR(void) __interrupt 1
{
    TF0 = 0;            //interrupt code
    counts++;           //increment global counts variable
}
 

/***********************/
void ADC_Init(void) //Do not touch
{
    REF0CN = 0x03; /* Set Vref to use internal reference voltage (2.4V) */
    ADC1CN = 0x80; /* Enable A/D converter (ADC1) */
    ADC1CF |= 0x01; /* Set A/D converter gain to 1 */
}

/***********************/
unsigned char read_AD_input(unsigned char n) // Do not touch
{
    AMX1SL = n; /* Set P1.n as the analog input for ADC1 */
    //LAB SAYS AMuX1SL ##error ??
    ADC1CN = ADC1CN & ~0x20; /* Clear the “Conversion Completed” flag */
    ADC1CN = ADC1CN | 0x10; /* Initiate A/D conversion */
    while ((ADC1CN & 0x20) == 0x00); /* Wait for conversion to complete */
    return ADC1; /* Return digital value in ADC1 register */
}
 
/***********************LAB-2-SPECIFIC FUNCTIONS***********************/

/***********************/
/*Turn off all LEDs and BILED*/
/***********************/
void TurnOff(void)
{
    LED0 = 1; LED1 = 1; LED2 = 1; LED3 = 1;
    BILED0 = 0; BILED1 = 0;
}

/***********************/
/*MODE 3 ONLY read the potentiometer at P1.n and scale the value to return counts linear to time low and high*/
/***********************/
int read_and_scale(int n, unsigned char low, unsigned char high)
{
    unsigned char AD = read_AD_input(n);
    unsigned char V = AD*2.4/256;
    unsigned char counts = ((((high - low)*V/2.4) + low) * 337);
    return counts;
}

/***********************/
/*return a random integer number between n and 3*/
/***********************/
int random(int n)
{
    return (rand()%(3-n) + n);   // rand returns a random number between 0 and 32767. 
                                // if n = 0, return number 0-3, if n = 1, return number 1-3
}

/***********************/
/*compare given answer to the desired value and light BILED*/
/***********************/
int compare(int correct, int user)
{
	if (correct == user)
	{
		int current_count = counts; //we don't want to reset the counts
    		while (counts < current_count + 337)
		    {
			BILED0 = 1;
			correct = 1;
		    }
		BILED0 = 0;
		}

	else
	{
		int current_count = counts; //we don't want to reset the counts
    		while (counts < current_count + 337)
		    {
			BILED1 = 1;
			correct = 0;
		    }
		BILED1 = 0;
	}
	return correct;

}

/***********************/
/*blink a specified LED the desired number of times at the rate set by Mode 3.*/
/***********************/
void blink_LED(int lednum, int times) //rate is a global variable so we don't need to pass it through the function
{
	//myled = the LED you want to blink (ie. LED0) ###is unsigned char correct for this???####
	//times = number of times you want it to blink
	counts = 0 ;
	for (a = 0; a <= times; a+=1)
	{
		while (counts <= blink_counts/2 )
		{
			if (lednum == 0)
			{
				LED0 = 1;
			}
			else if (lednum == 1)
			{
				LED1 = 1;
			}
			else if (lednum == 2)
			{
				LED2 = 1;
			}
			else if (lednum == 2)
			{
				LED3 = 1;
			}
		}
		while (counts <= blink_counts )
		{
			if (lednum == 0)
			{
				LED0 = 0;
			}
			else if (lednum == 1)
			{
				LED1 = 0;
			}
			else if (lednum == 2)
			{
				LED2 = 0;
			}
			else if (lednum == 2)
			{
				LED3 = 0;
			}
        	}
    	}
	counts = 0;
	while (counts <= delay_counts - (blink_counts/2))
	{
		if (lednum == 0)
		{
			LED0 = 0;
		}
		else if (lednum == 1)
		{
			LED1 = 0;
		}
		else if (lednum == 2)
		{
			LED2 = 0;
		}
		else if (lednum == 2)
		{
			LED3 = 0;
		}
	}
} 

/***********************/
/*flash the BiLED red for 1 s when an incorrect sequence has been entered.*/
/***********************/
void incorrect(void)
{
    int current_count = counts; //we don't want to reset the counts
    while (counts < current_count + 337)
    {
        BILED1 = 1;
    }
    BILED1 = 0;
}

/*******************/
//store each sequence of LEDS and blinks in an array    
/*******************/
void game (void)
{
	int b = 0;
	int blink = random(1);
	int led = random(0);
	while (b<9)
	{
		if (led == 0)
        {
            game_sequence[b][0] = 0;
            game_sequence[b][1] = blink;
		

        }
        if (led == 1)
        {
		 	game_sequence[b][0] = 1;
            game_sequence[b][1] = blink;
		
        }
        if (led == 2)
        {
		 	game_sequence[b][0] = 2;
            game_sequence[b][1] = blink;
		
        }
        if (led == 3)
        {
             game_sequence[b][0] = 3;
             game_sequence[b][1] = blink;
        }
		
		b++;
	}
}

/***********************/

