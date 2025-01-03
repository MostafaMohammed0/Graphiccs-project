#ifndef __I_GRAPHICS__
#define __I_GRAPHICS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <fstream>

#define PI (acos(-1.0))
#ifndef ERR
#define ERR 1e-8
#endif

using namespace std;

class iG {
protected:
    struct point
    {
        double x, y;
    };

    static point solve_sim_eqn(double a1, double b1, double c1, double a2, double b2, double c2)
    {
        double d = a1 * b2 - a2 * b1;
        struct point p;
        p.x = (b1 * c2 - b2 * c1) / d;
        p.y = (c1 * a2 - c2 * b1) / d;
        return p;
    }

    static void iPath(double X[], double Y[], int n, double d = 1, int closed = 0, int dashed = 0, double dash = 10, double gap = 5, int aligned = 0)
    {
        // Path drawing logic remains the same
        // Ensure the rendering functions use OpenGL commands
    }

    static void iClear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glClearColor(iClearR / 255, iClearG / 255, iClearB / 255, 1.0);
        glFlush();
    }

    virtual void iAbstract() = 0;

    static int iWindowHeight, iWindowWidth, iScreenHeight, iScreenWidth, iWindowX, iWindowY;
    static double iClearR, iClearG, iClearB;
    static double iMouseX, iMouseY;
    static double iMouseDir;

public:
    static int ifft;
    static void iDraw();
    static void iKeyboard(unsigned char);
    static void iKeyboardUp(unsigned char);
    static void iSpecialKeyboard(unsigned char);
    static void iSpecialKeyboardUp(unsigned char);
    static void iMouseDrag(int, int);
    static void iMouseMove(double, double);
    static void iMouseClick(GLFWwindow*, int, int, int);
    static void iMouseScroll(GLFWwindow*, double, double);
    static void iResize();
    static void iSetClearColor(double r, double g, double b)
    {
        iClearR = r;
        iClearG = g;
        iClearB = b;
    }

    static int iGetWindowHeight()
    {
        return iWindowHeight;
    }
    static int iGetWindowWidth()
    {
        return iWindowWidth;
    }
    static void iSetWindowHeight(int height)
    {
        iWindowHeight = height;
    }
    static void iSetWindowWidth(int width)
    {
        iWindowWidth = width;
    }
    static int iGetScreenHeight()
    {
        return iScreenHeight;
    }
    static int iGetScreenWidth()
    {
        return iScreenWidth;
    }
    static void iSetScreenHeight(int height)
    {
        iScreenHeight = height;
    }
    static void iSetScreenWidth(int width)
    {
        iScreenWidth = width;
    }

    static double iGetMouseX()
    {
        return iMouseX;
    }
    static double iGetMouseY()
    {
        return iMouseY;
    }
};


    static void iSetMouseX(double x)
{
    glfwSetCursorPos(window, x, iMouseY);  // Use glfwSetCursorPos for setting mouse position
}

static void iSetMouseY(double y)
{
    glfwSetCursorPos(window, iMouseX, y);  // Use glfwSetCursorPos for setting mouse position
}

static void iSetWindowX(double x)
{
    iWindowX = x;
}

static void iSetWindowY(double y)
{
    iWindowY = y;
}

static void iSetMouse(double x, double y)
{
    glfwSetCursorPos(window, x, y);  // Use glfwSetCursorPos for setting mouse position
}

static double getMouseDirection()
{
    return iMouseDir;
}

static void iMouseDirection(int mx, int my)
{
    // Setting the mouse direction between 0 and 360
    int dx = mx - iMouseX, dy = my - iMouseY;
    double dir = (atan(abs(1.0 * dy / dx)) * 180) / acos(-1);
    if (dx >= 0 && dy >= 0)
    {
        iMouseDir = dir;
    }
    else if (dx >= 0 && dy < 0)
    {
        iMouseDir = 360 + dir;
    }
    else if (dx < 0 && dy >= 0)
    {
        iMouseDir = 180 + dir;
    }
    else if (dx < 0 && dy < 0)
    {
        iMouseDir = 180 + dir;
    }
}

static void reshapeFF(int width, int height)
{
    iWindowWidth = width;
    iWindowHeight = height;
    iResize();
}

static void displayFF(void)
{
    iDraw();
    glfwSwapBuffers(window);  // Replace glutSwapBuffers with glfwSwapBuffers
}

static void animFF(void)
{
    if (ifft == 0) {
        ifft = 1;
        iClear();
    }
    glfwPostEmptyEvent();  // Replace glutPostRedisplay with glfwPostEmptyEvent if needed
}

static void joystickHandlerFF(unsigned int buttonMask, int x, int y, int z)
{
    cout << buttonMask << " " << x << " " << y << " " << z << endl;
}

static void keyboardHandler1FF(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        iKeyboard(key);
    }
}

static void keyboardUpHandler1FF(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE) {
        iKeyboardUp(key);
    }
}

static void keyboardHandler2FF(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        iSpecialKeyboard(key);
    }
}

static void keyboardUpHandler2FF(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE) {
        iSpecialKeyboardUp(key);
    }
}

static void mouseDragHandlerFF(GLFWwindow* window, double xpos, double ypos)
{
    iMouseX = xpos;
    iMouseY = iWindowHeight - ypos;
    iMouseDrag(iMouseX, iMouseY);
    glFlush();
}

static void mouseMoveHandlerFF(GLFWwindow* window, double xpos, double ypos)
{
    iMouseDirection(xpos, iWindowHeight - ypos);
    iMouseX = xpos;
    iMouseY = iWindowHeight - ypos;
    iMouseMove(iMouseX, iMouseY);
    glFlush();
}

static void mouseClickHandlerFF(GLFWwindow* window, int button, int action, int mods)
{
    iMouseX = xpos;
    iMouseY = iWindowHeight - ypos;
    if (action == GLFW_PRESS) {
        iMouseClick(button, GLFW_PRESS, iMouseX, iMouseY);
    } else if (action == GLFW_RELEASE) {
        iMouseClick(button, GLFW_RELEASE, iMouseX, iMouseY);
    }
    glFlush();
}

static void mouseWheelHandlerFF(GLFWwindow* window, double xoffset, double yoffset)
{
    iMouseScroll(yoffset);
}

class IText {
public:
    static void iSmall(double x, double y, const char *str)
    {
        glRasterPos3d(x, y, 0);
        int i;
        for (i = 0; str[i]; i++) {
            // For simplicity, using a placeholder text rendering function.
            // Consider using a text rendering library like FreeType or FTGL.
            renderBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        }
    }

    static void iBig(double x, double y, const char *str)
    {
        const char *p;
        glPushMatrix();
        glTranslatef(x, y, 0);
        for (p = str; *p; p++) {
            // For simplicity, using a placeholder text rendering function.
            // Consider using a text rendering library like FreeType or FTGL.
            renderStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
        glPopMatrix();
    }

private:
    static void renderBitmapCharacter(void *font, char c) {
        // Placeholder function to render a bitmap character
        // Replace with actual implementation
    }

    static void renderStrokeCharacter(void *font, char c) {
        // Placeholder function to render a stroke character
        // Replace with actual implementation
    }
};

    class ITimer {
    private:
        static void (*iAnimFunction[10])(void);
        static int iAnimCount;
        static int iAnimDelays[10];
        static int iAnimPause[10];
        static void  __stdcall iA0(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[0])iAnimFunction[0]();}
        static void  __stdcall iA1(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[1])iAnimFunction[1]();}
        static void  __stdcall iA2(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[2])iAnimFunction[2]();}
        static void  __stdcall iA3(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[3])iAnimFunction[3]();}
        static void  __stdcall iA4(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[4])iAnimFunction[4]();}
        static void  __stdcall iA5(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[5])iAnimFunction[5]();}
        static void  __stdcall iA6(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[6])iAnimFunction[6]();}
        static void  __stdcall iA7(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[7])iAnimFunction[7]();}
        static void  __stdcall iA8(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[8])iAnimFunction[8]();}
        static void  __stdcall iA9(HWND, unsigned int, unsigned int, unsigned long) {if (!iAnimPause[9])iAnimFunction[9]();}
    public:
        static int iSet(int msec, void (*f)(void))
        {
            int i = iAnimCount;

            if (iAnimCount >= 10) {printf("Error: Maximum number of already timer used.\n"); return -1;}

            iAnimFunction[i] = f;
            iAnimDelays[i] = msec;
            iAnimPause[i] = 0;

            if (iAnimCount == 0) SetTimer(0, 0, msec, iA0);
            if (iAnimCount == 1) SetTimer(0, 0, msec, iA1);
            if (iAnimCount == 2) SetTimer(0, 0, msec, iA2);
            if (iAnimCount == 3) SetTimer(0, 0, msec, iA3);
            if (iAnimCount == 4) SetTimer(0, 0, msec, iA4);

            if (iAnimCount == 5) SetTimer(0, 0, msec, iA5);
            if (iAnimCount == 6) SetTimer(0, 0, msec, iA6);
            if (iAnimCount == 7) SetTimer(0, 0, msec, iA7);
            if (iAnimCount == 8) SetTimer(0, 0, msec, iA8);
            if (iAnimCount == 9) SetTimer(0, 0, msec, iA9);
            iAnimCount++;

            return iAnimCount - 1;
        }
        static void iPause(int index) {
            if (index >= 0 && index < iAnimCount) {
                iAnimPause[index] = 1;
            }
        }

        static void iResume(int index) {
            if (index >= 0 && index < iAnimCount) {
                iAnimPause[index] = 0;
            }
        }
    };
    class ISetColor {
    public:
        static void iSolid(double r, double g, double b)
        {
            double mmx;
            mmx = r;
            if (g > mmx)mmx = g;
            if (b > mmx)mmx = b;
            mmx = 255;
            // r,g,b should be o to 1
            if (mmx > 0) {
                r /= mmx;
                g /= mmx;
                b /= mmx;
            }
            glColor3f(r, g, b);
        }

        static void iSolid(tuple<double, double, double> rgb)
        {
            double r = get<0>(rgb), g = get<1>(rgb), b = get<2>(rgb);
            double mmx;
            mmx = r;
            if (g > mmx)mmx = g;
            if (b > mmx)mmx = b;
            mmx = 255;
            if (mmx > 0) {
                r /= mmx;
                g /= mmx;
                b /= mmx;
            }
            glColor3f(r, g, b);
        }


        static void iTrans(double r, double g, double b, double a = 1.0)
        {
            double mmx = 255;
            if (r > mmx)
                r = mmx;
            if (g > mmx)
                g = mmx;
            if (b > mmx)
                b = mmx;
            r /= mmx;
            g /= mmx;
            b /= mmx;
            glColor4f(r, g, b, a);
        }
        static void iTrans(tuple<double, double, double> rgb, double a = 1.0)
        {
            double r = get<0>(rgb), g = get<1>(rgb), b = get<2>(rgb);
            double mmx = 255;
            if (r > mmx)
                r = mmx;
            if (g > mmx)
                g = mmx;
            if (b > mmx)
                b = mmx;
            r /= mmx;
            g /= mmx;
            b /= mmx;
            glColor4f(r, g, b, a);
        }
    };
    class IShowImage {
    public:
        static void BMP2(int x, int y, const char* filename, int ignoreColor);
        static void BMP3(int x, int y, char filename[], int ignoreColor)
        {
            AUX_RGBImageRec *TextureImage;
            TextureImage = auxDIBImageLoad(filename);

            int i, j, k;
            int width = TextureImage->sizeX;
            int height = TextureImage->sizeY;
            int nPixels = width * height;
            int *rgPixels = new int[nPixels];

            for (i = 0, j = 0; i < nPixels; i++, j += 3)
            {
                int rgb = 0;
                for (int k = 2; k >= 0; k--)
                {
                    rgb = ((rgb << 8) | TextureImage->data[j + k]);
                }

                rgPixels[i] = (rgb == ignoreColor) ? 0 : 255;
                rgPixels[i] = ((rgPixels[i] << 24) | rgb);
            }

            glRasterPos2f(x, y);
            glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgPixels);

            delete []rgPixels;
            free(TextureImage->data);
            free(TextureImage);
        }


        static void BMP(int x, int y, char filename[])
        {
            BMP2(x, y, filename, -1 /* ignoreColor */);
        }
    } IShowImage;

    class IDraw {
    public:
        class IFilled {
        public:
            static void iPolygon(double x[], double y[], int n)
            {
                int i;
                if (n < 3)return;
                glBegin(GL_POLYGON);
                for (i = 0; i < n; i++) {
                    glVertex2f(x[i], y[i]);
                }
                glEnd();
            }
            static void iRectangle(double left, double bottom, double dx, double dy)
            {
                double xx[4], yy[4];
                double x1, y1, x2, y2;

                x1 = left;
                y1 = bottom;
                x2 = x1 + dx;
                y2 = y1 + dy;

                xx[0] = x1;
                yy[0] = y1;
                xx[1] = x2;
                yy[1] = y1;
                xx[2] = x2;
                yy[2] = y2;
                xx[3] = x1;
                yy[3] = y2;
                iPolygon(xx, yy, 4);
            }

            static void iTriangle(double x1 , double y1 , double x2 , double y2 , double x3 , double y3)
            {
                double x[] = {x1, x2, x3};
                double y[] = {y1, y2, y3};
                iPolygon(x, y, 3);
            }

            static void iCircle(double x, double y, double r, int slices = 100)
            {
                double t, dt, x1, y1, xp, yp;
                dt = 2 * PI / slices;
                xp = x + r;
                yp = y;
                glBegin(GL_POLYGON);
                for (t = 0; t <= 2 * PI; t += dt)
                {
                    x1 = x + r * cos(t);
                    y1 = y + r * sin(t);

                    glVertex2f(xp, yp);
                    xp = x1;
                    yp = y1;
                }
                glEnd();
            }
            static void iEllipse(double x, double y, double a, double b, int slices = 100)
            {
                double t, dt, x1, y1, xp, yp;
                dt = 2 * PI / slices;
                xp = x + a;
                yp = y;
                glBegin(GL_POLYGON);
                for (t = 0; t <= 2 * PI; t += dt)
                {
                    x1 = x + a * cos(t);
                    y1 = y + b * sin(t);
                    glVertex2f(xp, yp);
                    xp = x1;
                    yp = y1;
                }
                glEnd();
            }

        };
        class IDashed {
        public:
            static void iLine(double x1, double y1, double x2, double y2, double d = 1, double dash = 10, double gap = 5)
            {
                double X[] = {x1, x2}, Y[] = {y1, y2};
                iPath(X, Y, 2, d, 0, 1, dash, gap);
            }
            static void iRectangle(double x, double y, double dx, double dy, double d = 1, double dash = 10, double gap = 5)
            {
                double X[] = {x, x + dx, x + dx, x}, Y[] = {y, y, y + dy, y + dy};
                iPath(X, Y, 4, d, 1, 1, dash, gap, 1);
            }
            static void iCircle(
                double x, double y, double r, double d = 1, int slices = 90, double dash = 10, double gap = 5)
            {
                double *X = (double *)malloc(sizeof(double) * slices);
                double *Y = (double *)malloc(sizeof(double) * slices);
                double t, dt = 2 * PI / slices;
                int i;
                for (t = i = 0; t < 2 * PI; t += dt, i++)
                    X[i] = x + r * cos(t), Y[i] = y + r * sin(t);
                iPath(X, Y, slices, d, 1, 1, dash, gap);
            }

            // static void iCircle(double x, double y, double r, double width=2.0,double dash = 10, double gap = 5,int slices = 100)
            // {
            //     double t, dt, x1, y1, xp, yp;
            //     dt = 2 * PI / slices;
            //     xp = x + r;
            //     yp = y;
            //     for (t = 0; t <= 2 * PI; t += dt)
            //     {
            //         x1 = x + r * cos(t);
            //         y1 = y + r * sin(t);
            //         IDraw::iLine(xp, yp, x1, y1,width);
            //         if(x1>xp) xp = x1+gap;
            //         else if(x1<xp) xp = x1-gap;

            //         if(y1>yp) yp = y1+gap;
            //         else if(y1<yp) yp=y1-gap;
            //     }
            // }
            static void iPolygon(double x[], double y[], int n,double d = 1, double dash = 10, double gap = 5)
            {
                iPath(x, y, n, d, 1, 1, dash, gap, 1);
            }
            static void iTriangle(double x1 , double y1 , double x2 , double y2 , double x3 , double y3,double d = 1, double dash = 10, double gap = 5)
            {
                double x[] = {x1, x2, x3};
                double y[] = {y1, y2, y3};
                 iPath(x, y, 3, d, 1, 1, dash, gap, 1);
            }
        };
        static void iPoint(double x, double y, int size = 0)
        {
            int i, j;
            glBegin(GL_POINTS);
            glVertex2f(x, y);
            for (i = x - size; i < x + size; i++)
            {
                for (j = y - size; j < y + size; j++)
                {
                    glVertex2f(i, j);
                }
            }

            glEnd();
            //    iFilledCircle(x,y,size/2.0);
        }

        static void iLine(double x1, double y1, double x2, double y2,double width=2.0)
        {
            glLineWidth(width);
            glBegin(GL_LINE_STRIP);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
            glLineWidth(2.0);
        }


        static void iPolygon(double x[], double y[], int n,double width=2.0)
        {
            int i;
            if (n < 3)return;
            glLineWidth(width);
            glBegin(GL_LINE_STRIP);
            for (i = 0; i < n; i++) {
                glVertex2f(x[i], y[i]);
            }
            glVertex2f(x[0], y[0]);
            glEnd();
            glLineWidth(2.0);
        }

        static void iTriangle(double x1 , double y1 , double x2 , double y2 , double x3 , double y3,double width=2.0)
        {
            double X[] = {x1, x2, x3};
            double Y[] = {y1, y2, y3};
            iPath(X, Y, 3,width, 1);
        }

        // static void iRectangle(double left, double bottom, double dx, double dy,double width=2.0)
        // {
        //     double x1, y1, x2, y2;

        //     cout<<width<<endl;
        //     x1 = left;
        //     y1 = bottom;
        //     x2 = x1 + dx;
        //     y2 = y1 + dy;

        //     double X[] = {x1,x2,x2,x1}, Y[] = {y1, y1, y2,y2};
        //     iLine(x1, y1, x2, y1,width);
        //     iLine(x2, y1, x2, y2,width);
        //     iLine(x2, y2, x1, y2,width);
        //     iLine(x1, y2, x1, y1,width);
        // }
        static void iRectangle(double x, double y, double dx, double dy, double width = 2)
        {
            double X[] = {x, x + dx, x + dx, x}, Y[] = {y, y, y + dy, y + dy};
            iPath(X, Y, 4,width, 1);
        }


        static void iCircle(double x, double y, double r, double width=2.0,int slices = 100)
        {
            double t, dt, x1, y1, xp, yp;
            dt = 2 * PI / slices;
            xp = x + r;
            yp = y;
            for (t = 0; t <= 2 * PI; t += dt)
            {
                x1 = x + r * cos(t);
                y1 = y + r * sin(t);
                iLine(xp, yp, x1, y1,width);
                xp = x1;
                yp = y1;
            }
        }

        static void iEllipse(double x, double y, double a, double b, int slices = 100,double width=2.0)
        {
            double t, dt, x1, y1, xp, yp;
            dt = 2 * PI / slices;
            xp = x + a;
            yp = y;
            for (t = 0; t <= 2 * PI; t += dt)
            {
                x1 = x + a * cos(t);
                y1 = y + b * sin(t);
                iLine(xp, yp, x1, y1,width);
                xp = x1;
                yp = y1;
            }
        }
    };

    static void iDelay(int sec)
    {
        int t1, t2;
        t1 = time(0);
        while (1) {
            t2 = time(0);
            if (t2 - t1 >= sec)
                break;
        }
    }

    static void igetPixelColor (int cursorX, int cursorY, int rgb[])
    {
        GLubyte pixel[3];
        glReadPixels(cursorX, cursorY, 1, 1,
                     GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

        rgb[0] = pixel[0];
        rgb[1] = pixel[1];
        rgb[2] = pixel[2];

        //printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
    }
    static void iRotate(double x, double y, double degree)
    {
        // push the current matrix stack
        glPushMatrix();

        //
        // The below steps take effect in reverse order
        //

        // step 3: undo the translation
        glTranslatef(x, y, 0.0);

        // step 2: rotate the co-ordinate system across z-axis
        glRotatef(degree, 0, 0, 1.0);

        // step 1: translate the origin to (x, y)
        glTranslatef(-x, -y, 0.0);
    }

    static void iUnRotate()
    {
        glPopMatrix();
    }

    static void windowSetup();
    static void iInitialize(char* title);
};

#endif