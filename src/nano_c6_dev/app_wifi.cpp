/**
 * @file app_wifi.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief WiFiアプリ
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu(https://github.com/Chimipupu)
 * 
 */
#include "app_wifi.hpp"
#include "app_main.hpp"
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

extern const char HTML_PAGE[];
extern Adafruit_NeoPixel g_neopixel;
WiFiServer server(HTTP_PORT);
// bool g_rgb_override_flg = false;
uint32_t g_current_color = 0;

static int getParamValue(String request, const String &key);

static int getParamValue(String request, const String &key)
{
    int idx = request.indexOf(key + "=");
    if (idx == -1)
        return 0;
    int start = idx + key.length() + 1;
    int endAmp = request.indexOf('&', start);
    int endSpc = request.indexOf(' ', start);
    int end = (endAmp == -1) ? endSpc : (endSpc == -1 ? endAmp : min(endAmp, endSpc));
    if (end == -1)
        end = request.length();
    return request.substring(start, end).toInt();
}

/**
 * @brief WiFiアプリ初期化
 * 
 */
void app_wifi_init(void)
{
    app_wifi_ap_init();
}

/**
 * @brief WiFiアプリメイン
 * 
 */
void app_wifi_main(void)
{
    WiFiClient client = server.available();
    String currentLine = "";
    String header = "";

    if (!client) {
        return;
    } else {
        Serial.println("New Client connected");
        String currentLine = "";
        while (client.connected())
        {
            if (client.available()) {
                char c = client.read();
                header += c;
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // LEDの制御
                        if (header.indexOf("GET /on") >= 0) {
                            digitalWrite(LED_PIN, HIGH);
                        } else if (header.indexOf("GET /off") >= 0) {
                            digitalWrite(LED_PIN, LOW);

                        // NeoPixelの制御
                        } else if (header.indexOf("/color/red") >= 0) {
                            g_current_color = g_neopixel.Color(255, 0, 0);
                        } else if (header.indexOf("/color/yellow") >= 0) {
                            g_current_color = g_neopixel.Color(255, 255, 0);
                        } else if (header.indexOf("/color/orange") >= 0) {
                            g_current_color = g_neopixel.Color(255, 165, 0);
                        } else if (header.indexOf("/color/yellowgreen") >= 0) {
                            g_current_color = g_neopixel.Color(173, 255, 47);
                        } else if (header.indexOf("/color/green") >= 0) {
                            g_current_color = g_neopixel.Color(0, 255, 0);
                        } else if (header.indexOf("/color/blue") >= 0) {
                            g_current_color = g_neopixel.Color(0, 0, 255);
                        } else if (header.indexOf("/color/purple") >= 0) {
                            g_current_color = g_neopixel.Color(128, 0, 128);
                        } else if (header.indexOf("/color/white") >= 0) {
                            g_current_color = g_neopixel.Color(255, 255, 255);
                        } else if (header.indexOf("GET /setrgb") >= 0) {
                            uint8_t r = getParamValue(header, "r");
                            uint8_t g = getParamValue(header, "g");
                            uint8_t b = getParamValue(header, "b");
                            g_current_color = g_neopixel.Color(r, g, b);
                            Serial.printf("Set RGB: R=%d G=%d B=%d\n", r, g, b);
                        }
                        // NeoPixelに色反映
                        g_neopixel.setPixelColor(0, g_current_color);
                        g_neopixel.show();

                        // HTTPレスポンスヘッダー
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        // HTML
                        client.print(HTML_PAGE);
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        delay(1);
        client.stop();
        Serial.println("Client disconnected");
    }
}

/**
 * @brief WiFi AP初期化
 * 
 */
void app_wifi_ap_init(void)
{
    WiFi.softAP(AP_SSID, AP_PASSWORD, AP_CHANNEL, 0, AP_MAX_CONN);

    Serial.println("WiFi AP Started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    server.begin();
    Serial.println("HTTP server started");
}