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

- Set Linker/System/Subsystem in VS Community to Windows.
- Add to Linker/General/Additional Library Directories -> C:\Windows\System32;
- Add to Linker/Input/Additional Dependencies -> opengl32.lib; glu32.lib;
- Include "peasants_engine.h" into any *.cpp file.
- Implement init(void) and draw(void) functions in the *.cpp file.
- Run your application. ESC - to exit and F1 - to toggle fullscreen.

- Do option 1 or option 2:
	- Option 1, set C/C++/General/Additional Include Directories
		-> %ENGINEPATH%/include
	- Option 2, copy %ENGINEPATH%/include/* to your project folder.

*/

#pragma once

// A list of functions to access platform features.
#include "peasants_library.h"

// _tWinMain, that _t part is from tchar.h.
#include <tchar.h>

// Console debug I/O.
#include <stdio.h>

/* API Design-Implementation. Start here. */

extern void init();
extern void draw();

/* API Design-Implementation. End here. */

/* Global engine constants. Start here. */

/* Global engine constants. End here. */

/* Global engine static variables. Start here. */
/* Global engine static variables. End here. */

/* Operating System Layer. Below this line. */

INT APIENTRY _tWinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR pCmdLine,
	_In_ INT nCmdShow
)
{
	/* Adding console output to the app. Start here. */

	// If the function succeeds, the return value is nonzero.
	// If the function fails, the return value is zero. 
	// To get extended error information, call GetLastError.
	BOOL isAlloc = AllocConsole();

	// TO DO: Handle AllocConsole failure.
	if (!isAlloc) 
	{
		// Just terminate.
		return (0);
	}

	// If the function succeeds, the return value is nonzero.
	// If the function fails, the return value is zero. 
	// To get extended error information, call GetLastError.
	BOOL isConsoleTitleSet = SetConsoleTitle(PE_CONSOLETITLE_NAME);

	// TO DO: Handle SetConsoleTitle failure.
	if (!isConsoleTitleSet)
	{
		// Just terminate.
		return (0);
	}

	// Re-purpose standard output file to use new console.
	_tfreopen_s((FILE**)stdout, TEXT("CONOUT$"), TEXT("w"), stdout);

	// Welcome message for a peasant.
	_tprintf_s(TEXT("Peasants Engine [Version 1.0.0.0]\n"));
	_tprintf_s(TEXT("(c) 2020 Vladislav Li. All rights reserved.\n\n"));
	_tprintf_s(TEXT("Welcome back, peasant!\n\n"));

	/* Adding console output to the app. End here. */

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
