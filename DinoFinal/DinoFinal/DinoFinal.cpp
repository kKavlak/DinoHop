// Google İnternet kopunca dinozor oyunu açıyo ya hah işte o

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool timer = 0;

bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int score = 0;

int cactix = 400, dinoy = -160;

int j = 0, stepc = 1, stepw = 4;

bool grocol = 1, lossf = 0, startf = 1;

double diff = 0, g = 0;

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void drawCacti(int x, int y)
{
    glColor3f(0, 0.5, 0);
    glRectf(x - 5, y, x + 5, y + 80);
}

void drawDino(int x, int y, int cnt)
{
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x - 90, y);
    glVertex2f(x - 30, y + 30);
    glVertex2f(x, y + 60);
    glVertex2f(x, y + 90);
    glVertex2f(x + 10, y + 100);
    glVertex2f(x + 40, y + 100);
    glVertex2f(x + 40, y + 80);
    glVertex2f(x + 20, y + 80);
    glVertex2f(x + 20, y + 20);
    glVertex2f(x, y + 20);
    glEnd();

    if (lossf != 1) {
        glColor3f(1, 1, 1);
        circle(x + 12, y + 93, 3);
    }
    glColor3f(0, 0, 0);
    circle(x + 12, y + 93, 2);

    glColor3f(0.3, 0.3, 0.3);
    circle(x + 35, y + 95, 2);

    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(x + 20, y + 40);
    glVertex2f(x + 30, y + 40);
    glVertex2f(x + 35, y + 35);
    glVertex2f(x + 20, y + 35);
    glVertex2f(x + 20, y + 60);
    glEnd();

    switch (cnt)
    {

    case 0:
    case 1:
    case 2:
        glColor3f(0.4, 0.4, 0.4);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, y);
        glVertex2f(x - 40, y - 20);
        glVertex2f(x - 60, y - 20);
        glVertex2f(x - 40, y);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.3, 0.3, 0.3);
        glVertex2f(x - 20, y);
        glVertex2f(x, y - 20);
        glVertex2f(x + 20, y - 20);
        glVertex2f(x, y);
        glEnd();
        break;

    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        glColor3f(0.4, 0.4, 0.4);
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x, y - 10);
        glVertex2f(x + 10, y - 20);
        glVertex2f(x - 20, y - 20);
        glVertex2f(x - 20, y);
        glEnd();
        break;

    case 9:
    case 10:
    case 11:
        glColor3f(0.3, 0.3, 0.3);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, y);
        glVertex2f(x - 40, y - 20);
        glVertex2f(x - 60, y - 20);
        glVertex2f(x - 40, y);
        glEnd();

        glColor3f(0.4, 0.4, 0.4);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, y);
        glVertex2f(x, y - 20);
        glVertex2f(x + 20, y - 20);
        glVertex2f(x, y);
        glEnd();
        break;
    }
}

//
// To display onto window using OpenGL commands
//
void display() {
    //
    // clear window to blue
    //
    glClearColor(0.5, 0.5, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2, 0.2, 0.2);
    glRectf(-winWidth / 2, -winHeight / 2, winWidth / 2, -winHeight / 2.5);

    glColor3f(0.8, 0.8, 0.1);
    glRectf(-winWidth / 2, -winHeight / 2 + 60, winWidth / 2, -winHeight / 2.5 + 60);

    drawCacti(cactix, -winHeight / 2.5 + 60);

    drawDino(-200, dinoy, stepw);

    {
        glColor3f(1, 1, 1);
        vprint(-290, -260, GLUT_BITMAP_8_BY_13, "<Spacebar>: Jump");
        vprint(-290, -280, GLUT_BITMAP_8_BY_13, "<F1>: Start/Restart");
        vprint(-100, -260, GLUT_BITMAP_8_BY_13, "<F2>: Pause/Unpause");
        vprint(-100, -280, GLUT_BITMAP_8_BY_13, "<Esc>: Close");
        glColor3f(0, 0, 0);
        vprint(-220, -220, GLUT_BITMAP_8_BY_13, "Score: %d", score);

    }

    if (startf == 1)
    {
        glColor3f(1, 0, 0);
        vprint(-100, 100, GLUT_BITMAP_8_BY_13, "Press <F1> to start");
    }

    if (lossf == 1)
    {
        glColor3f(1, 0, 0);
        vprint(-70, 0, GLUT_BITMAP_8_BY_13, "You Lost!");
        vprint(-70, -20, GLUT_BITMAP_8_BY_13, "Your Score: %d", score);
        vprint(-70, -40, GLUT_BITMAP_8_BY_13, "<F1> to restart");
    }


    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == 32)
    {
        if (grocol == 1)
            j += 24;
        grocol = 0;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    case GLUT_KEY_F1:
        timer = 1;
        dinoy = -160;
        cactix = 400;
        g = 0;
        j = 0;
        diff = 0;
        lossf = 0;
        score = 0;
        startf = 0;
        break;
    case GLUT_KEY_F2:
        timer = !timer;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (timer == 1)
    {
        cactix -= (7 + diff);
        if (cactix < -300)
        {
            cactix = 400;
            diff += 0.075;
            score++;
        }

        if (dinoy >= -160)
        {
            dinoy += (j - g);

            if (dinoy > -160)
                g += 1.5;

            if (abs(dinoy - -160) < 20)
            {
                g = 0;
                j = 0;
                grocol = 1;
            }
        }

        if (abs(dinoy - (-winHeight / 2.5 + 140) < 5 && abs(cactix - -200) < 25))
        {
            timer = 0;
            lossf = 1;
        }

        stepc++;
        if (grocol == 0)
            stepw = 4;
        else
            stepw = stepc % 12;


        // to refresh the window it calls display() function
        glutPostRedisplay(); // display()
    }
}
#endif

void Init()
{
    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Kayra's Small Summer Project");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}