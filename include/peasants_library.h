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
Purpose:

This file contains a list of low-level C-like functions.
They provide low-level connections with OS and middleware libraries.

*/

/*
Notes, Bibliography, References:

*/

#pragma once

// WIN32 API dependency.
#include "peasants_windows.h"

// OpenGL dependency.
#include "peasants_opengl.h"

// That _t part is from tchar.h.
#include <tchar.h>

// Special debugging routine for OpenGL functions.
#ifdef _DEBUG
#define DO(x, y) x; y;
#else
#define DO(x, y) x;
#endif

/* Global library variables. Start here. */

// Window RECT information when it's not maximised.
RECT peWindowedModeRect = { NULL };

/* Global library variables. End here. */

void peLogGLError(GLenum errorCode)
{
	switch (errorCode)
	{
	case (GL_NO_ERROR):
		_tprintf_s(TEXT("GL_NO_ERROR\n"));
		break;

	case (GL_INVALID_ENUM):
		_tprintf_s(TEXT("Error encountered ... GL_INVALID_ENUM\n"));
		break;

	case (GL_INVALID_VALUE):
		_tprintf_s(TEXT("Error encountered ... GL_INVALID_VALUE\n"));
		break;

	case (GL_INVALID_OPERATION):
		_tprintf_s(TEXT("Error encountered ... GL_INVALID_OPERATION\n"));
		break;

	case (GL_STACK_OVERFLOW):
		_tprintf_s(TEXT("Error encountered ... GL_STACK_OVERFLOW\n"));
		break;

	case (GL_STACK_UNDERFLOW):
		_tprintf_s(TEXT("Error encountered ... GL_STACK_UNDERFLOW\n"));
		break;

	case (GL_OUT_OF_MEMORY):
		_tprintf_s(TEXT("Error encountered ... GL_OUT_OF_MEMORY\n"));
		break;
	}
}

void peLogGLErrors()
{
	while (GLenum errorCode = glGetError() != GL_NO_ERROR)
	{
		peLogGLError(errorCode);
	}
}

bool peWin32Init(HDC hDC)
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

	// Setup OpenGL hints.
	DO(glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST), peLogGLErrors());
	DO(glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST), peLogGLErrors());
	DO(glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST), peLogGLErrors());
	DO(glHint(GL_FOG_HINT, GL_FASTEST), peLogGLErrors());
	DO(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST), peLogGLErrors());

	_tprintf_s(TEXT("GL_POINT_SMOOTH_HINT set to GL_FASTEST.\n"));
	_tprintf_s(TEXT("GL_LINE_SMOOTH_HINT set to GL_FASTEST.\n"));
	_tprintf_s(TEXT("GL_POLYGON_SMOOTH_HINT set to GL_FASTEST.\n"));
	_tprintf_s(TEXT("GL_FOG_HINT set to GL_FASTEST.\n"));
	_tprintf_s(TEXT("GL_PERSPECTIVE_CORRECTION_HINT set to GL_FASTEST.\n"));

	// Culling is ON.
	DO(glEnable(GL_CULL_FACE), peLogGLErrors());

	// Point smoothing is OFF.
	DO(glDisable(GL_POINT_SMOOTH), peLogGLErrors());

	// Back culling is default.
	DO(glCullFace(GL_BACK), peLogGLErrors());

	// Front of the polygon considered from counter-clockwise 
	// winding as a default.
	DO(glFrontFace(GL_CCW), peLogGLErrors());

	// Default clear colour is opaque gray.
	DO(glClearColor(0.50f, 0.50f, 0.50f, 1.00f), peLogGLErrors());

	// Fill-up global OpenGL information.
	PE_GL_VENDOR = DO(glGetString(GL_VENDOR), peLogGLErrors());
	PE_GL_RENDERER = DO(glGetString(GL_RENDERER), peLogGLErrors());
	PE_GL_VERSION = DO(glGetString(GL_VERSION), peLogGLErrors());
	PE_GL_EXTENSIONS = DO(glGetString(GL_EXTENSIONS), peLogGLErrors());

	// Notify developer about OpenGL status.
	_tprintf_s(TEXT("GPU vendor: %hs \n"), PE_GL_VENDOR);
	_tprintf_s(TEXT("GPU name: %hs \n"), PE_GL_RENDERER);
	_tprintf_s(TEXT("OpenGL information: %hs \n"), PE_GL_VERSION);
	_tprintf_s(TEXT("OpenGL extensions available: \n - "));

	// An infinite loop to show all extensions in a readable format.
	for (int i = 0;; i++)
	{
		// Until we reach the end of the string.
		if (PE_GL_EXTENSIONS[i] == '\0')
		{
			// Add a new line.
			_tprintf_s(TEXT("\n"));

			// And, leave the loop.
			break;
		}

		// Words are separated by 'space'.
		else if (PE_GL_EXTENSIONS[i] == ' ')
		{
			// Format output to make it readable.
			_tprintf_s(TEXT("\n - "));
		}

		// In other cases.
		else
		{
			// Output character.
			_tprintf_s(TEXT("%c"), PE_GL_EXTENSIONS[i]);
		}
	}

	/* Default OpenGL settings. End here. */

	/* Customisable user-defined initalisation. Start separate function. */

	init();

	/* Customisable user-defined initalisation. End separate function. */

	// Generally, if we reach this point than that's success.
	return true;
}

bool peWin32Destroy(HDC hDC, HGLRC hGLRC)
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
	bool didEngineInit = peWin32Init(hDC);

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
	bool didEngineDestroy = peWin32Destroy(hDC, hGLRC);

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
