#ifndef WINDW_H  
#define WINDW_H  


#include "../include/header.h"

///////////////////////| STR DEFINE |//////////////////////////
#define WIN_NAME          "GAMEPIG"
#define WIN_CLASS_NAME    "gamepigwc"
#define WIN_EXIT_BTN_TEXT "X"

//////////////////////| COLOR DEFINE |/////////////////////////
#define WIN_TITLE_COLOR              RGB(0,  64,  48  )
#define WIN_TITLE_BUTTON_COLOR       RGB(28, 199, 146 )
#define WIN_TITLE_BUTTON_COLOR_HOVER RGB(110, 199, 199)
#define WIN_TITLE_TEXT_COLOR         RGB(0,  0,   0   )
#define WIN_EXIT_TEXT_BUTTON_COLOR   RGB(41, 178, 134 )
#define WIN_BACK_COLOR        	     RGB(0,  0,   0   )

/////////////////////| SIZE DEFINE |//////////////////////////
#define WIN_HEIGHT              560
#define WIN_WIDTH               280
#define WIN_START_POS_X		    100
#define WIN_START_POS_Y		    100
#define WIN_TITLE_WIDTH         25
#define WIN_TITLE_EXIT_BUTTON   30
#define WIN_TITLE_OUTLINE_WIDTH 2

//////////////////////| ERROR DEFINE |///////////////////////
#define FAILD_WIN_CLASS_REG "faild registration window class for this application!"
#define FAILD_WIN_CREATE    "faild create window for this application!"


//////////////////////////////////////////////////////////////
///////////////////////| Custom title |///////////////////////
//////////////////////////////////////////////////////////////
struct WINDOWTITLE				  
{
	RECT   button_exit_rect;      // RECT of button exit
	RECT   button_help_rect;
	RECT   title_rect_for_draw;	  // RECT only for drawing in fn:DrawWindowTitle
	RECT   title_rect_before_btn; // Title part before exit button, for handling collisions
	RECT   title_rect_after_btn;  // Title part after exit button, for handling collisions
	LPCSTR text_on_title;		  // Window name, string in title
	LPCSTR text_on_exit_button;	  // Text in exit button(X)
	
}; 
typedef struct WINDOWTITLE WINDOWTITLE;

// The window title is initialized to start rendering every time you need to render the window components in WM_PRINT.
extern WINDOWTITLE WindowTitleInitialization(RECT *main_win_rect, int height_title, LPSTR _text_on_title, LPSTR _text_on_exit_button);

// Rendering the window title using GDI
extern void DrawWindowTitle(BOOL is_pointer_on_btn, WINDOWTITLE *wc, HWND window_hand, HDC hdc);

// Draw line use 2 points for outline window
extern BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

// If the mouse was pointed at the exit button
extern void IsMouseOnWindowTitle(RECT *colision_rect, POINT *point);

// If the mouse click exit button
extern void IsMouseClickOnExitButton(RECT *colision_rect, POINT *point);

// Gives a free area to draw.
extern RECT GetAreaForDraw(void);

// DELETE AFTER CODING
extern void GetMsg(LPSTR text);

// Show error message and exit  
extern void GetMessageErrorAndExit(LPSTR text_error);
//-----------------------------------------------------------------


//////////////////////////////////////////////////////////////
//////////////| Initialization window in OS |/////////////////
//////////////////////////////////////////////////////////////

WNDCLASS CreateMainWindowClass(HINSTANCE hInstance);

HWND CreateMainWindow(HINSTANCE hInstance);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//-----------------------------------------------------------------



#endif









