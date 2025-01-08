#define STB_IMAGE_IMPLEMENTATION
#include "main.h"
#include "color.h"
int iG::iWindowWidth;
int iG::iWindowHeight;
int iG::iWindowX;
int iG::iWindowY;
int iG::iScreenWidth;
int iG::iScreenHeight;
int iG::ifft;
double iG::iMouseDir;
double iG::iMouseX;
double iG::iMouseY;
double iG::iClearR;
double iG::iClearG;
double iG::iClearB;
int iG::ITimer::iAnimCount;
int iG::ITimer::iAnimDelays[10];
int iG::ITimer::iAnimPause[10];
void (*iG::ITimer::iAnimFunction[10])(void);

void iG::iResize()
{
	glViewport(0, 0,iWindowWidth,iWindowHeight);
	// glMatrixMode(GL_PROJECTION);
 //    glLoadIdentity();
 //    glOrtho(0.0, iWindowWidth, 0.0, iWindowHeight, -1.0, 1.0);
 //    glViewport(0.0, 0.0, iWindowWidth, iWindowHeight);
}

void iG::iInitialize(char* title)
    {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
        glutInitWindowSize(iWindowWidth , iWindowHeight ) ;        // Window Size
        glutInitWindowPosition(iWindowX,iWindowY) ;     // Window Position
        glutCreateWindow(title);    // Window Title
        glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;     // Window Background Color
        glMatrixMode( GL_PROJECTION) ;
        glLoadIdentity() ;
        // default window range is (-1,1) in x and (-1,1) in y
        glOrtho(0.0 , iWindowWidth , 0.0 , iWindowHeight , -1.0 , 1.0);    // Window range (0,iWindowWidth) in x and (0,iWindowHeight) in y   
        iClear();

        
        glutDisplayFunc(displayFF);     // Window Display Callback
        glutReshapeFunc(reshapeFF);     // Callback when window is resized
        glutKeyboardFunc(keyboardHandler1FF); // Callback when normal key is pressed down
        glutKeyboardUpFunc(keyboardUpHandler1FF);   // Callback when normal key is pressed up
        glutSpecialFunc(keyboardHandler2FF);  // Callback when special key is pressed down
        glutSpecialUpFunc(keyboardUpHandler2FF);    // Callback when normal key is pressed up
        glutJoystickFunc(joystickHandlerFF,0);
        glutMouseFunc(mouseClickHandlerFF);     // Callback when mouse is clicked
        glutMotionFunc(mouseDragHandlerFF);     // Callback when mouse is dragged
        glutPassiveMotionFunc(mouseMoveHandlerFF);     // Callback when mouse is moved
        glutMouseWheelFunc(mouseWheelHandlerFF);    // Callback when mouse is scrolled
        glutIdleFunc(animFF) ;      // Timers

        
        glAlphaFunc(GL_GREATER, 0.0f);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);     // Transparent Color
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Transparent Color
        glLineWidth(2.0);       // Width of drawing lines
    }
