/*
 * obstacle-avoiding-robot.c
 *
 * Created: 28-01-2019 13:40:59
 * Author : SAHIL
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>

int is_white(int n)
{
	return bit_is_clear(PINA,n);//returns true if there is white line under
}

void move_forward(){
	PORTD|=(1<<PIND1)|(1<<PIND2);
	PORTD&=~(1<<PIND0);
	PORTD&=~(1<<PIND3);
}

void move_backward(){
	PORTD|=(1<<PIND3)|(1<<PIND0);
	PORTD&=~(1<<PIND1);
	PORTD&=~(1<<PIND2);
}

void turn_left(){
	PORTD|=(1<<PIND2);
	PORTD&=~(1<<PIND0);
	PORTD&=~(1<<PIND1);
	PORTD&=~(1<<PIND3);
}

void turn_right(){
	PORTD|=(1<<PIND1);
	PORTD&=~(1<<PIND0);
	PORTD&=~(1<<PIND2);
	PORTD&=~(1<<PIND3);
}

void turn_left_hard(){
	PORTD|=(1<<PIND2);
	PORTD|=(1<<PIND0);
	PORTD&=~(1<<PIND1);
	PORTD&=~(1<<PIND3);
}

void turn_right_hard(){
	PORTD|=(1<<PIND1);
	PORTD|=(1<<PIND3);
	PORTD&=~(1<<PIND2);
	PORTD&=~(1<<PIND0);
	}

void stop(){
	PORTA&=~(1<<PINA2);
	PORTA&=~(1<<PINA3);
	PORTA&=~(1<<PINA4);
	PORTA&=~(1<<PINA5);
}

int main(void)
{
	 DDRA=0x00;
	 DDRD=0xFF;
	//Code for other ports I/O not set
    while (1)
    {
		//Stop and Reverse
	if(is_white(0) && is_white(1) && is_white(2) && is_white(3) && is_white(4) && is_white(5) && is_white(6) && is_white(7)){
		stop();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		move_backward();
	}
		//4 White Code
	else if(is_white(0) && is_white(1) && is_white(2) && is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
			turn_right_hard();
		}
	else if(!is_white(0) && is_white(1) && is_white(2) && is_white(3) && is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
			turn_right();
    }
	else if(!is_white(0) && !is_white(1) && is_white(2) && is_white(3) && is_white(4) && is_white(5) && !is_white(6) && !is_white(7)){
		move_forward();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && is_white(3) && is_white(4) && is_white(5) && is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && is_white(4) && is_white(5) && is_white(6) && is_white(7)){
		turn_right_hard();
	}
	//3 White Code
	else if(is_white(0) && is_white(1) && is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right_hard();
	}
	else if(!is_white(0) && is_white(1) && is_white(2) && is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && is_white(2) && is_white(3) && is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && is_white(3) && is_white(4) && is_white(5) && !is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && is_white(4) && is_white(5) && is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && is_white(5) && is_white(6) && is_white(7)){
		turn_left_hard();
	}
	//2 white code
	else if(is_white(0) && is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right_hard();
	}
	else if(!is_white(0) && is_white(1) && is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && is_white(2) && is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && is_white(3) && is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		move_forward();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && is_white(4) && is_white(5) && !is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && is_white(5) && is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && is_white(6) && is_white(7)){
		turn_left_hard();
	}
	//1 line code
	else if(is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right_hard();
	}
	else if(!is_white(0) && is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_right();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && is_white(4) && !is_white(5) && !is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && is_white(5) && !is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && is_white(6) && !is_white(7)){
		turn_left();
	}
	else if(!is_white(0) && !is_white(1) && !is_white(2) && !is_white(3) && !is_white(4) && !is_white(5) && !is_white(6) && is_white(7)){
		turn_left_hard();
	}

	}
return 0;
}
