#include "DispLib.h"
#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#define printIIC(args)	Wire.write(args)
inline size_t LiquidCrystal_I2C::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

#else
#include "WProgram.h"

#define printIIC(args)	Wire.send(args)
inline void LiquidCrystal_I2C::write(uint8_t value) {
	send(value, Rs);
}

#endif
#include "Wire.h"

LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t lcd_addr,uint8_t lcd_cols,uint8_t lcd_rows)
{
  addr = lcd_addr;
  cols = lcd_cols;
  rows = lcd_rows;
}

void LiquidCrystal_I2C::init(){
	Wire.begin();
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  begin(cols, rows); 
}

void LiquidCrystal_I2C::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}
	delay(50); 
	expanderWrite(backlightval);
	delay(1000);
   write4bits(0x03 << 4);
   delayMicroseconds(4500);
   write4bits(0x03 << 4);
   delayMicroseconds(4500);
   write4bits(0x03 << 4); 
   delayMicroseconds(150);
   write4bits(0x02 << 4);
	command(LCD_FUNCTIONSET | _displayfunction);
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	clear();
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
	home();
}

void LiquidCrystal_I2C::clear(){
	command(LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}

void LiquidCrystal_I2C::home(){
	command(LCD_RETURNHOME);
	delayMicroseconds(2000);
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_I2C::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::backlight(void) {
	backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}

inline void LiquidCrystal_I2C::command(uint8_t value) {
	send(value, 0);
}

void LiquidCrystal_I2C::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void LiquidCrystal_I2C::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void LiquidCrystal_I2C::expanderWrite(uint8_t _data){                                        
	Wire.beginTransmission(addr);
	printIIC((int)(_data) | backlightval);
	Wire.endTransmission();   
}

void LiquidCrystal_I2C::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);
	delayMicroseconds(1);
	
	expanderWrite(_data & ~En);
	delayMicroseconds(50);
} 
	
