
#ifndef __I_GRAPHICS__
#define __I_GRAPHICS__
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <Gl/GLAux.h>
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
        p.y = (c1 * a2 - c2 * a1) / d;
        return p;
    }

    static void iPath(double X[],
                      double Y[],
                      int n,
                      double d = 1,
                      int closed = 0,
                      int dashed = 0,
                      double dash = 10,
                      double gap = 5,
                      int aligned = 0)
    {
        /*
         *  Solves equations of consecutive parallel straight lines, distanced d/2 from the
         *  original line to determine points for the stroked path.
         *
         *  For the first end points in non-closed, finds perpendicularly d/2 distanced points
         *
         */

        //  p1 ------------------- p2
        //     -------------------
        //  p0 ------------------- p3
        double pX[4], pY[4];
        double dy, dx, a1, b1, c1, a2, b2, c2, M1, M2, S;
        int s1, s2, end = n + 2 * closed;
        point p1, p2;
        S = 0;
        // repeating first two points like points in the middle for closed
        for (int i = 0; i < end; i++)
        {
            if (i == n - 1 && !closed)
            {
                s2 = s1;
                a2 = a1, b2 = b1, c2 = c1;
            }
            else
            {
                dy = Y[(i + 1) % n] - Y[i % n];
                dx = X[(i + 1) % n] - X[i % n];
                if (i == 0)
                    s2 = 1;
                else
                {
                    // only combination of inequalities that gives the right signs :3
                    s2 = (X[i % n] > X[(i - 1) % n] && X[(i + 1) % n] > X[i % n]) ||
                         (X[i % n] <= X[(i - 1) % n] && X[(i + 1) % n] <= X[i % n]);
                    s2 = s1 * (2 * s2 - 1);
                }
                if (dx > 0)
                    a2 = -dy, b2 = dx;
                else
                    a2 = dy, b2 = -dx;
                c2 = -(a2 * X[i % n] + b2 * Y[i % n]);
                M2 = sqrt(a2 * a2 + b2 * b2);
            }
            // we don't want to draw the end points normally for closed
            if ((!closed && (i == 0 || i == n - 1)) || fabs(a1 * b2 - a2 * b1) < ERR)
            {
                // solving the perpendicular and two parralel st lines with distance d/2 from the original
                a1 = b2, b1 = -a2, c1 = -(a1 * X[i % n] + b1 * Y[i % n]);
                p1 = solve_sim_eqn(a1, b1, c1, a2, b2, c2 + s2 * d * M2 / 2),
                p2 = solve_sim_eqn(a1, b1, c1, a2, b2, c2 - s2 * d * M2 / 2);
            }
            // we want to draw for i == n - 1 normally for closed, but not i == 0
            else if (i != 0)
            {
                // solving two consecutive parallel d distanced st lines
                p1 = solve_sim_eqn(a1, b1, c1 + s1 * d * M1 / 2, a2, b2, c2 + s2 * d * M2 / 2),
                p2 = solve_sim_eqn(a1, b1, c1 - s1 * d * M1 / 2, a2, b2, c2 - s2 * d * M2 / 2);
            }
            // keeping last two points
            pX[2] = p1.x, pY[2] = p1.y;
            pX[3] = p2.x, pY[3] = p2.y;
            // nothing to draw when i == 0 and i == 1 if closed
            if (i != 0 && !(closed && i == 1))
            {
                if (dashed)
                {
                    dx = X[i % n] - X[(i - 1) % n];
                    dy = Y[i % n] - Y[(i - 1) % n];
                    double dS = sqrt(dx * dx + dy * dy);
                    double x, y;
                    double S1 = S, S2;
                    double tX[4], tY[4];
                    // taking the vector approach for points at perpendicular distance
                    struct point dr
                    {
                        .x = dy / dS * d / 2, .y = -dx / dS * d / 2
                    };
                    if (aligned)
                    {
                        double t, dt;
                        int m = floor((dS - dash - gap) / (dash + gap));             // number of dashes in between
                        double gap_ = gap + (dS - (m + 1) * (dash + gap)) / (m + 1); // leading and trailing space
                        for (int j = -1; j <= m; j++)
                        {
                            if (j == -1)
                                t = 0, dt = dash / 2;
                            else if (j == m)
                                t = dS - dash / 2, dt = dash / 2;
                            else
                            {
                                t = (dash / 2 + gap_ + j * (dash + gap_));
                                dt = dash;
                            }
                            for (int k = 0; k < 2; k++)
                            {
                                x = (t + dt * k) / dS * dx + X[(i - 1) % n];
                                y = (t + dt * k) / dS * dy + Y[(i - 1) % n];
                                if ((j == -1 && !k) || (j == m && k))
                                {
                                    tX[1 + k] = pX[1 + k], tY[1 + k] = pY[1 + k];
                                    tX[3 * k] = pX[3 * k], tY[3 * k] = pY[3 * k];
                                }
                                else
                                {
                                    tX[1 + k] = x + dr.x, tY[1 + k] = y + dr.y;
                                    tX[3 * k] = x - dr.x, tY[3 * k] = y - dr.y;
                                }
                            }
                            iG::IDraw::IFilled::iPolygon(tX, tY, 4);
                        }
                    }
                    else
                    {
                        while (S1 < dS)
                        {
                            S2 = S1 + dash;
                            for (int j = 0; j < 2; j++)
                            {
                                if (j == 0 && S1 <= 0)
                                {
                                    tX[1] = pX[1], tY[1] = pY[1];
                                    tX[0] = pX[0], tY[0] = pY[0];
                                }
                                else if (j == 1 && S2 >= dS)
                                {
                                    tX[2] = pX[2], tY[2] = pY[2];
                                    tX[3] = pX[3], tY[3] = pY[3];
                                }
                                else
                                {
                                    double t = (j == 0 ? S1 : S2);
                                    x = t / dS * dx + X[(i - 1) % n];
                                    y = t / dS * dy + Y[(i - 1) % n];
                                    tX[1 + j] = x + dr.x, tY[1 + j] = y + dr.y;
                                    tX[3 * j] = x - dr.x, tY[3 * j] = y - dr.y;
                                }
                            }
                            iG::IDraw::IFilled::iPolygon(tX, tY, 4);
                            S1 += (dash + gap);
                        }
                        if (S2 <= dS)
                            S = S1 - dS; // gap before first dash
                        else
                            S = S1 - dash - gap - dS; // unfinished dash
                    }
                }
                else
                    iG::IDraw::IFilled::iPolygon(pX, pY, 4);
            }
            a1 = a2, b1 = b2, c1 = c2, M1 = M2, s1 = s2;
            // shifting points left
            pX[1] = pX[2], pY[1] = pY[2];
            pX[0] = pX[3], pY[0] = pY[3];
        }
    }
    static void iClear()
    {
        glClear(GL_COLOR_BUFFER_BIT) ;
        glMatrixMode(GL_MODELVIEW) ;
        glClearColor(iClearR / 255, iClearG / 255, iClearB / 255, 1.0);
        glFlush();
    }
    virtual void iAbstract() = 0;
    static int iWindowHeight, iWindowWidth, iScreenHeight, iScreenWidth, iWindowX, iWindowY;
    static double iClearR, iClearG, iClearB;
    static double iMouseX, iMouseY;
    static double  iMouseDir;
public:
    static int ifft;
    static void iDraw();
    static void iKeyboard(unsigned char);
    static void iKeyboardUp(unsigned char);
    static void iSpecialKeyboard(unsigned char);
    static void iSpecialKeyboardUp(unsigned char);
    static void iMouseDrag(int, int);
    static void iMouseMove(int, int);
    static void iMouseClick(int button, int state, int x, int y);
    static void iMouseScroll(int dir);
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
    static int iSetWindowHeight(int height)
    {
        iWindowHeight = height;
    }
    static int iSetWindowWidth(int width)
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
    static int iSetScreenHeight(int height)
    {
        iScreenHeight = height;
    }
    static int iSetScreenWidth(int width)
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
    static void iSetMouseX(double x)
    {
        glutWarpPointer(x, iMouseY);
    }
    static void iSetMouseY(double y)
    {
        glutWarpPointer(iMouseX, y);
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
        glutWarpPointer(x, y);
    }
    static double getMouseDirection()
    {
        return iMouseDir;
    }
    static void iMouseDirection(int mx, int my)
    {
        // Setting the mouse direction between 0 and 360
        int dx = mx  - iMouseX , dy = my - iMouseY ;
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
        glutSwapBuffers() ;
    }

    static void animFF(void)
    {
        if (ifft == 0) {
            ifft = 1;
            iClear();
        }
        glutPostRedisplay();
    }

    static void joystickHandlerFF(unsigned int buttonMask, int x, int y, int z)
    {
        cout << buttonMask << " " << x << " " << y << " " << z << endl;
    }
    static void keyboardHandler1FF(unsigned char key, int x, int y)
    {
        iKeyboard(key);
        glutPostRedisplay();
    }
    static void keyboardUpHandler1FF(unsigned char key, int x, int y)
    {
        iKeyboardUp(key);
        glutPostRedisplay();
    }
    static void keyboardHandler2FF(int key, int x, int y)
    {
        iSpecialKeyboard(key);
        glutPostRedisplay();
    }
    static void keyboardUpHandler2FF(int key, int x, int y)
    {
        iSpecialKeyboardUp(key);
        glutPostRedisplay();
    }
    static void mouseDragHandlerFF(int mx, int my)
    {
        iMouseX = mx;
        iMouseY = iWindowHeight - my;
        iMouseDrag(iMouseX, iMouseY);
        glFlush();
    }

    static void mouseMoveHandlerFF(int mx, int my)
    {
        iMouseDirection(mx, iWindowHeight - my);
        iMouseX = mx;
        iMouseY = iWindowHeight - my;
        iMouseMove(iMouseX, iMouseY);
        glFlush();
    }

    static void mouseClickHandlerFF(int button, int state, int x, int y)
    {
        iMouseX = x;
        iMouseY = iWindowHeight - y;
        iMouseClick(button, state, iMouseX, iMouseY);
        glFlush();
    }

    static void mouseWheelHandlerFF(int button, int dir, int x, int y)
    {
        iMouseScroll(dir);
    }

    class IText {
    public:
        static void iSmall(double x, double y, char *str, void* font = GLUT_BITMAP_TIMES_ROMAN_24)
        {
            glRasterPos3d(x, y, 0);
            int i;
            for (i = 0; str[i]; i++) {
                glutBitmapCharacter(font, str[i]); //GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
            }
        }

        static void iBig(double x, double y, char *str, void* font = GLUT_STROKE_ROMAN)
        {
            char *p;
            glPushMatrix();
            glTranslatef(x, y, 0);
            for (p = str; *p; p++)
                glutStrokeCharacter(font, *p); // GLUT_STROKE_ROMAN  , GLUT_STROKE_MONO_ROMAN
            glPopMatrix();
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









