#pragma once
#include "MyPG.h"
#include "Position.h"

class SlideMove
{
private:
	float		moveTiming;
	float		speed;
	float		time;
	Position startpos;
	Position endpos;
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

	//������
	void Initialize(float spd)
	{
		moveTiming = 0.f;
		speed = spd;
		time = 0.f;
		*pos = startpos;
	}

	//�w����W�ύX
	void ChangePosition(Position start, Position end)
	{
		startpos = start;
		endpos = end;
	}

	//���� (�V���b�ƈړ����Ă������ɂȂ��Ď~�܂�����܂�������Ƃ��X�s�[�h�������ăV���b�Ƃ������̓����ł���)
	//�߂�l�F���삪�����������ۂ�
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

	//���� (�Ȃ񂩎w����W�Ɍ������ăV�����Ĉړ����Ē�~���邠�̓����ł���)
	//�߂�l�F���삪�����������ǂ���
	bool ShuMoveStop()
	{
		if (time <= speed * 10)
		{
			++time;
			pos->x += (endpos.x - pos->x) / speed;
			pos->y += (endpos.y - pos->y) / speed;
			return false;
		}
		return true;
	}
};