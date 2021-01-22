#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "VirtualSerial.h"
#include <util/delay.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

void mon_putchar(char c)
{if (c=='\n') fprintf(&USBSerialStream,"\r"); // \n -> \r\n
 fprintf(&USBSerialStream,"%c",c);
 CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
 CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
 USB_USBTask();
}

void usart_setup()
{CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
 GlobalInterruptEnable();
}

void clock_setup()
{SetupHardware();}
