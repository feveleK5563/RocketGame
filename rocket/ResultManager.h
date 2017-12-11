#pragma once
#include "TaskFlag.h"

struct ResultManager
{
	//ゲームパッド
	DI::VGamePad* in[2];
	//モード
	int* mode;
	//プレイヤー数
	int* playerNum;
	//どっちが勝ったか
	bool winPlayer;
	//クリア時間
	int clearTime;

	ResultManager(DI::VGamePad* pad, int* md, int* pn):
		mode(md),
		playerNum(pn)
	{
		for (int i = 0; i < 2; ++i)
		{
			in[i] = pad + i;
		}
	}

	//----------------------------------------------------------------------------
	//初期化処理
	void Initialize(int cleart, bool winp)
	{
		winPlayer = winp;
		clearTime = cleart;
	}
};