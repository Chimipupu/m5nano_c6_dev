/**
 * @file app_main.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメインヘッダー
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu(https://github.com/Chimipupu)
 * 
 */
#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include <stdint.h>
#include <string.h>

#define NEOPIXEL_PWR_PIN        19 // NeoPixelの電源ピン
#define NEOPIXEL_DATA_PIN       20 // NeoPixelのデータピン
#define NUMPIXELS 1                // LEDの数

#define BUTTON_PIN              9  // ボタンのピン番号
#define LED_PIN                 7    // LEDのピン番号
#define IR_LED_PIN              3  // IR LEDのピン番号

void app_init(void);
void app_main(void);

#endif // APP_MAIN_HPP