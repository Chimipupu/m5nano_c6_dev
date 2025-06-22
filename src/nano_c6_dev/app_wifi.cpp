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

static String getParam(String request, const String &key);

static String getParam(String request, const String &key)
{
    int idx = request.indexOf(key + "=");
    if (idx == -1) return "";
    int start = idx + key.length() + 1;
    int endAmp = request.indexOf('&', start);
    int endSpc = request.indexOf(' ', start);
    int end;

    if (endAmp == -1 && endSpc == -1) {
        end = request.length();
    } else if (endAmp == -1) {
        end = endSpc;
    } else if (endSpc == -1) {
        end = endAmp;
    } else {
        end = min(endAmp, endSpc);
    }

    String value = request.substring(start, end);
    value.replace('+', ' '); // スペース変換
    return value;
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
                            uint8_t r = (uint8_t)getParam(header, "r").toInt();
                            uint8_t g = (uint8_t)getParam(header, "g").toInt();
                            uint8_t b = (uint8_t)getParam(header, "b").toInt();
                            g_current_color = g_neopixel.Color(r, g, b);
                            Serial.printf("Set RGB: R=%d G=%d B=%d\n", r, g, b);
                        }else if (header.indexOf("/debug?") >= 0) {
                            String dbgMode = getParam(header, "dbg");
                            String dbgMsg  = getParam(header, "msg");

                            if (dbgMode == "on") {
                                Serial.println("[DEBUG] ON");
                            } else if (dbgMode == "off") {
                                Serial.println("[DEBUG] OFF");
                            }

                            Serial.print("[DEBUG MSG] ");
                            Serial.println(dbgMsg);
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
                        client.println();
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