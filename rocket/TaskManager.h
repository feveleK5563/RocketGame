#pragma once
#include "TaskFlag.h"
#include "TitleManager.h"
#include "GameManager.h"

//地下ステージ
const int Underground = 4; //40
//ビルステージ
const int Building = 4; //40
//空ステージ
const int Sky = 4; //50
//宇宙ステージ
const int Space = 4; //17
//各ステージ間の長さ
const int toB = Underground + Building;	//ビルステージ終了までの長さ
const int toS = toB + Sky;				//空ステージ終了までの高さ
const int MapLength = toS + Space;		//マップの全長

//マップ画像
//地下ステージ → 0~9(計10)
//ビルステージ → 10~17(計8)
//空ステージ → 18~37(計16)
//宇宙ステージ → 38,(39は画像無し)
const int imgNum = 39;

MapData		mapData[imgNum];		//マップの画像データ
MapOrder	mapOrder[MapLength];	//マップ場所、当たり判定

struct TaskManager
{
	//ゲームパッド
	DI::VGamePad  in[2];

	ImageManager	img;			//画像の読み込み
	MapManager		mapManager;		//マップの管理
	Back				back[2];		//背景(空)の管理
	MoveCameraData		camData[2];		//各プレイヤー用カメラとカメラの設置座標

	TaskFlag	actTask, nextTask;	//現在のタスク名と次のタスク名
	int			mode;				//モード番号		(0：一人プレイ, 1：二人プレイ)
	int			playerNum;			//プレイヤー数	(1：一人, 2：二人)
	Fade		fade;				//フェード

	TitleManager	tm;	//タイトルマネージャー
	GameManager		gm;	//ゲームマネージャー

	bool endMove;	//入力を認めるか否か

	//----------------------------------------------------------------------------
	TaskManager() :
		actTask(Task_Non),
		nextTask(Task_Non),
		mode(0),
		playerNum(0),
		tm(in, camData, &mode, &playerNum, &endMove),
		gm(in, &mode, &playerNum, camData, &mapManager, &endMove){}

	//------------------------------------------------------------------------------------------------
	//初期化処理
	void Initialize()
	{
		DG::Image_Create("Back", "./data/image/BackImg.png");		//背景
		DG::Image_Create("FadeImg", "./data/image/FadeImg.png");	//フェード用黒画像
		DG::Image_Create("FlashImg", "./data/image/FlashImg.png");	//フラッシュ用白画像

		img.SkyImageCreate();
		img.WallImageCreate(imgNum, mapData);

		//フェードの設定
		ML::Box2D fadesrc(0, 0, ge->screenWidth, ge->screenHeight);
		fade.ImageSet(PositionI(0, 0), "FadeImg", fadesrc);		//フェード画像を設定
		fade.FadeSwitch(true, 60);								//30フレームでフェードインする

		//マップを自動生成する
		mapManager.WallInitialize(Underground, toB, toS, MapLength, mapOrder);

		//カメラ
		for (int i = 0; i < 2; ++i)
		{
			//空を初期化
			back[i].Initialize(0, 0);
			//カメラを初期化
			camData[i].camera.InitializeCamera();
			camData[i].camera.SetCPos(Position(50.f, MapLength * -360.f));
			camData[i].camera.SetViewPort(180, 0, 360, 405);
			camData[i].camera.SetExcursion(0.f, MapLength * -360.f, 460.f, 0.f);
			camData[i].SetViewCamera(Position(180, 0), 1.f);
			camData[i].SetGameCamera(Position(50.f, MapLength * -360.f), 1.f);
		}

		//プレイヤー数
		playerNum = 1;

		endMove = false;

		actTask = Task_Non;		//最初のタスクは無効
		nextTask = Task_Title;	//次のタスク
	}

	//------------------------------------------------------------------------------------------------
	//終了処理
	void Finalize()
	{
		DI::GPad_Erase("P1");
		DI::GPad_Erase("P2");

		DG::Image_Erase("Back");
		DG::Image_Erase("FadeImg");
		DG::Image_Erase("Flashimg");
		img.SkyImageErase();
		img.WallImageErase(imgNum);
	}

	//------------------------------------------------------------------------------------------------
	//更新処理
	void Update()
	{
		if (playerNum <= 0 || playerNum > 2)
			exit(0);

		in[0] = DI::GPad_GetState("P1");
		in[1] = DI::GPad_GetState("P2");

		if (actTask != nextTask)
		{
			//終了処理
			switch (actTask)
			{
			case Task_Title:
				tm.Finalize();

			case Task_Game:
				gm.Finalize();
				break;
			}
			
			//現在のタスクに次のタスクを代入
			actTask = nextTask;

			//初期化処理
			switch (actTask)
			{
			case Task_Title:
				tm.Initialize(MapLength);
				break;
			
			case Task_Game:
				gm.Initialize(MapLength);
				mapManager.WallInitialize(Underground, toB, toS, MapLength, mapOrder);
				break;
			}
		}
		//更新処理
		switch (actTask)
		{
		case Task_Title:
			nextTask = tm.Update(MapLength);
			break;

		case Task_Game:
			nextTask = gm.Update(mapManager, MapLength, mapOrder, fade);
			break;
		}

		//カメラの動作と壁の更新
		bool endCameraMove;
		for (int i = 0; i < playerNum; ++i)
		{
			endCameraMove = camData[i].MoveCamera();
			//空がカメラを追尾
			back[i].PosTracking(camData[i].camera.pos.y);

			//壁の更新
			mapManager.WallUpdate(MapLength, mapOrder, camData[i]);
		}
		mapManager.ResetUpdate(mapOrder, MapLength);

		endMove = fade.Update() && endCameraMove;
	}

	//------------------------------------------------------------------------------------------------
	//描画処理
	void Render()
	{
		//背景
		{
			ML::Box2D draw(0, 0, ge->screenWidth, ge->screenHeight);
			ML::Box2D src(0, 0, ge->screenWidth, ge->screenHeight);
			DG::Image_Draw("Back", draw, src);
		}

		for (int i = 0; i < playerNum; ++i)
		{
			//空
			back[i].Render(camData[i].camera);
			
			//壁
			mapManager.WallRender(imgNum, MapLength, mapOrder, mapData, camData[i].camera, false);

			//タイトル
			if (actTask == Task_Title)
				tm.Render(MapLength, i);

			//ロケット
			if (actTask == Task_Game)
			{
				gm.RenderRocket(i);
			}

			//ロケットより手前にある装飾
			mapManager.WallRender(imgNum, MapLength, mapOrder, mapData, camData[i].camera, true);
		}

		//全体UI
		if (actTask == Task_Game)
			gm.RenderStageUI();

		for (int i = 0; i < playerNum; ++i)
		{
			//UI
			if (actTask == Task_Game)
				gm.RenderUI(i);
		}

		//カウントダウンとメッセージ表示
		if (actTask == Task_Game)
			gm.RenderCount();

		//フェード
		fade.Render();
	}
};