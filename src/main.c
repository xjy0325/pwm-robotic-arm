/*
 * ADCdemo.c
 *
 * Created: 15-04-2026 21:59:56
 * Author : marie
 */ 
#define F_CPU 16000000UL //frequency of CPU

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "initADC.h"
#include "I2C.h"  //include library for i2c driver
#include "ssd1306.h" //include display driver



void Channel_Select(uint8_t channel){
	
	ADMUX = (ADMUX & 0b11100000)|channel;//shift channel
}

volatile int current_channel = 0;
volatile int channel = 0;
ISR (TIMER0_COMPA_vect){

	current_channel = channel;
	
	Channel_Select(channel);
	
	ADCSRA |= (1<<ADSC);  //start conversion for next time data reading
	
	if(channel < 3){
		channel++;
		} else {
		channel = 0;
	}
				
}

volatile int data[4] = {0,0,0,0};
volatile int data_ready = 0;
ISR (ADC_vect){
	
	 data[current_channel] = ADC;
	 data_ready = 1;

}

void update_duty_cycle (int current_channel, int sample){
	
	//hold the last position of each channel
	static int last3 = 1500;
	static int last2 = 1500;
	static int last1 = 1500;
	static int last0 = 1500;
	
	//hold the position of the current channel 
	int last = 0;
	
	switch (current_channel){
		case 0: last = last0;
		break;
		case 1: last = last1;
		break;
		case 2: last = last2;
		break;
		case 3: last = last3;
		break;
	}
	
	if (sample > 525 && sample <= 1023) {
		last+=5;
	} else if (sample < 490 && sample >= 0) {
		last-=5;
	}
	
	if (last > 2000) last = 2000;
	if (last < 1000) last = 1000;
	
	switch (current_channel){
		case 0: OCR1A = last;
		last0 = last;
		break;
		case 1: OCR3A = last;
		last1 = last;
		break;
		case 2: OCR4A = last;
		last2 = last;
		break;
		case 3: OCR5A = last;
		last3 = last;
		break;
	}	
	
}

int main(void)
{
	//OLED initiation
	_i2c_address = 0X78; // write address for i2c interface
	I2C_Init();  //initialize i2c interface to display
	InitializeDisplay(); //initialize  display
	clear_display();   //use this before writing you own text
					
	//initialize timer & ADC & UART
	initTimer1(20000);
	initTimer3(20000);
	initTimer4(20000);
	initTimer5(20000);
	initADC();
	initTimer0(249);

	
	sei(); //enable global interrupt

	//display ADC value on OLED
	char LX[10];
	char LY[10];
	char RX[10];
	char RY[10];

    while (1) 
    {
		if (data_ready == 1){
			
			    //set flag back to 0 and convert data to string
			    data_ready = 0;
			
				switch (current_channel){
					case 0: update_duty_cycle (0, data[0]);
					
					break;
					case 1: update_duty_cycle (1, data[1]);
					
					break;
					case 2: update_duty_cycle (2, data[2]);
					
					break;
					case 3: update_duty_cycle (3, data[3]);
					
					break;	
				}
				
				static int print_wait = 0;
				print_wait++;
				if (print_wait >= 100){
					print_wait = 0;
					sprintf(LX, "LX: %04d", data[0]);
					sendStrXY(LX, 0, 0);
					sprintf(LY, "LY: %04d", data[1]);
					sendStrXY(LY, 1, 0);
					sprintf(RX, "RX: %04d", data[2]);
					sendStrXY(RX, 2, 0);
					sprintf(RY, "RY: %04d", data[3]);
					sendStrXY(RY, 3, 0);
				}
				
		}
    }
}
