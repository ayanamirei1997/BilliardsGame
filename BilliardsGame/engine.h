#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <ctime>
#include "ball.h"
#include "table.h"
#include "sound.h"

void timer(int timerid);
void mouse(int button, int state, int x, int y);
void passive(int x, int y);
void special(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void display(void);