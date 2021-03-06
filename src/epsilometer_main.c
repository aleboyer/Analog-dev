/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "stdint.h"


#include "ep_common.h"
#include "ep_analog.h"
#include "ep_coms.h"
#include "stdio.h"
#include "em_usart.h"

#include "em_chip.h"



#define STREAMMODE
//#define STORAGEMODE

/******************************************************************************/
/*************************** List of Possible Channels / Sensor *******************************/
/******************************************************************************/

epsiSetup boardSetup = EPSI_SETUP_DEFAULT;
epsiSetupPtr boardSetup_ptr = &boardSetup;

SensorSpec fp07_1 = {"T1", AD7124_RESET_DEFAULT, {gpioPortA, 0}};  //PA0
SensorSpec fp07_2 = {"T2", AD7124_RESET_DEFAULT, {gpioPortC, 5}};  //PC5
SensorSpec shr_1  = {"S1", AD7124_RESET_DEFAULT, {gpioPortC, 6}};  //PC6
SensorSpec shr_2  = {"S2", AD7124_RESET_DEFAULT, {gpioPortC, 7}};  //PC7
SensorSpec con_1  = {"C1", AD7124_RESET_DEFAULT, {gpioPortC, 12}}; //PC12
SensorSpec ax     = {"AX", AD7124_RESET_DEFAULT, {gpioPortC, 14}}; //PC14
SensorSpec ay     = {"AY", AD7124_RESET_DEFAULT, {gpioPortC, 15}}; //PC15
SensorSpec az     = {"AZ", AD7124_RESET_DEFAULT, {gpioPortA, 1}};  //PA1


volatile SensorSpec_ptr sensors[8]={&fp07_1, &fp07_2, &shr_1, &shr_2, &con_1, &ax, &ay, &az};


volatile uint32_t pendingSamples = 0; // counter in the background IRQ
volatile uint32_t samplesSent    = 0;    // counter in the foreground IRQ
volatile uint32_t numSync        = 0;    // number of sync signal sent
volatile uint32_t flagSync       = 0;    // flag to reset pending sample in the interrupt.
//int pendingSamples;


/******************************************************************************
 * @brief
 *   Main function.
 * @details
 *   Configures the DVK for SPI
 *****************************************************************************/
int main(void) {

    /* Initialize chip - handle erratas */
    CHIP_Init();

	/* Use 14 MHZ HFRCO as core clock frequency*/
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_TIMER0, true);
	CMU_ClockEnable(cmuClock_TIMER1, true);



//	numChannel       = boardSetup_ptr->numSensor + boardSetup_ptr->timeStampFlag;  // 2 temp 2 shear 1 cond 3 accelerometer
//	bufferSize       = boardSetup_ptr->maxSamples*numChannel;      //
//	byteSample       = numChannel*4;               // 4 bytes in numChannel uint32 channel
//	uint32_t coreclockCycle   = boardSetup_ptr->coreClock/boardSetup_ptr->MclockFreq;       // 0xb=11 cycles of 14MHz clock
//	uint32_t timer1PhaseShift = .5 * boardSetup_ptr->coreClock/boardSetup_ptr->MclockFreq;
//    dataBuffer    =  (uint32_t*) malloc(sizeof(uint32_t)*bufferSize);


	// define GPIO pin mode
	GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 1); // Enable Analog power
	GPIO_PinModeSet(gpioPortF, 3, gpioModePushPull, 1); // Enable 485 Driver
	GPIO_PinModeSet(gpioPortF, 4, gpioModePushPull, 0); // Enable 485 Receiver power
	GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 1); // Enable 485 Transmitter
	GPIO_PinModeSet(gpioPortA, 2,	gpioModePushPull, 1); // PA2 in output mode to send the MCLOCK  to ADC
	GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 1);   // PB7 in output mode to send the SYNC away




	for( int i = 0; i < boardSetup_ptr->numSensor ; i++) {
			AD7124_ChipSelect(sensors[i], LHI); // bring them all high
	}
	GPIO_PinModeSet(gpioPortC, 13, gpioModePushPull, 1); // and the ADA2200

#ifdef STREAMMODE
	UART_Setup();
#endif


	SPI_Init();     // Initialize the SPI interface for the Analog front end
	AD7124_Reset(); // Place devices into a known state

	setupGpioInt(); // Setup gpio Interupt but leave disabled


	AD7124 COMMON_SETUP = AD7124_RESET_DEFAULT;
	COMMON_SETUP.ERROR_EN = AD7124_ERREN_REG_REF_DET_ERR_EN | AD7124_ERREN_REG_SPI_IGNORE_ERR_EN;
	COMMON_SETUP.CONFIG_0 = AD7124_CONFIG_BIPOLAR |
				AD7124_CONFIG_BURNOUT_OFF |
				AD7124_CONFIG_INTREF |
				AD7124_CONFIG_GAIN_1;
	COMMON_SETUP.ADC_CONTROL = AD7124_CTRL_CS_EN(0) |
				AD7124_CTRL_HIG_PWR |
				AD7124_CTRL_CONT_MODE |
				AD7124_CTRL_REF_EN(2) |
				AD7124_CTRL_CLKSEL(2);

	COMMON_SETUP.FILTER_0 = 0x06003C; // 0x3C for 320hz on sinc4 filter



	AD7124 TEMP_SETUP = COMMON_SETUP;
	TEMP_SETUP.CHANNEL_0 = AD7124_CH_EN | AD7124_CH_AINP(0) | AD7124_CH_AINM(1);

	AD7124 SHR_SETUP = COMMON_SETUP;
	SHR_SETUP.CHANNEL_0 = AD7124_CH_EN | AD7124_CH_AINP(0) | AD7124_CH_AINM(1);

	AD7124 ACCL_SETUP = COMMON_SETUP;
	ACCL_SETUP.CHANNEL_0 = AD7124_CH_EN | AD7124_CH_AINP(0) | AD7124_CH_AINM(AD7124_CH_AVSS);
	ACCL_SETUP.CONFIG_0 = AD7124_CONFIG_UNIPOLAR |
			AD7124_CONFIG_BURNOUT_OFF |
			AD7124_CONFIG_GAIN_1 |
			AD7124_CONFIG_INTREF;

	AD7124 COND_SETUP = COMMON_SETUP;
	COND_SETUP.CHANNEL_0 = AD7124_CH_EN | AD7124_CH_AINP(AD7124_CH_TEMP_SENSOR) | AD7124_CH_AINM(AD7124_CH_AVSS);
	COND_SETUP.CONFIG_0 = AD7124_CONFIG_UNIPOLAR |
			AD7124_CONFIG_BURNOUT_OFF |
			AD7124_CONFIG_GAIN_1 |
			AD7124_CONFIG_INTREF;

	AD7124 OFF_SETUP = AD7124_RESET_DEFAULT;
	OFF_SETUP.ADC_CONTROL = OFF_SETUP.ADC_CONTROL | AD7124_CTRL_PWRDOWN_MODE;


	//set up timer MCLOCK and SYNC
	//configure TIMER0 create and output a
	/* Configure TIMER */
	//TIMER_Init(TIMER0, &timerInit);
	TIMER0->CTRL =(TIMER0->CTRL &~_TIMER_CTRL_CLKSEL_MASK)| TIMER_CTRL_CLKSEL_PRESCHFPERCLK;
	TIMER0->CTRL =(TIMER0->CTRL &~_TIMER_CTRL_PRESC_MASK)| TIMER_CTRL_PRESC_DIV1;
	TIMER0->CTRL =(TIMER0->CTRL &~_TIMER_CTRL_MODE_MASK)| TIMER_CTRL_MODE_UP;
	TIMER0->TOP =(TIMER0->TOP &~_TIMER_TOP_MASK)| TIMER_TOP_TOP_DEFAULT;
    TIMER0->TOP =(TIMER0->TOP &~_TIMER_TOP_MASK)| 0xb;
	TIMER0->CC[2].CTRL =(TIMER0->CC[2].CTRL &~_TIMER_CC_CTRL_MODE_MASK)| TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
	TIMER0->CC[2].CTRL =(TIMER0->CC[2].CTRL &~_TIMER_CC_CTRL_CMOA_MASK)| TIMER_CC_CTRL_CMOA_TOGGLE;
	TIMER0->CC[2].CCV =(TIMER0->CC[2].CCV &~_TIMER_CC_CCV_CCV_MASK)| TIMER_CC_CCV_CCV_DEFAULT;
	TIMER0->CC[2].CTRL =(TIMER0->CC[2].CTRL &~_TIMER_CC_CTRL_OUTINV_MASK)| TIMER_CC_CTRL_OUTINV;
	TIMER0->CC[2].CCV =(TIMER0->CC[2].CCV &~_TIMER_CC_CCV_CCV_MASK)| 0x6;  // control the phase of TIMER0
	TIMER0->ROUTE =(TIMER0->ROUTE &~_TIMER_ROUTE_LOCATION_MASK)| TIMER_ROUTE_LOCATION_LOC0;
	TIMER0->ROUTE =(TIMER0->ROUTE &~_TIMER_ROUTE_MASK)| TIMER_ROUTE_CC2PEN;

	//configure TIMER1 to help SYNC the ADC
	TIMER1->CTRL =(TIMER1->CTRL &~_TIMER_CTRL_MODE_MASK)| TIMER_CTRL_MODE_UP;
	TIMER1->CTRL =(TIMER1->CTRL &~_TIMER_CTRL_OSMEN_MASK)| TIMER_CTRL_OSMEN;
    TIMER1->CTRL =(TIMER1->CTRL &~_TIMER_CTRL_SYNC_MASK)| TIMER_CTRL_SYNC_DEFAULT;
	TIMER1->CTRL =(TIMER1->CTRL &~_TIMER_CTRL_CLKSEL_MASK)| TIMER_CTRL_CLKSEL_TIMEROUF;
	TIMER1->CTRL =(TIMER1->CTRL &~_TIMER_CTRL_OSMEN_MASK)| TIMER_CTRL_OSMEN;
	TIMER1->CC[0].CTRL =(TIMER1->CC[0].CTRL &~_TIMER_CC_CTRL_MODE_MASK)| TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
	TIMER1->CC[0].CTRL =(TIMER1->CC[0].CTRL &~_TIMER_CC_CTRL_OUTINV_MASK)| TIMER_CC_CTRL_OUTINV;
	TIMER1->CC[0].CTRL =(TIMER1->CC[0].CTRL &~_TIMER_CC_CTRL_CMOA_MASK)| TIMER_CC_CTRL_CMOA_TOGGLE;
	TIMER1->CC[0].CTRL =(TIMER1->CC[0].CTRL &~_TIMER_CC_CTRL_INSEL_MASK)| TIMER_CC_CTRL_INSEL_PIN;
	TIMER1->TOP =(TIMER1->TOP &~_TIMER_TOP_MASK)| 0x13;
	TIMER1->ROUTE =(TIMER1->ROUTE &~_TIMER_ROUTE_MASK)| TIMER_ROUTE_CC0PEN;
	TIMER1->ROUTE =(TIMER1->ROUTE &~_TIMER_ROUTE_LOCATION_MASK)| TIMER_ROUTE_LOCATION_LOC3;


	uint32_t delay = 0xFFFF;
	while (delay--); // Delay after power on to ensure registers are ready to write
	AD7124_ConfigureDevice(&fp07_1, TEMP_SETUP);
	AD7124_ConfigureDevice(&fp07_2, TEMP_SETUP);
	AD7124_ConfigureDevice(&shr_1, SHR_SETUP);
	AD7124_ConfigureDevice(&shr_2, SHR_SETUP);
	AD7124_ConfigureDevice(&con_1, COND_SETUP);
	AD7124_ConfigureDevice(&ax, ACCL_SETUP);
	AD7124_ConfigureDevice(&ay, ACCL_SETUP);
	AD7124_ConfigureDevice(&az, ACCL_SETUP);


	/****************************************************************
	 * Primitive Sampling routine
	 * ***************************************************************/

	int pendingTimeout = 0;
	AD7124_StartConversion(&sensors[boardSetup_ptr->numSensor]);
	//res = f_lseek(&fsrc, 0);

		/****************************************************************
		 * Primitive Sampling routine
		 ****************************************************************/
	while (1) {

	    }// end while loop
}// end main
