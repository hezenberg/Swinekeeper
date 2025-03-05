#include "window.h"

extern WNDCLASS CreateMainWindowClass(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.style         = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;        
	wc.hIcon         = LoadIcon(NULL, IDI_SHIELD);       
	wc.hCursor       = LoadCursor(NULL, IDC_HAND);      
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = WIN_CLASS_NAME;
	
	return wc;
}


extern HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND mainwin;
	mainwin = CreateWindowEx(0, 
							 WIN_CLASS_NAME, 
							 WIN_NAME, 
							 WS_POPUP, 
							 WIN_START_POS_X, 
							 WIN_START_POS_Y, 
							 WIN_WIDTH, 
							 WIN_HEIGHT, 
							 NULL, NULL, hInstance, NULL);
	
	return mainwin;
}


extern WINDOWTITLE WindowTitleInitialization(RECT *main_win_rect, int height_title, LPSTR _text_on_title, LPSTR _text_on_exit_button)
{
    int button_widht = 30;
	int widht_title = main_win_rect->right;

	int widht_title_part2 = 20;
	int widht_title_part1 = (widht_title - button_widht) - widht_title_part2;
	
	WINDOWTITLE wt;
	
	wt.title_rect_for_draw.left     = 0;
	wt.title_rect_for_draw.top      = 0;
	wt.title_rect_for_draw.right    = widht_title;
	wt.title_rect_for_draw.bottom   = height_title;
	
	wt.button_exit_rect.left        = widht_title_part1;
	wt.button_exit_rect.top         = 0;
	wt.button_exit_rect.right       = widht_title_part1 + button_widht;
	wt.button_exit_rect.bottom      = height_title;
	
	wt.title_rect_before_btn.left   = 0;
	wt.title_rect_before_btn.top    = 0;
	wt.title_rect_before_btn.right  = widht_title_part1;
	wt.title_rect_before_btn.bottom = height_title;
	
	wt.title_rect_after_btn.left    = widht_title_part1 + button_widht;
	wt.title_rect_after_btn.top     = 0;
	wt.title_rect_after_btn.right   = widht_title;
	wt.title_rect_after_btn.bottom  = height_title;
		
	wt.text_on_title       = _text_on_title;
	wt.text_on_exit_button = _text_on_exit_button;
		
	return wt;
}


extern BOOL CheckColision(RECT *colision_rect, POINT *point)
{
	if(colision_rect->left <= point->x && colision_rect->right >= point->x)
		if(colision_rect->top <= point->y && colision_rect->bottom >= point->y)
			return TRUE;
	
	return FALSE;
}


extern void IsMouseClickOnExitButton(RECT *colision_rect, POINT *point)
{
	if(CheckColision(colision_rect, point)) PostQuitMessage(0);			
}


extern void DrawWindowTitle(BOOL is_pointer_on_btn, WINDOWTITLE *wt, HWND main_window_hand, HDC hdc)
{	
	//----------------- TITLE AND OUTLINE-----------------//
	HBRUSH titlebrush = CreateSolidBrush(WIN_TITLE_COLOR);
	HPEN hpen = CreatePen(PS_SOLID, WIN_TITLE_OUTLINE_WIDTH, WIN_TITLE_COLOR);
	SelectObject(hdc, hpen);
	
	//                X1            Y1           X2           Y2      //
	DrawLine(hdc, 1,           1,            1,           WIN_HEIGHT  );
	DrawLine(hdc, 1,           WIN_HEIGHT-1, WIN_WIDTH,   WIN_HEIGHT-1);
	DrawLine(hdc, WIN_WIDTH-1, WIN_HEIGHT-1, WIN_WIDTH-1, 1           );
	
	FillRect(hdc, &wt->title_rect_for_draw, titlebrush);

	DeleteObject(titlebrush);
	DeleteObject(hpen);
	//----------------------------------------------------//
	

	//-------------------- EXIT BTN ----------------------//
	HBRUSH exit_button_brush;

	if(is_pointer_on_btn) exit_button_brush = CreateSolidBrush(WIN_TITLE_BUTTON_COLOR_HOVER);
	else exit_button_brush = CreateSolidBrush(WIN_TITLE_BUTTON_COLOR);

	FillRect(hdc, &wt->button_exit_rect, exit_button_brush);
	DeleteObject(exit_button_brush);
	//----------------------------------------------------//
	
	
	//--------------------- TEXT -------------------------//
	SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, WIN_TITLE_TEXT_COLOR);
		DrawText(hdc, wt->text_on_exit_button, -1, &wt->button_exit_rect, DT_CENTER  
												| DT_SINGLELINE 
												| DT_VCENTER  
												| DT_NOCLIP);
												
		SetTextColor(hdc, WIN_EXIT_TEXT_BUTTON_COLOR);
		
		DrawText(hdc, wt->text_on_title, -1, &wt->title_rect_for_draw, DT_CENTER  
												        | DT_SINGLELINE 
												        | DT_VCENTER  
												        | DT_NOCLIP);
	SetBkMode(hdc, OPAQUE); 
	
	//----------------------------------------------------//
	
		
}

extern BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
  POINT pt;
  MoveToEx(hdc, x1, y1, &pt);
  return LineTo(hdc, x2, y2);
}

extern RECT GetAreaForDraw(void)
{
	RECT free_rect;
	
	free_rect.left   = WIN_TITLE_OUTLINE_WIDTH;
	free_rect.top    = WIN_TITLE_WIDTH; 
	free_rect.right  = WIN_WIDTH  - WIN_TITLE_OUTLINE_WIDTH;
	free_rect.bottom = WIN_HEIGHT - WIN_TITLE_OUTLINE_WIDTH;
	
	return free_rect;
}

extern void GetMsg(LPSTR text)
{
	MessageBox(NULL, text, "Debug message", MB_OK);
}

extern void GetMessageErrorAndExit(LPSTR text_error)
{
	MessageBox(NULL, text_error, "Error", MB_ICONERROR);
	PostQuitMessage(1);  
}


extern void GetIntegerMessage(LONG num)
{
	char str[10];
	sprintf(str, "%li", num);
	GetMsg(str);
}

