/**
 * @file nano_c6_dev.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief Arduino IDE用ファイル
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu(https://github.com/Chimipupu)
 * 
 */
#include "app_main.hpp"

void setup()
{
    Serial.begin(115200);
    pixels.begin();
    pixels.show();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(NEOPIXEL_PWR_PIN, OUTPUT);
    pinMode(IR_LED_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(NEOPIXEL_PWR_PIN, HIGH);

    // 初期色セット
    pixels.setPixelColor(0, colors[colorIndex]);
    pixels.show();
}

void loop()
{
    app_main();
}