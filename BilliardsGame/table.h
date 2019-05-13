#pragma once

#include <Box2D/Common/b2Draw.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Common/b2Settings.h>
#include <Box2D/Common/b2Timer.h>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/b2TimeStep.h>
#include <Box2D/Dynamics/Contacts/b2CircleContact.h>
#include <Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h>

class Table
{
	Ball balls[16];    // 16����
	int time;          // ÿ������ģ�������ʱ��
	double stickAngle; // ��ǰײ���Ƕ�
	int player;        // ��ǰ���
	int curNumber;     // ��ǰ���
	bool isPlay;
	bool isChange;
	int scores[2];

public:
	Table();
	void setStickAngle(double angle);
	int getPlayer();
	void switchPlayer();
	int getScores(int player);
	void setScores(int player, int offset);
	void reset();
	int visibleNumber();
	bool moving();
	void shoot();
	void update(int currentTime);
	void paintScore();
	void draw();
	void restore();
	void renew();
};