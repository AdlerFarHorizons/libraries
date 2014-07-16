/*

L3G4200D_I2C.h - Header file for the L3G4200H triple axis gyro / angular rate sensor Arduino library

Note: This chip supports I2C and SPI interfaces; this library supports I2C

Datasheet here: http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Gyros/3-Axis/CD00265057.pdf

Author: Ryan Pierce, rdpierce@pobox.com
Makes use of example code by Jim Lindblom, SparkFun Electronics
Patterned after and uses code from the HMC5883L library (C) 2011 Love Electronics (loveelectronics.co.uk)/ 2012 bildr.org

Circuit description:

GND -> Ground
VCC -> +3.3V
SCL and SDA -> Appropriate I2C pins for the Arduino in question
SDO -> To Ground or 3.3V (selects one of two I2C addresses, set bSDO to false or true, respectively)
CS -> +3.3V (selects I2C mode as opposed to SPI)
INT1 and INT2 -> Not currently supported

*/

#ifndef L3G4200D_I2C_h
#define L3G4200D_I2C_h

#include <Arduino.h>
#include <Wire.h>

#define L3G4200D_I2C_Base_Address 0x68

/*************************
    L3G4200D Registers
*************************/
#define L3G4200D_I2C_WHO_AM_I 0x0F
#define L3G4200D_I2C_CTRL_REG1 0x20
#define L3G4200D_I2C_CTRL_REG2 0x21
#define L3G4200D_I2C_CTRL_REG3 0x22
#define L3G4200D_I2C_CTRL_REG4 0x23
#define L3G4200D_I2C_CTRL_REG5 0x24
#define L3G4200D_I2C_REFERENCE 0x25
#define L3G4200D_I2C_OUT_TEMP 0x26
#define L3G4200D_I2C_STATUS_REG 0x27
#define L3G4200D_I2C_OUT_X_L 0x28
#define L3G4200D_I2C_OUT_X_H 0x29
#define L3G4200D_I2C_OUT_Y_L 0x2A
#define L3G4200D_I2C_OUT_Y_H 0x2B
#define L3G4200D_I2C_OUT_Z_L 0x2C
#define L3G4200D_I2C_OUT_Z_H 0x2D
#define L3G4200D_I2C_FIFO_CTRL_REG 0x2E
#define L3G4200D_I2C_FIFO_SRC_REG 0x2F
#define L3G4200D_I2C_INT1_CFG 0x30
#define L3G4200D_I2C_INT1_SRC 0x31
#define L3G4200D_I2C_INT1_TSH_XH 0x32
#define L3G4200D_I2C_INT1_TSH_XL 0x33
#define L3G4200D_I2C_INT1_TSH_YH 0x34
#define L3G4200D_I2C_INT1_TSH_YL 0x35
#define L3G4200D_I2C_INT1_TSH_ZH 0x36
#define L3G4200D_I2C_INT1_TSH_ZL 0x37
#define L3G4200D_I2C_INT1_DURATION 0x38

struct L3G4200D_I2C_GyroScaled
{
	float XRate;
	float YRate;
	float ZRate;
};

struct L3G4200D_I2C_GyroRaw
{
	int16_t XRate;
	int16_t YRate;
	int16_t ZRate;
};

#define L3G4200D_I2C_ErrorCode_1 "Entered rate scale was not valid, valid gauss values are: 250, 500, 2000"
#define L3G4200D_I2C_ErrorCode_1_Num 1

class L3G4200D_I2C
{
	public:
		L3G4200D_I2C(bool bSDO);
		uint8_t Initialize(uint16_t rate);
		uint8_t SetRate(uint16_t rate);
		bool CheckWhoAmI();
		
		L3G4200D_I2C_GyroRaw ReadRawAxis();
		L3G4200D_I2C_GyroScaled ReadScaledAxis();
		L3G4200D_I2C_GyroScaled Raw2Scaled(L3G4200D_I2C_GyroRaw raw);
		
		char* GetErrorText(uint8_t errorCode);
	protected:
		void Write(uint8_t address, uint8_t data);
		uint8_t* Read(uint8_t address, uint8_t length);
		
	private:
		uint8_t m_Address;
		float m_Scale;	  	  
};	  
	  
#endif