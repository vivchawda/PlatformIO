#include <Arduino.h>

/* Hello World OLED Test */

#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`
SSD1306 display(0x3c, 5, 4); // Initialise the OLED display using Wire library
void setup()
{
  Serial.begin(115200);
  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
}

String numbr= "420";

void loop()
{

    display.drawString(0, 0, String(DISPLAY_WIDTH));
    display.drawString(0, 10, String(DISPLAY_HEIGHT));
    //display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2,  "OTA Update");
    display.display();

}
