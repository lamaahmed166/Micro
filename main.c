#include <REG52.H> 
#include <stdio.h> 
#include <string.h>
//#include <util/delay.h>
//#include <time.h>
/*-----------------------------------------------The following string is the stuff we're gonna send into the serial port. ------------------------------------------------*/ 
			unsigned char xdata serial_input_buffer [] = "This is a test to see if this data gets ";
			unsigned	int i=0; 
			unsigned	int count =0; 
			unsigned	char key[20] = {'.','t','i','e','5','R','o','n','a', 'l','\0'};
			sbit switch1= P0^0;   //training vs testing phases   training=0 , testing=1
			sbit switch2=P0^1;   //users phases   A=0, B=1
			
	void main (void) 
		{ 

		/*-----------------------------------------------Setup the serial port for 2400 baud at 12MHz. ------------------------------------------------*/ 
			SCON = 0x50; // SCON: mode 1, 8-bit UART, enable reciever 
			TMOD |= 0x20; // TMOD: timer 1, mode 2, 8-bit reload 
			TH1 = 0xF3; // TH1: reload value for 2400 baud @ 12MHz 
			TR1 = 1; // TR1: timer 1 run 
			TI = 1; // TI: set TI to send first char of UART
			switch1=1;
			switch2=1;
			
		while (1) 
			{ 
				
				unsigned char x = _getkey(); 

				if(switch1 ==0) 
					{
							//training 
						printf("Training mode activated\n");
					}
					
					else 
					{
						//testing
						printf("Testing mode activated\n");
					}
				
				if(switch2 == 0) 
				{
				    //choose profile userA
					printf("userA profile selected\n");
				}
				
				else
				{
					//user B
					printf("userB profile selected\n");
				}
				
				if (x == key[i]) 
					{
						i++;
					} 
				else 
					{
						i = 0; 
					}
				if (i == 10) 
					{ 
						count++; 
						printf("Count is= %d\n", count); 
					}
				if(x == 'b')
				{
					//activate training mode
					switch1= 0;
				}
				
						if(x == 'm')
				{
					//activate testing mode
					switch1= 1;
				}
				
						if(x == 'q')
				{
					//activate userA
					switch2= 0;
				}
				
						if(x == 'w')
				{
					//activate userB
					switch2= 1;
				}
				
			}
		}