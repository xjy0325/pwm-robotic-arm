/*
 * IncFile1.h
 *
 * Created: 14-03-2026 20:23:03
 *  Author: marie
 */ 


#ifndef UART0_H_
#define UART0_H_

#define BAUD 19200
#define MYUBRRF (F_CPU/8/BAUD -1) //double speed

extern void uart0_Init(unsigned int ubrr);
extern void putchUART0 (char tx);
extern void putstrUART0 (char *ptr);
extern char getchUART0(void);
extern int  getlineUART0(char *line_Whole);

#endif /* UART0_H_ */