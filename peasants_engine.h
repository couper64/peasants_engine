/*

MIT License

Copyright 2020 Vladislav Li

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

/*
Notes, Bibliography, References:

12. To switch from fullscreen and back to window I had to use 
Get/SetWindowLongPtr functions, which weren't covered in the book.
12.1 Link
https://stackoverflow.com/questions/34462445/fullscreen-vs-borderless-window

11. In ancient times of Win16 people were using ATOM and MAKEINTATOM to gain 
some performance boosts to look up registered class names in system arrays. 
However, on modern day hardware it's pointless. Although, I did it anyway, 
because I am planning to run this code on legacy systems.
11.1 Link
https://stackoverflow.com/questions/4884910/what-is-the-use-of-atom-returned-by-registerclassex-function

10. Calling GetDC(HWND hWnd) inside main loop were causing memory leakages. It 
was found experimentally. No documentation. Although, presumably, I was think 
it would just retrieve a stack-level variable and would delete itself every 
iteration. However, it looked like it had some heap allocations nested 
somewhere deep in function calls.

9. There are problems with syntax highlighting in header files when viewed
through Visual Studio Community.
9.1 Link
https://developercommunity.visualstudio.com/content/problem/547841/c-header-files-do-not-have-syntax-highlighting-ena.html

8. Added UpdateWindow() function, to let operating system send WM_PAINT
messages to the application.
8.1 Link
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-updatewindow

7. Although, _tWinMain is questionable, I thought it's good to try to stay
cross-standard as possible. And, it looked like old-school guys were still using
TCHAR and similar names.
7.1 Link
https://stackoverflow.com/questions/234365/is-tchar-still-relevant

6. Explanation of WPARAM and LPARAM. WPARAM - 16-bit word and LPARAM - 32-bit long.
6.1 Link
https://stackoverflow.com/questions/6339793/wparam-and-lparam-parameters

5. Instead of wWinMain or WinMain use _tWinMain which then expands into
wWinMain or WinMain based on whether its UNICODE or ANSI.
5.1 Link
https://stackoverflow.com/questions/4681443/apientry-twinmain-and-winapi-winmain-difference

4. Instead of L"Hello World" use TEXT("Hello World") for WIN32API calls.
Identifies a string as Unicode when UNICODE is defined by a preprocessor 
directive during compilation. 
Otherwise, the macro identifies a string as an ANSI string.
4.1 Link
https://docs.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-text

4. Keep forgeting to set the size of the structure for WNDCLASSEX.
4.1 Link
https://stackoverflow.com/questions/8775443/win32-api-registerclassex-errors

3. wWinMain is based of the Microsoft online documentation.
3.1 Link
https://docs.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point

2. Source-code Annotations Language is used by Microsoft to improve code
analysis of their compilers.
Supposedly, it compiler dependant. _In_, _In_opt_ are part of this SAL scheme.
2.1 Link
https://docs.microsoft.com/en-gb/visualstudio/code-quality/understanding-sal?view=vs-2019

1. These errors appeared if project property Link/System/Subsystem is not
set to Windows. Default is Console.
1.1 Error Message 1
Severity	Code	Description	Project	File	Line	Suppression State
Error	LNK2019	unresolved external symbol _main referenced in function
"int __cdecl invoke_main(void)" (?invoke_main@@YAHXZ)
windows_manager
C:\Users\USERNAME\Desktop\renderer\windows_manager\MSVCRTD.lib(exe_main.obj)	1
1.2 Error Message 2
Severity	Code	Description	Project	File	Line	Suppression State
Error	LNK1120	1 unresolved externals	windows_manager
C:\Users\USERNAME\Desktop\renderer\Debug\windows_manager.exe	1

*/

/*

Content:

Entry callback is defined at the bottom of the file.

Use PE_IMPLEMENTATION to define peasants engine implementation.

*/

/*

Getting Started.

- Set Link/System/Subsystem in VS Community to Windows.
- Include "peasnats_engine.h" into any *.cpp file.
- Implement init(void) and draw(void) functions in the *.cpp file.
- Run your application. ESC - to exit and F1 - to toggle fullscreen.

*/

#pragma once

// from 76896 to 48476 lines after preprocessing
#define NOGDICAPMASKS    
//#define NOVIRTUALKEYCODES // VK_ESCAPE
//#define NOWINMESSAGES // WM_DESTROY, WM_SIZE, WM_CREATE, WM_KEYDOWN
//#define NOWINSTYLES // WS_OVERLAPPEDWINDOW
// #define NOSYSMETRICS // GetSystemMetrics
#define NOMENUS          
//#define NOICONS // IDI_APPLICATION
#define NOKEYSTATES      
#define NOSYSCOMMANDS    
#define NORASTEROPS      
#define NOSHOWWINDOW     
#define OEMRESOURCE      
#define NOATOM           
#define NOCLIPBOARD      
//#define NOCOLOR // COLOR_WINDOW
#define NOCTLMGR         
#define NODRAWTEXT       
//#define NOGDI // GetStockObject
#define NOKERNEL         
//#define NOUSER // WNDCLASSEX, CW_USEDEFAULT, PAINTSTRUCT
#define NONLS            
#define NOMB             
#define NOMEMMGR         
#define NOMETAFILE       
#define NOMINMAX         
//#define NOMSG // MSG, GetMessage, TranslateMessage, DispatchMessage
#define NOOPENFILE       
#define NOSCROLL         
#define NOSERVICE        
#define NOSOUND          
#define NOTEXTMETRIC     
#define NOWH             
//#define NOWINOFFSETS SetWindowLongPtr
#define NOCOMM           
#define NOKANJI          
#define NOHELP           
#define NOPROFILER       
#define NODEFERWINDOWPOS 
#define NOMCX            

// from 48476 to 26104 lines after preprocessing
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

// OpenGL functionality.
#include <gl/GL.h>
#include <gl/GLU.h>

// _tWinMain, that _t part is from tchar.h.
#include <tchar.h>

// Main loop timer dependency.
#include <chrono>

/* API Design-Implementation. Start here. */

extern void init();
extern void draw();

/* API Design-Implementation. End here. */

/* Global engine constants. Start here. */

const TCHAR PE_WNDCLASSEX_NAME[] = TEXT("PE_WNDCLASSEX_NAME");
const TCHAR PE_WINDOWEX_NAME[] = TEXT("Made by Peasants Engine");

const PIXELFORMATDESCRIPTOR PE_PFD
{
	// nSize.
	sizeof(PIXELFORMATDESCRIPTOR),

	// nVersion, always set to 1.
	1,

	// dwFlags. dw - double word, DWORD. Flags for pixel buffer properties.
	PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,

	// iPixelType. Type of pixel data.
	PFD_TYPE_RGBA,

	// cColorBits. Number of bits per pixel.
	32,

	// cRedBits. Number of red bits.
	0,

	// cRedShift. Shift count for red bits.
	0,

	// cGreenBits. Number of green bits.
	0,

	// cGreenShift. Shift count for red bits.
	0,

	// cBlueBits. Number of blue bits.
	0,

	// cBlueShift. Shift count for red bits.
	0,

	// cAlphaBits. Number of alpha bits.
	0,

	// cAlphaShift. Shift count for red bits.
	0,

	// cAccumBits. Number of accumulation buffer bits.
	0,

	// cAccumRedBits. Number of red accumulation bits.
	0,

	// cAccumGreenBits. Number of green accumulation bits.
	0,

	// cAccumBlueBits. Number of blue accumulation bits.
	0,

	// cAccumAlphaBits. Number of alpha accumulation bits.
	0,

	// cDepthBits. Number of depth buffer bits.
	24,

	// cStencilBits. Number of stencil buffer bits.
	0,

	// cAuxBuffers. Number of auxiliary buffer bits. Not supported.
	0,

	// iLayerType. No longer used.
	PFD_MAIN_PLANE,

	// bReserved. Number of overlay and underlay planes.
	0,

	// dwLayerMask. No longer used.
	0,

	// dwVisibleMask. Transparent underlay plane color.
	0,

	// dwDamageMask. No longer used.
	0
};

/* Global engine constants. End here. */

/* Global engine static variables. Start here. */
/* Global engine static variables. End here. */

/* Global engine variables. Start here. */

RECT peWindowedModeRect = { NULL };

/* Global engine variables. End here. */

bool peInit(HDC hDC) 
{
	// If the function succeeds, the return value is a valid handle to an 
	// OpenGL rendering context.
	// If the function fails, the return value is NULL.To get extended error
	// information, call GetLastError.
	HGLRC hGLRC = wglCreateContext(hDC);

	// TO DO: Handle wglCreateContext failure.
	if (!hGLRC)
	{
		return false;
	}

	// When the wglMakeCurrent function succeeds, the return value is TRUE; 
	// otherwise the return value is FALSE.To get extended error information, 
	// call GetLastError.
	BOOL madeCurrent = wglMakeCurrent(hDC, hGLRC);

	// TO DO: Handle wglMakeCurrent failure.
	if (!madeCurrent)
	{
		return false;
	}

	/* Default OpenGL settings. Start here. */

	// Culling is ON.
	glEnable(GL_CULL_FACE);

	// Back culling is default.
	glCullFace(GL_BACK);

	// Front of the polygon considered from counter-clockwise 
	// winding as a default.
	glFrontFace(GL_CCW);

	// Default clear colour is opaque gray.
	glClearColor(0.50f, 0.50f, 0.50f, 1.00f);

	/* Default OpenGL settings. End here. */

	/* Customisable user-defined initalisation. Start separate function. */

	init();

	/* Customisable user-defined initalisation. End separate function. */

	// Generally, if we reach this point than that's success.
	return true;
}

bool peDestroy(HDC hDC, HGLRC hGLRC) 
{
	// When the wglMakeCurrent function succeeds, the return value is TRUE; 
	// otherwise the return value is FALSE.To get extended error information, 
	// call GetLastError.
	BOOL madeCurrent = wglMakeCurrent(hDC, NULL);

	// TO DO: Handle wglMakeCurrent failure.
	if (!madeCurrent)
	{
		// Since, we are leaving application anyways. All we want is 
		// to log the state to analyse it later.
		return false;
	}

	// If the function succeeds, the return value is TRUE.
	// If the function fails, the return value is FALSE. 
	// To get extended error information, call GetLastError.
	BOOL isDeleted = wglDeleteContext(hGLRC);

	// TO DO: Handle wglDeleteContext failure.
	if (!isDeleted)
	{
		// Since, we are leaving application anyways. All we want is 
		// to log the state to analyse it later.
		return false;
	}

	// Otherwise, we consider it success.
	return true;
}

void peDraw(HDC hDC) 
{
	// Clear all neccessary buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset GL_MODELVIEW matrix.
	glLoadIdentity();

	// Do whatever user wants us to do.
	draw();

	// Image is ready, bring in to the screen.
	SwapBuffers(hDC);
}

void peToggleFullscreen() 
{
	HWND hWnd = GetActiveWindow();

	if (GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP)
	{
		SetWindowLongPtr
		(
			hWnd, 
			GWL_STYLE, 
			WS_VISIBLE | WS_OVERLAPPEDWINDOW
		);
		SetWindowPos
		(
			hWnd, 
			NULL, 
			peWindowedModeRect.left, 
			peWindowedModeRect.top, 
			peWindowedModeRect.right - peWindowedModeRect.left,
			peWindowedModeRect.bottom - peWindowedModeRect.top,
			SWP_FRAMECHANGED
		);
	}
	else 
	{
		// Store before entering fullscreen.
		GetWindowRect(hWnd, &peWindowedModeRect);

		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		SetWindowLongPtr(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
	}
}

/*
hWnd - Handle to current Window.
ppfd - Pointer to Pixel Format Descriptor.
*/
void peOnWindowMessageCreate
(
	HWND hWnd, 
	const PIXELFORMATDESCRIPTOR* ppfd
) 
{
	// The order is important. Because rendering context depends on the format.
	// 1. Pixel format.
	// 2. OpenGL rendering context.

	// Because this function processes Win32 messages, parameters should be 
	// dependant on WindowProc arguments.
	// *Before, 1 variable below was at the beginning of WindowProc function.
	HDC hDC = GetDC(hWnd);

	// If the function succeeds, the return value is a pixel format index 
	// (one-based) that is the closest match to the given pixel format 
	// descriptor.
	// If the function fails, the return value is zero.
	// To get extended error information, call GetLastError.
	int pixelFormatIndex = ChoosePixelFormat(hDC, ppfd);

	// If the function succeeds, the return value is TRUE.
	// If the function fails, the return value is FALSE.
	// To get extended error information, call GetLastError.
	BOOL isSet = SetPixelFormat(hDC, pixelFormatIndex, ppfd);

	// TO DO: Handle SetPixelFormat failure.
	if (!isSet) 
	{
		return;
	}

	// Using non-Win32 standard bool, because that's our custom 
	// "cross-platform" function.
	bool didEngineInit = peInit(hDC);

	// TO DO: Handle peInit failure.
	if (!didEngineInit)
	{
		return;
	}
}

void peOnWindowMessageDestroy(HWND hWnd) 
{
	// Because this function processes Win32 messages, parameters should be 
	// dependant on WindowProc arguments.
	// *Before, 2 variables below were at the beginning of WindowProc function.
	HDC hDC = GetDC(hWnd);
	HGLRC hGLRC = wglGetCurrentContext();

	// Using non-Win32 standard bool, because that's our custom 
	// "cross-platform" function.
	bool didEngineDestroy = peDestroy(hDC, hGLRC);

	// TO DO: Handle peDestroy failure.
	if (!didEngineDestroy)
	{
		// Since, we are leaving application anyways. All we want is 
		// to log the state to analyse it later.
	}

	// Try to tell main loop to leave.
	PostQuitMessage(0);
}

/*
lParam - Long pointer parameter, received by WinowProc callback. Part of Win32.
*/
void peOnWindowMessageSize(LPARAM lParam)
{
	// Retrieve width and height values from lower and upper parts of 
	// a double word parameter.
	int width = LOWORD(lParam);
	int height = HIWORD(lParam);

	// From quick search, this function doesn't require ceratin matrix mode 
	// to be set before calling it.
	// Using unsafe casting, because I am sure it won't break anything.
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Perspective manipulations are computed in GL_PROJECTION mode.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.00, (GLdouble)width / (GLdouble)height, 0.10, 100.00);

	// Return to default matrix mode of GL_MODELVIEW.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void peOnWindowMessageKeyDown(HWND hWnd, WPARAM wParam) 
{
	switch (wParam)
	{
		case (VK_ESCAPE): DestroyWindow(hWnd); break;
		case (VK_F1): peToggleFullscreen(); break;
	}
}

LRESULT CALLBACK peWindowProc
(
	_In_ HWND hWnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uMsg)
	{
		// Windows "create" message should be called only once at the 
		// start of the creation event.
		case (WM_CREATE):
			peOnWindowMessageCreate(hWnd, &PE_PFD);
			break;

		case (WM_DESTROY):
			peOnWindowMessageDestroy(hWnd);
			break;

		case(WM_SIZE):
			peOnWindowMessageSize(lParam);
			break;

		case(WM_KEYDOWN):
			peOnWindowMessageKeyDown(hWnd, wParam);
			break;
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

INT APIENTRY _tWinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR pCmdLine,
	_In_ INT nCmdShow
)
{
	// Filling up the structure.
	const WNDCLASSEX PE_WNDCLASSEX =
	{
		// Count of bytes of this class.
		sizeof(PE_WNDCLASSEX),

		/* Win 3.x */

		// Style.
		CS_HREDRAW | CS_VREDRAW,

		// Long pointer to function WndProc.
		peWindowProc, 

		// Count of bytes Class Extra.
		0,

		// Count of bytes Window Class Extra.
		0,

		// Handle to an instance.
		hInstance,

		// Handle to icon.
		LoadIcon(NULL, IDI_APPLICATION),

		// Handle to cursor.
		LoadCursor(NULL, IDC_ARROW),

		// Handle to brush.
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		
		// Menu name.
		TEXT("Menu Name"),

		// Class Name.
		PE_WNDCLASSEX_NAME,

		/* Win 4.0 */

		// Handle to small icon.
		LoadIcon(NULL, IDI_WINLOGO)
	};

	// Registering that structure. Returned ATOM then used in window 
	// creation as a method to look up class name in system-array. 
	// Supposedly, it should do better for Win16. Note 11.
	const ATOM PE_WNDCLASSEX_ATOM = RegisterClassEx(&PE_WNDCLASSEX);

	// Creating window.
	HWND hWnd = CreateWindowEx
	(
		// WS_EX - Window Style Extended.
		0,

		// Class name in system-array.
		MAKEINTATOM(PE_WNDCLASSEX_ATOM),

		// Window top bar title.
		PE_WINDOWEX_NAME,

		// WS - Window Style.
		WS_OVERLAPPEDWINDOW,

		// CW - Create Window. X - coordinate.
		CW_USEDEFAULT,

		// CW - Create Window. Y - coordinate.
		CW_USEDEFAULT,

		// CW - Create Window. nWidth.
		CW_USEDEFAULT,

		// CW - Create Window. nHeight.
		CW_USEDEFAULT,

		// hWndParent. Handle to Parennt Window.
		NULL,

		// hMenu. Handle to menu.
		NULL,

		// Handle to current process instance.
		hInstance,

		// lpParam. Long Pointer Parameter.
		NULL
	);

	// Check whether we failed to create it or not.
	if (hWnd == NULL)
	{
		// Terminate when failed.
		return(0);
	}

	// Make window visible to the user.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Simple message processing.
	MSG msg = {};
	HDC hDC = GetDC(hWnd);

	// Main loop.
	while (true)
	{
		// Event processing.
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return (0);
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// TO DO: Logic updating function. Locked at a certain FPS.


		// Graphics rendering.
		peDraw(hDC);
	}

	return(0);
}
