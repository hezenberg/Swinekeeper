#include "header.h"
#include "window.h"
#include "gamerender.h"


static WNDCLASS    window_class;
static HWND        window_hand;
static WINDOWTITLE window_title;
static RECT        window_rect;
static POINT 	   mouse_pos;

static BOOL IsMouseOnExitBtn = FALSE;
static BOOL IsMouseOnHelpBtn = FALSE;

static BOOL isFirstPaint     = TRUE;

void Initialization(void);
void Rendering(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

//////////////////////| init window class create section |////////////////////
	
	window_class = CreateMainWindowClass(hInstance);
	ATOM atom_window_class = RegisterClass(&window_class);
	if(!atom_window_class){
		MessageBox(NULL, FAILD_WIN_CLASS_REG, "Error", MB_ICONERROR);
		return 1;
	}	
	
//////////////////////////| window create section |///////////////////////////
	window_hand = CreateMainWindow(hInstance);
	if(!window_hand){
		MessageBox(NULL, FAILD_WIN_CREATE, "Error", MB_ICONERROR);
		return 1;
	}	

	ShowWindow(window_hand, nCmdShow);
    UpdateWindow(window_hand);							 


//////////////////////////| window message section |///////////////////////////
	MSG msg = {0};    
	INT8 iGetOk = 0;   
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) 
	{
		if (iGetOk == -1) 
			return 3;  

		TranslateMessage(&msg);    
		DispatchMessage(&msg);
	}

  return msg.wParam;  
}
	
	
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT ht;

  switch (message)
  {	
		case WM_CREATE:
			SetTimer(hWnd, 1, 20, NULL);

			break;
			
		case WM_PAINT:
			if(isFirstPaint){
				Initialization();
				isFirstPaint = FALSE;
			}
					
			Rendering();

			break;
			
		case WM_LBUTTONDOWN:
			if(!isFirstPaint){
				GetCursorPos(&mouse_pos);
				ScreenToClient(window_hand, &mouse_pos);
				RenderHandleMouseEvent(mouse_pos, MOUSE_L_BTN);
				IsMouseClickOnExitButton(&window_title.button_exit_rect, &mouse_pos);
			
				if(CheckColision(&window_title.title_rect_before_btn, &mouse_pos) || 
					CheckColision(&window_title.title_rect_after_btn,  &mouse_pos)) {
					ReleaseCapture();
					SendMessage(window_hand, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
				}
			}

			break;

		case WM_RBUTTONDOWN:
			if(!isFirstPaint)
				RenderHandleMouseEvent(mouse_pos, MOUSE_R_BTN);
	
			break;	
		
		case WM_KEYDOWN:
			if(!isFirstPaint)
				if(RenderHandleKeysEvent(wParam))
					break;
				
			
		case WM_MOUSEMOVE:

			GetCursorPos(&mouse_pos);
			ScreenToClient(window_hand, &mouse_pos);

			if(CheckColision(&window_title.button_exit_rect, &mouse_pos))
				IsMouseOnExitBtn = TRUE;
			else
				IsMouseOnExitBtn = FALSE;

			break;
			
		case WM_TIMER:
		    RedrawWindow(window_hand, &window_title.button_exit_rect, NULL , RDW_INVALIDATE | RDW_UPDATENOW);

			INT8 iter;
			RECT *redraw_area = GetRedrawArea(&iter);

			if(redraw_area == NULL)
				break;
				
			for(INT8 i = 0; i < iter; i++)
				RedrawWindow(window_hand, &redraw_area[i], NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);  

			break;
			
		default:  
			return DefWindowProc(hWnd, message, wParam, lParam);
  }
  
    return 0;
}

void Initialization(void)
{
	GetClientRect(window_hand, &window_rect);
	window_title = WindowTitleInitialization(&window_rect, WIN_TITLE_WIDTH, WIN_NAME, WIN_EXIT_BTN_TEXT);
	RECT area_for_draw = GetAreaForDraw();
	GameRenderInitialization(&area_for_draw);
	
}

void Rendering(void)
{	
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_hand, &ps);
	
	DrawWindowTitle(IsMouseOnExitBtn, &window_title, window_hand, hdc);
	DrawGame(hdc);
	
	EndPaint(window_hand, &ps);
}

