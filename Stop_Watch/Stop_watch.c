/*
 * Stop_watch.c
 *
 *  Created on: Sep 17, 2022
 *      Author: Mahmoud Ehab
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<string.h>//for memset usage
unsigned char flag_a_second_passed = 0, flag_a_minute_passed = 0,
		flag_an_hour_passed = 0;
unsigned char Time_array[6] = { 0 }; //{sec1,sec2,min1,min2,hour1,hour2}
void Pins_Ini(void);
void Timer1_Ini(void);
void External_INT_Ini(void);
void a_second_passed(void);
void a_minute_passed(void);
void an_hour_passed(void);
ISR(TIMER1_COMPA_vect) {
	flag_a_second_passed = 1;
}
ISR(INT0_vect) {
	memset(Time_array, 0, sizeof(Time_array));//clear the array of time
	TCNT1 = 0;//reset timer counter
}
ISR(INT1_vect) {
	TCCR1B &= ~0x07;//stop the timer clock
	TCNT1 = 0;//reset timer counter
}
ISR(INT2_vect) {
	TCNT1 = 0;//reset timer counter
	TCCR1B |= 0x05;//enable clock
}
int main(void) {
	Pins_Ini();
	Timer1_Ini();
	External_INT_Ini();
	SREG |= (1 << 7); //enable interrupts
	while (1) {
		if (flag_a_second_passed == 1) {
			a_second_passed();
		} else if (flag_a_minute_passed == 1) {
			a_minute_passed();
		} else if (flag_an_hour_passed == 1) {
			an_hour_passed();
		}
		PORTA = (PORTA & 0xC0) | 0x01; //enable sec1 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[0]; //display sec1
		_delay_us(5);
		PORTA = (PORTA & 0xC0) | 0x02; //enable sec2 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[1]; //display sec2
		_delay_us(5);
		PORTA = (PORTA & 0xC0) | 0x04; //enable min1 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[2]; //display min1
		_delay_us(5);
		PORTA = (PORTA & 0xC0) | 0x08; //enable min2 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[3]; //display min2
		_delay_us(5);
		PORTA = (PORTA & 0xC0) | 0x10; //enable hour1 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[4]; //display hour1
		_delay_us(5);
		PORTA = (PORTA & 0xC0) | 0x20; //enable hour2 7-segment
		PORTC = (PORTC & 0xF0) | Time_array[5]; //display hour2
		_delay_us(5);
	}
}
void a_second_passed(void) { //used whenever a second passes
	if (Time_array[0] < 9) {
		Time_array[0]++;
	} else {
		Time_array[0] = 0;
		if (Time_array[1] < 5) {
			Time_array[1]++;
		} else {
			Time_array[1] = 0;
			flag_a_minute_passed = 1;
		}
	}
	flag_a_second_passed = 0;
}
void a_minute_passed(void) { //used whenever a minute passes
	if (Time_array[2] < 9) {
		Time_array[2]++;
	} else {
		Time_array[2] = 0;
		if (Time_array[3] < 5) {
			Time_array[3]++;
		} else {
			Time_array[3] = 0;
			flag_an_hour_passed = 1;
		}
	}
	flag_a_minute_passed = 0;
}
void an_hour_passed(void) { //used whenever an hour passes
	if (Time_array[4] < 9) {
		Time_array[4]++;
	} else {
		Time_array[4] = 0;
		if (Time_array[5] < 9) {
			Time_array[5]++;
		} else {
			Time_array[5] = 0;
		}
	}
	flag_an_hour_passed = 0;
}
void Timer1_Ini(void) {
	TCNT1 = 0; //counting start clearing
	OCR1A = 977; //Top value initialization
	TIMSK |= (1 << 4); //output comapre match A enable
	TCCR1A = 0x08; //CTC (mode 4) enable
	TCCR1B = 0x0D; //prescaler 1024
}
void Pins_Ini(void) {
	DDRC |= 0x0F; // output PC Pins
	DDRA |= 0x3F; //output PA Pins
	DDRD &= ~0x0C; //Input PD Pins
	DDRB &= ~(1 << 2); //Input PB pins
	PORTD |= (1 << 2); //internal pull-up resistor enable
	PORTB |= (1 << 2); //internal pull-up resistor enable
	PORTC &= 0xF0; //clear of PC lower pins
}
void External_INT_Ini(void) {
	MCUCR |= 0x0E;
	MCUCR &= ~(1 << 0);    //INT0&INT1 edges configuration
	GICR |= 0xE0;  //external INT enable
	MCUCSR &= ~(1 << 6); //INT2 falling edge configuration
}

