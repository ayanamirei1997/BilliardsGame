#pragma once

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "ball.h"
#include "table.h"

extern Table table;
extern int ii;
GLUquadricObj* quadricObject = NULL;

// ͨ���뾶����
void drawSphere(double radius)
{
	// ��������Ŀ��
	int slices = 60;// ����
	int stacks = 60;// γ��
					
					// ���ֵ���Խ�󻭳��������Խ�⻬
	gluSphere(quadricObject, radius, slices, stacks);
}

// ͨ������߻�������
void drawCuboid(double width, double height, double depth)
{
	glPushMatrix();					// ��ջ ���浱ǰ����ϵ
	glScaled(width, height, depth); // ��ʾ����ǰͼ����x,y,z��ֱ�Ŵ�Ϊԭ����n��
	glutSolidCube(1);				// ʵ��
	glPopMatrix();					// �ָ�ԭ��������ϵ
}

// ��Բ����
void drawCylinder(double baseRadius, double topRadius, double height)
{
	int slices = 30;
	int stacks = 1;

	// ���ֵײ�
	glPushMatrix();
	//glRotated(0, 0, 1, 0);
	gluDisk(quadricObject, 0, baseRadius, slices, stacks);
	glPopMatrix();

	//�������壬��������
	gluCylinder(quadricObject, baseRadius, topRadius, height, slices, stacks);
	glPushMatrix();
	
	glTranslated(0, 0, height);
	//�����Ƹ�
	gluDisk(quadricObject, 0, topRadius, slices, stacks);
	glPopMatrix();
}

// �ı䵱ǰ����
void setShininess(double s)
{
	// ���þ��淴��
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	// set specular colour
	float colour[4];
	colour[0] = 5 * (float)s;
	colour[1] = 5 * (float)s;
	colour[2] = 5 * (float)s;//��ľ��淴�� ����
	colour[3] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colour);
}

// ball���캯��
Ball::Ball()
{
	setColour(0, 0, 0);
	setPosition(0, 0);
	setoPosition(0, 0);
	setSpeed(0, 0);
	setVisible(true);
	setoVisible(true);
	setScore(1);
	radius = 0.1;
}

// �ı���ɫ
void Ball::setColour(double r0, double g0, double b0)
{
	r = r0;
	g = g0;
	b = b0;
}

// �ı�λ��
void Ball::setPosition(double x0, double z0)
{
	x = x0;
	z = z0;
}

// ����λ��
void Ball::setoPosition(double x0, double z0)
{
	ox = x0;
	oz = z0;
}

// ����X����
double Ball::getX()
{
	return x;
}

// ����Z����
double Ball::getZ()
{
	return z;
}

// ����ԭʼX����
double Ball::getoX()
{
	return ox;
}

// ����ԭʼZ����
double Ball::getoZ()
{
	return oz;
}

// �ı��ٶ�
void Ball::setSpeed(double sx0, double sz0)
{
	sx = sx0;
	sz = sz0;
}

// �ı��Ƿ�ɼ�״̬
void Ball::setVisible(bool v)//�Ƿ�ɼ�
{
	visible = v;
}

// �����Ƿ�ɼ�״̬
bool Ball::getVisible()
{
	return visible;
}

// �ı�ԭʼ�ɼ�״̬
void Ball::setoVisible(bool v)//�Ƿ�ɼ�
{
	ovisible = v;
}

// �ж��Ƿ�ɼ�
bool Ball::getoVisible()
{
	return ovisible;
}

// ���ط���
int Ball::getScore()
{
	return score;
}

// ���÷���
void Ball::setScore(int dscore)
{
	score = dscore;
}

// ���ذ뾶
double Ball::getRadius()
{
	return radius;
}

// ���ض���״̬
bool Ball::moving()
{
	if (!visible) return false;
	return sx != 0 || sz != 0;
}

// �������
double Ball::distanceTo(double px, double pz)
{
	// ʹ��2D����
	double dx = x - px;
	double dz = z - pz;
	return sqrt(dx * dx + dz * dz);
}

// ������ײ
void Ball::collideHoles()
{
	////srand(unsigned(time(0)));
	//int suiji1 = (rand() % (4 - 0)) + 0;
	//int suiji2 = (rand() % (2 - 0)) + 0;
	// ����������
	double holes[9][2] =
	{
		{ 4, 2 },
	    { 4, -2 },
	    { -4, 2 },
	    { -4, -2 },
	    { 0, 2 },
	    { 0, -2 },
		{ 1,-1},
	    {3,0},
		{1,1}
	};
	
	int i;
	//printf("%d",ii);
	// ����������
	for (i = 0; i < 9; i++)
	{
		if (i != 6 && i != 7 && i != 8)
		{// ������
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score);
				visible = false;// �����жϣ����óɲ��ɼ�
				break;
			}
		}
		if(i==7)
		{// ������
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score==-1?score:4);
				visible = false;// �����жϣ����óɲ��ɼ�
				break;
			}
		}
		if (i == 6)
		{// ������
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score == -1 ? score : 3);
				visible = false;// �����жϣ����óɲ��ɼ�
				break;
			}
		}
		if (i == 8)
		{// ������
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score == -1 ? score : 2);
				visible = false;//�����жϣ����óɲ��ɼ�
				break;
			}
		}

	}

}

// �����߽���ײ
void Ball::collideCushions()
{
	// ���������ص���
	if (!visible) return;
	// �߽���ײ���䣬�ٶȸı� ֻҪ�ı䷽�򼴿�
	// �ı��ٶȷ���
	if (x - radius < -3.9 && sx < 0) sx = -sx;//�±�
	if (x + radius > +3.9 && sx > 0) sx = -sx;//�ϱ�
	if (z - radius < -1.9 && sz < 0) sz = -sz;//���
	if (z + radius > +1.9 && sz > 0) sz = -sz;//�ұ�
	if (x + radius < 0.4 && x - radius > -0.4 && z + radius < 1.1 && z - radius > -1.1) { sx = -sx; sz = -sz; } // test
}

// ������ײ
void Ball::collideBall(Ball& other)		  // �����漰��̨�����ײ
{
	// ��������������
	if (!visible) return;				  // ��һ�����ɼ���return
	if (!other.visible) return;

	// ��ײ����
	double distance = distanceTo(other.x, other.z);
	if (distance * 0.5 > radius) return;  // �������0.2,�������ľ���֮�ͣ�����ײ

										  // ������׼��
										  // if(distance < 0.001) return;
										  // ��׼������x,z
	double ux = (other.x - x) / distance; //cos��
	double uz = (other.z - z) / distance; //sin��

	// �����ٶ�
	double n1 = sx * ux + sz * uz;		  // �ֽ��ٶȵ�����������
	double n2 = other.sx * ux + other.sz * uz;

	// �����ƶ�����
	if (n1 < n2) return;				  // �ܲ����ľͲ�׷�� 
										  // ������������
										  // ��ײ�Ĺ���
	sx += n2 * ux - n1 * ux;
	sz += n2 * uz - n1 * uz;
	other.sx += n1 * ux - n2 * ux;
	other.sz += n1 * uz - n2 * uz;
}

// ˢ�������ٶ�
void Ball::updateSpeed(double timeStep)
{
	// ��������������
	if (!visible) return;

	double s = sqrt(sx * sx + sz * sz); // �ٶ�
	double k = 4;						// Ħ������

	// ֹͣ����
	if (s < k * timeStep)//ֹͣ����˶�
	{
		sx = 0;
		sz = 0;
		return;
	}

	// Ӧ��Ħ����
	double f = 1 - k / s * timeStep;//v=v0-at=v0-ugt  k/sֻ��һ��ϵ��
	if (f < 0) f = 0;
	sx *= f;
	sz *= f;
}

// ˢ������λ��
void Ball::updatePosition(double timeStep)// ���ƶ�
{
	// ��������������
	if (!visible) return;

	// �����ٶȸı�λ��
	x += sx * timeStep;
	z += sz * timeStep;
}

// ����
void Ball::draw()//����
{
	if (!visible) return;//�������Ĳ���

	// ����Ӱ
	glColor3d(0.1, 0.2, 0.3); // ��ɫ
	setShininess(0.0);        // �޷���
	glPushMatrix();
	glTranslated(x, 0, z);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(radius, 0.01, 20, 1);
	glPopMatrix();

	// ����
	glColor3d(r, g, b);		 // ������ɫ
	setShininess(1.0);		 // ����
	glPushMatrix();
	glTranslated(x, radius, z);
	glRotated(180, 1, 0, 0);
	drawSphere(radius);
	glPopMatrix();
}

// ����λ��
void Ball::resetPosition()
{
	x = ox;
	z = oz;
}

// ���ÿɼ�״̬
void Ball::resetVisible()
{
	if (visible== false && ovisible == true && score > 0)
	{
		table.setScores(table.getPlayer(), -score);
	}
	visible = ovisible;
}

