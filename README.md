# Lab2
dying? yes


1 second = 674 counts

FUNCTIONS#########################################
void TurnOff(void);		
//turns off all LEDs and BILEDs
int read_and_scale (int n, unsigned char low, unsigned char high);
//reads P1.n and scales that voltage input between value low and high
unsigned char random(int n);
	//returns a random number between n and 3
int compare(int correct, int user)
	//blinks green BILED if PB(user) is pressed for LED(correct)
	//blinks red BILED if if user =/= correct for 0.5 seconds
	//returns 1 if correct, 0 if incorrect
void blink_LED(char myled, int times)
	//blinks LED with the name myled times times
int game(unsigned int blinks, unsigned int led, unsigned int i)
	//stores each sequence of LEDS in an array
	//for reagan’s mode


//do not touch 
void Port_Init(void);
void Interrupt_Init(void);
void Timer_Init(void);
void ADC_Init(void);
unsigned char read_AD_input(unsigned char n);


