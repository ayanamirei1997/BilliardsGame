#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <ctime>
#include "ball.h"
#include "table.h"
#include "sound.h"

void selectMyFont(int size, int charset, const char* face);
void drawTextString(const char* str);