/**
 * This header addresses the various ways that OpenGL headers
 * are handled on different systems
 */

#ifndef _WIN32
// Non windows, doesn't require Windows header to work correctly
#ifndef __gl_h_
#ifdef __APPLE_CC__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif                
#endif

// Required for compatibility with glext.h style function definitions
#ifndef APIENTRY
#define APIENTRY
#endif

#else	// Win32 Platform

#ifdef _WIN32 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#endif	//	 WIN32
