#pragma once

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "ball.h"
#include "table.h"

extern Table table;
extern int ii;
GLUquadricObj* quadricObject = NULL;

// 通过半径画球
void drawSphere(double radius)
{
	// 二次曲线目标
	int slices = 60;// 经度
	int stacks = 60;// 纬度
					
					// 这个值设的越大画出来的球就越光滑
	gluSphere(quadricObject, radius, slices, stacks);
}

// 通过长宽高画立方体
void drawCuboid(double width, double height, double depth)
{
	glPushMatrix();					// 堆栈 保存当前坐标系
	glScaled(width, height, depth); // 表示将当前图形沿x,y,z轴分别放大为原来的n倍
	glutSolidCube(1);				// 实心
	glPopMatrix();					// 恢复原来的坐标系
}

// 画圆柱体
void drawCylinder(double baseRadius, double topRadius, double height)
{
	int slices = 30;
	int stacks = 1;

	// 灯罩底部
	glPushMatrix();
	//glRotated(0, 0, 1, 0);
	gluDisk(quadricObject, 0, baseRadius, slices, stacks);
	glPopMatrix();

	//灯罩主体，杆子主体
	gluCylinder(quadricObject, baseRadius, topRadius, height, slices, stacks);
	glPushMatrix();
	
	glTranslated(0, 0, height);
	//顶部灯盖
	gluDisk(quadricObject, 0, topRadius, slices, stacks);
	glPopMatrix();
}

// 改变当前亮度
void setShininess(double s)
{
	// 设置镜面反射
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	// set specular colour
	float colour[4];
	colour[0] = 5 * (float)s;
	colour[1] = 5 * (float)s;
	colour[2] = 5 * (float)s;//球的镜面反射 很亮
	colour[3] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colour);
}

// ball构造函数
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

// 改变颜色
void Ball::setColour(double r0, double g0, double b0)
{
	r = r0;
	g = g0;
	b = b0;
}

// 改变位置
void Ball::setPosition(double x0, double z0)
{
	x = x0;
	z = z0;
}

// 返回位置
void Ball::setoPosition(double x0, double z0)
{
	ox = x0;
	oz = z0;
}

// 返回X坐标
double Ball::getX()
{
	return x;
}

// 返回Z坐标
double Ball::getZ()
{
	return z;
}

// 返回原始X坐标
double Ball::getoX()
{
	return ox;
}

// 返回原始Z坐标
double Ball::getoZ()
{
	return oz;
}

// 改变速度
void Ball::setSpeed(double sx0, double sz0)
{
	sx = sx0;
	sz = sz0;
}

// 改变是否可见状态
void Ball::setVisible(bool v)//是否可见
{
	visible = v;
}

// 返回是否可见状态
bool Ball::getVisible()
{
	return visible;
}

// 改变原始可见状态
void Ball::setoVisible(bool v)//是否可见
{
	ovisible = v;
}

// 判断是否可见
bool Ball::getoVisible()
{
	return ovisible;
}

// 返回分数
int Ball::getScore()
{
	return score;
}

// 设置分数
void Ball::setScore(int dscore)
{
	score = dscore;
}

// 返回半径
double Ball::getRadius()
{
	return radius;
}

// 返回动作状态
bool Ball::moving()
{
	if (!visible) return false;
	return sx != 0 || sz != 0;
}

// 计算距离
double Ball::distanceTo(double px, double pz)
{
	// 使用2D距离
	double dx = x - px;
	double dz = z - pz;
	return sqrt(dx * dx + dz * dz);
}

// 桌洞碰撞
void Ball::collideHoles()
{
	////srand(unsigned(time(0)));
	//int suiji1 = (rand() % (4 - 0)) + 0;
	//int suiji2 = (rand() % (2 - 0)) + 0;
	// 设置球洞坐标
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
	// 遍历所有球洞
	for (i = 0; i < 9; i++)
	{
		if (i != 6 && i != 7 && i != 8)
		{// 检查距离
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score);
				visible = false;// 进洞判断，设置成不可见
				break;
			}
		}
		if(i==7)
		{// 检查距离
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score==-1?score:4);
				visible = false;// 进洞判断，设置成不可见
				break;
			}
		}
		if (i == 6)
		{// 检查距离
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score == -1 ? score : 3);
				visible = false;// 进洞判断，设置成不可见
				break;
			}
		}
		if (i == 8)
		{// 检查距离
			if (distanceTo(holes[i][0], holes[i][1]) < 0.3 && visible) {
				table.setScores(table.getPlayer(), score == -1 ? score : 2);
				visible = false;//进洞判断，设置成不可见
				break;
			}
		}

	}

}

// 球桌边界碰撞
void Ball::collideCushions()
{
	// 忽略已隐藏的球洞
	if (!visible) return;
	// 边界碰撞反射，速度改变 只要改变方向即可
	// 改变速度分量
	if (x - radius < -3.9 && sx < 0) sx = -sx;//下边
	if (x + radius > +3.9 && sx > 0) sx = -sx;//上边
	if (z - radius < -1.9 && sz < 0) sz = -sz;//左边
	if (z + radius > +1.9 && sz > 0) sz = -sz;//右边
	if (x + radius < 0.4 && x - radius > -0.4 && z + radius < 1.1 && z - radius > -1.1) { sx = -sx; sz = -sz; } // test
}

// 桌球碰撞
void Ball::collideBall(Ball& other)		  // 这里涉及到台球的碰撞
{
	// 忽略已隐藏球体
	if (!visible) return;				  // 有一个不可见就return
	if (!other.visible) return;

	// 碰撞分析
	double distance = distanceTo(other.x, other.z);
	if (distance * 0.5 > radius) return;  // 距离大于0.2,超过球心距离之和，不碰撞

										  // 向量标准化
										  // if(distance < 0.001) return;
										  // 标准化距离x,z
	double ux = (other.x - x) / distance; //cosθ
	double uz = (other.z - z) / distance; //sinθ

	// 正常速度
	double n1 = sx * ux + sz * uz;		  // 分解速度到球心连线上
	double n2 = other.sx * ux + other.sz * uz;

	// 忽略移动球体
	if (n1 < n2) return;				  // 跑不过的就不追了 
										  // 交换向量方向
										  // 碰撞的过程
	sx += n2 * ux - n1 * ux;
	sz += n2 * uz - n1 * uz;
	other.sx += n1 * ux - n2 * ux;
	other.sz += n1 * uz - n2 * uz;
}

// 刷新桌球速度
void Ball::updateSpeed(double timeStep)
{
	// 忽略已隐藏桌球
	if (!visible) return;

	double s = sqrt(sx * sx + sz * sz); // 速度
	double k = 4;						// 摩擦阻力

	// 停止慢球
	if (s < k * timeStep)//停止球的运动
	{
		sx = 0;
		sz = 0;
		return;
	}

	// 应用摩擦力
	double f = 1 - k / s * timeStep;//v=v0-at=v0-ugt  k/s只是一个系数
	if (f < 0) f = 0;
	sx *= f;
	sz *= f;
}

// 刷新桌球位置
void Ball::updatePosition(double timeStep)// 逐步移动
{
	// 忽略已隐藏桌球
	if (!visible) return;

	// 根据速度改变位置
	x += sx * timeStep;
	z += sz * timeStep;
}

// 画球
void Ball::draw()//画球
{
	if (!visible) return;//看不到的不画

	// 画阴影
	glColor3d(0.1, 0.2, 0.3); // 灰色
	setShininess(0.0);        // 无反射
	glPushMatrix();
	glTranslated(x, 0, z);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(radius, 0.01, 20, 1);
	glPopMatrix();

	// 画球
	glColor3d(r, g, b);		 // 桌球颜色
	setShininess(1.0);		 // 反射
	glPushMatrix();
	glTranslated(x, radius, z);
	glRotated(180, 1, 0, 0);
	drawSphere(radius);
	glPopMatrix();
}

// 重置位置
void Ball::resetPosition()
{
	x = ox;
	z = oz;
}

// 重置可见状态
void Ball::resetVisible()
{
	if (visible== false && ovisible == true && score > 0)
	{
		table.setScores(table.getPlayer(), -score);
	}
	visible = ovisible;
}

