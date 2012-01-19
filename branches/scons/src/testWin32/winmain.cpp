#include <windows.h>

#include "renderApi.h"

//#include "KeyState.h"
//#include "KeysDef.h"
//#include "Render.h"

#define IDI_TUTORIAL1           107

#define WIN_SIZE_X 640
#define WIN_SIZE_Y 480

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HWND g_hWnd = NULL;
POINT g_Pt;

renderApi mApi;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
		return 0;

	int iS=sizeof(HWND);

	//инициализация рендера
	mApi.init((tUInt64)g_hWnd, WIN_SIZE_X, WIN_SIZE_Y, false, 0, 0, render::MSAA_2x);

	//Инициализация
//	Render::Instance().Init(g_hWnd,WIN_SIZE_X, WIN_SIZE_Y);

	// Main message loop
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			//отобразить фрейм
			//Render::Instance().Display();
			Sleep(16);
		}
	}

	//CleanupDevice();

	return ( int )msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "TutorialWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	// Create window
	RECT rc = { 0, 0, WIN_SIZE_X, WIN_SIZE_Y };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	g_hWnd = CreateWindow( "TutorialWindowClass", "Direct3D 11 Tutorial 4: 3D Spaces", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !g_hWnd )
		return E_FAIL;

	ShowWindow( g_hWnd, nCmdShow );

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_CREATE:
		//KeyState::Instance().Init();
		//KeyState::Instance().SetWinSize( WIN_SIZE_X, WIN_SIZE_Y);
		break;
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_KEYDOWN:
		//KeyState::Instance().SetKey(wParam, true);
		//if (wParam == KEY_ESC)
		//	SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		break;

	case WM_KEYUP:
		//KeyState::Instance().SetKey(wParam, false);
		break;

	case WM_LBUTTONDOWN:
		//KeyState::Instance().SetMouseLeft(true);
		break;

	case WM_LBUTTONUP:
		//KeyState::Instance().SetMouseLeft(false);
		break;

	case WM_RBUTTONDOWN:
		//KeyState::Instance().SetMouseRight(true);
		break;

	case WM_RBUTTONUP:
		//KeyState::Instance().SetMouseRight(false);
		break;

	case WM_MOUSEMOVE:
		GetCursorPos(&g_Pt);
		//KeyState::Instance().SetMousePos(g_Pt.x,g_Pt.y);
		break;

	case WM_SIZE:
		//KeyState::Instance().SetWinSize(LOWORD(lParam),HIWORD(lParam));
		//Render::Instance().Resize(LOWORD(lParam),HIWORD(lParam));
		break;

	case WM_DESTROY:
	case WM_CLOSE:
		//Render::Instance().Close();
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}