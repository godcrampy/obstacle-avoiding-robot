/*
 * obstacle-avoiding-robot.c
 *
 * Created: 28-01-2019 13:40:59
 * Author : SAHIL
 */ 
//

#include <avr/io.h>
#include <avr/sfr_defs.h>

int is_white(int n)
{
	return bit_is_clear(PINA,n);//returns true if there is white line under
}


void pwm_init(){
	TCCR0|=(1<<WGM00)|(1<<WGM01); //Set PWM to Fast PWM Mode
	TCCR0|=(1<<COM00)|(1<<COM01); //Set Fast PWM to inverting mode
	TCCR0 |=(1<<CS01); //Prescale 8 bit counter to prescaling of 8 to count till 2048 counting (>100)(coz ICR1 is 1000 and hence couter must be greater than 1000)
	    
	//TCCR0 &=~(1<<CS02);
	ICR1=1000; //Sets ICP1(Reference to 1000)(Although it is called ICP1
}

void move_forward(float left_rpm, float right_rpm)
{
	PORTA|=(1<<PINA2)|(1<<PINA4);
	PORTA&=~(1<<PINA3);
	PORTA&=~(1<<PINA5);
	OCR1A=left_rpm;//Run Motor 1 at 100% of ICR1(Reference) value
	OCR1B=right_rpm;//Run Motor 2 at 100% of ICR1(Reference) value
}

void stop()
{
	PORTA&=~(1<<PINA2);
	PORTA&=~(1<<PINA3);
	PORTA&=~(1<<PINA4);
	PORTA&=~(1<<PINA5);
}
/*
1. Return Error
2. Make RPM Global
3. Make 6-7 lines of PID in Main
4. 0 to 14

*/

int main(void)
{
    //Code for other ports I/O not set

	 DDRA=0x00;
	 DDRD=0xFF;
	 pwm_init();
	 //Set PID Constants=========
	 float baseline=900;
	 float k_p=1;
	 float k_d=1;
	 int pin_weights[8]=[-4,-3,-2,-1,1,2,3,4];
     int pin_map[8]=[0,0,0,0,0,0,0,0];	
     int pin_frequency = 0;
     int cost = 0;
     float prev_error=0;
	 //==========================
	 
	
    while (1)
    {
    	
    	for(int i=0; i<8; i++){//Set Pin Frequency and Cost of White Line Error
    		if is_white(i){
    			pin_frequency++;
    			cost+=pin_weights[i]*pin_map[i];
    		}
    	}
    	if(pin_frequency==0){//White Line not visible
    		if(prev_error>0){
    			move_forward(1000,200);
    		}
    		else{
    			move_forward(200,1000);
    		}
    		error=prev_error;
    	}
    	else if(pin_frequency==8){//All White
    		stop();
    	}
    	else{// Check Error and move
    		float error = cost/pin_frequency;
    		float diff_error = error - prev_error;
    		float left_rpm = baseline + k_p*error + k_d*diff_error;
    		float left_rpm = baseline - k_p*error - k_d*diff_error;
    		move_forward(left_rpm, right_rpm);
    		float prev_error = error;
    	}
	}
	return 0;
}

