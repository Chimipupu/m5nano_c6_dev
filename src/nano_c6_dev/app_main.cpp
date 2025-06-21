/**
 * @file app_main.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメイン
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu(https://github.com/Chimipupu)
 * 
 */
#include "app_main.hpp"
#include <Adafruit_NeoPixel.h>
#include "app_wifi.hpp"

Adafruit_NeoPixel g_neopixel(NUMPIXELS, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);

int g_color_Idx = 0;

// 色配列（赤、黄、橙、黄緑、緑、青、紫、白）
uint32_t colors[] = {
    g_neopixel.Color(255, 0, 0),      // 赤
    g_neopixel.Color(255, 255, 0),    // 黄
    g_neopixel.Color(255, 165, 0),    // 橙
    g_neopixel.Color(173, 255, 47),   // 黄緑
    g_neopixel.Color(0, 255, 0),      // 緑
    g_neopixel.Color(0, 0, 255),      // 青
    g_neopixel.Color(128, 0, 128),    // 紫
    g_neopixel.Color(255, 255, 255)   // 白
};

/**
 * @brief ガウス＝ルジャンドル法による円周率計算
 * 
 * @param iterations 反復計算回数
 * @return double 円周率の計算結果
 */
double pi_gauss_legendre(uint32_t iterations)
{
    double a = 1.0;
    double b = 1.0 / sqrt(2.0);
    double t = 0.25;
    double p = 1.0;

    for (int i = 0; i < iterations; i++)
    {
        double a_next = (a + b) / 2.0;
        double b_next = sqrt(a * b);
        double t_next = t - p * pow(a - a_next, 2);
        a = a_next;
        b = b_next;
        t = t_next;
        p *= 2.0;
    }
    return pow(a + b, 2) / (4.0 * t);
}

/**
 * @brief アプリ初期化
 * 
 */
void app_init(void)
{
    // シリアル通信初期化
    Serial.begin(115200);

    // GPIO初期化
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(NEOPIXEL_PWR_PIN, OUTPUT);
    pinMode(IR_LED_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(NEOPIXEL_PWR_PIN, HIGH);

    // NeoPixel初期化
    g_neopixel.begin();
    g_neopixel.show();
    g_neopixel.setPixelColor(0, colors[g_color_Idx]);
    g_neopixel.show();

    // WiFi初期化
    app_wifi_init();
}

/**
 * @brief アプリメイン
 * 
 */
void app_main(void)
{
    bool currentButtonState = digitalRead(BUTTON_PIN);

    // WiFiメイン
    app_wifi_main();

    // ボタン処理関連
    if (currentButtonState == LOW) {
        // 色を次に進める
        g_color_Idx++;
        if (g_color_Idx >= sizeof(colors) / sizeof(colors[0])) {
            g_color_Idx = 0;
        }

        // NeoPixelに色をセット
        g_neopixel.setPixelColor(0, colors[g_color_Idx]);
        g_neopixel.show();

        // RGB値をシリアルに表示
        uint32_t c = colors[g_color_Idx];
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;

        Serial.print("NeoPixel RGB: ");
        Serial.print(r);
        Serial.print(", ");
        Serial.print(g);
        Serial.print(", ");
        Serial.println(b);

        // 円周率
        double pi = pi_gauss_legendre(3);
        Serial.print("円周率 : ");
        Serial.println(pi, 15);
    }

    // delay(300);
}