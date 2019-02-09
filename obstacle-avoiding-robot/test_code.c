void forward(){
	PORTD|=(1<<PIND1)|(1<<PIND2);
	PORTD&=~(1<<PIND0);
	PORTD&=~(1<<PIND3);
}

void turn_left(){
	PORTD|=(1<<PIND2);
	PORTD&=~(1<<PIND0);
	PORTD&=~(1<<PIND1);
	PORTD&=~(1<<PIND3);
}

void main(){
	DDRD = 0xFF;
	while(1){
		forward()
	}
}