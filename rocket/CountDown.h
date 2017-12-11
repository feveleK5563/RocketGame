#pragma once
#include "MyPG.h"
#include "SlideMove.h"

class CountDown
{
private:
	SlideMove slide;
	Position pos;
	int transition;
	ML::Box2D imgdraw[5];
	ML::Box2D imgsrc[5];

public:
	//コンストラクタ
	CountDown() :
		slide(&pos, Position(-250, 200), Position(970, 200))
	{
		transition = 0;
		int i = 0;
		for (; i < 3; ++i)
		{
			imgdraw[i] = ML::Box2D(-85, -85, 170, 170);
			imgsrc[i] = ML::Box2D(i * 170, 0, 170, 170);
		}
		for (; i < 5; ++i)
		{
			imgdraw[i] = ML::Box2D(-300, -85, 600, 170);
			imgsrc[i] = ML::Box2D(0, 170 * (i - 2), 600, 170);
		}
	}

	//初期化
	void Initialize()
	{
		transition = 0;
		slide.ChangePosition(Position(-250, 200), Position(970, 200));
		slide.Initialize(5.f);
	}

	//ゲームスタートカウント
	bool GameStart(bool startTime)
	{
		if (transition > 3)
		{
			return true;
		}

		if (!startTime && transition != 3)
			return false;

		if (slide.ShuPitaShu())
		{
			++transition;

			if (transition < 3)
				slide.Initialize(5.f);
			else if (transition == 3)
				slide.Initialize(3.5f);
			else
			{
				slide.ChangePosition(Position(360.f, -85.f), Position(360.f, 203.f));
				slide.Initialize(7.f);
			}
		}
		if (transition == 3)
			return true;
		else
			return false;
	}

	//ゲーム終了
	bool GameEnd()
	{
		return slide.ShuMoveStop();
	}

	//描画
	void Render()
	{
		ML::Box2D draw = imgdraw[transition].OffsetCopy(pos.x, pos.y);
		DG::Image_Draw("Count", draw, imgsrc[transition]);
	}
};