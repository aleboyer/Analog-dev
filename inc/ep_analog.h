/***************************************************************************//**
 *   @file   AD7124.h
 *   @brief  Header file of AD7124 Driver.
 *   @author DNechita (Dan.Nechita@analog.com)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 903
*******************************************************************************/

#ifndef __AD7124_H__
#define __AD7124_H__


/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "stdint.h"
#include "em_gpio.h"
#include "ep_common.h"
#include "ep_coms.h"



/******************************************************************************/
/******************************** Defines *************************************/
/******************************************************************************/

#define _24SWAPEND(x) ((x>>16)&0xff) | 			\
                    	((x<<16)&0xff0000) | 	\
                    	((x)&0xff00)

#define _16SWAPEND(x) ((x>>8)&0xff) | 			\
                    	((x<<8)&0xff00) 	\

#define LHI 1
#define LLO 0


#define AD7124_RESET_DEFAULT                             	             	    \
  { 0x0,																		\
	0x0,																		\
	0x0,																		\
	0x0,																		\
	0x0,																		\
	0x0,																		\
	0x2,																		\
	0x0,																		\
	0x40,																		\
	0x0,																		\
	0x8001,																		\
	0x860,																		\
	0x60180,																	\
	0x800000,																	\
	0x500000																	\
  }


typedef struct AD7124_REGISTERS {
	uint8_t 	COMMS;
	uint8_t		STATUS;
	uint16_t	ADC_CONTROL;
	uint32_t 	DATA;
	uint32_t 	IO_CONTROL_1;
	uint16_t	IO_CONTROL_2;
	uint8_t		ID;
	uint32_t	ERROR;
	uint32_t	ERROR_EN;
	uint8_t		MCLK_COUNT;
	uint16_t	CHANNEL_0;
	uint16_t	CONFIG_0;
	uint32_t	FILTER_0;
	uint32_t	OFFSET_0;
	uint32_t	GAIN_0;
} AD7124;

typedef struct {
	uint8_t gpioPort;
	uint8_t gpioPin;
} csLocation;

typedef struct SensorSpec{
	char				name[2]; 		// Sensor Name/ID
	AD7124 				registers; 		// Software register emulators
	csLocation			csLoc; 			// Location
} SensorSpec, *SensorSpec_ptr;


/******************************************************************************/
/************************ external variable       *****************************/
/******************************************************************************/
extern volatile SensorSpec_ptr sensors[8];

/******************************************************************************/
/************************ AD7124 Register Defines *****************************/
/******************************************************************************/

/* AD7124 Register Map */
#define AD7124_REG_COMM			0x00		// Communications Register 					(WO, 8-bit)
#define AD7124_REG_STATUS		0x00 		// Status Register         					(RO, 8-bit)
#define AD7124_REG_CTRL			0x01 		// Ctrl Register           					(RW, 16-bit)
#define AD7124_REG_DATA			0x02 		// Data Register							(RO, 24-bit)
#define AD7124_REG_IOCTRL1		0x03 		// I/O Control 1 Register					(RW, 24-bit)
#define AD7124_REG_IOCTRL2		0x04 		// I/O Control 2 Register   				(RW, 16-bit)
#define AD7124_REG_ID			0x05 		// ID Register             					(R, 8-bit)
#define AD7124_REG_ERROR		0x06 		// Error Register        					(RW, 24-bit)
#define AD7124_REG_ERROREN		0x07 		// Error Enable Register 					(RW, 24-bit)
#define AD7124_REG_MCLK			0x08		// MCLK Register							(R, 8-bit)
#define AD7124_REG_CH0			0x09		// Ch 0 Register							(RW, 16-bit)
#define AD7124_REG_CH1			0x0A		// Ch 1 Register							(RW, 16-bit)
#define AD7124_REG_CFG0			0x19		// Ch 0 Cfg Register						(RW, 16-bit)
#define AD7124_REG_CFG1			0x1A		// Ch 1 Cfg Register						(RW, 16-bit)
#define AD7124_REG_FLTR0		0x21		// Ch 0 Filter Register						(RW, 24-bit)
#define AD7124_REG_FLTR1		0x22		// Ch 1 Filter Register						(RW, 24-bit)
#define AD7124_REG_CH0OFFSET	0x29		// Ch 0 Offset Register						(RW, 24-bit)
#define AD7124_REG_CH1OFFSET	0x2A		// Ch 1 Offset Register						(RW, 24-bit)
#define AD7124_REG_GAIN0		0x31		// Ch 0 Gain Register						(RW, 24-bit)
#define AD7124_REG_GAIN1		0x32		// Ch 1 Gain Register						(RW, 24-bit)

/* Communications Register Bit Designations (AD7124_REG_COMM) */
#define AD7124_COMM_WRITE			(0x0 << 6)						// Write Operation.
#define AD7124_COMM_READ			(0x1 << 6)						// Read Operation.

/* Status Register Bit Designations (AD7124_REG_STAT) */
#define AD7124_STATUS_RDY				(1 << 7)			// Ready.
#define AD7124_STATUS_ERROR				(1 << 6)			// ADC error bit.
#define AD7124_STATUS_POR				(1 << 4)			// Power-on Reset Flag
#define AD7124_STATUS_CH_MASK			(0xF)				// ADC Status Channel Mask
#define AD7124_STATUS_REG_CH_ACTIVE(x) 	((x) & 0xF)			// Quick macro for checking active CH
#define AD7124_STATUS_CH(x)				(x)					// Channel 0-15.

/* Adc Control Register */
#define AD7124_CTRL_DEFAULT_MASK			(0x0000)
#define AD7124_CTRL_DOUT_RDY_DELAY			(1 << 12)
#define AD7124_CTRL_CONT_READ(x)			(x << 11)
#define AD7124_CTRL_DATA_STATUS(x)			(x << 10)
#define AD7124_CTRL_CS_EN(x)				(x << 9)
#define AD7124_CTRL_REF_EN(x)				(x << 8)

#define AD7124_CTRL_PWR_MASK				(0x3 << 6)
#define AD7124_CTRL_LOW_PWR					(0 << 6)
#define AD7124_CTRL_MID_PWR					(1 << 6)
#define AD7124_CTRL_HIG_PWR					(2 << 6)

#define AD7124_CTRL_MODE_MASK				(0xF << 2)
#define AD7124_CTRL_CONT_MODE				(0x0 << 2)
#define AD7124_CTRL_SINGLE_MODE				(0x1 << 2)
#define AD7124_CTRL_STANDBY_MODE			(0x2 << 2)
#define AD7124_CTRL_PWRDOWN_MODE			(0x3 << 2)
#define AD7124_CTRL_IDLE_MODE				(0x4 << 2)

#define AD7124_CTRL_CLKSEL_MASK				(0x3 << 0)
#define AD7124_CTRL_CLKSEL(x)				(x & 0x03) /*	0 = Internal 614kHz clock, no clk out
													        1 = Internal 614kHz clock, clk pin out
													        2 = external 614kHz clock
													        3 = external 614kHz clock / 4	*/

/* IO_Control_1 Register bits */
#define AD7124_IO_CTRL1_GPIO_DAT2     (1 << 23)
#define AD7124_IO_CTRL1_GPIO_DAT1     (1 << 22)
#define AD7124_IO_CTRL1_GPIO_CTRL2    (1 << 19)
#define AD7124_IO_CTRL1_GPIO_CTRL1    (1 << 18)
#define AD7124_IO_CTRL1_PDSW          (1 << 15)
#define AD7124_IO_CTRL1_IOUT1(x)      (((x) & 0x7) << 11)
#define AD7124_IO_CTRL1_IOUT0(x)      (((x) & 0x7) << 8)
#define AD7124_IO_CTRL1_IOUT_CH1(x)   (((x) & 0xF) << 4)
#define AD7124_IO_CTRL1_IOUT_CH0(x)   (((x) & 0xF) << 0)

/* IO_Control_2 Register bits */
#define AD7124_IO_CTRL2_GPIO_VBIAS7   (1 << 15)
#define AD7124_IO_CTRL2_GPIO_VBIAS6   (1 << 14)
#define AD7124_IO_CTRL2_GPIO_VBIAS5   (1 << 11)
#define AD7124_IO_CTRL2_GPIO_VBIAS4   (1 << 10)
#define AD7124_IO_CTRL2_GPIO_VBIAS3   (1 << 5)
#define AD7124_IO_CTRL2_GPIO_VBIAS2   (1 << 4)
#define AD7124_IO_CTRL2_GPIO_VBIAS1   (1 << 1)
#define AD7124_IO_CTRL2_GPIO_VBIAS0   (1 << 0)

/* ID Register bits */
#define AD7124_ID_REG_DEVICE_ID(x)   (((x) & 0xF) << 4)
#define AD7124_ID_REG_SILICON_REV(x) (((x) & 0xF) << 0)

/* Error Register bits */
#define AD7124_ERR_REG_LDO_CAP_ERR        (1 << 19)
#define AD7124_ERR_REG_ADC_CAL_ERR        (1 << 18)
#define AD7124_ERR_REG_ADC_CONV_ERR       (1 << 17)
#define AD7124_ERR_REG_ADC_SAT_ERR        (1 << 16)
#define AD7124_ERR_REG_AINP_OV_ERR        (1 << 15)
#define AD7124_ERR_REG_AINP_UV_ERR        (1 << 14)
#define AD7124_ERR_REG_AINM_OV_ERR        (1 << 13)
#define AD7124_ERR_REG_AINM_UV_ERR        (1 << 12)
#define AD7124_ERR_REG_REF_DET_ERR        (1 << 11)
#define AD7124_ERR_REG_DLDO_PSM_ERR       (1 << 9)
#define AD7124_ERR_REG_ALDO_PSM_ERR       (1 << 7)
#define AD7124_ERR_REG_SPI_IGNORE_ERR     (1 << 6)
#define AD7124_ERR_REG_SPI_SLCK_CNT_ERR   (1 << 5)
#define AD7124_ERR_REG_SPI_READ_ERR       (1 << 4)
#define AD7124_ERR_REG_SPI_WRITE_ERR      (1 << 3)
#define AD7124_ERR_REG_SPI_CRC_ERR        (1 << 2)
#define AD7124_ERR_REG_MM_CRC_ERR         (1 << 1)

/* Error_En Register bits */
#define AD7124_ERREN_REG_MCLK_CNT_EN           (1 << 22)
#define AD7124_ERREN_REG_LDO_CAP_CHK_TEST_EN   (1 << 21)
#define AD7124_ERREN_REG_LDO_CAP_CHK(x)        (((x) & 0x3) << 19)
#define AD7124_ERREN_REG_ADC_CAL_ERR_EN        (1 << 18)
#define AD7124_ERREN_REG_ADC_CONV_ERR_EN       (1 << 17)
#define AD7124_ERREN_REG_ADC_SAT_ERR_EN        (1 << 16)
#define AD7124_ERREN_REG_AINP_OV_ERR_EN        (1 << 15)
#define AD7124_ERREN_REG_AINP_UV_ERR_EN        (1 << 14)
#define AD7124_ERREN_REG_AINM_OV_ERR_EN        (1 << 13)
#define AD7124_ERREN_REG_AINM_UV_ERR_EN        (1 << 12)
#define AD7124_ERREN_REG_REF_DET_ERR_EN        (1 << 11)
#define AD7124_ERREN_REG_DLDO_PSM_TRIP_TEST_EN (1 << 10)
#define AD7124_ERREN_REG_DLDO_PSM_ERR_ERR      (1 << 9)
#define AD7124_ERREN_REG_ALDO_PSM_TRIP_TEST_EN (1 << 8)
#define AD7124_ERREN_REG_ALDO_PSM_ERR_EN       (1 << 7)
#define AD7124_ERREN_REG_SPI_IGNORE_ERR_EN     (1 << 6)
#define AD7124_ERREN_REG_SPI_SCLK_CNT_ERR_EN   (1 << 5)
#define AD7124_ERREN_REG_SPI_READ_ERR_EN       (1 << 4)
#define AD7124_ERREN_REG_SPI_WRITE_ERR_EN      (1 << 3)
#define AD7124_ERREN_REG_SPI_CRC_ERR_EN        (1 << 2)
#define AD7124_ERREN_REG_MM_CRC_ERR_EN         (1 << 1)

/* Channel Register: AD7124_CONF_CHAN(x) options */

#define AD7124_CH_EN						(0x1 << 15)
#define AD7124_CH_DIS						(0x0 << 15)
#define AD7124_CH_SETUP(x)					(((x) & 0x7) << 12)
#define AD7124_CH_AINP(x)					(((x) & 0x1F) << 5)
#define AD7124_CH_AINM(x)					(((x) & 0x1F) << 0)

#define AD7124_CH_AVSS						0x11
#define AD7124_CH_DGND						0x13
#define AD7124_CH_TEMP_SENSOR				0x10
#define	AD7124_CH_INT_REF					0x12


/* Configuration Register Bit Designations (AD7124_REG_CONF) */
#define AD7124_CONFIG_DEFAULT_MASK			(0x0860)
#define AD7124_CONFIG_BIPOLAR				(1 << 11)            // Bipolar on/off.
#define AD7124_CONFIG_UNIPOLAR				(0 << 11)            // Bipolar on/off.

#define AD7124_CONFIG_BURNOUT_OFF      		(0x0 << 9)		// off
#define AD7124_CONFIG_BURNOUT_05UA      	(0x1 << 9)		// 0.5uA
#define AD7124_CONFIG_BURNOUT_2UA      		(0x2 << 9)		// 2uA
#define AD7124_CONFIG_BURNOUT_4UA      		(0x3 << 9)		// 4uA

#define AD7124_CONFIG_REF_BUFP(z)				(0xz << 7)		//Buffer ref posative input on/off
#define AD7124_CONFIG_REF_BUFM(z)				(0xz << 6)		// Buffer ref negative input on/off
#define AD7124_CONFIG_AIN_BUFP(z)				(0xz << 5)		// Buffer AIN positive input on/off
#define AD7124_CONFIG_AIN_BUFM(z)				(0xz << 4)		// Buffer AIN negative input on/off

#define AD7124_CONFIG_REFSEL1					(0x0 << 2) 		//Ref 1 Select
#define AD7124_CONFIG_REFSEL2					(0x1 << 2)		// Ref 2 Select
#define AD7124_CONFIG_INTREF					(0x2 << 3)		// Internal Ref
#define AD7124_CONFIG_REFAVDD					(0x3 << 2)		// AVdd

#define AD7124_CONFIG_GAIN_1					0 				// Gain 1
#define AD7124_CONFIG_GAIN_2					1 				// Gain 2
#define AD7124_CONFIG_GAIN_4					2 				// Gain 4
#define AD7124_CONFIG_GAIN_8					3 				// Gain 8
#define AD7124_CONFIG_GAIN_16					4 				// Gain 16
#define AD7124_CONFIG_GAIN_32					5 				// Gain 32
#define AD7124_CONFIG_GAIN_64					6 				// Gain 64
#define AD7124_CONFIG_GAIN_128					7 				// Gain 128

/* Filter Register 0-7 bits */
#define AD7124_FILT_REG_FILTER(x)         (((x) & 0x7) << 21)
#define AD7124_FILT_REG_REJ60             (1 << 20)
#define AD7124_FILT_REG_POST_FILTER(x)    (((x) & 0x7) << 17)
#define AD7124_FILT_REG_SINGLE_CYCLE      (1 << 16)
#define AD7124_FILT_REG_FS(x)             (((x) & 0x7FF) << 0)


/******************************************************************************/
/******************** Exported Function Declarations **************************/
/******************************************************************************/

/*! Writes data into a register. */
void AD7124_SetRegisterValue(	SensorSpec *s,
								uint8_t registerAddress,
								uint32_t registerValue,
								uint8_t bytes);

/*! Reads the value of a register. */
uint32_t AD7124_GetRegisterValue(	SensorSpec *s,
									uint8_t registerAddress,
									uint8_t bytes);

/*! Resets the device. */
void AD7124_Reset(void);

/*! Returns the result of a single conversion. */
//void AD7124_StartConversion(Sensor *s);
void AD7124_StartConversion();

void AD7124_ChipSelect(SensorSpec *s, int state);

void AD7124_ConfigureDevice(SensorSpec *s, AD7124 regSetup);

void SPI_Init();

void setupGpioInt();

#endif /* __AD7124_H__ */
