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

// ��������������������
int main(int argc, char* argv[])
{
	// ���ű�������
	playbgm();
	// ��ʼ��OpenGL
	glutInit(&argc, argv);
	// �������ó�ʼ����Ϸ��Ϣ
	configInit();
	// ��Ϸѭ��
	glutMainLoop();// ��������¼�����ѭ�����ú���������main�����������һ����䡣
	return 0;
}