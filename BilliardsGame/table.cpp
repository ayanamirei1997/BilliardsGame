#pragma once
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "ball.h"
#include "table.h"
#define break 20

extern Table table;
extern double speed;
extern int ii;
SYSTEMTIME old;
int count=break;

// table���캯��
Table::Table()
{
	// ����������ɫ 16��С�����ɫ����ͬ 
	balls[0].setColour(0.9, 0.9, 0.9); // white
	balls[1].setColour(1.0, 0.9, 0.2); // yellow
	balls[2].setColour(0.1, 0.2, 0.7); // dark blue
	balls[3].setColour(1.0, 0.0, 0.0); // red
	balls[4].setColour(0.4, 0.0, 0.5); // dark purple
	balls[5].setColour(1.0, 0.5, 0.3); // light orange
	balls[6].setColour(0.2, 0.8, 0.4); // green
	balls[7].setColour(1.0, 0.5, 0.8); // light purple
	balls[8].setColour(0.0, 0.0, 0.0); // black
	balls[9].setColour(0.6, 0.5, 0.2); // dark yellow
	balls[10].setColour(0.2, 0.5, 1.0); // blue
	balls[11].setColour(1.0, 0.2, 0.3); // light red
	balls[12].setColour(0.7, 0.0, 0.7); // purple
	balls[13].setColour(0.8, 0.3, 0.0); // orange
	balls[14].setColour(0.0, 0.3, 0.2); // dark green
	balls[15].setColour(0.5, 0.0, 0.0); // dark red

	// ��ʼ��
	time = 0;
	stickAngle = 90;
	player = 0;
	curNumber = 16;
	isPlay = false;
	isChange = false;
	reset();
	balls[0].setScore(-1);
}

// �ı�ײ���ϵ�
void Table::setStickAngle(double angle)
{
	stickAngle = angle;
}

// �������
int Table::getPlayer()
{
	return player;
}

// ѡ�����
void Table::switchPlayer()
{
	player = !player;
	GetLocalTime(&old);
}

// ���ط���
int Table::getScores(int player)
{
	return scores[player];
}

// ���÷���
void Table::setScores(int player, int offset)
{
	scores[player] += offset;	
}

// ������Ϸ״̬
void Table::reset()
{
	isPlay = false;
	// ��ʼ����������
	balls[0].setPosition(2, 0);
	balls[0].setoPosition(2, 0);
	balls[0].setSpeed(0, 0);
	balls[0].setVisible(true);
	balls[0].setoVisible(true);

	// ��ʼ��������
	int k = 1;
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < i + 1; j++)
		{
			// ʹ��������
			double r = balls[k].getRadius();
			double x = (6 - i * 2) * r - 2;
			double z = (j * 2 - i - 1) * r;
			balls[k].setPosition(x, z);
			balls[k].setoPosition(x, z);
			balls[k].setSpeed(0, 0);
			balls[k].setVisible(true);
			balls[k].setoVisible(true);
			k++;
		}
	}
	scores[0] = 0;
	scores[1] = 0;
}

// ���ؿɼ���������
int Table::visibleNumber()
{
	int number = 0;
	for (int i = 0; i < 16; i++)
	{
		if (balls[i].getVisible()) number++;
	}
	return number;
}

// ��������̬��Ϣ
bool Table::moving()
{
	// ����ƶ�����
	for (int i = 0; i < 16; i++)
	{
		if (balls[i].moving()) return true;
	}

	// û�������ƶ�
	return false;
}


// ��������
void Table::update(int currentTime)
{
	double timeStep = 0.001; // ����ʱ����Ϣ
	int i, j;
	// �ڼ��ʱ���и�����Ϣ
	while (time < currentTime)
	{
		// Ϊÿ������ײ���
		for (i = 0; i < 16; i++)   //����������
		{
			// ������еĶ�
			balls[i].collideHoles();
			balls[i].collideCushions();
			//if (balls[i].getVisible() == false) {//����С�򲻿ɼ�
			//	flag = true;
			//}
			// collide ball with other balls
			for (j = 0; j < i; j++)
			{
				balls[i].collideBall(balls[j]);
			}
		}

		// ���������ٶȺ�λ��
		for (i = 0; i < 16; i++)
		{
			balls[i].updateSpeed(timeStep);
			balls[i].updatePosition(timeStep);
		}

		// ������������°ڷ�
		if (!moving() && !balls[0].getVisible())
		{
			balls[0].setPosition(0, 0);
			balls[0].setSpeed(0, 0);
			balls[0].setVisible(true);
			restore();
			table.switchPlayer();
		}

		// ��������������أ�������Ϸ
		if (visibleNumber() == 1) reset();

		time++;
	}
}

// ��������
void glDrawString(unsigned char *str)
{
	GLYPHMETRICSFLOAT pgmf[1];

	HDC hDC = wglGetCurrentDC();
	HFONT hFont;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 1;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = GB2312_CHARSET;
	lf.lfOutPrecision = OUT_TT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN;
	lstrcpy(lf.lfFaceName, "����");
	hFont = CreateFontIndirect(&lf);
	// ���õ�ǰ����
	SelectObject(wglGetCurrentDC(), hFont);

	DWORD dwChar;
	int ListNum;
	for (size_t i = 0; i<strlen((char *)str); i++)
	{
		if (IsDBCSLeadByte(str[i]))
		{
			dwChar = (DWORD)((str[i] << 8) | str[i + 1]);
			i++;
		}
		else
			dwChar = str[i];
		ListNum = glGenLists(1);
		wglUseFontOutlines(hDC, dwChar, 1, ListNum, 0.0, 0.1f, WGL_FONT_POLYGONS, pgmf);
		glCallList(ListNum);
		glDeleteLists(ListNum, 1);
	}
}

// ѡ������
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

// ��������
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
					   // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

// ���Ʒ���
void Table::paintScore() {
	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glRasterPos3f(-7.0f, 2.0f, 5.0f);// �߶�
	glTranslated(0, 0, 0);
	char str1[100] = "Score1:";
	char temp1[1000];
	sprintf_s(temp1, "%d", scores[1]);
	strcat_s(str1, temp1);
	//glTranslated(0,0, 0);
	drawString(str1);
	glPopMatrix();

	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glRasterPos3f(-7.0f, 2.0f, -4.0f);// �߶�
	glTranslated(-3, 0, 0);
	char str2[1000] = "Score2:";
	char temp[100];

	sprintf_s(temp, "%d", scores[0]);
	strcat_s(str2, temp);
	//glTranslated(0,0, 0);
	drawString(str2);
	glPopMatrix();
}

// �������
void drawPlayer() {

	if (table.getPlayer() == 1) {
		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRasterPos3f(-7.0f, 2.5f, -4.0f);// �߶�
		glTranslated(-3, 0, 0);
		//glTranslated(0,0, 0);
		drawString("Player 2");
		glPopMatrix();

		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f(-7.0f, 2.5f, 5.0f);// �߶�
		//glRasterPos3f(-5.0f, 1.0f, 0.5f);
		//glTranslated(0,0, 0);
		drawString("Player 1");
		glPopMatrix();
	}
	else if (table.getPlayer() == 0) {
		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f(-7.0f, 2.5f, -4.0f);// �߶�
		//glRasterPos3f(-5.0f, 0.5f, 0.5f);// �߶�
		glTranslated(-3, 0, 0);
		//glTranslated(0,0, 0);
		drawString("Player 2");
		glPopMatrix();

		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRasterPos3f(-7.0f, 2.5f, 5.0f);// �߶�
		//glTranslated(0,0, 0);
		drawString("Player 1");
		glPopMatrix();
	}

}

// �����ٶ�
void paintSpeed(double speed) {
	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.6f, 0.8f);
	glRasterPos3f(-7.0f, 1.5f, 0.5f);// �߶�
	glTranslated(-3, 0, 0);
	char str1[100] = "Speed:";
	char temp1[1000];
	if (speed > 18)speed = 18;
	if (speed <= 5) speed = 0;
	int percent = (int)(speed / 18 * 100);
	//printf("%d\n", percent);
	sprintf_s(temp1, "%d", percent);
	strcat_s(str1, temp1);
	//glTranslated(0,0, 0); 
	drawString(str1);

	glRasterPos3f(4.f, 0.1f, 1.05f);// �߶�
	glColor3f(2.0f, -0.6f, -0.8f);
	char s2[20] = "+2";
	glTranslated(0, 0, 0);
	drawString(s2);

	glRasterPos3f(4.f, 0.1f, -0.95f);// �߶�
	glColor3f(2.0f, 1.0f, 0.0f);
	char s3[20] = "+3";
	glTranslated(0, 0, 0);
	drawString(s3);

	glRasterPos3f(6.f, 0.1f, 0.05f);// �߶�
	glColor3f(2.0f, 0.0f, 0.0f);
	char s1[20] = "+4";
	glTranslated(0, 0, 0);
	drawString(s1);

	glPopMatrix();

}

// ��������
void Table::draw()
{
	// ���Ƶذ�
	glColor3d(0.5, 0.5, 0.4); // ��ɫ
	setShininess(0.0);        // û�з���
	glPushMatrix();
	glTranslated(0, -2, 0);
	drawCuboid(20, 0.1, 20);
	glPopMatrix();

	// ����ǽ��
	glColor3d(1.0, 1.0, 0.6); // ǳ��ɫ
	glPushMatrix();
	glTranslated(-10, 0, 0); drawCuboid(0.1, 20, 20);
	glTranslated(+20, 0, 0); drawCuboid(0.1, 20, 20);
	glColor3d(1.0, 1.0, 0.7); // ���ɫ
	glTranslated(-10, 0, -10); drawCuboid(20, 20, 0.1);
	glTranslated(0, 0, +20); drawCuboid(20, 20, 0.1);
	glPopMatrix();

	// ���ƼƷְ�
	glColor3d(0.4, 0.3, 0.3); // ��ɫ
	glPushMatrix();
	glTranslated(-8, 0, 0);
	drawCuboid(0.1, 12, 18);  // ��� �߶� ���
	glPopMatrix();

	glColor3d(0.8, 0.8, 0.8); // ��ɫ
	glPushMatrix();
	glTranslated(-7.9, 0.25, 0);
	drawCuboid(0.0, 12, 15);  // ��� �߶� ���
	glPopMatrix();

	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "����");
	glColor3f(0.0f, .0f, 0.0f);
	glRasterPos3f(-6, 2, 3.3);
	glTranslated(-6, 3.5, 6);//ԽСԽԶ�� Խ��Խ�ߣ�  Խ��Խ��
	glRotated(90, 0, 2, 0);
	unsigned char str[] = { "��     ��     ��     ��" };
	//unsigned char cstr[] = { "   ��������" };
	//glDrawString(cstr);
	glDrawString(str);
	glPopMatrix();

	//glPushMatrix();

	drawPlayer();
	paintScore();
	paintSpeed(speed);

	// ���Ƶ�
	for (int i = -1; i <= 1; i++)
	{
		glPushMatrix();

		// ����
		glColor3d(1.0, 0.3, 0.2); // ��ɫ
		setShininess(0.0);		  // û�з���
		glTranslated(i * 2.3, 2.8, 0);
		glRotated(-90, 1, 0, 0);
		drawCylinder(0.8, 0, 1.1);

		// ����
		glColor3d(2.0, 2.0, 2.0); // ��ɫ
		drawSphere(0.25);

		// �ƹ�
		setShininess(1.0);		  // ����
		glTranslated(0, 0, 0.8);
		glColor3d(1.0, 0.8, 0.4); // ��ɫ�ƹ�
		drawCylinder(0.2, 0.2, 0.2);
		glTranslated(0, 0, 0.2);
		glColor3d(0.9, 0.7, 0.4); // ��ɫ�ƹ�
		drawCylinder(0.2, 0.04, 0.1);
		glColor3d(0.8, 0.6, 0.4); // ��ɫ�ƹ�
		drawCylinder(0.04, 0.04, 10);

		glPopMatrix();
	}

	double hsize = 0.5; // �򶴴�С

	// ������������
	glColor3d(0.3, 0.5, 0.6); // ǳ��ɫ
	setShininess(0.0);		  // ������
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	drawCuboid(8.4, 0.2, 4.4);
	glPopMatrix();

	// ���������Ե
	glColor3d(0.1, 0.3, 0.5); // ����ɫ
	glPushMatrix();
	/*int index = 0;
	if(index != ii)*/
	glTranslated(-4, 0, +0); drawCuboid(0.1, 0.2, 4.0 - hsize);
	glTranslated(+8, 0, +0); drawCuboid(0.1, 0.2, 4.0 - hsize);
	glTranslated(-2, 0, -2); drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(-4, 0, +0); drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(+0, 0, +4); drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(+4, 0, +0); drawCuboid(4.0 - hsize, 0.2, 0.1);
	glPopMatrix();

	// ����������Ե
	glColor3d(0.3, 0.2, 0.2); // ��ɫ
	setShininess(1.0);        // ����
	glPushMatrix();
	glTranslated(-4.2, 0, +0.0); drawCuboid(0.3, 0.3, 4.7);
	glTranslated(+8.4, 0, +0.0); drawCuboid(0.3, 0.3, 4.7);
	glTranslated(-4.2, 0, -2.2); drawCuboid(8.2, 0.3, 0.3);
	glTranslated(+0.0, 0, +4.4); drawCuboid(8.2, 0.3, 0.3);
	glTranslated(+0.0, 0, -2.2); drawCuboid(0.5, 1.2, 2);
	//new
	glPopMatrix();

	// ������
	glColor3d(0.0, 0.0, 0.0); // ��ɫ
	setShininess(0.0);	      // ����
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	
	glTranslated(+4, 2, 0);  glutSolidCone(hsize * 0.4, 0.01, 20, 1);  
	glTranslated(-4, 0, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); } ;
	glTranslated(-4, 0, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };
	glTranslated(0, -4, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };
	glTranslated(+4, 0, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };
	glTranslated(+4, 0, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); }; 
	glTranslated(-1, +2, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };
	glTranslated(-2, +1, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };
	glTranslated(0, -2, 0);{ glutSolidCone(hsize * 0.4, 0.01, 20, 1); };

	//glTranslated(suiji3, suiji4, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	//glTranslated(3-1, -1, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glPopMatrix();

	// ��������
	glColor3d(0.2, 0.2, 0.2); // ��ɫ
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(+3.5, +1.5, 0.1); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, -3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(-7.0, +0.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, +3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glPopMatrix();

	// ��������
	for (int b = 0; b < 16; b++)
	{
		balls[b].draw();
	}

	// �������
	if (!moving())
	{
		glColor3d(0.7, 0.6, 0.5); // ľɫ
		glPushMatrix();
		glTranslated(balls[0].getX(), 0, balls[0].getZ());
		glRotated(stickAngle, 0, 1, 0);
		if (speed < 18)
		{
			glTranslated(0, 0.15, 0.4+speed*0.04);
		}
		else
		{
			glTranslated(0, 0.15, 0.4+18*0.04);
		}
		glRotated(-5, 1, 0, 0);
		drawCylinder(0.02, 0.06, 5.0);
		glPopMatrix();
	}

	if (!moving()) 
	{//������ֹ��

		if (curNumber == visibleNumber() && isPlay && isChange) {// ��������£���������䣻û����������������Щ�����Ҫ������Ȩ
			switchPlayer();	// ������Ȩ
			renew();		// ����ԭʼλ��
		}
		else 
		{
			if (balls[0].getVisible())
			{
				curNumber = visibleNumber(); // ���µ�ǰ��������	
				renew();
			}
			else
			{
				restore();
				switchPlayer();
			}			
		}			
		isChange = false;					// ��ֹ�ظ�����
	}
	else 
	{
		isChange = true;
	}
	if (!moving())
	{
		SYSTEMTIME now;
		GetLocalTime(&now);
		//printf("old=%d", old.wSecond);
		//printf("now=%d", now.wSecond);
		if (now.wSecond > old.wSecond)
		{
			count = break - (now.wSecond - old.wSecond);
		}
		else
		{
			count = break - (old.wSecond - now.wSecond);
		}
	}
	if (count <= 0)
	{
		switchPlayer();
	}
	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(0.5f, 0.5f, 0.5f);
	glRasterPos3f(-6.0f, 0.7f, 0.8f);// �߶�
	glTranslated(-3, 0, 0);
	char str2[1000] = "Rest Time:";
	char temp[100];
	sprintf_s(temp, "%ds", count);
	strcat_s(str2, temp);
	drawString(str2);
	glPopMatrix();
}

// �ָ�֮ǰλ��
void Table::restore()
{
	// restore all balls
	for (int i = 0; i <= 15; i++)
	{
		balls[i].resetPosition();
		balls[i].resetVisible();
	}
}

// ���¿�ʼ
void Table::renew()
{
	// �ָ����е�����
	for (int i = 0; i <= 15; i++)
	{
		balls[i].setoPosition(balls[i].getX(), balls[i].getZ());
		balls[i].setoVisible(balls[i].getVisible());
	}
}

// ����
void Table::shoot()
{
	isPlay = true;
	double a = stickAngle * pi / 180 + pi;
	if (speed > 18) speed = 18;

	// double speed = 18;
	// ���û����ٶ�
	balls[0].setSpeed(speed * sin(a), speed * cos(a));
}
