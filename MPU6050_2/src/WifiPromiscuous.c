// Espressif ESP32 promiscuous mode and packet injection experiments
// by brainstorm at nopcode org

#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_internal.h"
#include "lwip/err.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

uint8_t HEX_COLSIZE = 7;

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void process_promisc(void* buf, uint16_t len)
{
    char* buflen = (char*) buf + len;
    uint8_t hexdump_cols = 0;
    uint8_t offset = 0;

    // RAW packet
    for (char* ptr = buf; ptr < buflen; ptr++) printf("%c", *ptr);
    printf("\n\n");

    // Hexdump (wireshark-friendly)
    for (char* ptr = buf; ptr < buflen; ptr+=HEX_COLSIZE) {
        // print offset
        printf(" %06X ", offset);

        for (hexdump_cols=0; hexdump_cols < HEX_COLSIZE; hexdump_cols++)
            printf(" %02X", *(ptr+hexdump_cols*sizeof(char)));

        offset = offset + HEX_COLSIZE;
        printf("\n");
    }

    printf("\n\n");
}

void send_packet(esp_interface_t iface, void* buf, uint8_t len)
{
    printf("Sending actual packet via driver...\n");
    switch(esp_wifi_internal_tx(iface, buf, len))
    {
        case ERR_OK:
            printf("Packet in the air!\n");
            break;
        case ERR_IF:
            printf("WiFi driver error\n");
            break;
        default:
            printf("Some other error I don't want to control now\n");
            break;
    }
}

void app_main(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_interface_t wifi_if;
    void* wifi_eth = NULL;

    nvs_flash_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

    printf("Setting up wifi\n");
	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );

    //printf("Promiscuous mode callback\n");
	//esp_wifi_set_promiscuous(true);
    //esp_wifi_set_promiscuous_rx_cb(&process_promisc);

    ESP_ERROR_CHECK( esp_wifi_start() );

    // Borrowed from the original esp8266 injection example:
    // https://github.com/kripthor/WiFiBeaconJam/blob/master/WiFiBeaconJam.ino
    uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*22*/  0xc0, 0x6c,
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                /*32*/  0x64, 0x00,
                /*34*/  0x01, 0x04,
                /* SSID */
                /*36*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01,
                /*56*/  0x04};

    wifi_if = tcpip_adapter_get_esp_if(wifi_eth);

    printf("About to send packets every 200ms\n");
    while(true)
    {
        send_packet(wifi_if, (void*)packet, sizeof(packet));
        vTaskDelay(200 / portTICK_RATE_MS);
    }
}
