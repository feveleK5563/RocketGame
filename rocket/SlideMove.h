#pragma once
#include "MyPG.h"
#include "Position.h"

class SlideMove
{
private:
	float		moveTiming;
	float		speed;
	float		time;
	Position	startpos;
	Position	endpos;
	Position*	pos;

public:
	SlideMove(Position* setPos, Position start, Position end) :
		moveTiming(0.f),
		speed(0.f),
		time(0.f),
		pos(setPos),
		startpos(start),
		endpos(end)
	{
		if (speed < 1.f)
			speed = 1.f;
	}

	//初期化
	void Initialize(float spd)
	{
		moveTiming = 0.f;
		speed = spd;
		time = 0.f;
		*pos = startpos;
	}

	//指定座標変更
	void ChangePosition(Position start, Position end)
	{
		startpos = start;
		endpos = end;
	}

	//動作 (シュッと移動してゆっくりになって止まったらまたちょっとずつスピードをあげてシュッといくあの動きですよ)
	//戻り値：動作が完了したか否か
	bool ShuPitaShu()
	{
		if (time <= 360.f)
		{
			time += 1.f * speed;
			moveTiming = cos(ML::ToRadian(time)) + 1.f;
			pos->x += (endpos.x - startpos.x) / (360.f / speed) * moveTiming;
			pos->y += (endpos.y - startpos.y) / (360.f / speed) * moveTiming;

			return false;
		}
		return true;
	}

	//動作 (なんか指定座標に向かってシュって移動して停止するあの動きですよ)
	//戻り値：動作が完了したか否か
	bool ShuMoveStop()
	{
		if (time <= 180.f)
		{
			time += 1.f * speed;
			moveTiming = cos(ML::ToRadian(time)) + 1.f;
			pos->x += (endpos.x - startpos.x) / (180.f / speed) * moveTiming;
			pos->y += (endpos.y - startpos.y) / (180.f / speed) * moveTiming;
			return false;
		}
		return true;
	}
};