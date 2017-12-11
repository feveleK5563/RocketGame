#pragma once
#include "TaskFlag.h"
#include "CountDown.h"

//-----------------------------------------------------------------------------
//プレイヤー
struct Player
{
	Rocket	rocket;
	MoveCameraData*	camData;
	UI		ui;
};

//-----------------------------------------------------------------------------
//ゲーム本編管理
struct GameManager
{
	//ゲームパッド
	DI::VGamePad* in[2];
	//モード
	int*		mode;
	//プレイヤー数
	int*		playerNum;
	//各プレイヤーの持つデータ
	Player		player[2];
	//画面に一つだけ表示するUI
	StageUI		sUI;
	//カメラ動作の終了を伝える
	bool* endMove;

	//画像読み込みするやつ
	ImageManager img;
	//ゲーム開始までのカウントダウンとゲーム終了の動作
	CountDown count;
	//勝ってるプレイヤー
	bool winPlayer;
	//ゲーム本編とリザルト画面の遷移(trueでゲーム本編、falseでリザルト画面)
	bool gameORresult;

	GameManager(DI::VGamePad* pad, int* md, int* pn, MoveCameraData* camD, MapManager* mapM, bool* em) :
		playerNum(pn),
		mode(md),
		winPlayer(0),
		endMove(em)
	{
		for (int i = 0; i < 2; ++i)
		{
			player[i].camData = &camD[i];
			in[i] = pad + i;
		}
	}

	//------------------------------------------------------------------------------------------------
	//初期化処理
	void Initialize(int MapLength)
	{
		img.RocketImageCreate();
		img.UIImageCreate();
		img.CountDownImageCreate();

		count.Initialize();
		gameORresult = true;

		for (int i = 0; i < *playerNum; ++i)
		{
			//UI(プレイヤー用)
			Position rktPos;
			PositionI egauge, tgauge, mPlayer;
			if (*playerNum == 1)
			{
				//ロケットの初期化
				rktPos = Position(230.f, 0.f);

				egauge = PositionI(115, 10);
				tgauge = PositionI(149, 10);
				mPlayer = PositionI(632, 10);
			}
			else
			{
				rktPos = Position(160.f + (i * 140.f), 0.f);

				egauge = PositionI(-10 + i * 707, 55);
				tgauge = PositionI(20 + (i * 655), 146);
				mPlayer = PositionI(355 + (i * 10), 10);
			}
			player[i].rocket.InitializeRocket(rktPos, i);
			ML::Color mColor;
			switch (i)
			{
			case 0:
				mColor = ML::Color(1.f, 1.f, 0.f, 0.f);
				break;

			case 1:
				mColor = ML::Color(1.f, 0.f, 0.f, 1.f);
				break;
			}
			player[i].ui.Initialize(egauge, tgauge, mPlayer, mColor);
			player[i].camData->swingCamera = true;
		}
		player[0].rocket.state = Nomal;
		player[1].rocket.state = Nomal;

		//UI(ゲーム全体用)//565
		PositionI timer;
		if (*playerNum == 1)
			timer = PositionI(565, 10);
		else
			timer = PositionI(293, 10);
		sUI.Initialize(timer);

		winPlayer = 0;
	}

	//------------------------------------------------------------------------------------------------
	//終了処理
	void Finalize()
	{
		img.RocketImageErase();
		img.UIImageErase();
		img.CountDownImageErase();
		for (int i = 0; i < 2; ++i)
		{
			player[i].rocket.state = Non;
			player[i].rocket.EndRocket();
		}
	}

	//------------------------------------------------------------------------------------------------
	//ゲーム本編の更新処理
	void GameUpdate(TaskFlag& tf, MapManager& mapManager, int MapLength, MapOrder* mapOrder, Fade& fade)
	{
		//ロケットが操作を受け付けるか否か
		bool canMove = false;
		//ゲーム開始時の時間計り
		canMove = count.GameStart(*endMove);

		//ゲーム終了時のFINISHの表示
		if (player[0].rocket.state == Non || player[1].rocket.state == Non)
			if (canMove = count.GameEnd())
			{
				gameORresult = false;
				for (int i = 0; i < 2; ++i)
				{
					player[i].camData->swingCamera = false;
					player[i].rocket.state = Non;
				}
				fade.ImageSet(PositionI(0, 0), "FadeImg", ML::Box2D(0, 0, 720, 405));
				fade.FadeSwitch(false, 180, 0.7f);
			}

		for (int i = 0; i < *playerNum; ++i)
		{
			//ロケットの入力受け付け
			player[i].rocket.JetRocket(*in[i], canMove);
			//壁衝突判定
			mapManager.WallHit(MapLength, mapOrder, player[i].rocket, fade);
		}

		//プレイヤーが二人以上 && ロケット同士が一定距離以下まで近付いている && 両ロケットの状態がNonじゃない ときに
		//ロケット同士の当たり判定処理を行う
		bool toRocketHit =
			!(*playerNum < 2 ||
				fabsf(player[0].rocket.pos.y - player[1].rocket.pos.y) > 76.f) &&
			player[0].rocket.state != Non && player[1].rocket.state != Non;

		//ロケット同士の当たり判定(toRocketHitがtrueのときのみ)
		if (toRocketHit)
			ToRocketHit(player[0].rocket, player[1].rocket);

		for (int i = 0; i < *playerNum; ++i)
		{
			//ロケットの更新(動作更新と移動量反転とアニメーション)
			player[i].rocket.UpdateRocket(player[i].camData->camera, *in[i], toRocketHit, canMove);
			player[i].rocket.LoopPositionX(-9.f, 469.f);

			//カメラの追尾
			player[i].camData->SetGameCamera(Position(player[i].rocket.pos.x - 180.f, player[i].rocket.pos.y - 290.f), 7.f);

			//UIの更新
			player[i].ui.Update(player[i].rocket, MapLength);
		}
		sUI.Update(canMove);

		if (in[0]->ST.down || in[1]->ST.down)
			tf = Task_Title;

		winPlayer = !(player[0].rocket.pos.y < player[1].rocket.pos.y);

	}

	//------------------------------------------------------------------------------------------------
	//リザルト画面の更新処理
	void ResultUpdate()
	{
		
	}

	//------------------------------------------------------------------------------------------------
	//更新処理
	TaskFlag Update(MapManager& mapManager, int MapLength, MapOrder* mapOrder, Fade& fade)
	{
		TaskFlag tf = Task_Game;

		if (gameORresult)
			GameUpdate(tf, mapManager, MapLength, mapOrder, fade);
		else
			ResultUpdate();

		return tf;
	}
	
	//------------------------------------------------------------------------------------------------
	//描画処理
	void RenderRocket(int i)
	{
		for (int j = *playerNum < 2 ? 0: !winPlayer, k = 0; k < *playerNum; j = !j, ++k)
		{
			player[j].rocket.RenderRocket(player[i].camData->camera);
		}
	}

	void RenderUI(int i)
	{
		player[i].ui.Render(player[i].rocket, player[i].camData->camera);
	}

	void RenderCount()
	{
		count.Render();
	}

	void RenderStageUI()
	{
		sUI.Render();
	}
};