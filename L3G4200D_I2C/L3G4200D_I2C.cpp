/*

L3G4200D_I2C.h - Source file for the L3G4200H triple axis gyro / angular rate sensor Arduino library

Author: Ryan Pierce, rdpierce@pobox.com

*/

#include <Arduino.h> 
#include "L3G4200D_I2C.h"

L3G4200D_I2C::L3G4200D_I2C(bool bSDO) {
	m_Address = L3G4200D_I2C_Base_Address;
	if (bSDO)
		++m_Address;
}

uint8_t L3G4200D_I2C::Initialize(uint16_t rate) {
	// Defaults:
	// 100 Hz data rate
	// 12.5 bandwidth cutoff
	// Power down mode: normal
	// X, Y, Z axes enabled
	Write(L3G4200D_I2C_CTRL_REG1, 0b00001111);
	// High Pass Filter Mode: Normal mode (reset reading HP_RESET_FILTER)
	// High Pass Filter Cutoff Frequency: 8 Hz
	// Note: High Pass Filter is disabled in CTRL_REG5 below
	Write(L3G4200D_I2C_CTRL_REG2, 0b00000000);
	// Interrupt enable INT1: Disable
	// Boot status enable INT1: Disable
	// Interrupt active config INT1: Disable
	// Push-Pull vs. Open Drain: Push-Pull
	// Data ready on DRDY/INT2: Disable
	// FIFO watermark interrupt on DRDY/INT2: Disable
	// FIFO overrun interrupt on DRDY/INT2: Disable
	// FIFO empty interrupt on DRDY/INT2: Disable
	Write(L3G4200D_I2C_CTRL_REG3, 0b00000000);
	// CTRL_REG4 contains rate
	// Reboot memory content: Normal
	// FIFO disable
	// High Pass filter disable
	// Non-High Pass filter data used for interrupt generation
	// Data in DataReg and FIFO are non-High Pass Filtered
	Write(L3G4200D_I2C_CTRL_REG5, 0b00000000);	
	return SetRate(rate);
}

uint8_t L3G4200D_I2C::SetRate(uint16_t rate) {
	// All the writes below set:
	// Block Data Update: Continuous
	// Endian: Data LSB at lower address
	// Self Test Disabled
	// SPI mode: 4 wire (doesn't matter, we use I2C)
	
	switch ( rate ) {
		case 250:
			Write(L3G4200D_I2C_CTRL_REG4, 0b00000000);
			m_Scale = 0.00875;
			return 0;
			break;
		case 500:
			Write(L3G4200D_I2C_CTRL_REG4, 0b00010000);
			m_Scale = 0.0175;
			return 0;
			break;
		case 2000:
			Write(L3G4200D_I2C_CTRL_REG4, 0b00100000);
			m_Scale = 0.07;
			return 0;
			break;
		default:
			return L3G4200D_I2C_ErrorCode_1_Num;
	}
}

bool L3G4200D_I2C::CheckWhoAmI() {
	uint8_t* buffer = Read(L3G4200D_I2C_WHO_AM_I, 1);
	return (buffer[0] == 0b11010011);
}

L3G4200D_I2C_GyroRaw L3G4200D_I2C::ReadRawAxis() {
  uint8_t* buffer = Read(L3G4200D_I2C_OUT_X_L | 0x80, 6);
  L3G4200D_I2C_GyroRaw raw = L3G4200D_I2C_GyroRaw();
  raw.XRate = (buffer[1] << 8) | buffer[0];
  raw.YRate = (buffer[3] << 8) | buffer[2];
  raw.ZRate = (buffer[5] << 8) | buffer[4];
  return raw;  
}

L3G4200D_I2C_GyroScaled L3G4200D_I2C::ReadScaledAxis() {
	L3G4200D_I2C_GyroRaw raw = ReadRawAxis();
	return Raw2Scaled(raw);
}

L3G4200D_I2C_GyroScaled L3G4200D_I2C::Raw2Scaled(L3G4200D_I2C_GyroRaw raw) {
	L3G4200D_I2C_GyroScaled scaled = L3G4200D_I2C_GyroScaled();
	scaled.XRate = raw.XRate * m_Scale;
	scaled.YRate = raw.YRate * m_Scale;
	scaled.ZRate = raw.ZRate * m_Scale;
	return scaled;
}

char* L3G4200D_I2C::GetErrorText(uint8_t errorCode)
{
	if(L3G4200D_I2C_ErrorCode_1_Num == 1)
		return L3G4200D_I2C_ErrorCode_1;
	
	return "Error not defined.";
}
		
void L3G4200D_I2C::Write(uint8_t address, uint8_t data) {
	Wire.beginTransmission(m_Address);
	Wire.write(address);
	Wire.write(data);
	Wire.endTransmission();
}

uint8_t* L3G4200D_I2C::Read(uint8_t address, uint8_t length) {
	Wire.beginTransmission(m_Address);
	Wire.write(address);
	Wire.endTransmission();
  
	Wire.beginTransmission(m_Address);
	Wire.requestFrom(m_Address, length);

	uint8_t buffer[length];
	if(Wire.available() == length) {
		for(uint8_t i = 0; i < length; i++) {
			buffer[i] = Wire.read();
		}	
	}
	Wire.endTransmission();

	return buffer;
}

