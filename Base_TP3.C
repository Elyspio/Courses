//------------------------------------------------------------------------------------
// Base_TP3_IRC
//------------------------------------------------------------------------------------
//
// AUTH: FJ
// DATE: 03-03-2009
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h> // SFR declarations

//------------------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//------------------------------------------------------------------------------------
sfr16 TMR3RL = 0x92; // Timer3 reload value
sfr16 TMR3 = 0x94;   // Timer3 counter
sfr16 ADC0 = 0xbe;   // ADC0 data
sfr16 ADC0GT = 0xc4; // ADC0 greater than window
sfr16 ADC0LT = 0xc6; // ADC0 less than window
sfr16 RCAP2 = 0xca;  // Timer2 capture/reload
sfr16 T2 = 0xcc;	 // Timer2
sfr16 RCAP4 = 0xe4;  // Timer4 capture/reload
sfr16 T4 = 0xf4;	 // Timer4
sfr16 DAC0 = 0xd2;   // DAC0 data
sfr16 DAC1 = 0xd5;   // DAC1 data

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400 //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

extern code char Sin_table[];

// El�ments pr�sents sur la carte 8051F020
sbit LED = P1 ^ 6; // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;  // Bouton Poussoir '1' relach�, '0' press�

// El�ments de l'application Pilotage d'un syst�me de tri
sbit Tst4 = P3 ^ 4;
sbit Tst5 = P3 ^ 5;
sbit Tst6 = P3 ^ 6;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void);		  // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void wait(unsigned int milli);
void exBtnPoussoir();
void exTimer();
void exTimerInterrupt();
void confT2();
void exo5();

int refresh_rate = 1000;
int timer_count = 0;

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void)
{
	Init_Device();

	putchar('c');
	
	exo5();
}

void T2wait20ms()
{
	confT2();
	while (TF2 == 0)
	{
	}
	return;
}

void exo5()
{
	
	// Config LED 
	TR2 = 1;
	P1MDOUT |= 1 << 6;

	BP = 1;
	P3MDOUT &= ~(1 << 7);

	Tst4 = 0;
	LED = LED_Off;
	
	// Config Btn
	//P3IF |= (1 << 7);
	P3IF &= ~(1 << 7);
	P3IF &= ~(1 << 3);

	EIE2 |= (1 << 5);
	EIP2 |= (1 << 5);

	IT0 = 1;


	
	confT2();
	
	while (1)
	{}
}

void confT2()
{
	TF2 = 0;
	EXF2 = 0;
	RCLK0 = 0;
	TCLK0 = 0;
	EXEN2 = 0;
	EXEN2 = 0;
	TR2 = 0;
	CT2 = 0;
	CPRL2 = 0;
	CKCON &= ~0x20;
	RCAP2H = 0x6f;
	RCAP2L = 0xda;
	TH2 = 0x6f;
	TL2 = 0xda;
	TR2 = 1;
	EA = 1;
	ET2 = 1;
}

void interruptBtn() interrupt 19
{
	Tst6 = 1;
	
	refresh_rate = (refresh_rate == 100) ? 1000 : 100;
	P3IF &= ~(1 << 7);

	Tst6 = 0;
}

/**
 * EXO 5 
 * clignotement tout les refresh_rate / 20ms 
 */
void interuptT2() interrupt 5
{
	Tst5 = 1;
	timer_count++;
	TF2 = 0;
	if (timer_count >= (refresh_rate / 20))
	{

		LED = ~LED;
		Tst4 = ~Tst4;
		timer_count = 0;
	}
		Tst5 = 0;
}

// /**
// EXO 4
//  * clignotement tout les 5 * 20ms
//  */
// void interuptT2() interrupt 5
// {
// 	timer_count++;
// 	TF2 = 0;
// 	if (timer_count == 5)
// 	{
// 		if (BP != 0)
// 		{
// 			LED = ~LED;
// 			Tst4 = ~Tst4;
// 		}
// 		else
// 		{
// 			LED = LED_Off;
// 		}
// 		timer_count = 0;
// 	}
// }

void exTimerInterrupt()
{

	TR2 = 1;
	P1MDOUT |= 1 << 6;

	BP = 1;
	P3MDOUT &= ~(1 << 7);

	Tst4 = 0;
	LED = LED_Off;

	confT2();

	while (1)
	{
	}
}

void exTimer()
{

	TR2 = 1;
	P1MDOUT |= 1 << 6;

	BP = 1;
	P3MDOUT &= ~(1 << 7);

	Tst4 = 0;
	LED = LED_Off;

	while (1)
	{
		int i = 0;
		for (; i < 5; i++)
		{
			T2wait20ms();
		}

		if (BP != 0)
		{
			LED = ~LED;
			Tst4 = ~Tst4;
		}
		else
		{
			LED = LED_Off;
		}
	}
}

void exBtnPoussoir()
{

	P1MDOUT |= 1 << 6;

	BP = 1;
	P3MDOUT &= ~(1 << 7);

	Tst4 = 0;
	LED = LED_Off;

	while (1)
	{

		if (BP != 0)
		{

			LED = ~LED;
			Tst4 = ~Tst4;
		}
		else
		{
			LED = LED_Off;
		}

		wait(100);
	}
}

/**
* Wait a multiple of 50 ms 
*/
void wait(unsigned int milli)
{
	int i = 0;
	for (; i < milli; i += 50)
	{
		fct_tempo(50000);
	}
}
