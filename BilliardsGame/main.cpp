#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <ctime>
#include "ball.h"
#include "table.h"
#include "sound.h"
#include "engine.h"
#include "text.h"
#include "config.h"

// 主函数，整个程序的入口
int main(int argc, char* argv[])
{
	// 播放背景音乐
	playbgm();
	// 初始化OpenGL
	glutInit(&argc, argv);
	// 根绝配置初始化游戏信息
	configInit();
	// 游戏循环
	glutMainLoop();// 程序进入事件处理循环。该函数必须是main主函数的最后一条语句。
	return 0;
}