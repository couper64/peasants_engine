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

1. Information about #define STRICT preprocessor and hence why it is here.
1.1 Link
https://docs.microsoft.com/en-us/windows/win32/winprog/enabling-strict

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
#define STRICT
#include <windows.h>

/* Global WIN32 engine variables. Start here. */

const TCHAR PE_WNDCLASSEX_NAME[] = TEXT("PE_WNDCLASSEX_NAME");
const TCHAR PE_WINDOWEX_NAME[] = TEXT("Made by Peasants Engine");
const TCHAR PE_CONSOLETITLE_NAME[] = TEXT("Console for Peasants Engine");

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

/* Global WIN32 engine variables. End here. */
