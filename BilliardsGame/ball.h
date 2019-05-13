#pragma once

#define MAX_CHAR 128
#define pi 3.14159265358979

#include <Box2D/Collision/b2BroadPhase.h>
#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Collision/b2Distance.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <ctime>
#include <stdlib.h>

//GLU��������
extern GLUquadricObj* quadricObject;
static int ii=rand()%8;

void drawSphere(double radius);
void drawCuboid(double width, double height, double depth);
void drawCylinder(double baseRadius, double topRadius, double height);
void setShininess(double s);

class Ball
{
	double r, g, b;				   // ��ɫ
	double x, z;				   // λ��
	double ox, oz;				   // ֮ǰλ��
	b2Vec2 speed = b2Vec2(0, 0);;  // �ٶ�
	bool visible;				   // ״̬
	bool ovisible;				   // ֮ǰ״̬
	int score;					   // ÿ�����
	double radius;				   // �뾶

public:
	Ball();
	void setColour(double r0, double g0, double b0);
	void setPosition(double x0, double z0);
	void setoPosition(double x0, double z0);
	double getX();
	double getZ();
	double getoX();
	double getoZ();
	double sx, sz;
	void setSpeed(double sx0, double sz0);
	void setVisible(bool v);
	bool getVisible();	
	void setoVisible(bool v);
	bool getoVisible();
	int getScore();
	void setScore(int dscore);
	double getRadius();
	bool moving();
	double distanceTo(double px, double pz);
	void collideHoles();
	void collideCushions();
	void collideBall(Ball& other);
	void updateSpeed(double timeStep);
	void updatePosition(double timeStep);
	void draw();
	void resetPosition();
	void resetVisible();
	int getrand()
	{
		return ii;
	}

};