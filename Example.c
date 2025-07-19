#include "lcd_i2c.h"
extern I2C_HandleTypeDef hi2c1;  // تعریف‌شده در main.c یا i2c.c

uint8_t heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    LCDInit();
    LCDCreateChar(0, heart);
    LCDSetCursor(0, 0);
    LCDPrint("I2C LCD Ready");
    LCDSetCursor(1, 0);
    LCDSendData(0);  // نمایش قلب

    while (1) {}
}