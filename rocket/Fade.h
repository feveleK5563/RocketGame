#pragma once
#include "MyPG.h"
#include "Position.h"

//指定画像でフェードイン、フェードアウトする
//フェードイン… 画像を薄くする
//フェードアウト… 画像を濃くする
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
	//※注 直後にFadeSwitchを呼んでください
	void ImageSet(PositionI setpos, string imgnm, ML::Box2D img2d)
	{
		pos = setpos;
		imgName = imgnm;
		src = img2d;
		visible = -1.f;
	}

	//フェード設定
	//引数：フェードインかフェードアウト(bool, trueでイン falseでアウト), フェード完了までのフレーム数(int, デフォで60)
	//	　　フェード色制限(float, デフォルトで-1.f(自動で0.fか1.fになる))
	//※注 フェード色をリセットする場合、直前にImageSetを呼んでくだしあ
	void FadeSwitch(bool InOut, int time = 60, float limit = -1.f)
	{
		if (InOut)
		{
			fadestate = FadeIn;
			if (visible == -1.f)
				visible = 1.f;

			if (limit == -1.f)
				visibleLimit = 0.f;
			else
				visibleLimit = limit;
		}
		else
		{
			fadestate = FadeOut;
			if (visible == -1.f)
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
