#include <avr/io.h>      // voir /usr/lib/avr/include/avr/iom36u4.h
#include <avr/wdt.h>
#include <avr/power.h>

#define F_CPU 16000000UL

///////////////////// start simavr
#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega32");
AVR_MCU_VCD_FILE("trace_file.vcd", 1000);
const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
        { AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB, },
        { AVR_MCU_VCD_SYMBOL("UDR1"), .what = (void*)&UDR1, },
};
///////////////////// end of simavr

#define USART_BAUDRATE (57600)

void mon_putchar(char c)
{while (!( UCSR1A & (1<<UDRE1))); // wait while register is free
 UDR1 = c;                        // load data in the register
}

void usart_setup()
{ unsigned short baud;
  UCSR1A = (1<<UDRE1); // 0;                         // importantly U2X1 = 0
  UCSR1B = (1 << RXEN1)|(1 << TXEN1); // enable receiver and transmitter
  UCSR1C = (1<<UCSZ11)|(1<<UCSZ10); // _BV(UCSZ11) | _BV(UCSZ10); // 8N1
  // UCSR1D = 0;                         // no rtc/cts (probleme de version de libavr)
  baud  = (((( F_CPU / ( USART_BAUDRATE * 16UL))) - 1));
  UBRR1H = (unsigned char)(baud>>8);
  UBRR1L = (unsigned char)baud;

  DDRB|=1<<3;
//  volatile long boucle;
//  while (1) 
//    {PORTB=0xff;
//     for (boucle=0;boucle<0xffff;boucle++) {}
//     PORTB=0;
//     for (boucle=0;boucle<0xffff;boucle++) {}
//    }
}

void clock_setup()
{MCUSR = 0;
 wdt_disable();
  USBCON=0;      // disable USB in Arduino AVR109 mode
  clock_prescale_set (clock_div_1);
}

