#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <queue>
#include <map>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 500

using namespace std;

const int n = 16;
const int m = 16;
unsigned char prevKey;

class GrilaCarteziana
{
private:
    double cx, cy;
    double eps;
    int c0, c1, l0, l1, gcx, gcy;
    double dc, dl;
public:
    int n, m;

    GrilaCarteziana(int n, int m)
    {
        this->n = n;
        this->m = m;
        eps = 0.1;
        setOg(0, 0);
    }

    void setOg(int x = 0, int y = 0)
    {
        dc = (2 - 2*eps)/(m - 1);
        dl = (2 - 2*eps)/(n - 1);

		// seteaza originea
        gcx = x;
        gcy = y;

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
            cerc(13);
        }
        else if(ex == 2)
        {
            elipsa(10, 5);
        }
        else if(ex == 3)
        {
            poligon();
        }
    }

    void cerc(int R)
    {
        double xgl = cx;
        double ygl = cy;
        int triunghiuri = 360;

        glColor3d(1, 0, 0);
        glLineWidth(5);
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i <= triunghiuri; i++)
            {
                glVertex2d(
                    xgl + (R*dc * cos(i * 2.0*M_PI/triunghiuri)),
                    ygl + (R*dl * sin(i * 2.0*M_PI/triunghiuri))
                );
            }
        glEnd();

        int x = R, y = 0;
        int d = 1 - R;
        int dN = 3;
        int dNV = -2*R + 5;

        if(x+1 < m) writePixel(x+1, y);
        writePixel(x, y);
        if(x-1 >= 0) writePixel(x-1, y);

        while(x > y)
        {
            if(d < 0)
            {
                d += dN;
                dN += 2; dNV += 2;
            }
            else
            {
                d += dNV;
                dN += 2; dNV += 4;
                x--;
            }
            y++;

            if(x+1 < m) writePixel(x+1, y);
            writePixel(x, y);
            if(x-1 >= 0) writePixel(x-1, y);
        }
    }

    void elipsa(int a, int b)
    {
        double xgl = cx;
        double ygl = cy;
        int triunghiuri = 360;

        glColor3d(1, 0, 0);
        glLineWidth(5);
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i <= triunghiuri; i++)
            {
                glVertex2d(
                    xgl + (a*dc * cos(i * 2.0*M_PI/triunghiuri)),
                    ygl + (b*dl * sin(i * 2.0*M_PI/triunghiuri))
                );
            }
        glEnd();

        int x = 0, y = -b;
        double d = 0.0;
        double deltaV, deltaNV, deltaN;

        writePixel(x, y);

        while(a*a*(y-0.5) < b*b*(x+1))
        {
            printf("%d %d\n",a,b);
            deltaV = b*b*(-2*x+1);
            deltaNV = b*b*(-2*x + 1) + a*a*(2*y + 1);

            if(d + deltaV <= 0.0)
            {
                d += deltaV;
                x--;

                writePixel(x, y);
            }
            else if(d + deltaNV <= 0.0)
            {
                d += deltaNV;
                x--; y++;

                for(int xi = x; xi <= 0; xi++)
                {
                    writePixel(xi, y);
                }
            }
        }

        while(y < 0)
        {
            deltaNV = b*b*(-2*x + 1) + a*a*(2*y + 1);
            deltaN = a*a*(2*y + 1);

            if(d + deltaNV <= 0.0)
            {
                d += deltaNV;
                x--; y++;
            }
            else
            {
                d += deltaN;
                y++;
            }

            for(int xi = x; xi <= 0; xi++)
            {
                writePixel(xi, y);
            }
        }
    }

    void poligon()
    {

    }
};

void Display0()
{
    GrilaCarteziana gc(n, m);
    gc.afisare(0);
}


void Display1() // afisare cerc
{
    GrilaCarteziana gc(n, m);
    gc.afisare(1);
}

void Display2() // umplere elipsa
{
    GrilaCarteziana gc(27, 27);
    gc.setOg(13, 10);
    gc.afisare(2);
}

void Display3() // umplere poligon
{
    GrilaCarteziana gc(n, m);
    gc.afisare(3);
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
