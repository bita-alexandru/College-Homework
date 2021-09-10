#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 500

const int n = 16;
const int m = 16;
unsigned char prevKey;

class GrilaCarteziana
{
private:
    double cx, cy;
    double eps;
    int c0, c1, l0, l1;
    double dc, dl;
public:
    int n, m;

    GrilaCarteziana(int n, int m)
    {
        this->n = n;
        this->m = m;
        eps = 0.1;
        setOg();
    }

    void setOg()
    {
        dc = (2 - 2*eps)/(m - 1);
        dl = (2 - 2*eps)/(n - 1);

		// seteaza originea
        int gcx = 0;//m/2;
        int gcy = 0;//n/2;

//        printf("OG:(%i,%i)\n",gcx,gcy);

        cx = -1 + eps + gcx*dc;//1 - eps - gcx*dc + dc*(m%2 == 0); // trateaza cazurile de paritate
        cy = -1 + eps + gcy*dl;

        // minimul si maximul pt coordonata x
        c0 = -gcx;
        c1 = m - gcx - 1;

        // minimul si maximul pt coordonata y
        l0 = -gcy;
        l1 = n - gcy - 1;

//        printf("%i, %i\n%i, %i\n\n",c0,c1,l0,l1);
    }

    void writePixel(int x, int y)
    {
        double xgl = cx + x*dc;
        double ygl = cy + y*dl;

//        printf("(%i,%i) %f, %f\n",x,y,xgl, ygl);

        int triunghiuri = 50; // cate triunghiuri formeaza cercul: mai multe -> mai rotund
        double raza = 0.03;

        if(xgl == cx && ygl == cy) glColor3d(0,0,1);
        else glColor3d(0,1,1);
        glBegin(GL_TRIANGLE_FAN); // deseneaza triunghiuri umplute ca sa acopere raza
            glVertex2f(xgl, ygl); // centrul cercului
            for(int i = 0; i <= triunghiuri; i++) {
                glVertex2d(
                    xgl + (raza * cos(i * 2.0*M_PI/triunghiuri)),
                    ygl + (raza * sin(i * 2.0*M_PI/triunghiuri))
                );
            }
        glEnd();
    }

    void afisare(int ex)
    {
        glColor3d(0, 0, 0);
        glLineWidth(1);

        double x0 = -1 + eps; // punctul de start pt desenarea iterativa a coloanelor
        for(int i = 0; i < m; i++)
        {
            glBegin(GL_LINES);
                glVertex2d(x0, 1 - eps);
                glVertex2d(x0, -1 + eps);
            glEnd();

            x0 += dc;
        }

        double y0 = 1 - eps; // punctul de start pt desenarea iterativa a liniilor
        for(int i = 0; i < n; i++)
        {
            glBegin(GL_LINES);
                glVertex2d(-1 + eps, y0);
                glVertex2d(1 - eps, y0);
            glEnd();

            y0 -= dl;
        }

        if(ex == 1)
        {
            varfuri();
        }
        else if(ex == 2)
        {
            segment();
        }
    }

    void varfuri()
    {
        // aprindere pixeli de sus -> jos & stanga -> dreapta
        for(int y = l0; y <= l1; y++)
        {
            for(int x = c0; x <= c1; x++)
            {
                writePixel(x, y);
            }
        }
    }

    void segment()
    {
        segmentInf();
        segmentSup();
    }

    void segmentInf()
    {
        const int x0 = 0, xn = c1;
        const int y0 = 0, yn = 7;

        glColor3d(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
            glVertex2d(cx + x0*dc, cy + y0*dl);
            glVertex2d(cx + xn*dc, cy + yn*dl);
        glEnd();

        const int dx = xn - x0;
        const int dy = yn - y0;
        int d = 2*dy - dx;
        int dE = 2*dy;
        int dNE = 2*(dy - dx);

        int x = x0, y = y0;
        writePixel(x, y);

        while(x < xn)
        {
            if(d <= 0) // alegem E
            {
                d += dE;
                x++;
            }
            else // alegem NE
            {
                d += dNE;
                x++; y++;
            }

            writePixel(x, y);
        }
    }

    void segmentSup()
    {
        const int x0 = 0, xn = c1;
        const int y0 = n-1, yn = 10;

        glColor3d(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
            glVertex2d(cx + x0*dc, cy + y0*dl);
            glVertex2d(cx + xn*dc, cy + yn*dl);
        glEnd();

        const int dx = xn - x0;
        const int dy = yn - y0;
        int d = 2*dy + dx;
        int dE = 2*dy;
        int dSE = 2*(dy + dx);

        int x = x0, y = y0;

        if(y+1 < n) writePixel(x, y+1);
        writePixel(x, y);
        if(y-1 >= 0) writePixel(x, y-1);

        while(x < xn)
        {
            if(d > 0) // alegem E
            {
                d += dE;
                x++;
            }
            else // alegem SE
            {
                d += dSE;
                x++; y--;
            }

            if(y+1 < n) writePixel(x, y+1);
            writePixel(x, y);
            if(y-1 >= 0) writePixel(x, y-1);
        }
    }
};

void Display0()
{
    GrilaCarteziana gc(n, m);
    gc.afisare(0);
}


void Display1()
{
    GrilaCarteziana gc(n, m);
    gc.afisare(1);
}

void Display2()
{
    GrilaCarteziana gc(n, m);
    gc.afisare(2);
}

void Init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);

    glLineWidth(1);

    glPointSize(1);

    glPolygonMode(GL_FRONT, GL_FILL); // pt umplerea poligoanelor
}

void Display(void)
{
    switch(prevKey)
    {
    case '0':
        glClear(GL_COLOR_BUFFER_BIT);
        Display0();
        break;
    case '1':
        glClear(GL_COLOR_BUFFER_BIT);
        Display1();
        break;
    case '2':
        glClear(GL_COLOR_BUFFER_BIT);
        Display2();
        break;
    default:
        break;
    }

    glFlush();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow (argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}
