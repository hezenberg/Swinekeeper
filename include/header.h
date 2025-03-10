#ifndef HEADER_H  
#define HEADER_H  

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")

#define TRUE  1
#define FALSE 0

#define MOUSE_R_BTN    1
#define MOUSE_L_BTN    2
#define MOUSE_L_BTN_UP 3
#define MOUSE_R_BTN_UP 4

#define KEY_R 0x52

#define TIMER_REDRAW_MS 5

extern void GetIntegerMessage(INT8 num);   // DEBUG
extern void GetMsg(LPSTR text);            // DEBUG

extern void GetMessageErrorAndExit(LPSTR text_error);


// General purpose function for checking for collisions between two points
extern BOOL CheckColision(RECT *colision_rect, POINT *point);

#endif

