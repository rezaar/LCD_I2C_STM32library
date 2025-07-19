#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdio.h>

// ===== تنظیمات =====
#define LCD_ADDR 0x27 << 1    // آدرس I2C قابل تغییر
#define LCD_COLS 16
#define LCD_ROWS 2

extern I2C_HandleTypeDef hi2c1; // هندل I2C (باید در main تعریف شده باشد)

// ===== توابع اصلی =====
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(const char *str);
void LCD_CreateChar(uint8_t location, uint8_t charmap[]);
void LCD_PrintInt(int num);
void LCD_PrintFloat(float num, uint8_t decimal_places);
void LCD_SendData(uint8_t data);
void LCD_SendCommand(uint8_t cmd);

// ===== توابع اسکرول =====
void LCD_ScrollText(uint8_t row, const char *text, uint16_t delay_ms);
void LCD_ScrollTextLoop(uint8_t row, const char *text, uint16_t delay_ms);
void LCD_ScrollTextBounce(uint8_t row, const char *text, uint16_t delay_ms);

#endif
