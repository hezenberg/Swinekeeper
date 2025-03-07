#ifndef GAMEREND_H
#define GAMEREND_H

#include "../include/header.h"
#include "../include/gamelogic.h"

///////////////////////| STR DEFINE |//////////////////////////
#define HELP_TEXT "Corn attracts swine.\nDon't step on corn!\nFlag the corn."

//////////////////////| COLOR DEFINE |/////////////////////////
#define HELP_TEXT_COLOR    RGB(0,   224,  162)
#define OUTLINE_COLOR      RGB(0,   254,  196)
#define FLAG_CHAR_COLOR    RGB(254, 145,  0)
#define NORMAL_BLOCK_BKG   RGB(0,   255,  0)
#define NORMAL_BLOCK_COVER RGB(0,   128,  0)
#define EMPTY_BLOCK_BKG    RGB(0,   100,  0)
///////////////////////| SIZE DEFINE |////////////////////////
#define WIN_HEIGHT              560
#define WIN_WIDTH               280
#define OUTLINE_SPACE           5
#define RECT_SIZE_ON_FLAG       70
#define TOTAL_PUSH_REDRAW_OBJ   15
///////////////////////| ERROR DEFINE |////////////////////////
#define FAILD_FONT  "faild load font for rendering"

#define MOUSE_R_BTN 1
#define MOUSE_L_BTN 2

// The structure stores data about all coordinates 
// of objects that will be drawn in GameDraw 
struct WINOBJPOS				  
{
	RECT help_text_rect;               // RECT main help text
	RECT count_text_flags;             // Title part before exit button, for handling collisions
	 
	RECT line_on_the_left;             //
	RECT line_on_the_bottom;           // 
	RECT line_on_the_right;            // The outline inside 
	RECT line_on_the_top;              // the game space
	RECT line_on_the_corner_left;      // The object consists of lines that will include 4 
  	RECT line_on_the_corner_bottom;    // coordinates pointing to 2 points that will be connected.
	
	
	RECT line_on_the_char_flag_main;   //
	RECT line_on_the_char_flag_top;    // 	A symbol indicating -
	RECT line_on_the_char_flag_right;  // the remaining number of flags
	RECT line_on_the_char_flag_bottom; //
	
	
}; 
typedef struct WINOBJPOS WINOBJPOS;


// Redraw the structure, if there is a need to redraw an area, 
// last_object_iter - iterator RECT arr_area, ilast_object_iter updating in PushRedrawArea
struct NEEDREDRAW				  
{
	INT8 last_object_iter;
	RECT arr_area[5];
}; 
typedef struct NEEDREDRAW NEEDREDRAW;

// Geting game area for redraw, will return size array or NULL if arr empty
extern RECT* GetRedrawArea(INT8 *iter); 

// Push new object for redraw
extern BOOL PushRedrawArea(RECT *redraw_area);

// Redraw all objects in window
extern void RedrawAll(void);

// Internal font loading function before rendering
static void LoadFonts(void);

// Uploading fonts and object positions
extern void GameRenderInitialization(RECT* rendering_area);

// Rendering the internal elements of a window
extern void DrawGame(HDC hdc);

// Handler mouse event for rendering and gamelogic
extern void RenderHandleMouseEvent(POINT mouse_pos, INT8 mouse_btn);

// Handler keydown events for rendering and gamelogic
extern BOOL RenderHandleKeysEvent(UINT_PTR key);

// Drawin line use RECT(POINT1, POINT2);
static BOOL RectToDrawLine(HDC hdc, RECT* rect);

// Restart game and redraw game area
static void RenderGameRestart(void);


             /* DRAWING BLOCKS */
////////////////////////////////////////////////////
                                                  //
static void DrawFlagOnBlock(HDC hdc, RECT* pos);  //
                                                  //
static void DrawBombBlock(HDC hdc, RECT* pos);    //
                                                  //
static void DrawNormalBlock(HDC hdc, RECT *pos);  //
                                                  //
static void DrawEmptyBlock(HDC hdc, RECT *pos);   //
////////////////////////////////////////////////////


#endif