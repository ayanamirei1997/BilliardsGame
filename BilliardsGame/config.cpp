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

void configInit() {

	// initialise GLUT
	// glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	// 显示模式
	glutInitWindowSize(1280, 720);								// 窗口大小	
	glutCreateWindow("创意桌球游戏_王浩然");						// 窗口名字

	// register callbacks 注册一些列回调函数
	glutKeyboardFunc(keyboard);									// 键盘功能
	glutSpecialFunc(special);									// 响应键盘方向控制键
	glutMouseFunc(mouse);										// 鼠标功能
	glutPassiveMotionFunc(passive);								// 相应鼠标没有被按下去时，移到鼠标的情形
	glutDisplayFunc(display);									// 显示当前窗口
	glutTimerFunc(10, timer, 1);
	quadricObject = gluNewQuadric();
}