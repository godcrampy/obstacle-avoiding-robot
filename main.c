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

/*void pwm_init(){
	TCCR0 |= (1<<WGM00)|(1<<WGM01); //Set PWM to Fast PWM Mode
	TCCR0 |= (1<<COM00)|(1<<COM01); //Set Fast PWM to inverting mode
	TCCR0 |= (1<<CS01) //Pre scale 8 bit counter to prescaling of 8 to count till 2048 counting (>100)(coz ICR1 is 1000 and hence couter must be greater than 1000)
	TCCR0 &= ~(1<<CS02)
	ICR1 = 1000; //Sets ICP1(Reference to 1000)(Although it is called ICP1
}*/

void move_forward(){
	PORTA |= (1<<PINA2)|(1<<PINA4);
	PORTA &= ~(1<<PINA3);
	PORTA &= ~(1<<PINA5);
	OCR1A =  1000;//Run Motor 1 at 100% of ICR1(Reference) value
	OCR1B =  1000;//Run Motor 2 at 100% of ICR1(Reference) value
}

void move_backward(){
	PORTA |= (1<<PINA3)|(1<<PINA5);
	PORTA &= ~(1<<PINA2);
	PORTA &= ~(1<<PINA4);
	OCR1A  = 1000;//Run Motor 1 at 100% of ICR1(Reference) value {Reverse}
	OCR1B  = 1000;//Run Motor 2 at 100% of ICR1(Reference) value {Reverse}
}

void turn_left(){
	PORTA |= (1<<PINA2)|(1<<PINA4);
	PORTA &= ~(1<<PINA3);
	PORTA &= ~(1<<PINA5);
	OCR1A = 1000;//Run Motor 1 at 100% of ICR1(Reference) value
	OCR1B = 450;//Run Motor 2 at 45% of ICR1(Reference) value
}

void turn_right(){
	PORTA |= (1<<PINA2)|(1<<PINA4);
	PORTA &= ~(1<<PINA3);
	PORTA &= ~(1<<PINA5);
	OCR1A = 450;//Run Motor 1 at 45% of ICR1(Reference) value
	OCR1B = 1000;//Run Motor 2 at 100% of ICR1(Reference) value
}

void turn_left_hard(){
	PORTA |= (1<<PINA2)|(1<<PINA5);
	PORTA &= ~(1<<PINA3);
	PORTA &= ~(1<<PINA4);
	OCR1A = 750;//Run Motor 1 at 100% of ICR1(Reference) value
	OCR1B = 750;//Run Motor 2 at 100% of ICR1(Reference) value {Reverse}
}

void turn_right_hard(){
	PORTA |= (1<<PINA3)|(1<<PINA4);
	PORTA &= ~(1<<PINA2);
	PORTA &= ~(1<<PINA5);
	OCR1A = 750;//Run Motor 1 at 75% of ICR1(Reference) value {Reverse}
	OCR1B = 750;//Run Motor 2 at 75% of ICR1(Reference) value
	}

void stop(){
	PORTA &= ~(1<<PINA2);
	PORTA &= ~(1<<PINA3);
	PORTA &= ~(1<<PINA4);
	PORTA &= ~(1<<PINA5);
}

 int main()
{
    
	 DDRA = 0x00;
	 DDRD = 0xFF;
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
