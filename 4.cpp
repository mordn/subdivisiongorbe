#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;

typedef struct point2d { GLfloat x, y; } POINT2D;
std::vector<POINT2D> pontok,pontok2,pontok3,pontok4,pontok5;
GLint dragged = -1, n, n2, n3, n4, n5, keyStates[256];
GLdouble alapbeta = 0.0, beta, beta2, beta3, beta4, gamma, gamma2, gamma3, gamma4, a[4], a2[4], a3[4], a4[4], x, y;	              
bool elso = true, masodik = true, harmadik = true, negyedik = true;
bool elsom = true, masodikm = true, harmadikm = true, negyedikm = true;

POINT2D initPoint2D(GLfloat x, GLfloat y) {
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

void keyOperations() {
	if (keyStates['q'])
		elsom = true;
	if (keyStates['w'])
		masodikm = true;
	if (keyStates['e'])
		harmadikm = true;
	if (keyStates['r'])
		negyedikm = true;
	if (keyStates['a'])
		elsom = false;
	if (keyStates['s'])
		masodikm = false;
	if (keyStates['d'])
		harmadikm = false;
	if (keyStates['f'])
		negyedikm = false;
	if (keyStates['+']){
		alapbeta += 0.01;
		elso = true;
		masodik = true;
		harmadik = true;
		negyedik = true;
		//std::cout << alapbeta << std::endl;
	}
	if (keyStates['-'] && alapbeta > -2.00){
			alapbeta -= 0.01;
			if (alapbeta < -2.0) // wut m8
				alapbeta = -2.0;
			elso = true;
			masodik = true;
			harmadik = true;
			negyedik = true;
			//std::cout << alapbeta << std::endl;	
	}
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void racsoz() {
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_LINES);
	for (int i = 0; i < 32; i++) {
		glVertex2d(i * 25, 0);     // Y-tengely menti csíkozás
		glVertex2d(i * 25, 600);
	}
	for (int i = 0; i < 24; i++) {	 // X-tengely menti csíkozás
		glVertex2d(0, i * 25);
		glVertex2d(800, i * 25);
	}
	glEnd();
}

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, winWidth, 0.0f, winHeight, 0.0f, 1.0f);
	glLineWidth(1.25);
	glPointSize(5.0);
}

void finomitas1() {
	beta = sqrt(2.0 + alapbeta);
	gamma = -1.0 / (3.0 * (1.0 - (beta * beta))*(1.0 + beta));
	a[0] = (1.0 / 60.0)*(-90.0 * gamma - 1.0);
	a[1] = (1.0 / 60.0)*(90.0 * gamma + 43.0);
	a[2] = (1.0 / 60.0)*(90.0 * gamma + 17.0);
	a[3] = (1.0 / 60.0)*(-90.0 * gamma + 1.0);
}
void finomitas2() {
	beta2 = sqrt(2.0 + beta);
	gamma2 = -1.0 / (3.0 * (1.0 - (beta2 * beta2))*(1.0 + beta2));
	a2[0] = (1.0 / 60.0)*(-90.0 * gamma2 - 1.0);
	a2[1] = (1.0 / 60.0)*(90.0 * gamma2 + 43.0);
	a2[2] = (1.0 / 60.0)*(90.0 * gamma2 + 17.0);
	a2[3] = (1.0 / 60.0)*(-90.0 * gamma2 + 1.0);
}
void finomitas3() {
	beta3 = sqrt(2.0 + beta2);
	gamma3 = -1.0 / (3.0 * (1.0 - (beta3 * beta3))*(1.0 + beta3));
	a3[0] = (1.0 / 60.0)*(-90.0 * gamma3 - 1.0);
	a3[1] = (1.0 / 60.0)*(90.0 * gamma3 + 43.0);
	a3[2] = (1.0 / 60.0)*(90.0 * gamma3 + 17.0);
	a3[3] = (1.0 / 60.0)*(-90.0 * gamma3 + 1.0);
}
void finomitas4() {
	beta4 = sqrt(2.0 + beta3);
	gamma4 = -1.0 / (3.0 * (1.0 - (beta4 * beta4))*(1.0 + beta4));
	a4[0] = (1.0 / 60.0)*(-90.0 * gamma4 - 1.0);
	a4[1] = (1.0 / 60.0)*(90.0 * gamma4 + 43.0);
	a4[2] = (1.0 / 60.0)*(90.0 * gamma4 + 17.0);
	a4[3] = (1.0 / 60.0)*(-90.0 * gamma4 + 1.0);
}

void elsoiteracio() {
	if (elso) {
		finomitas1();
		elso = false;
	}
	pontok2.clear();
	for (int i = 1; i < n + 1; i++) {
		pontok2.push_back(pontok[i%n]);
		x = a[0] * pontok[(i - 1) % n].x + a[1] * pontok[i%n].x + a[2] * pontok[(i + 1) % n].x + a[3] * pontok[(i + 2) % n].x;
		y = a[0] * pontok[(i - 1) % n].y + a[1] * pontok[i%n].y + a[2] * pontok[(i + 1) % n].y + a[3] * pontok[(i + 2) % n].y;
		pontok2.push_back(initPoint2D(x, y));
		x = a[3] * pontok[(i - 1) % n].x + a[2] * pontok[i%n].x + a[1] * pontok[(i + 1) % n].x + a[0] * pontok[(i + 2) % n].x;
		y = a[3] * pontok[(i - 1) % n].y + a[2] * pontok[i%n].y + a[1] * pontok[(i + 1) % n].y + a[0] * pontok[(i + 2) % n].y;
		pontok2.push_back(initPoint2D(x, y));
	}
}
void masodikiteracio() {
	elsoiteracio();
	if (masodik) {
		finomitas2();
		masodik = false;
	}
	pontok3.clear();
	for (int i = 1; i < n2 + 1; i++) {
		pontok3.push_back(pontok2[i%n2]);
		x = a2[0] * pontok2[(i - 1) % n2].x + a2[1] * pontok2[i%n2].x + a2[2] * pontok2[(i + 1) % n2].x + a2[3] * pontok2[(i + 2) % n2].x;
		y = a2[0] * pontok2[(i - 1) % n2].y + a2[1] * pontok2[i%n2].y + a2[2] * pontok2[(i + 1) % n2].y + a2[3] * pontok2[(i + 2) % n2].y;
		pontok3.push_back(initPoint2D(x, y));
		x = a2[3] * pontok2[(i - 1) % n2].x + a2[2] * pontok2[i%n2].x + a2[1] * pontok2[(i + 1) % n2].x + a2[0] * pontok2[(i + 2) % n2].x;
		y = a2[3] * pontok2[(i - 1) % n2].y + a2[2] * pontok2[i%n2].y + a2[1] * pontok2[(i + 1) % n2].y + a2[0] * pontok2[(i + 2) % n2].y;
		pontok3.push_back(initPoint2D(x, y));
	}
}

void harmadikiteracio() {
	masodikiteracio();
	if (harmadik) {
		finomitas3();
		harmadik = false;
	}
	pontok4.clear();
	for (int i = 1; i < n3 + 1; i++) {
		pontok4.push_back(pontok3[i%n3]);
		x = a3[0] * pontok3[(i - 1) % n3].x + a3[1] * pontok3[i%n3].x + a3[2] * pontok3[(i + 1) % n3].x + a3[3] * pontok3[(i + 2) % n3].x;
		y = a3[0] * pontok3[(i - 1) % n3].y + a3[1] * pontok3[i%n3].y + a3[2] * pontok3[(i + 1) % n3].y + a3[3] * pontok3[(i + 2) % n3].y;
		pontok4.push_back(initPoint2D(x, y));
		x = a3[3] * pontok3[(i - 1) % n3].x + a3[2] * pontok3[i%n3].x + a3[1] * pontok3[(i + 1) % n3].x + a3[0] * pontok3[(i + 2) % n3].x;
		y = a3[3] * pontok3[(i - 1) % n3].y + a3[2] * pontok3[i%n3].y + a3[1] * pontok3[(i + 1) % n3].y + a3[0] * pontok3[(i + 2) % n3].y;
		pontok4.push_back(initPoint2D(x, y));
	}
}

void negyedikiteracio() {
	harmadikiteracio();
	if (negyedik) {
		finomitas4();
		negyedik = false;
	}
	pontok5.clear();
	for (int i = 1; i < n4 + 1; i++) {
		pontok5.push_back(pontok4[i%n4]);
		x = a4[0] * pontok4[(i - 1) % n4].x + a4[1] * pontok4[i%n4].x + a4[2] * pontok4[(i + 1) % n4].x + a4[3] * pontok4[(i + 2) % n4].x;
		y = a4[0] * pontok4[(i - 1) % n4].y + a4[1] * pontok4[i%n4].y + a4[2] * pontok4[(i + 1) % n4].y + a4[3] * pontok4[(i + 2) % n4].y;
		pontok5.push_back(initPoint2D(x, y));
		x = a4[3] * pontok4[(i - 1) % n4].x + a4[2] * pontok4[i%n4].x + a4[1] * pontok4[(i + 1) % n4].x + a4[0] * pontok4[(i + 2) % n4].x;
		y = a4[3] * pontok4[(i - 1) % n4].y + a4[2] * pontok4[i%n4].y + a4[1] * pontok4[(i + 1) % n4].y + a4[0] * pontok4[(i + 2) % n4].y;
		pontok5.push_back(initPoint2D(x, y));
	}
}

void TopKek()
{
		keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	racsoz();
	glColor3f(1.0f, 0.0f, 0.0f);
	n = pontok.size();
	glBegin(GL_POINTS);
	for (int i = 0; i < pontok.size(); i++) {
		glVertex2f(pontok[i].x, pontok[i].y);
	}
	glEnd();
	if (n > 3) {
		//alappontok kirahzolasa
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		for (int i = 0; i < n; i++) {
			glVertex2f(pontok[i].x, pontok[i].y);
			glVertex2f(pontok[(i + 1) % n].x, pontok[(i + 1) % n].y);
		}
		glEnd();
		elsoiteracio();
		n2 = pontok2.size();
		//elso iteracio kirajzolasa
		if (elsom) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);
			for (int i = 0; i < n2; i++) {
				glVertex2f(pontok2[i].x, pontok2[i].y);
				glVertex2f(pontok2[(i + 1) % n2].x, pontok2[(i + 1) % n2].y);
			}
			glEnd();
		}
		masodikiteracio();
		n3 = pontok3.size();
		//masodik iteracio kirajzolasa
		if (masodikm) {
			glColor3f(0.0f, 0.5f, 0.0f);
			glBegin(GL_LINES);
			for (int i = 0; i < n3; i++) {
				glVertex2f(pontok3[i].x, pontok3[i].y);
				glVertex2f(pontok3[(i + 1) % n3].x, pontok3[(i + 1) % n3].y);
			}
			glEnd();
		}
		harmadikiteracio();
		n4 = pontok4.size();
		//harmadik iteracio kirajzolasa
		if (harmadikm) {
			glColor3f(0.33f, 0.15f, 0.53f);
			glBegin(GL_LINES);
			
			for (int i = 0; i < n4; i++) {
				glVertex2f(pontok4[i].x, pontok4[i].y);
				glVertex2f(pontok4[(i + 1) % n4].x, pontok4[(i + 1) % n4].y);
			}
			glEnd();
		}
		negyedikiteracio();
		n5 = pontok5.size();
		//negyedik iteracio kirajzolasa
		if (negyedikm) {
			glColor3f(0.75f, 0.1f, 0.1f);
			glBegin(GL_LINES);
			
			for (int i = 0; i < n5; i++) {
				glVertex2f(pontok5[i].x, pontok5[i].y);
				glVertex2f(pontok5[(i + 1) % n5].x, pontok5[(i + 1) % n5].y);
			}
			glEnd();
		}
	}
	
	glFlush();
	glutSwapBuffers();
}

GLfloat dist(POINT2D P1, POINT2D P2) {
	GLfloat t1 = P1.x - P2.x;
	GLfloat t2 = P1.y - P2.y;
	return t1 * t1 + t2 * t2;
}

GLint getActivePoint(GLint sens, GLint x, GLint y) { 
	GLint i, s = sens * sens;
	POINT2D P = initPoint2D(x, y);

	for (i = 0; i < pontok.size(); i++)
		if (dist(pontok[i], P) < s)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		if ((i = getActivePoint(8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
		else {
			pontok.push_back(initPoint2D(xMouse, winHeight - yMouse));
		}	
	}
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		pontok.clear();
	}
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		pontok[dragged].x = xMouse;
		pontok[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(800, 600);      // Set display-window width and height.
	glutCreateWindow("4. házi - Subdivision-görbe"); // Create display window.
	init();                            // Execute initialization procedure.
	glutDisplayFunc(TopKek);       // Send graphics to display window.
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();                    // Display everything and wait.
	return 0;
}