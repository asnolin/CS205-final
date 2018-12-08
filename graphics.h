//
// Written by Yile Li
//
#ifndef graphics_h
#define graphics_h

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Program Initialization NOT OpenGL/GLUT Dependent, As We Haven't Created a GLUT Window Yet
void init();

// Initialize OpenGL Graphics
void InitGL();

// Callback Functions for GLUT

// Draw the Window - This is Where All the GL Actions Are
void display();

// Trap and Process Alphanumeric Keyboard Events
void kbd(unsigned char key, int x, int y);

// Trap and Process Special Keyboard Events
void kbdS(int key, int x, int y);

// Handle "Mouse Cursor Moved" Events
void cursor(int x, int y);

// Calls Itself After a Specified Time
void timer(int dummy);

// Handle Mouse Button Pressed and Released Events
void mouse(int button, int state, int x, int y);

#endif /* graphics_h */
