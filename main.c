#include <REG52.H> 
#include <stdio.h> 
#include <string.h>
/*-----------------------------------------------The following string is the stuff we're gonna send into the serial port. ------------------------------------------------*/ 
		
					sfr Port0= 0x80;  //starting address of port 0
        	sbit switch1= Port0^0;   //training vs testing phases   training=0 , testing=1
		    	sbit switch2=Port0^1;   //users phases   A=0, B=1
					sbit LED= Port0^7;
					unsigned int counter=0;
	void main (void) 
		{ 
			unsigned	int i=0; 
			unsigned	int j; 
			unsigned	int countA =0;
			unsigned	int countB =0;			
			unsigned	int m=0;
			unsigned	int n=0;
			unsigned	char xdata word[11] = {'.','t','i','e','5','R','o','n','a', 'l','\0'};
		  int  xdata arrayA[10]={0,0,0,0,0,0,0,0,0,0};
		  int  xdata arrayB[10]={0,0,0,0,0,0,0,0,0,0};
		  int xdata arrayTest[10]={0,0,0,0,0,0,0,0,0,0};
			unsigned int finishedA =0;
			unsigned int finishedB =0;
			unsigned int DA=0;
			unsigned int DB=0;
			/*-----------------------------------------------Setup the serial port for 9600 baud at 12MHz. ------------------------------------------------*/ 
			SCON = 0x50; // SCON: mode 1, 8-bit UART, enable reciever 
			TMOD |= 0x21; // TMOD: timer 1, mode 2, 8-bit reload 
			TH1 = 0xFD; // TH1: reload value for 10,416.67 (approx=9600) baud @ 12MHz 
			TI = 1; // TI: set TI to send first char of UART
			
			
			//TIMER 0 mode 1
			TH0 = 0X4B;        //Load the timer value 
			TL0 = 0XFD;
			ET0=1; //ENABLE interrupt of timer
			EA=1;   //global 
		while (1) 
			{ 
				
				unsigned char x = _getkey(); 

				//Training phase activated
				if(switch1 ==0) 
					{
							//training 
					//	printf("Training mode activated\n");
					
					
					//choose profile userA'
				if(switch2 == 0 && finishedA == 0) 
					{
				  //  printf("userA profile selected\n");
					//user entered 1st character	
				if (x == word[i] && i==0) 
					{	
						//start timer
						TR0 = 1; //  
						i++;
					}//end if

					//user entered the correct character at the correct position (general case)
				 if(x == word[i] && i != 0) 
					{
						//stop timer, save value, start timer again
							TR0=0; 
							arrayA[i] += counter;
							counter=0;
							TR0=1;
							i++;

					}//end if  
				
					//user entered wrong character
					if(x != word[i])
					{
						//restart the timer
						TR0=0;
						TR0=1;
					}//end if
					
				if (i == 10) 
					{ 
						countA++; 
						i = 0;
						TR0=0;
						counter=0;
					//	printf("Count is= %d\n", countA); 
					}//end if
				
					if(countA == 5)
					{
							for(j=0; j<sizeof(arrayA);j++)
						{
								//calculate average of flight times of training phase
								arrayA[j]= arrayA[j]/5;  //five times
						}//end for
						
						finishedA = 1;
					//	printf("User A completed the training phase\n");
					}//flag to stop training phase for A
				
				}//end userA
				
				//
					//choose profile userB
				if(switch2 == 1 && finishedB == 0) 
					{
				  //  printf("userB profile selected\n");
	
					//user entered 1st character	
				if (x == word[i] && i==0) 
					{	
						//start timer
						TR0 = 1; // TR1: timer 1 run 
						i++;
					}//end if

					//user entered the correct character at the correct position (general case)
				 if(x == word[i] && i != 0) 
					{
						//stop timer, save value, start timer again
							TR0=0; 
							arrayB[i] += counter;
						  counter=0;
							TR0=1;
							i++;

					}//end if  
				
					//user entered wrong character
					if(x != word[i])
					{
						//restart the timer
						TR0=0;
						TR0=1;
					}//end if
					
				if (i == 10) 
					{ 
						countB++; 
						TR0=0;
						counter=0;
						i = 0;
					//	printf("Count is= %d\n", countB); 
					}//end if
				
					if(countB == 5)
					{
						for(j=0; j<sizeof(arrayB);j++)
						{
								//calculate average of flight times of training phase
								arrayB[j]= arrayB[j]/5;  //five times
						}//end for
						
						finishedB = 1;
					//	printf("User B completed the training phase\n");
					}//flag to stop training phase for A
				
				}//end userB
		}//end training phase
			
				//testing phase activated
					else 
					{
					//	printf("Testing mode activated\n");
						
						//take test sample from user
					//user entered 1st character	
				if (x == word[i] && i==0) 
					{	
						//start timer
						TR0 = 1; // TR1: timer 1 run 
						i++;
					}//end if

					//user entered the correct character at the correct position (general case)
				 if(x == word[i] && i != 0) 
					{
						//stop timer, save value, start timer again
							TR0=0; 
							arrayTest[i] += counter;
							counter=0;
							TR0=1;
						i++;
					}//end if  
				
					//user entered wrong character
					if(x != word[i])
					{
						//restart the timer
						TR0=0;
						TR0=1;
					}//end if
					
				if (i == 10) 
					{ 
						i = 0;
						TR0=0;
						counter=0;
						
							for(j=0; j<sizeof(arrayTest);j++)
						{
							//flight test - flight A of this specific char
							DA += arrayTest[j]- arrayA[j];
							DB += arrayTest[j]- arrayB[j];
						}//end for
						
						//avarage DA
						DA= DA * DA; 
						//avarage DB
						DB= DB * DB; 
						
						//user A 
						if(DA<DB)
						{
					//			printf("IT'S USER A!\n");
							LED=1;
							LED=0;
						}
						//user B
						else
						{
							while(1){
						LED= !LED;
							}//end while
							}//end else
					}//end if
					}//end testing phase
			}//end while
		}//end main
		
		void timer0_isr()interrupt 1
		{
			//TIMER 0 MODE 1
			TH0 = 0X4B;        //Load the timer value 
			TL0 = 0XFD;
			counter++;
		}