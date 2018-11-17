# Micro


				Microprocessors Report
			Team Name: MICRO PROFESSORS
				  Lama Ahmed 37-8757
				  Yomna Osama 37-11566
				  Sarah Ayman 37-3459
				  Nehal Essam 37-11466
			    Ahmed Hisham Rihan 37-3032
	There are 2 arrays dedicated to save flight time between characters for each user. (arrayA, arrayB).
	Timer 1, mode 2 were used with Baud rate 9600.
	Timer 0, mode 1 were used for the keylogging process. (Flight time calculation)
	Firstly, there are 2 switches used, the first switch to identify the training/testing phase. Whereas the second switch is used to identify which is user is typing (A or B) during the training phase.
	Next, in the training phase the user types the sentence “.tie5Ronal” 5 times. Each time a character is written its flight time between it and the following typed character is calculated and added to the corresponding position of the corresponding user array. After the 5 times of the training phase are done, each array will have an accumulation of the flight times of each character, and an average is calculated for those accumulations and stored to their corresponding positions.
	Next, in the testing phase, a random user types the sentence “.tie5Ronal” once. Afterwards, the Euclidean distance is calculated as the difference between the test fight times of each character (stored in ArrayTest)  and the currently existing flight times of arrays A and B. The results of the vector is stored in the variables “DA” and “DB”. This calculation reveals which user typed in the testing phase. If the LED flashes on and off repetitively, this means that DB was less than DA, therefore it was user B who had typed in the testing phase. If the LED is turned off, then this means that DA was less than DB and user A is the one who had typed in the testing phase.
	 To calculate flight times, the interrupt method timer0_isr was used to increment a counter (counter) which represent the number of ticks every time an overflow occurred.
	Some precautions have been taken into consideration.
-If the user mistyped a character the timer is restarted.
-When the user types a new character the timer is stopped and the value of the counter is saved to the corresponding array, the counter is cleared and the timer is restarted.
- In the training phase, only the first 5 times’ values are taken into consideration, other values are not taken into consideration.
	Screenshots for the watch, UART, and timers’ windows: 

 
 					(Figure 1)
		arrayA average values after 5 times of trial




 
				        (Figure 2)
			arrayB average values after 5 times of trial

 
					(Figure 3)
		arrayTest values during testing phase DA<DB






 
					(Figure 4)
		ArrayTest values during testing phase DB>DA
