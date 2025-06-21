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

WiFiServer server(HTTP_PORT);

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

    if (client) {
        Serial.println("New Client connected");
        String currentLine = "";
        while (client.connected())
        {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // HTTPレスポンスヘッダー
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        // HTMLコンテンツ
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
                        client.println("<title>ESP32 LED Control</title>");
                        client.println("<style>");
                        client.println("body { font-family: Arial; text-align: center; margin: 20px; }");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px;");
                        client.println("text-align: center; text-decoration: none; display: inline-block; font-size: 16px;");
                        client.println("margin: 4px 2px; cursor: pointer; border-radius: 4px; }");
                        client.println("</style></head>");
                        // ボディ
                        client.println("<body>");
                        client.println("<h1>ESP32 LED Control</h1>");
                        client.println("<p><a href='/on'><button class='button'>ON</button></a></p>");
                        client.println("<p><a href='/off'><button class='button'>OFF</button></a></p>");
                        client.println("</body></html>");
                        break;
                    } else {
                        // LEDの制御
                        if (currentLine.indexOf("GET /on") >= 0) {
                            digitalWrite(LED_PIN, HIGH);
                        } else if (currentLine.indexOf("GET /off") >= 0) {
                            digitalWrite(LED_PIN, LOW);
                        }
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
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