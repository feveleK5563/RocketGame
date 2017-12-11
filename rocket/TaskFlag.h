#pragma once
#include "MyPG.h"
#include "Fade.h"
#include "BackGround.h"
#include "Rocket.h"
#include "Camera.h"
#include "Wall.h"
#include "UI.h"
#include "ImageManager.h"


//タスク名
enum TaskFlag
{
	Task_Non,		//タスクが未選択状態
	Task_Title,		//タイトル画面
	Task_Game,		//ゲーム本編
	Task_Result		//リザルト画面
};
