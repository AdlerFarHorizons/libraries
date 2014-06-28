/*

HMC5883L_T.h - Header file for Teensy version. Changed as noted in comments. Formerly...

HMC5883L.h - Header file for the HMC5883L Triple Axis Magnetometer Arduino Library.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk) / 2012 bildr.org (Arduino 1.0 compatible)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

 WARNING: THE HMC5883L IS NOT IDENTICAL TO THE HMC5883!
 Datasheet for HMC5883L:
 http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf

*/

#ifndef HMC5883L_T_h
#define HMC5883L_T_h

#include <Arduino.h>
#include <Wire.h>



#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03
#define StatusRegister 0x09

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define Averaging_1 0x00
#define Averaging_2	0x20
#define Averaging_4 0x40
#define Averaging_8	0x60

#define Rate_0_75 0x00
#define Rate_1_5  0x04
#define Rate_3    0x08
#define Rate_7_5  0x0c
#define Rate_15   0x10
#define Rate_30   0x14
#define Rate_75   0x18

#define Bias_Normal 0x00
#define Bias_Positive 0x01
#define Bias_Negative 0x02

#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1

struct MagnetometerScaled
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

// Types changed from int to int16_t for Teensy
struct MagnetometerRaw
{
	int16_t XAxis;
	int16_t YAxis;
	int16_t ZAxis;
};

class HMC5883L
{
	public:
	  HMC5883L();

	  MagnetometerRaw ReadRawAxis();
	  MagnetometerScaled ReadScaledAxis();
  
	  int SetConfiguration(uint8_t averaging, uint8_t rate, uint8_t bias);
	  int SetMeasurementMode(uint8_t mode);
	  int SetScale(float gauss);

	  char* GetErrorText(int errorCode);

	  uint8_t GetStatus();
	  
	protected:
	  void Write(int address, int byte);
	  uint8_t* Read(int address, int length);

	private:
	  float m_Scale;
};
#endif
