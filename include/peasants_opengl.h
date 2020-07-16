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

This file contains OpenGL includes for various platforms.

*/

/*
Notes, Bibliography, References:

*/

#pragma once

// OpenGL functionality.
#include <gl/GL.h>
#include <gl/GLU.h>

/* Global OpenGL variables. Start here. */

// The string that indicates the name of the company whose OpenGL 
// implementation you are using. (Benstead, L. 2009).
const GLubyte* PE_GL_VENDOR;

// The string that usually reflects the hardware being used. 
// (Benstead, L. 2009).
const GLubyte* PE_GL_RENDERER;

// The string contains a version number in the form of either 
// major_number.minor_number or major_number.minor_number.release_number. 
// (Benstead, L. 2009).
const GLubyte* PE_GL_VERSION;

// The string returned contains a space-delimited list of all of the available 
// OpenGL extensions. (Benstead L. 2009).
const GLubyte* PE_GL_EXTENSIONS;

/* Global OpenGL variables. End here. */
