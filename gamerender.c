#include "gamerender.h"

static RECT         drawing_free_area;
static WINOBJPOS    win_objects_pos;
static HFONT        help_text_font       = NULL;
static HFONT        count_flag_text_font = NULL;
static PLAYFBLOCK   *rplayfblocks;
static RECT         rand_line_cover[30];
static NEEDREDRAW   need_redraw;

extern void GameRenderInitialization(RECT* _drawing_free_area)
{
	LoadFonts();
	rplayfblocks = GameBlocksInitialization();
	GenerateRandCover();
	drawing_free_area = *_drawing_free_area;
	need_redraw.last_object_iter = 0;

	
	win_objects_pos.help_text_rect       = drawing_free_area;
	win_objects_pos.help_text_rect.left += 10;
	win_objects_pos.help_text_rect.top  += 10;
	
	win_objects_pos.count_text_flags.left   = drawing_free_area.right - RECT_SIZE_ON_FLAG + 30;
	win_objects_pos.count_text_flags.top    = drawing_free_area.top   + OUTLINE_SPACE + 50;  
	win_objects_pos.count_text_flags.right  = drawing_free_area.right - OUTLINE_SPACE; 
	win_objects_pos.count_text_flags.bottom = drawing_free_area.top   + OUTLINE_SPACE + RECT_SIZE_ON_FLAG;     
	
	win_objects_pos.line_on_the_left.left               = drawing_free_area.left + OUTLINE_SPACE; 
	win_objects_pos.line_on_the_left.top                = drawing_free_area.top  + OUTLINE_SPACE;
	win_objects_pos.line_on_the_left.right              = WIN_WIDTH - drawing_free_area.right + OUTLINE_SPACE;
	win_objects_pos.line_on_the_left.bottom             = drawing_free_area.bottom - OUTLINE_SPACE; 
	
	win_objects_pos.line_on_the_bottom.left             = WIN_WIDTH - drawing_free_area.right + OUTLINE_SPACE;    
	win_objects_pos.line_on_the_bottom.top              = drawing_free_area.bottom - OUTLINE_SPACE;  
	win_objects_pos.line_on_the_bottom.right            = drawing_free_area.right  - OUTLINE_SPACE; 
	win_objects_pos.line_on_the_bottom.bottom           = drawing_free_area.bottom - OUTLINE_SPACE; 
	
	win_objects_pos.line_on_the_right.left              = drawing_free_area.right  - OUTLINE_SPACE;
	win_objects_pos.line_on_the_right.top               = drawing_free_area.bottom - OUTLINE_SPACE;
	win_objects_pos.line_on_the_right.right             = drawing_free_area.right  - OUTLINE_SPACE;
	win_objects_pos.line_on_the_right.bottom            = drawing_free_area.top    + OUTLINE_SPACE;  	
	
	win_objects_pos.line_on_the_top.left                = drawing_free_area.right - OUTLINE_SPACE;   
	win_objects_pos.line_on_the_top.top                 = drawing_free_area.top   + OUTLINE_SPACE; 
	win_objects_pos.line_on_the_top.right               = drawing_free_area.left  + OUTLINE_SPACE; 
	win_objects_pos.line_on_the_top.bottom              = drawing_free_area.top   + OUTLINE_SPACE;
	
	win_objects_pos.line_on_the_corner_left.left        = drawing_free_area.right - RECT_SIZE_ON_FLAG;   
	win_objects_pos.line_on_the_corner_left.top         = drawing_free_area.top   + OUTLINE_SPACE;
	win_objects_pos.line_on_the_corner_left.right       = drawing_free_area.right - RECT_SIZE_ON_FLAG;
	win_objects_pos.line_on_the_corner_left.bottom      = drawing_free_area.top   + OUTLINE_SPACE + RECT_SIZE_ON_FLAG;    
	
  	win_objects_pos.line_on_the_corner_bottom.left      = drawing_free_area.right - RECT_SIZE_ON_FLAG;
	win_objects_pos.line_on_the_corner_bottom.top       = drawing_free_area.top   + OUTLINE_SPACE + RECT_SIZE_ON_FLAG;    
	win_objects_pos.line_on_the_corner_bottom.right     = drawing_free_area.right - OUTLINE_SPACE; 
	win_objects_pos.line_on_the_corner_bottom.bottom    = drawing_free_area.top   + OUTLINE_SPACE + RECT_SIZE_ON_FLAG;     
	
	win_objects_pos.line_on_the_char_flag_main.left     = drawing_free_area.right - RECT_SIZE_ON_FLAG + 10;
	win_objects_pos.line_on_the_char_flag_main.top      = drawing_free_area.top   + OUTLINE_SPACE + 10;
	win_objects_pos.line_on_the_char_flag_main.right    = drawing_free_area.right - RECT_SIZE_ON_FLAG + 10;
	win_objects_pos.line_on_the_char_flag_main.bottom   = drawing_free_area.top   + OUTLINE_SPACE + 60;
	
	
	win_objects_pos.line_on_the_char_flag_top.left      = drawing_free_area.right - RECT_SIZE_ON_FLAG + 10;
	win_objects_pos.line_on_the_char_flag_top.top       = drawing_free_area.top   + OUTLINE_SPACE + 10;
	win_objects_pos.line_on_the_char_flag_top.right     = drawing_free_area.right - RECT_SIZE_ON_FLAG + 40;
	win_objects_pos.line_on_the_char_flag_top.bottom    = drawing_free_area.top   + OUTLINE_SPACE + 10;	
	
	win_objects_pos.line_on_the_char_flag_right.left    = drawing_free_area.right - RECT_SIZE_ON_FLAG + 40;
	win_objects_pos.line_on_the_char_flag_right.top     = drawing_free_area.top   + OUTLINE_SPACE + 10;
	win_objects_pos.line_on_the_char_flag_right.right   = drawing_free_area.right - RECT_SIZE_ON_FLAG + 40;
	win_objects_pos.line_on_the_char_flag_right.bottom  = drawing_free_area.top   + OUTLINE_SPACE + 30;
	
	win_objects_pos.line_on_the_char_flag_bottom.left   = drawing_free_area.right - RECT_SIZE_ON_FLAG + 40;
	win_objects_pos.line_on_the_char_flag_bottom.top    = drawing_free_area.top   + OUTLINE_SPACE + 30; 
	win_objects_pos.line_on_the_char_flag_bottom.right  = drawing_free_area.right - RECT_SIZE_ON_FLAG + 10; 
	win_objects_pos.line_on_the_char_flag_bottom.bottom = drawing_free_area.top   + OUTLINE_SPACE + 30;  
	
}	


static void LoadFonts(void)
{
  help_text_font = CreateFont(25, 0, 0, 0, FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
										   OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
										   DEFAULT_QUALITY,VARIABLE_PITCH,
										   "Cambria");
										  
  count_flag_text_font = CreateFont(20, 0, 0, 0, FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
										         OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
										         DEFAULT_QUALITY,VARIABLE_PITCH,
										         "Arial");
										 
  if(help_text_font == NULL || count_flag_text_font == NULL)
		GetMessageErrorAndExit(FAILD_FONT);
										   
}


extern void RenderHandleMouseEvent(POINT mouse_pos, INT8 mouse_btn)
{
	for(INT8 block = 0; block < OVER_BLOCKS; block++){
		if (CheckColision(&rplayfblocks[block].pos_block, &mouse_pos)){
			GameHandleGameBlocks(mouse_btn, block);
			PushRedrawArea(&rplayfblocks[block].pos_block);
			PushRedrawArea(&win_objects_pos.count_text_flags);
			
		}
	}
}


BOOL RenderHandleKeysEvent(UINT_PTR key)
{
	switch (key)
	{ 
		case KEY_R:  
			RenderGameRestart();  
			return TRUE;
		case VK_ESCAPE:
			PostQuitMessage(0);  
			return TRUE;
	
		default:
			return FALSE;
	}
	
}


extern RECT* GetRedrawArea(INT8 *iter)
{
	if(need_redraw.last_object_iter > 0){
		*iter = need_redraw.last_object_iter;
		need_redraw.last_object_iter = 0;

		return need_redraw.arr_area;
	}
		
    return NULL;
}


static BOOL PushRedrawArea(RECT *redraw_area)
{
	if(need_redraw.last_object_iter > 5) 
		return FALSE;
		
	need_redraw.arr_area[need_redraw.last_object_iter] = *redraw_area;
	need_redraw.last_object_iter ++;

    return TRUE;
}


void RedrawAll(void)
{
	PushRedrawArea(&drawing_free_area);
}


extern void DrawGame(HDC hdc)
{
  	//------------------- Help text ------------------//
  	SetBkMode(hdc, TRANSPARENT);
 	SetTextColor(hdc, HELP_TEXT_COLOR);
  	SelectObject(hdc, help_text_font);
		DrawText(hdc, HELP_TEXT, -1, &win_objects_pos.help_text_rect, DT_NOCLIP);
  	SelectObject(hdc, count_flag_text_font);
		INT8 flags = GameGetNumbersOfFlags();
		CHAR sflags[3]; sflags[2] = '\0';
		sprintf(sflags, "%i", flags);
		DrawText(hdc, sflags, -1, &win_objects_pos.count_text_flags, DT_BOTTOM | DT_CENTER | DT_NOCLIP);
 	SetBkMode(hdc, OPAQUE);
  
	//------------------- Outlines ------------------//
 	 HPEN pen_outl = CreatePen(PS_SOLID, 1, OUTLINE_COLOR);
 	SelectObject(hdc, pen_outl);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_left);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_bottom);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_right);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_top);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_corner_left);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_corner_bottom);
 	DeleteObject(pen_outl);
 	 HPEN pen_flag = CreatePen(PS_SOLID, 1, FLAG_CHAR_COLOR);
 	 SelectObject(hdc, pen_flag);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_char_flag_main);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_char_flag_top);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_char_flag_right);
		RectToDrawLine(hdc, &win_objects_pos.line_on_the_char_flag_bottom);
 	DeleteObject(pen_flag);
  
	//------------------- Flag char ------------------//
		HBRUSH block_brush = CreateSolidBrush(OUTLINE_COLOR);
		HBRUSH block_brush_2 = CreateSolidBrush(FLAG_CHAR_COLOR);
		SelectObject(hdc, block_brush);
	

	//------------------- Game blocks ----------------//
		for(INT8 i = 0; i < OVER_BLOCKS; i++){

			if(rplayfblocks[i].status == STATUS_NORM)
				DrawNormalBlock(hdc, &rplayfblocks[i].pos_block);
			if(rplayfblocks[i].status == STATUS_MARK)
				DrawFlagOnBlock(hdc, &rplayfblocks[i].pos_block);
			if(rplayfblocks[i].status == STATUS_OPEN)
				DrawEmptyBlock(hdc,  &rplayfblocks[i].pos_block);
		}
	
	DeleteObject(block_brush);
	DeleteObject(block_brush_2);
}


static BOOL RectToDrawLine(HDC hdc, RECT *rect)
{ 
	POINT pt; 
	LONG x1 = rect->left;
	LONG y1 = rect->top;
	LONG x2 = rect->right;
	LONG y2 = rect->bottom;
	MoveToEx(hdc, x1, y1, &pt);

	return LineTo(hdc, x2, y2);
}


void RenderGameRestart(void)
{
	rplayfblocks = GameBlocksInitialization();
	RedrawAll();
}


static void GenerateRandCover(void)
{
	RECT rect;
	for(INT8 i = 0; i < 30; i++){
		rect.left =   rplayfblocks[i].pos_block.left   + rand()%rplayfblocks[i].pos_block.right;
		rect.top =    rplayfblocks[i].pos_block.top    + rand()%rplayfblocks[i].pos_block.bottom;
		rect.right =  rplayfblocks[i].pos_block.right  + rand()%rplayfblocks[i].pos_block.left;
		rect.bottom = rplayfblocks[i].pos_block.bottom + rand()%rplayfblocks[i].pos_block.top;
		rand_line_cover[i] = rect;

	}
}


void DrawFlagOnBlock(HDC hdc, RECT *pos)
{
	HPEN flag_pen = CreatePen(PS_SOLID, 2, FLAG_CHAR_COLOR);
	SelectObject(hdc, flag_pen);

		RECT line_on_the_char_flag_main;
		RECT line_on_the_char_flag_top;
		RECT line_on_the_char_flag_right;
		RECT line_on_the_char_flag_bottom;

		DrawNormalBlock(hdc, pos);

		line_on_the_char_flag_main.left     = pos->left +  SIZE_BLOCK / 3.5;
		line_on_the_char_flag_main.top      = pos->top  - SIZE_BLOCK + 45;
		line_on_the_char_flag_main.right    = pos->left + SIZE_BLOCK / 3.5;
		line_on_the_char_flag_main.bottom   = pos->bottom  - SIZE_BLOCK + 30;
	
	
		line_on_the_char_flag_top.left      = line_on_the_char_flag_main.right;
		line_on_the_char_flag_top.top       = line_on_the_char_flag_main.top;
		line_on_the_char_flag_top.right     = line_on_the_char_flag_main.right + SIZE_BLOCK / 3;
		line_on_the_char_flag_top.bottom    = line_on_the_char_flag_main.top;
	
		line_on_the_char_flag_right.left    = line_on_the_char_flag_top.right;
		line_on_the_char_flag_right.top     = line_on_the_char_flag_top.top; 
		line_on_the_char_flag_right.right   = line_on_the_char_flag_top.right;
		line_on_the_char_flag_right.bottom  = line_on_the_char_flag_top.bottom + 10;
	
		line_on_the_char_flag_bottom.left   = line_on_the_char_flag_right.right;
		line_on_the_char_flag_bottom.top    = line_on_the_char_flag_right.bottom;
		line_on_the_char_flag_bottom.right  = line_on_the_char_flag_main.right - 1; 
		line_on_the_char_flag_bottom.bottom = line_on_the_char_flag_right.bottom; 

		RectToDrawLine(hdc, &line_on_the_char_flag_main);
		RectToDrawLine(hdc, &line_on_the_char_flag_top);
		RectToDrawLine(hdc, &line_on_the_char_flag_right);
		RectToDrawLine(hdc, &line_on_the_char_flag_bottom);

	HBRUSH flag_brush = CreateSolidBrush(FLAG_CHAR_COLOR);
		RECT rect_flag;
		rect_flag.left  = line_on_the_char_flag_main.left;
		rect_flag.top   = line_on_the_char_flag_main.top;
		rect_flag.right =  line_on_the_char_flag_right.right;
		rect_flag.bottom = line_on_the_char_flag_right.bottom;
		FillRect(hdc, &rect_flag, flag_brush);
		
	DeleteObject(flag_brush);
	DeleteObject(flag_pen);
	
}


static void DrawNormalBlock(HDC hdc, RECT *pos)
{
	HBRUSH block_brush = CreateSolidBrush(NORMAL_BLOCK_BKG);
	HBRUSH cover_brush = CreateSolidBrush(NORMAL_BLOCK_COVER);

	SelectObject(hdc, block_brush);
	FillRect(hdc, pos, block_brush);
	DeleteObject(block_brush);
	DeleteObject(cover_brush);
}


static void DrawEmptyBlock(HDC hdc, RECT *pos)
{
	HBRUSH block_brush = CreateSolidBrush(EMPTY_BLOCK_BKG);
	HBRUSH cover_brush = CreateSolidBrush(NORMAL_BLOCK_COVER);

	SelectObject(hdc, block_brush);
	FillRect(hdc, pos, block_brush);
	DeleteObject(block_brush);
	DeleteObject(cover_brush);
}