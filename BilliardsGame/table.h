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
	Ball balls[16];    // 16个球
	int time;          // 每次物理模拟的物理时间
	double stickAngle; // 当前撞击角度
	int player;        // 当前玩家
	int curNumber;     // 当前球号
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