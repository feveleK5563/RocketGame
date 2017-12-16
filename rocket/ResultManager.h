#pragma once
#include "TaskFlag.h"

class ResultManager
{
private:
	//時間(タイミング)計測
	int time;
	//現在のフラグと次のフラグ
	int nowFlag;
	int nextFlag;

public:

	//初期化
	void Initialize()
	{
		time = 0;
		nowFlag = 0;
		nextFlag = 0;
	}

	//アニメーション変更時の処理
	void ChangeAnim(Fade& fade)
	{
		switch (nextFlag)
		{
		case 1:
			fade.ImageSet(PositionI(0, 0), "FadeImg", ML::Box2D(0, 0, 720, 405));
			fade.FadeSwitch(false, 50, 0.6f);
			break;

		default:
			break;
		}
		nowFlag = nextFlag;
	}

	//アニメーション処理
	void Animation(Fade& fade)
	{
		//現在のフラグと次のフラグが異なる場合
		if (nowFlag != nextFlag)
			ChangeAnim(fade);

		//基本的な処理はここに書け
		bool endFlag = false;
		switch (nowFlag)
		{
		case 0:
			++time;
			endFlag = time > 90;
			break;

		case 1:
			endFlag = fade.endFade;
			break;

		case 2:
			++time;
			endFlag = time > 70;
			break;

		case 3:
			endFlag = true;
			break;

		default:
			break;
		}

		//フラグ遷移
		if (endFlag)
		{
			time = 0;
			++nextFlag;
		}
	}
};