/*****************************************************/
/*********** End of Fleat testing notes **************/
/*****************************************************/

* When you power on the analog front end, there needs to be a good delay to make sure the chips have powered up before they can be read/written to.
* Not enough throughput while 8 ch at 320hz for 115200 bit/s UART interface.
* Add a weak pullup to the ADP5302 power supply ENABLE line, otherwise the default state of the EFM32 is floating and will not power on the board.



/*****************************************************/
/************* Brain storming task list **************/
/*****************************************************/

Control menu.
	- Develop simple menu hierarchy for picking options.
		Options could include...
			# and Type of sensors to include.
			Sampling freq
			SBE 49 interfacing on/off
			Memory options (erase, directory, so on...)
			Deployment options and Logging averaging
			Set system time
			
	-put all options in giant bit array for easy access?
		maybe seperate smaller arrays so less passing needs to happen?
		
Sampling
	- Integrate the rest of the samplers into the routine based off of a "whats configured" list
	- Put all data into one giant receive buffer. Probably in excess of 1024 x 32 bits.

	
Communications
	- Devlop simple comm protocol for both streaming and SBE49 transmission
	- Integrate DMA for better task management and more throughput.
	
Storage
	- Ideas for how to store data
	- One file for deployment?
	- binary data?
	- timestamp?
	- truncation / averaging?
	
Battery monitoring and Micro power
	- Methods for sample and sleep mode
	- auto shutdown for low voltage
	- analog front end shutdown
	
DSP routines?
	- Try doing some DSP instead of sending raw voltage counts