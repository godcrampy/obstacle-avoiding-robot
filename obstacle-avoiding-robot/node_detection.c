int node_type;
int number_of_pins_high()
{
	int c = 0;
	for(int i=0; i<8;i++)
	{
		if(bit_is_set(PINA,i)==1)
			c++;
	}
	return c;
}

void detect_node()
{

	if(number_of_pins_high()>=4)
	{
		if(bit_is_set(0)&&bit_is_set(7)){//Case 1 or 2
			node_type=0;
		}
		else if(bit_is_set(0)){//Case 3
			node_type=3;
		}
		else(bit_is_set(7)){//Case 4
			node_type=4;
		}
	}
}

void inch()
{
	move_forward(1000,1000);
}
void after_node_detect()
{
	if(number_of_pins_high==8)
	{
		move(0,0);																			
	}
	else if(number_of_pins_high==0)
	{
		//left turn
	}
	else if(number_of_pins_high==2)
	{
		if(node_type==0||node_type==3)
		{
			//left turn
		}
		else
			//forward
	}

}

/*
1.
       ||
=================
       ||

2.
=================
       ||

3.
       ||
=========
       ||

4.
||
=========
||
*/
detect_node()
inch()
after_node_detect()
