#pragma once
#include "MyPG.h"
#include "Position.h"

//指定画像でフェードイン、フェードアウトする
class Fade
{
private:
	enum FadeState
	{
		Off,
		FadeIn,
		FadeOut,
	};
	FadeState fadestate;

	float	visible;
	float	visibleLimit; //-1 = Non
	float	fadeTime;

	string	 imgName;
	PositionI	pos;
	ML::Box2D	src;

public:

	bool	endFade;
	
	Fade() :
		visible(0.f),
		fadeTime(0),
		fadestate(Off),
		endFade(false),
		imgName(""),
		pos(PositionI()),
		src(ML::Box2D()){}

	//画像のセット
	//引数：画像の表示位置(PositionI), 画像名(string), 画像を読み込む大きさ(ML::Box2D)
	void ImageSet(PositionI setpos, string imgnm, ML::Box2D img2d)
	{
		pos = setpos;
		imgName = imgnm;
		src = img2d;
	}

	//フェードフラグ
	//引数：フェードインかフェードアウト(bool, trueでイン falseでアウト), フェード完了までのフレーム数(int, デフォルトで60)
	//	　　フェード色制限(float, デフォルトで-1.f(無効))
	void FadeSwitch(bool InOut, int time = 60, float limit = -1.f)
	{
		if (InOut)
		{
			fadestate = FadeIn;
			visible = 1.f;
			if (limit == -1.f)
				visibleLimit = 0.f;
			else
				visibleLimit = limit;
		}
		else
		{
			fadestate = FadeOut;
			visible = 0.f;
			if (limit == -1.f)
				visibleLimit = 1.f;
			else
				visibleLimit = limit;
		}
		fadeTime = (float)time;
		endFade = false;
	}

	//更新
	bool Update()
	{
		switch (fadestate)
		{
		case Off:
			endFade = true;
			break;

		case FadeIn:
			visible -= 1.f / fadeTime;
			if (visible <= visibleLimit)
			{
				fadestate = Off;
				endFade = true;
			}
			break;

		case FadeOut:
			visible += 1.f / fadeTime;
			if (visible >= visibleLimit)
			{
				fadestate = Off;
				endFade = true;
			}
			break;
		}
		return endFade;
	}

	//描画
	void Render()
	{
		ML::Box2D draw = src.OffsetCopy(pos.x, pos.y);
		DG::Image_Draw(imgName, draw, src, ML::Color(visible, 1.f, 1.f, 1.f));
	}
};
