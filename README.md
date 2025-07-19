<h1 align="center">📟 کتابخانه LCD I2C برای STM32 (با قابلیت‌های پیشرفته)</h1>

<p align="center">
  <img src="https://img.shields.io/badge/stm32f1xx-supported-green?style=flat-square" />
  <img src="https://img.shields.io/badge/I2C-LCD%20PCF8574-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/Language-C-blue.svg?style=flat-square" />
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square" />
</p>

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/d/d1/LCD_blue_backlight.jpg" width="300">
</p>

---

## 💡 معرفی

این پروژه شامل یک **کتابخانه سبک و حرفه‌ای** برای راه‌اندازی نمایشگرهای LCD کاراکتری 16x2 یا 20x4 با استفاده از ماژول I2C (تراشه PCF8574) بر روی میکروکنترلرهای **STM32 (HAL-based)** است.

کتابخانه علاوه بر توابع پایه، دارای قابلیت‌های پیشرفته‌ای مانند:
- اسکرول متن ساده، حلقه‌ای و رفت‌وبرگشتی
- پشتیبانی از چاپ عدد صحیح و اعشاری
- تعریف کاراکترهای سفارشی (مثل ♥ یا آیکون‌ها)
- طراحی ماژولار و قابل توسعه

---

## ⚙️ ویژگی‌ها

| ویژگی                 | توضیح |
|-----------------------|-------|
| ✅ پشتیبانی از HAL    | سازگار با `stm32f1xx_hal` |
| ✅ LCD های 16x2 و 20x4 | قابل تنظیم در فایل هدر |
| ✅ اسکرول پیشرفته     | شامل اسکرول ساده، حلقه‌ای، و رفت‌وبرگشتی |
| ✅ پشتیبانی از UTF-8  | (در صورت افزودن) |
| ✅ کد تمیز و ماژولار  | مناسب پروژه‌های تجاری و آموزشی |

---
---

## 🖼️ تصویر پروژه نمونه

<p align="center">
  <img src="images/demo.jpg" width="400" alt="پروژه LCD I2C با STM32">
</p>

---