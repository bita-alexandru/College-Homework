#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

// dimensiunea ferestrei in pixeli
#define dim 300
#define inf 99999

using namespace std;

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Exemplu1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1);
   double ratia = 0.05;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;

   double t;
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP);
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Exemplu2() {
   double pi = 4 * atan(1);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display1()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
    double ratia = 0.01;

    xmin = 0;
    for(double t = ratia; t < 100; t += ratia) // 0 < x < 100, f(x) = d/x, d = round(x)-x
    {
        double d = fabs(round(t) - t);
        double y = d/t;
        double x = t;

        xmax = max(xmax, x);
        xmin = min(xmin, x);
        ymax = max(ymax, y);
        ymin = min(ymin, y);
    }

    printf("x: [%.2f, %.2f]\n", xmin, xmax);
    printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

    glColor3f(1,0.1,0.1); // rosu
    glBegin(GL_LINE_STRIP);
        glVertex2f(0, 1-ratia); // x = 0 => f(x) = 1

        for(double t = ratia; t < 100; t += ratia) // 0 < x < 100, f(x) = d/x, d = round(x)-x
        {
            double d = fabs(round(t) - t);
            double y = min(d/t, 1-ratia);
            double x = t/xmax;

            glVertex2f(x,y);
        }
    glEnd();
}

void Display2()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
    double a = 0.3, b = 0.2;
    double pi = 4 * atan(1);
    double ratia = 0.01;

    for(double t = -pi+ratia; t < pi; t += ratia)
    {
        double x = 2*(a*cos(t) + b)*cos(t);
        xmax = max(xmax, x);
        xmin = min(xmin, x);

        double y = 2*(a*cos(t) + b)*sin(t);
        ymax = max(ymax, y);
        ymin = min(ymin, y);
    }

    printf("x: [%.2f, %.2f]\n", xmin, xmax);
    printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

    glColor3f(1,0.1,0.1); // rosu
    glBegin(GL_LINE_STRIP);
        for(double t = -pi + ratia; t < pi; t += ratia)
        {
            double x = 2*(a*cos(t) + b)*cos(t);
            double y = 2*(a*cos(t) + b)*sin(t);

            x -= 0.15;

            glVertex2f(x,y);
        }
    glEnd();
}

void Display3()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
    double a = 0.2;
    double pi = 4 * atan(1);
    double ratia = 0.01;

    for(double t = -pi/2 + ratia; t < pi/2; t += ratia)
    {
        if(fabs(t) == pi/6) continue;

        double x = a/(4*cos(t)*cos(t) - 3);
        double y = (a*tan(t))/(4*cos(t)*cos(t) - 3);

        xmax = max(xmax, x);
        xmin = min(xmin, x);
        ymax = max(ymax, y);
        ymin = min(ymin, y);
    }

    printf("x: [%.2f, %.2f]\n", xmin, xmax);
    printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

    vector<pair<double,double>> puncte;

    glColor3f(0,0,1); // albastru
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1+ratia*2, 1-ratia);
        for(double t = -pi/2 + ratia; t < -pi/5.5; t += ratia)
        {
            double x = a/(4*cos(t)*cos(t) - 3);
            double y = (a*tan(t))/(4*cos(t)*cos(t) - 3);

            x = max(x, -1+ratia*2);
            x = min(x, 1-ratia);
            y = min(y, 1-ratia);
            y = max(y, -1+ratia);

            glVertex2f(x, y);
            puncte.push_back({x,y});
        }
    glEnd();

    int n = puncte.size();

    glColor3f(1,0.1,0.1); // rosu
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < n-1; i += 2)
        {
            if(i > n/4 && i < 3*n/4) continue;

            glVertex2f(-1+ratia*2, 1-ratia);

            double x1 = puncte[i].first;
            double y1 = puncte[i].second;

            glVertex2f(x1,y1);

            double x2 = puncte[i+1].first;
            double y2 = puncte[i+1].second;

            glVertex2f(x2,y2);
        }
    glEnd();
}

void Display4()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
	double a = 0.1, b = 0.2;
	double ratia = 0.01;

	for(double d = -9.5; d < 9.5; d += ratia)
	{
		double x = a*d - b*sin(d);
		xmax = max(x, xmax);
		xmin = min(x, xmin);

		double y = a - b*cos(d);
		ymax = max(y, ymax);
		ymin = min(y, ymin);

		glVertex2f(x, y);
	}


	printf("x: [%.2f, %.2f]\n", xmin, xmax);
	printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
        for(double d = -9.5; d < 9.5; d += ratia)
        {
            double x = a*d - b*sin(d);
            double y = a - b*cos(d);

            glVertex2f(x, y);
        }
	glEnd();
}

void Display5()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
    double R = 0.1, r = 0.3;
    double pi = 4 * atan(1);
    double ratia = 0.01;

    for(double t = 0; t < 2*pi; t += ratia)
    {
        double x = (R + r)*cos(r/R * t) - r*cos(t + r/R * t);
        xmax = max(xmax, x);
        xmin = min(xmin, x);

        double y = (R + r)*sin(r/R * t) - r*sin(t + r/R * t);
        ymax = max(ymax, y);
        ymin = min(ymin, y);
    }

    printf("x: [%.2f, %.2f]\n", xmin, xmax);
    printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

    glColor3f(1,0.1,0.1); // rosu
    glBegin(GL_LINE_STRIP);
        for(double t = 0; t < 2*pi; t += ratia)
        {
            double x = (R + r)*cos(r/R * t) - r*cos(t + r/R * t);
            double y = (R + r)*sin(r/R * t) - r*sin(t + r/R * t);

            glVertex2f(x,y);
        }
    glEnd();
}

void Display6()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1);
	double ratia = 0.01;

	for(double t = 0; t <= 2*pi; t += ratia)
	{
		double x = (R - r)*cos(r/R * t) - r*cos(t - (r/R * t));
		xmax = max(x, xmax);
		xmin = min(x, xmin);

		double y = (R - r)*sin(r/R * t) - r*sin(t - (r/R * t));
		ymax = max(y, ymax);
		ymin = min(y, ymin);

	}

	printf("x: [%.2f, %.2f]\n", xmin, xmax);
	printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

	glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
        for(double t = 0; t <= 2*pi; t += ratia)
        {
            double x = (R - r)*cos(r/R * t) - r* cos(t - (r/R * t));
            double y = (R - r)*sin(r/R * t) - r*sin(t - (r/R * t));

            glVertex2f(x, y);

        }
	glEnd();
}

void Display7()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
    double a = 0.4;
    double pi = 4 * atan(1);
    double ratia = 0.01;

    for(double t = -pi/4 + ratia; t < pi/4; t += ratia)
    {
        double r = a*sqrt(2*cos(2*t));

        double x = r*cos(t);
        double y = r*sin(t);

        xmax = max({xmax, x, -x});
        xmin = min({xmin, x, -x});
        ymax = max({ymax, y, -y});
        ymin = min({ymin, y, -y});
    }

    printf("x: [%.2f, %.2f]\n", xmin, xmax);
    printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

    glColor3f(1,0.1,0.1); // rosu
    glBegin(GL_LINE_STRIP);
        for(double t = pi/4 - ratia; t > -pi/4; t -= ratia) // partea stanga
        {
            double r = a*sqrt(2*cos(2*t));

            double x = r*cos(t);
            double y = r*sin(t);

            glVertex2f(-x,-y);
        }

        for(double t = -pi/4 + ratia/10; t < pi/4; t += ratia) // partea dreapta
        {
            double r = a*sqrt(2*cos(2*t));

            double x = r*cos(t);
            double y = r*sin(t);

            glVertex2f(x,y);
        }
    glEnd();
}

void Display8()
{
    double xmax = -inf, ymax = -inf;
    double xmin = inf, ymin = inf;
	double a = 0.02;
	double ratia = 0.01;

	for(double t = 0; t <= 2.9; t += ratia)
	{
		double r = a*exp(1 + t);
		double x = r*cos(t);
		xmax = max(x, xmax);
		xmin = min(x, xmin);

		double y = r*sin(t);
		ymax = max(y, ymax);
		ymin = min(y, ymin);
	}

	printf("x: [%.2f, %.2f]\n", xmin, xmax);
	printf("y: [%.2f, %.2f]\n\n", ymin, ymax);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(double t = 0; t <= 2.9; t += ratia)
		{
			double r = a*exp(1 + t);
			double x = r*cos(t) ;
			double y = r*sin(t);
			glVertex2f(x, y);

		}
	glEnd();
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case 'a':
      Exemplu1();
      break;
   case 's':
      Exemplu2();
      break;
    case '1':
      Display1();
      break;
    case '2':
      Display2();
      break;
    case '3':
      Display3();
      break;
    case '4':
      Display4();
      break;
    case '5':
      Display5();
      break;
    case '6':
      Display6();
      break;
    case '7':
      Display7();
      break;
    case '8':
      Display8();
      break;
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

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
