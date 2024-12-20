/*
    LCD_I2C - Arduino library to control a 16x2 LCD via an I2C adapter based on PCF8574
    * 2021-11-18 Brewmanz: make changes to also work for 20x4 LCD2004

    Copyright(C) 2020 Blackhack <davidaristi.0504@gmail.com>

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#ifndef _LCD_I2C_h
#define _LCD_I2C_h

#include "Arduino.h"

/* This struct helps us constructing the I2C output based on data and control outputs.
   Because the LCD is set to 4-bit mode, 4 bits of the I2C output are for the control outputs
   while the other 4 bits are for the 8 bits of data which are send in parts using the enable output.*/
struct OutputState
{
    uint8_t rs = 0;
    uint8_t rw = 0;
    uint8_t E = 0;
    uint8_t Led = 0;

    uint8_t getLowData(uint8_t data) const
    {
        return getCommonData() | ((data & 0x0F) << 4);
    }

    uint8_t getHighData(uint8_t data) const
    {
        return getCommonData() | (data & 0xF0);
    }

private:
    inline uint8_t getCommonData() const {
    	return rs | (rw << 1) | (E << 2) | (Led << 3);
    }
};

class LCD_I2C : public Print
{
public:
    LCD_I2C(uint8_t address, uint8_t columns = 16, uint8_t rows = 2)
    : _address(address), _columnMax(columns-1), _rowMax(rows-1), _displayState(0x00), _entryState(0x00) {}

    void begin(bool beginWire = true);
    void backlight();
    void noBacklight();

    void clear();
    void home();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();
    void display();
    void noDisplay();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void createChar(uint8_t location, uint8_t charmap[]);
    void setCursor(uint8_t col, uint8_t row);

    // Method used by the Arduino class "Print" which is the one that provides the .print(string) method
    virtual size_t write(uint8_t character);

private:
    void InitializeLCD();
    void I2C_Write(uint8_t output);
    void LCD_Write(uint8_t output, bool initialization = false);

private:
    const uint8_t _address;
    const uint8_t _columnMax; // Last valid column index. Note the column index starts at zero.
    const uint8_t _rowMax;    // Last valid row index. Note the row index starts at zero.
    OutputState _output;
    uint8_t _displayState;
    uint8_t _entryState;
};

#endif
