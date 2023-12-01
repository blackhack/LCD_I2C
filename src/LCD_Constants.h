#ifndef _LCD_CONSTANTS_H
#define _LCD_CONSTANTS_H

/**
 * @brief Define Instructions Constants of HD44780U
 * 
 */
constexpr int LCD_CLEAR {0b00000001};
constexpr int LCD_HOME  {0b00000010};
constexpr int LCD_ENTRY_MODE_SET  {0b00000100};
constexpr int LCD_DISPLAY_CONTROL  {0b00001000};
constexpr int LCD_CURSOR_OR_DISPLAY_SHIFT  {0b00010000};
constexpr int LCD_FUNCTION_SET  {0b00100000};
constexpr int LCD_SET_CGRAM_ADDR  {0b01000000};
constexpr int LCD_SET_DDRRAM_ADDR  {0b10000000};






#endif