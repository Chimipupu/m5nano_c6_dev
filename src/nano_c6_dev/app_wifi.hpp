/**
 * @file app_wifi.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief WiFiアプリヘッダー
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu(https://github.com/Chimipupu)
 * 
 */
#ifndef APP_WIFI_HPP
#define APP_WIFI_HPP

// WiFi APの設定
#define AP_SSID         "Nano_C6_Develop_AP"      // APのSSID
#define AP_PASSWORD     "nanoc6dev"               // APのパスワード
#define AP_CHANNEL      1                         // WiFiチャンネル
#define AP_MAX_CONN     4                         // 最大接続数
#define HTTP_PORT       80                        // Webサーバ HTTPポート

#include <stdint.h>
#include <string.h>

void app_wifi_init(void);
void app_wifi_main(void);
void app_wifi_ap_init(void);

const char HTML_PAGE[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 LED & NeoPixel Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin: 20px; }
    .button { background-color: #4CAF50; border: none; color: white; padding: 10px 20px;
              margin: 5px; font-size: 16px; cursor: pointer; border-radius: 5px; }
    .slider { width: 300px; }
  </style>
</head>
<body>
  <h1>ESP32 LED & NeoPixel</h1>

  <p>
    <a href="/on"><button class="button">ON</button></a>
    <a href="/off"><button class="button">OFF</button></a>
  </p>

  <h2>Color Presets</h2>
  <p>
    <a href="/color/red"><button class="button" style="background-color:red">Red</button></a>
    <a href="/color/yellow"><button class="button" style="background-color:yellow;color:black">Yellow</button></a>
    <a href="/color/orange"><button class="button" style="background-color:orange">Orange</button></a>
    <a href="/color/yellowgreen"><button class="button" style="background-color:#ADFF2F;color:black">YellowGreen</button></a>
    <a href="/color/green"><button class="button" style="background-color:green">Green</button></a>
    <a href="/color/blue"><button class="button" style="background-color:blue">Blue</button></a>
    <a href="/color/purple"><button class="button" style="background-color:purple">Purple</button></a>
    <a href="/color/white"><button class="button" style="background-color:white;color:black">White</button></a>
  </p>

  <h2>RGB Custom Color</h2>
  <form action="/setrgb" method="get" target="_self">
    <p>R: <input type="range" name="r" min="0" max="255" value="0" class="slider"></p>
    <p>G: <input type="range" name="g" min="0" max="255" value="0" class="slider"></p>
    <p>B: <input type="range" name="b" min="0" max="255" value="0" class="slider"></p>
    <p><input type="submit" value="Set RGB" class="button"></p>
  </form>
</body>
</html>
)rawliteral";

#endif // APP_WIFI_HPP