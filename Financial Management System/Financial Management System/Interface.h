#pragma once
#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#define CONFIG "Config.ini"

#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)
#define BLUE RGB(0, 0, 255)
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define YELLOW RGB(255, 255, 0)
#define ORANGE RGB(255, 165, 0)
#define PURPLE RGB(128, 0, 128)
#define BROWN RGB(102, 51, 0)
#define SILVER RGB(192, 192, 192)

void changeBackgroundColor(short);
void changeTextColor(short);
void changeFontSize(short);

void systemConfiguration();