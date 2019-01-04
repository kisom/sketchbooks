#include <string.h>
#include <SPI.h>
#include <Wire.h>
#include "sh1106.h"

#define VCCSTATE SH1106_SWITCHCAPVCC
#define WIDTH     128
#define HEIGHT     64
#define NUM_PAGE    8  /* number of pages */

#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

uint8_t oled_buf[WIDTH * HEIGHT / 8];


void setup() {
  Serial.begin(9600);
  Serial.print("OLED Example\n");

  SH1106_begin();
  SH1106_clear(oled_buf);
  memset(oled_buf, 0xff, 1024);
  SH1106_display(oled_buf);
  delay(2000);
  memset(oled_buf, 0x00, 1024);
  SH1106_display(oled_buf);
  delay(2000);
  SH1106_clear(oled_buf);

}

void loop() {
  // put your main code here, to run repeatedly:

}
