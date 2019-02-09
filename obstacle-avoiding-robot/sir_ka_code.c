/*
 * LINE FOLLOWER ULTRASOUND.c
 *
 * Created: 2/17/2018 2:44:43 PM
 * Author : hp
 */ 
#define F_CPU 1000000      //telling controller crystal frequency attached

#include <avr/io.h>	//header to enable data flow control over pins

#include <util/delay.h>		//header to enable delay function in program

#include <avr/interrupt.h> //interrupt headerfile 

int i=0;
int pulse=0;

void forward(void)
{
	
	PORTB=PORTB|(1<<PINB1);//m1 + m1 forward
	PORTB=PORTB&(~(1<<PINB2));//m1 -
	PORTB=PORTB|(1<<PINB3);//m2 + m2 forward
	PORTB=PORTB&(~(1<<PINB5));//m2 -
}
void backward(void)
{

	PORTB=PORTB&(~(1<<PINB1));//m1 - m1 backward
	PORTB=PORTB|(1<<PINB2);//m1 +
	PORTB=PORTB&(~(1<<PINB3));//m2 - m2 backward
	PORTB=PORTB|(1<<PINB5);//m2 +
}


int main(void)

{

	DDRD = 0b11111011;
	
	DDRB = 0b00111110;

	GICR|=(1<<INT0);//enabling interrupt0

	MCUCR|=(1<<ISC00);//setting interrupt triggering logic change

	int16_t COUNTA = 0;//storing digital output

	sei();// enabling global interrupts



	while(1)

	{

		PORTD|=(1<<PIND0);

		_delay_us(15);	//triggering the sensor for 15usec

		PORTD &=~(1<<PIND0);

		COUNTA = (pulse/58);//getting the distance based on formula on introduction
		
		forward();
		
		if(COUNTA<=10)
		{
			backward();
		}
		
			

	}

}

ISR(INT0_vect)//interrupt service routine when there is a change in logic level

{

	if (i==1)//when logic from HIGH to LOW

	{

		TCCR1B=0;//disabling counter

		pulse=TCNT1;//count memory is updated to integer

		TCNT1=0;//resetting the counter memory

		i=0;

	}


	if (i==0)//when logic change from LOW to HIGH

	{

		TCCR1B|=(1<<CS10);//enabling counter

		i=1;

	}

}


