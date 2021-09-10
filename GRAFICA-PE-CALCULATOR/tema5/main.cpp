#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;
int nivel = 0;

class CComplex
{
public:
    CComplex() : re(0.0), im(0.0) {}
    CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0) {}
    CComplex(const CComplex &c) : re(c.re), im(c.im) {}
    ~CComplex() {}

    CComplex &operator=(const CComplex &c)
    {
        re = c.re;
        im = c.im;
        return *this;
    }

    double getRe()
    {
        return re;
    }
    void setRe(double re1)
    {
        re = re1;
    }

    double getIm()
    {
        return im;
    }
    void setIm(double im1)
    {
        im = im1;
    }

    double getModul()
    {
        return sqrt(re * re + im * im);
    }

    int operator==(CComplex &c1)
    {
        return ((re == c1.re) && (im == c1.im));
    }

    CComplex pow2()
    {
        CComplex rez;
        rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
        rez.im = 2.0 * re * im;
        return rez;
    }

    friend CComplex operator+(const CComplex &c1, const CComplex &c2);
    friend CComplex operator*(CComplex &c1, CComplex &c2);

    void print(FILE *f)
    {
        fprintf(f, "%.20f%+.20f i", re, im);
    }

private:
    double re, im;
};

CComplex operator+(const CComplex &c1, const CComplex &c2)
{
	CComplex rez(c1.re + c2.re, c1.im + c2.im);
	return rez;
}

CComplex operator*(CComplex &c1, CComplex &c2)
{
	CComplex rez(c1.re * c2.re - c1.im * c2.im,
                c1.re * c2.im + c1.im * c2.re);
	return rez;
}

class C2coord
{
public:
    C2coord()
    {
        m.x = m.y = 0;
    }

    C2coord(double x, double y)
    {
        m.x = x;
        m.y = y;
    }

    C2coord(const C2coord &p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
    }

    C2coord &operator=(C2coord &p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(C2coord &p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

protected:
    struct SDate
    {
        double x,y;
    } m;
};

class CPunct : public C2coord
{
public:
    CPunct() : C2coord(0.0, 0.0)
    {}

    CPunct(double x, double y) : C2coord(x, y)
    {}

    CPunct &operator=(const CPunct &p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    void getxy(double &x, double &y)
    {
        x = m.x;
        y = m.y;
    }

    int operator==(CPunct &p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }
};

class CVector : public C2coord
{
public:
    CVector() : C2coord(0.0, 0.0)
    {
        normalizare();
    }

    CVector(double x, double y) : C2coord(x, y)
    {
        normalizare();
    }

    CVector &operator=(CVector &p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(CVector &p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

    CPunct getDest(CPunct &orig, double lungime)
    {
        double x, y;
        orig.getxy(x, y);
        CPunct p(x + m.x * lungime, y + m.y * lungime);
        return p;
    }

    void rotatie(double grade)
    {
        double x = m.x;
        double y = m.y;
        double t = 2 * (4.0 * atan(1.0)) * grade / 360.0;
        m.x = x * cos(t) - y * sin(t);
        m.y = x * sin(t) + y * cos(t);
        normalizare();
    }

    void deseneaza(CPunct p, double lungime)
    {
        double x, y;
        p.getxy(x, y);
        glColor3f(1.0, 0.1, 0.1);
        glBegin(GL_LINE_STRIP);
        glVertex2d(x, y);
        glVertex2d(x + m.x * lungime, y + m.y * lungime);
        glEnd();
    }

private:
    void normalizare()
    {
        double d = sqrt(C2coord::m.x * C2coord::m.x + C2coord::m.y * C2coord::m.y);
        if (d != 0.0)
        {
            C2coord::m.x = C2coord::m.x * 1.0 / d;
            C2coord::m.y = C2coord::m.y * 1.0 / d;
        }
    }
};

class Fractal1 // sierpinski's carpet
{
public:
    void fractal(double lungime,
                 int nivel,
                 CPunct p,
                 CVector v)
    {
        CPunct p1;
        double x, y;
        if (nivel == 0)
        {
            // deseneaza patrat
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            v.rotatie(-90);
        }
        else
        {
            // patratul din mijloc
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            p = v.getDest(p, lungime);
            v.rotatie(-90);
            v.deseneaza(p, lungime);

            v.rotatie(-90);

            // patratele de sus
            p1 = p;
            p.getxy(x, y);
            p = CPunct(x-2.0*lungime/3.0, y+lungime*5.0/3.0);
            for(int i = 0; i < 3; i++)
            {
                fractal(lungime/3.0, nivel-1, p, v);
                p = v.getDest(p, lungime);
            }

            // patratele de jos
            p = p1;
            p.getxy(x, y);
            p = CPunct(x-2.0*lungime/3.0, y-lungime/3.0);
            for(int i = 0; i < 3; i++)
            {
                fractal(lungime/3.0, nivel-1, p, v);
                p = v.getDest(p, lungime);
            }

            // patratele din lateral
            p = p1;
            p.getxy(x, y);
            p = CPunct(x-2.0*lungime/3.0, y+lungime/1.5);
            for(int i = 0; i < 2; i++)
            {
                fractal(lungime/3.0, nivel-1, p, v);
                p = v.getDest(p, lungime*2.0);
            }
        }
    }

    void afisare(double lungime, int nivel)
    {
        CVector v(1.0, 0.0);
        CPunct p(-1.0, 1.0);

        v.deseneaza(p, lungime);

        p = v.getDest(p, lungime);
        v.rotatie(-90);
        v.deseneaza(p, lungime);

        p = v.getDest(p, lungime);
        v.rotatie(-90);
        v.deseneaza(p, lungime);

        p = v.getDest(p, lungime);
        v.rotatie(-90);
        v.deseneaza(p, lungime);

        p = CPunct(-1.0/3.0, 1.0/3.0);
        v.rotatie(-90);

        fractal(lungime/3.0, nivel, p, v);
    }
};

class Fractal2 // l-system branch
{
public:
    void fractal(double lungime,
                 int nivel,
                 double factordiviziune,
                 CPunct p,
                 CVector v)
    {
        assert(factordiviziune != 0);
        CPunct p1, p2;
        if (nivel == 0)
        {
        }
        else
        {
            v.rotatie(-45);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            fractal(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            v.rotatie(90);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            p2 = p1;

            v.rotatie(15);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            fractal(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(-60);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            p2 = p1;

            double f = 0.5;

            v.rotatie(30);
            v.deseneaza(p1, f*lungime);
            p1 = v.getDest(p1, f*lungime);
            fractal(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(-120);
            v.deseneaza(p1, f*lungime);
            p1 = v.getDest(p1, f*lungime);
            fractal(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);
        }
    }

    void afisare(double lungime, int nivel)
    {
        CVector v(0.0, -1.0);
        CPunct p(0.0, 1.0);

        v.deseneaza(p, 0.25);
        p = v.getDest(p, 0.25);
        fractal(lungime, nivel, 0.4, p, v);
    }
};

class Fractal3 // sierpinski's arrowhead
{
public:
    struct Turtle
    {
        double x;
        double y;
        int grade;
    };

    void roteste(Turtle* turtle, int grade)
    {
        turtle->grade = (turtle->grade + grade) % 360;
    }

    void deseneaza(Turtle* turtle, double lungime)
    {
        double theta = (M_PI * turtle->grade)/180.0;
        turtle->x += lungime * cos(theta);
        turtle->y += lungime * sin(theta);

//        printf("%5.3f %5.3f %5i\n",turtle->x,turtle->y,turtle->grade);

        glVertex2f(turtle->x, turtle->y);
    }

    void fractal(int nivel, double lungime, Turtle* turtle, int grade)
    {
        if(nivel == 0)
        {
            deseneaza(turtle, lungime);
        }
        else
        {
            fractal(nivel - 1, lungime/2, turtle, -grade);
            roteste(turtle, grade);

            fractal(nivel - 1, lungime/2, turtle, grade);
            roteste(turtle, grade);

            fractal(nivel - 1, lungime/2, turtle, -grade);
        }
    }

    void afisare(double lungime, int nivel)
    {
        Turtle turtle;
        turtle.grade = 90;
        turtle.x = 0.0 - lungime*0.5;
        turtle.y = 0.0 - lungime*0.5;

        if(nivel%2 != 0) roteste(&turtle, -60);

        glColor3f(1.0, 0.1, 0.1);
        glBegin(GL_LINE_STRIP);
            glVertex2f(turtle.x, turtle.y);
            fractal(nivel, lungime, &turtle, 60);
        glEnd();
    }
};

class Fractal4 // mandelbrot's set
{
public:
    int isIn(CComplex &c)
    {
        int max_it = 1000;
        CComplex z0;

        for(int i = 1; i < max_it; i++)
        {
            CComplex zn = z0*z0 + c;
            z0 = zn;

            if(zn.getModul() > 2.0) return i;

        }

        return -1;
    }

    void afisare()
    {
        double ratia = 0.005;

        glColor3f(1.0, 0.1, 0.1);
        glBegin(GL_POINTS);
            for(double x = -2+ratia; x < 2; x += ratia)
                for(double y = -2+ratia; y < 2; y += ratia)
                {
                    CComplex c(x, y);

                    int i = isIn(c);
                    if(i == -1)
                    {
                        glColor3f(1.0, 0.1, 0.1);
                        glVertex2d(x, y);
                    }
                    else
                    {
                        double r = 1.0/(i%256);
                        double g = 1.0/(i%256);
                        double b = 1.0/(i%256);

                        glColor3f(r, g, b);
                        glVertex2d(x, y);
                    }
                }
        glEnd();
    }
};

void Display1()
{
    Fractal1 f1;

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98,-0.98);

    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glPushMatrix();
    glLoadIdentity();
    glScaled(0.9, 0.9, 1);
    f1.afisare(2.0, nivel);
    glPopMatrix();
    nivel++;
}

void Display2()
{
    Fractal2 f;
    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98,-0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glPushMatrix();
    glLoadIdentity();
    glScaled(0.4, 0.4, 1);
    glTranslated(-0.5, 0.5, 0.0);
    f.afisare(1, nivel);
    glPopMatrix();
    nivel++;
}

void Display3()
{
    Fractal3 f;
    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98,-0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    f.afisare(1.0, nivel);

    nivel++;
}

void Display4()
{
    Fractal4 f;

    glPushMatrix();
    glLoadIdentity();
    glScaled(0.7, 0.7, 1);
    glTranslated(0.5, 0.0, 0.0);
    f.afisare();
    glPopMatrix();
}

void Init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);

    glLineWidth(1);

    glPointSize(5);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void)
{
    switch(prevKey)
    {
    case '0':
        glClear(GL_COLOR_BUFFER_BIT);
        nivel = 0;
        fprintf(stderr, "nivel = %d\n", nivel);
        break;
    case '1':
        glClear(GL_COLOR_BUFFER_BIT);
        Display1();
        break;
    case '2':
        glClear(GL_COLOR_BUFFER_BIT);
        Display2();
        break;
    case '3':
        glClear(GL_COLOR_BUFFER_BIT);
        Display3();
        break;
    case '4':
        glClear(GL_COLOR_BUFFER_BIT);
        Display4();
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


