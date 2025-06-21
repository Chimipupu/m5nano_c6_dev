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

#endif // APP_WIFI_HPP