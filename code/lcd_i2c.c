#include "lcd_i2c.h"

// بیت‌های کنترل
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RW        0x02
#define LCD_RS        0x01

static void LCD_SendInternal(uint8_t data, uint8_t flags) {
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up | flags | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[1] = up | flags | LCD_BACKLIGHT;
    data_arr[2] = lo | flags | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[3] = lo | flags | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_arr, 4, HAL_MAX_DELAY);
    HAL_Delay(1);
}

void LCD_SendCommand(uint8_t cmd) {
    LCD_SendInternal(cmd, 0x00);
}

void LCD_SendData(uint8_t data) {
    LCD_SendInternal(data, LCD_RS);
}

void LCD_Init(void) {
    HAL_Delay(50);
    LCD_SendCommand(0x33);
    LCD_SendCommand(0x32);
    LCD_SendCommand(0x28); // 4-bit, 2 line, 5x8 font
    LCD_SendCommand(0x0C); // Display on, cursor off
    LCD_SendCommand(0x06); // Increment cursor
    LCD_Clear();
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= LCD_ROWS) row = 0;
    if (col >= LCD_COLS) col = 0;
    LCD_SendCommand(0x80 | (row_offsets[row] + col));
}

void LCD_Print(const char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_CreateChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x07;
    LCD_SendCommand(0x40 | (location << 3));
    for (int i = 0; i < 8; i++) {
        LCD_SendData(charmap[i]);
    }
}

void LCD_PrintInt(int num) {
    char buffer[12];
    sprintf(buffer, "%d", num);
    LCD_Print(buffer);
}

void LCD_PrintFloat(float num, uint8_t decimal_places) {
    char format[10];
    char buffer[20];
    sprintf(format, "%%.%df", decimal_places);
    sprintf(buffer, format, num);
    LCD_Print(buffer);
}

// ===== اسکرول یک‌بار =====
void LCD_ScrollText(uint8_t row, const char *text, uint16_t delay_ms) {
    uint8_t len = strlen(text);

    if (len <= LCD_COLS) {
        LCD_SetCursor(row, 0);
        LCD_Print(text);
        return;
    }

    for (uint8_t i = 0; i <= len - LCD_COLS; i++) {
        LCD_SetCursor(row, 0);
        for (uint8_t j = 0; j < LCD_COLS; j++) {
            LCD_SendData(text[i + j]);
        }
        HAL_Delay(delay_ms);
    }
}

// ===== اسکرول بی‌نهایت =====
void LCD_ScrollTextLoop(uint8_t row, const char *text, uint16_t delay_ms) {
    char scrollText[100];
    snprintf(scrollText, sizeof(scrollText), "%s   %s", text, text);
    uint8_t len = strlen(scrollText);

    while (1) {
        for (uint8_t i = 0; i <= len - LCD_COLS; i++) {
            LCD_SetCursor(row, 0);
            for (uint8_t j = 0; j < LCD_COLS; j++) {
                LCD_SendData(scrollText[i + j]);
            }
            HAL_Delay(delay_ms);
        }
    }
}

// ===== اسکرول رفت و برگشتی =====
void LCD_ScrollTextBounce(uint8_t row, const char *text, uint16_t delay_ms) {
    uint8_t len = strlen(text);
    if (len <= LCD_COLS) {
        LCD_SetCursor(row, 0);
        LCD_Print(text);
        return;
    }

    uint8_t end = len - LCD_COLS;

    while (1) {
        for (uint8_t i = 0; i <= end; i++) {
            LCD_SetCursor(row, 0);
            for (uint8_t j = 0; j < LCD_COLS; j++) {
                LCD_SendData(text[i + j]);
            }
            HAL_Delay(delay_ms);
        }

        for (int i = end - 1; i >= 0; i--) {
            LCD_SetCursor(row, 0);
            for (uint8_t j = 0; j < LCD_COLS; j++) {
                LCD_SendData(text[i + j]);
            }
            HAL_Delay(delay_ms);
        }
    }
}
