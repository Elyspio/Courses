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
#include <c8051f020.h>                    // SFR declarations
//------------------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//------------------------------------------------------------------------------------
sfr16 TMR3RL   = 0x92;                    // Timer3 reload value
sfr16 TMR3     = 0x94;                    // Timer3 counter
sfr16 ADC0     = 0xbe;                    // ADC0 data
sfr16 ADC0GT   = 0xc4;                    // ADC0 greater than window
sfr16 ADC0LT   = 0xc6;                    // ADC0 less than window
sfr16 RCAP2    = 0xca;                    // Timer2 capture/reload
sfr16 T2       = 0xcc;                    // Timer2
sfr16 RCAP4    = 0xe4;                    // Timer4 capture/reload
sfr16 T4       = 0xf4;                    // Timer4
sfr16 DAC0     = 0xd2;                    // DAC0 data
sfr16 DAC1     = 0xd5;                    // DAC1 data

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400 //approximate SYSCLK frequency in Hz
#define BAUDRATE 115200 
#define LED_On 1
#define LED_Off 0

extern  code char Sin_table[];

// Eléments présents sur la carte 8051F020
sbit  LED = P1^6;         // LED verte: '1' = ON; '0' = OFF
sbit BP = P3^7;           // Bouton Poussoir '1' relaché, '0' pressé

// Eléments de l'application Pilotage d'un système de tri
sbit Tst4 = P3^4;
sbit Tst5 = P3^5;
sbit Tst6 = P3^6;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device (void); // Fonction codée dans LIB_Base.c
void fct_tempo(unsigned int);     // Fonction assembleur codée dans Asm_8051_Lib.asm
void temps (int);
void timer();
char  Putchar(char c);
unsigned char  Send_string(char *str_ptr);
void Config_UART0(void);
//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------

int limit = 5;

void main (void) {

 	Init_Device();
	Tst4 = 0;
	LED = LED_On;
	BP = 1;
	P1MDOUT |= 0x40;
	P3MDOUT &= ~0x80;
  timer();
	P3IF &= ~(1 << 7);
	P3IF |= (1 << 3);
	EIE2 |= (1 << 5);
	EIP2 &= ~(1 << 5);
	/*SCON0 |= (1 << 6);
	SCON0 &= ~(1 << 7);
	SCON0 &= ~(1 << 1);
	SCON0 |= (1 << 0);
	PCON      = 0x80;
  SCON0     = 0x50;
	CKCON     = 0x10;
  TCON      = 0x40;
  TMOD      = 0x20;
  TH1       = 0xF4;*/
	Config_UART0();
	
while (1)
   { 
		
}
}
void timer(){
	TR2 = 0;
	CKCON &= ~0x20;
	TF2 = 0;
	EXF2 = 0;
	RCLK0 = 0;
	TCLK0 = 0;
	EXEN2 = 0;
	TH2 = 0x6F;
	TL2 = 0xDA;
	RCAP2H = 0x6F;
	RCAP2L = 0xDA;
	ET2 = 1;
	TR2 = 1;
	EA = 1;
	
}

void Config_UART0()
{
// Config Timer1
	  CKCON |= 0x10; // T1M: Timer 1 Clock Select.  Timer1 CLK = system clock
    TMOD |= 0x20;  
    TMOD &= 0x2f;  // Timer1 configuré en timer 8 bit avec auto-reload
    TF1 = 0;	     // Flag Timer effacé
    TH1 = -(SYSCLK/BAUDRATE/16);
    ET1 = 0;	     // Interruption Timer 1 dévalidée
    TR1 = 1;	     // Timer1 démarré
// Config UART0	
    RCLK0 = 0;   // T2CON Source clock Timer 1
    TCLK0 = 0;   // T2CON
    PCON  |= 0x80; //SMOD0: UART0 Baud Rate Doubler Disabled.
    PCON &= 0xBF; // SSTAT0=0
    SCON0 = 0x70;   // Mode 1 - Check Stop bit - Réception validée		
    TI0 = 1;   												 
 }


void ISR_timer(void) interrupt 5{

	static int i;
	TF2=0;
	i = i+1;
	if(i >= limit)
	{
		i = 0;

		LED = ~LED;
		Tst4 = ~Tst4;
	}
}

void ISR_btn(void) interrupt 19{
	P3IF &= ~(1 << 7);
	Putchar('a');
	if(limit == 5){
		limit = 50;
}
	else {
		limit = 5;
}
}

void ISR_uart(void) interrupt 4{

	SCON0 &= ~(1 << 1);
	
	
}

char  Putchar(char c)
{
  while (!TI0);   // Traitement UART pas prête à transmettre
                 // Risque de blocage!!!
  SBUF0 = c;	   // Traitement UART prête à transmettre
  TI0 = 0;	   // Raz flag octet transmis
  return c;
}
unsigned char  Send_string(char *str_ptr)
{
unsigned char cp_char = 0;


	while (*str_ptr != 0)
	{
	   Putchar(*str_ptr); 
		 str_ptr++;
		 cp_char++;	
	}
	return cp_char;
}

