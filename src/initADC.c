/*
 * initADC.c
 *
 * Created: 29-04-2026 18:46:12
 *  Author: marie
 */ 
#include <avr/io.h>

void initADC(){
	
	ADMUX |= (1<<REFS0);//5V ref voltage
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) ;//enable ADC with 128 prescaler => clk = 125 kHz
	
	ADCSRA |= (1<<ADIE); //enable interrupt
	
	ADCSRA |= (1<<ADSC);//start first time sample
	
	ADMUX = (ADMUX & 0xE0) | 0x00; 
	
}