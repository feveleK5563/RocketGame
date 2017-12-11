#pragma once
#include "MyPG.h"
#include "Wall.h"

struct ImageManager
{
	//空の画像を読み込むよ！
	void SkyImageCreate()
	{
		DG::Image_Create("Sky", "./data/image/Sky.png");
	}

	//空の画像を解放するよ！
	void SkyImageErase()
	{
		DG::Image_Erase("Sky");
	}

	//----------------------------------------------------------------------------
	//壁の画像を読み込むよ！
	void WallImageCreate(const int imgNum, MapData* mapData)
	{
		for (int i = 0; i < imgNum; ++i)
		{
			string num = to_string(i);
			if (num.length() < 2)
			{
				num = "0" + num;
			}
			DG::Image_Create("Wall" + num, "./data/image/wall/Wall" + num + ".png");
			mapData[i].chip = "Wall" + num;
		}

		DG::Image_Create("RedLight", "./data/image/Object/Light.png");
		DG::Image_Create("Umiyama", "./data/image/Object/Umiyama.png");
	}

	//壁の画像を解放するよ！
	void WallImageErase(const int imgNum)
	{
		for (int i = 0; i < imgNum; ++i)
		{
			string num = to_string(i);
			if (num.length() < 2)
			{
				num = "0" + num;
			}
			DG::Image_Erase("Wall" + num);
		}
	}

	//----------------------------------------------------------------------------
	//UI用画像を読み込むよ！
	void UIImageCreate()
	{
		DG::Image_Create("Gauge", "./data/image/UI/Gauge.png");				//ゲージ
		DG::Image_Create("Timer", "./data/image/UI/Timer.png");				//タイマー
		DG::Image_Create("MiniMoon", "./data/image/UI/MiniMoon.png");		//ミニマップ用の月
		DG::Image_Create("MiniPlayer", "./data/image/UI/MiniPlayer.png");	//ミニマップ用のプレイヤー
																			//スピード線
		for (int i = 0; i < 4; ++i)
		{
			DG::Image_Create("Speed" + to_string(i), "./data/image/UI/Speed" + to_string(i) + ".png");
		}
		DG::Image_Create("Danger", "./data/image/UI/Danger.png");	//危険
		DG::Image_Create("Empty", "./data/image/UI/Empty.png");		//エネルギー切れ
	}

	//UI用画像を解放するよ！
	void UIImageErase()
	{
		DG::Image_Erase("Gauge");
		DG::Image_Erase("Timer");
		DG::Image_Erase("MiniMoon");
		DG::Image_Erase("MiniPlayer");
		for (int i = 0; i < 4; ++i)
		{
			DG::Image_Erase("Speed" + to_string(i));
		}
		DG::Image_Erase("Danger");
		DG::Image_Erase("Empty");
	}

	//----------------------------------------------------------------------------
	//ロケット用画像を読み込むよ！
	void RocketImageCreate()
	{
		DG::Image_Create("Rocket", "./data/image/Rocket.png");			//プレイヤー
		DG::Image_Create("Jet", "./data/image/Jet.png");				//ジェット噴射
		DG::Image_Create("Explosion", "./data/image/Explosion.png");	//爆発
	}

	//ロケット用画像を解放するよ！
	void RocketImageErase()
	{
		DG::Image_Erase("Rocket");
		DG::Image_Erase("Jet");
		DG::Image_Erase("Explosion");
	}

	//----------------------------------------------------------------------------
	//タイトルとかの画像を読み込むよ！
	void TitleExeImageCreate()
	{
		DG::Image_Create("Title", "./data/image/Title.png");
		DG::Image_Create("Mode", "./data/image/Mode.png");
		DG::Image_Create("HowTo0", "./data/image/HowTo0.png");
		DG::Image_Create("HowTo1", "./data/image/HowTo1.png");
	}

	//タイトルとかの画像を解放するよ！
	void TitleExeImageErase()
	{
		DG::Image_Erase("Title");
		DG::Image_Erase("Mode");
		DG::Image_Erase("HowTo0");
		DG::Image_Erase("HowTo1");
	}

	//ゲーム開始前のカウントダウンと終了時用画像を読み込むよ！
	void CountDownImageCreate()
	{
		DG::Image_Create("Count", "./data/image/StartEnd.png");
	}

	//カウントダウンと終了時用画像を解放するよ！
	void CountDownImageErase()
	{
		DG::Image_Erase("Count");
	}
};