/*
 * pid_2.c
 *
 * Created: 02-02-2019 16:04:35
 * Author : Lenovo
 */ 

#include <avr/io.h>
void pwm_init()
{
	TCCR0 |= (1<<WGM00)|(1<<WGM01); //Set PWM to Fast PWM Mode
	TCCR0 |= (1<<COM00)|(1<<COM01); //Set Fast PWM to inverting mode
	TCCR0 |= (1<<CS01); //Pre scale 8 bit counter to prescaling of 8 to count till 2048 counting (>100)(coz ICR1 is 1000 and hence couter must be greater than 1000)
	// TCCR0 &= ~(1<<CS02);
	ICR1 = 1000; //Sets ICP1(Reference to 1000)(Although it is called ICP1
}

int pin_status[8]=[0,0,0,0,0,0,0,0];
int pin_weightage[8]=[0,2,4,6,8,10,12,14];
float desired_value=7,kp,kd;
float error=0,error1=0,last_error=0,d_error=0,base_value=150,error2=0;
int c,i;

void move(int left,int right)
{
	PORTD |= (1<<PIND1)|(1<<PIND2);
	PORTD &= ~(1<<PIND0);
	PORTD &= ~(1<<PIND3);
	OCR1A =  left;
	OCR1B =  right;
	
}
int pid_calc(void)
{
	c=0;
	for(i=0;i<8;i++)
	{
		if(bit_is_set(PINA,i)==1)
			c++;
		error+=(bit_is_set(PINA,i)*pin_weightage[i]);
	}
	if(c==0)
	{
		c=1;
		if(last_error>0)
			error=20;
		else
			error=-20;
	}
	
	error=error/c;
	
	error=error-desired_value;
	error1+=kp*error+kd*d_error;
	d_error=error1-last_error;
	last_error=error1;
	return error1;
	
}

void interupt_init(void)
{
	GICR|=(1<<INT0);//enabling interrupt0

	MCUCR|=(1<<ISC00);//setting interrupt triggering logic change

	int16_t COUNTA = 0;//storing digital output

	sei();// enabling global interrupts
}

void detect_obstacle(void)
{
	PORTD|=(1<<PIND0);

		_delay_us(15);	//triggering the sensor for 15usec

		PORTD &=~(1<<PIND0);

		COUNTA = (pulse/58);//getting the distance based on formula on introduction
		
		forward();
		
		if(COUNTA<=10)
		{
			//uturn
		}
		
}


int main(void)
{
    DDRD=0x00;
    DDRA=0xFF;
	pwm_init();
	interupt_init();

	

	
    while (1) 
    {

    	detect_obstacle();
		//stop code 
		if(c==8)
		move(0,0);
		
		//basic line following
		error2=pid_calc();
		move(base_value+error2,base_value-error2);
		
	}
 
	return 0;
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
