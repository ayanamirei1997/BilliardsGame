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

// table构造函数
Table::Table()
{
	// 设置桌球颜色 16个小球的颜色都不同 
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

	// 初始化
	time = 0;
	stickAngle = 90;
	player = 0;
	curNumber = 16;
	isPlay = false;
	isChange = false;
	reset();
	balls[0].setScore(-1);
}

// 改变撞击较低
void Table::setStickAngle(double angle)
{
	stickAngle = angle;
}

// 返回玩家
int Table::getPlayer()
{
	return player;
}

// 选择玩家
void Table::switchPlayer()
{
	player = !player;
	GetLocalTime(&old);
}

// 返回分数
int Table::getScores(int player)
{
	return scores[player];
}

// 设置分数
void Table::setScores(int player, int offset)
{
	scores[player] += offset;	
}

// 重启游戏状态
void Table::reset()
{
	isPlay = false;
	// 初始化主球和球杆
	balls[0].setPosition(2, 0);
	balls[0].setoPosition(2, 0);
	balls[0].setSpeed(0, 0);
	balls[0].setVisible(true);
	balls[0].setoVisible(true);

	// 初始化其他球
	int k = 1;
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < i + 1; j++)
		{
			// 使用三角形
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

// 返回可见桌球数量
int Table::visibleNumber()
{
	int number = 0;
	for (int i = 0; i < 16; i++)
	{
		if (balls[i].getVisible()) number++;
	}
	return number;
}

// 返回桌球动态信息
bool Table::moving()
{
	// 检测移动桌球
	for (int i = 0; i < 16; i++)
	{
		if (balls[i].moving()) return true;
	}

	// 没有桌球移动
	return false;
}


// 更新桌球
void Table::update(int currentTime)
{
	double timeStep = 0.001; // 更新时间信息
	int i, j;
	// 在间隔时间中更新信息
	while (time < currentTime)
	{
		// 为每个球碰撞检测
		for (i = 0; i < 16; i++)   //遍历所有球
		{
			// 检测所有的洞
			balls[i].collideHoles();
			balls[i].collideCushions();
			//if (balls[i].getVisible() == false) {//遇到小球不可见
			//	flag = true;
			//}
			// collide ball with other balls
			for (j = 0; j < i; j++)
			{
				balls[i].collideBall(balls[j]);
			}
		}

		// 更新桌球速度和位置
		for (i = 0; i < 16; i++)
		{
			balls[i].updateSpeed(timeStep);
			balls[i].updatePosition(timeStep);
		}

		// 主球进洞，重新摆放
		if (!moving() && !balls[0].getVisible())
		{
			balls[0].setPosition(0, 0);
			balls[0].setSpeed(0, 0);
			balls[0].setVisible(true);
			restore();
			table.switchPlayer();
		}

		// 如果所有桌球都隐藏，重启游戏
		if (visibleNumber() == 1) reset();

		time++;
	}
}

// 绘制字体
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
	lstrcpy(lf.lfFaceName, "黑体");
	hFont = CreateFontIndirect(&lf);
	// 设置当前字体
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

// 选择字体
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

// 绘制字体
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
					   // 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

// 绘制分数
void Table::paintScore() {
	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glRasterPos3f(-7.0f, 2.0f, 5.0f);// 高度
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
	glRasterPos3f(-7.0f, 2.0f, -4.0f);// 高度
	glTranslated(-3, 0, 0);
	char str2[1000] = "Score2:";
	char temp[100];

	sprintf_s(temp, "%d", scores[0]);
	strcat_s(str2, temp);
	//glTranslated(0,0, 0);
	drawString(str2);
	glPopMatrix();
}

// 绘制玩家
void drawPlayer() {

	if (table.getPlayer() == 1) {
		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRasterPos3f(-7.0f, 2.5f, -4.0f);// 高度
		glTranslated(-3, 0, 0);
		//glTranslated(0,0, 0);
		drawString("Player 2");
		glPopMatrix();

		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f(-7.0f, 2.5f, 5.0f);// 高度
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
		glRasterPos3f(-7.0f, 2.5f, -4.0f);// 高度
		//glRasterPos3f(-5.0f, 0.5f, 0.5f);// 高度
		glTranslated(-3, 0, 0);
		//glTranslated(0,0, 0);
		drawString("Player 2");
		glPopMatrix();

		glPushMatrix();
		selectFont(24, ANSI_CHARSET, "Comic Sans MS");
		//glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRasterPos3f(-7.0f, 2.5f, 5.0f);// 高度
		//glTranslated(0,0, 0);
		drawString("Player 1");
		glPopMatrix();
	}

}

// 绘制速度
void paintSpeed(double speed) {
	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.6f, 0.8f);
	glRasterPos3f(-7.0f, 1.5f, 0.5f);// 高度
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

	glRasterPos3f(4.f, 0.1f, 1.05f);// 高度
	glColor3f(2.0f, -0.6f, -0.8f);
	char s2[20] = "+2";
	glTranslated(0, 0, 0);
	drawString(s2);

	glRasterPos3f(4.f, 0.1f, -0.95f);// 高度
	glColor3f(2.0f, 1.0f, 0.0f);
	char s3[20] = "+3";
	glTranslated(0, 0, 0);
	drawString(s3);

	glRasterPos3f(6.f, 0.1f, 0.05f);// 高度
	glColor3f(2.0f, 0.0f, 0.0f);
	char s1[20] = "+4";
	glTranslated(0, 0, 0);
	drawString(s1);

	glPopMatrix();

}

// 绘制球桌
void Table::draw()
{
	// 绘制地板
	glColor3d(0.5, 0.5, 0.4); // 灰色
	setShininess(0.0);        // 没有反射
	glPushMatrix();
	glTranslated(0, -2, 0);
	drawCuboid(20, 0.1, 20);
	glPopMatrix();

	// 绘制墙壁
	glColor3d(1.0, 1.0, 0.6); // 浅黄色
	glPushMatrix();
	glTranslated(-10, 0, 0); drawCuboid(0.1, 20, 20);
	glTranslated(+20, 0, 0); drawCuboid(0.1, 20, 20);
	glColor3d(1.0, 1.0, 0.7); // 深黄色
	glTranslated(-10, 0, -10); drawCuboid(20, 20, 0.1);
	glTranslated(0, 0, +20); drawCuboid(20, 20, 0.1);
	glPopMatrix();

	// 绘制计分板
	glColor3d(0.4, 0.3, 0.3); // 棕色
	glPushMatrix();
	glTranslated(-8, 0, 0);
	drawCuboid(0.1, 12, 18);  // 厚度 高度 宽度
	glPopMatrix();

	glColor3d(0.8, 0.8, 0.8); // 白色
	glPushMatrix();
	glTranslated(-7.9, 0.25, 0);
	drawCuboid(0.0, 12, 15);  // 厚度 高度 宽度
	glPopMatrix();

	glPushMatrix();
	selectFont(24, ANSI_CHARSET, "黑体");
	glColor3f(0.0f, .0f, 0.0f);
	glRasterPos3f(-6, 2, 3.3);
	glTranslated(-6, 3.5, 6);//越小越远， 越大越高，  越大越左
	glRotated(90, 0, 2, 0);
	unsigned char str[] = { "创     意     桌     球" };
	//unsigned char cstr[] = { "   创意桌球" };
	//glDrawString(cstr);
	glDrawString(str);
	glPopMatrix();

	//glPushMatrix();

	drawPlayer();
	paintScore();
	paintSpeed(speed);

	// 绘制灯
	for (int i = -1; i <= 1; i++)
	{
		glPushMatrix();

		// 灯罩
		glColor3d(1.0, 0.3, 0.2); // 红色
		setShininess(0.0);		  // 没有反射
		glTranslated(i * 2.3, 2.8, 0);
		glRotated(-90, 1, 0, 0);
		drawCylinder(0.8, 0, 1.1);

		// 灯泡
		glColor3d(2.0, 2.0, 2.0); // 白色
		drawSphere(0.25);

		// 灯光
		setShininess(1.0);		  // 反射
		glTranslated(0, 0, 0.8);
		glColor3d(1.0, 0.8, 0.4); // 黄色灯光
		drawCylinder(0.2, 0.2, 0.2);
		glTranslated(0, 0, 0.2);
		glColor3d(0.9, 0.7, 0.4); // 黄色灯光
		drawCylinder(0.2, 0.04, 0.1);
		glColor3d(0.8, 0.6, 0.4); // 黄色灯光
		drawCylinder(0.04, 0.04, 10);

		glPopMatrix();
	}

	double hsize = 0.5; // 球洞大小

	// 绘制球桌表面
	glColor3d(0.3, 0.5, 0.6); // 浅蓝色
	setShininess(0.0);		  // 不反射
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	drawCuboid(8.4, 0.2, 4.4);
	glPopMatrix();

	// 绘制桌面边缘
	glColor3d(0.1, 0.3, 0.5); // 深蓝色
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

	// 绘制球桌边缘
	glColor3d(0.3, 0.2, 0.2); // 棕色
	setShininess(1.0);        // 反射
	glPushMatrix();
	glTranslated(-4.2, 0, +0.0); drawCuboid(0.3, 0.3, 4.7);
	glTranslated(+8.4, 0, +0.0); drawCuboid(0.3, 0.3, 4.7);
	glTranslated(-4.2, 0, -2.2); drawCuboid(8.2, 0.3, 0.3);
	glTranslated(+0.0, 0, +4.4); drawCuboid(8.2, 0.3, 0.3);
	glTranslated(+0.0, 0, -2.2); drawCuboid(0.5, 1.2, 2);
	//new
	glPopMatrix();

	// 绘制球洞
	glColor3d(0.0, 0.0, 0.0); // 黑色
	setShininess(0.0);	      // 反射
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

	// 绘制桌腿
	glColor3d(0.2, 0.2, 0.2); // 黑色
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(+3.5, +1.5, 0.1); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, -3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(-7.0, +0.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, +3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glPopMatrix();

	// 绘制桌球
	for (int b = 0; b < 16; b++)
	{
		balls[b].draw();
	}

	// 绘制球杆
	if (!moving())
	{
		glColor3d(0.7, 0.6, 0.5); // 木色
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
	{//所有球静止了

		if (curNumber == visibleNumber() && isPlay && isChange) {// 犯规情况下，球个数不变；没打进，球个数不变这些情况都要交换球权
			switchPlayer();	// 交换球权
			renew();		// 更新原始位置
		}
		else 
		{
			if (balls[0].getVisible())
			{
				curNumber = visibleNumber(); // 更新当前数量的球	
				renew();
			}
			else
			{
				restore();
				switchPlayer();
			}			
		}			
		isChange = false;					// 防止重复更新
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
	glRasterPos3f(-6.0f, 0.7f, 0.8f);// 高度
	glTranslated(-3, 0, 0);
	char str2[1000] = "Rest Time:";
	char temp[100];
	sprintf_s(temp, "%ds", count);
	strcat_s(str2, temp);
	drawString(str2);
	glPopMatrix();
}

// 恢复之前位置
void Table::restore()
{
	// restore all balls
	for (int i = 0; i <= 15; i++)
	{
		balls[i].resetPosition();
		balls[i].resetVisible();
	}
}

// 重新开始
void Table::renew()
{
	// 恢复所有的桌球
	for (int i = 0; i <= 15; i++)
	{
		balls[i].setoPosition(balls[i].getX(), balls[i].getZ());
		balls[i].setoVisible(balls[i].getVisible());
	}
}

// 击球
void Table::shoot()
{
	isPlay = true;
	double a = stickAngle * pi / 180 + pi;
	if (speed > 18) speed = 18;

	// double speed = 18;
	// 设置击球速度
	balls[0].setSpeed(speed * sin(a), speed * cos(a));
}
