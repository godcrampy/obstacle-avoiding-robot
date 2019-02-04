void make_uturn(){
	while(is_white(7)&&is_white(6)){
		OCR1A=1000;//Run Motor 1 at 100% of ICR1(Reference) value
		OCR1B=0;//R+un Motor 2 at 0% of ICR1(Reference) value
	}
}