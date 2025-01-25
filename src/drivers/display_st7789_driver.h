#pragma once

class ESP_PanelLcd;

ESP_PanelLcd* display_init();
void clear_screen(ESP_PanelLcd* display);
void show_splash_screen(ESP_PanelLcd* lcd, const char* fileName);
