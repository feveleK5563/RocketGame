#include "MyGameMain.h"
#include "Fade.h"
#include "Camera.h"
#include "TaskManager.h"

//ゲーム情報
TaskManager tm;

//-----------------------------------------------------------------------------
//初期化処理
//機能概要：プログラム起動時に１回実行される（素材などの準備を行う）
//-----------------------------------------------------------------------------
void  MyGameMain_Initalize()
{
	srand((unsigned int)time(NULL));

	//キーボードの入力を受け取るオブジェクトを生成する
	DI::AnalogAxisKB	ls1 = { DIK_LEFT, DIK_RIGHT, DIK_UP, DIK_DOWN };
	DI::AnalogAxisKB	ls2 = { DIK_NUMPAD4, DIK_NUMPAD6, DIK_NUMPAD0, DIK_NUMPAD2 };
	DI::AnalogAxisKB	rs = {0, 0, 0, 0};
	DI::KeyDatas_KB	 key1 = {
		{ DIK_R, DI::But::B1 },{ DIK_E, DI::But::B2 },
		{ DIK_D, DI::But::B3 },{ DIK_F, DI::But::B4 },
		{ DIK_A, DI::But::SE },{ DIK_SPACE, DI::But::ST },
		{ DIK_Q, DI::But::L1 },{ DIK_W, DI::But::R1 },{ DIK_A, DI::But::L2 },
	};
	DI::KeyDatas_KB	 key2 = {
		{ DIK_R, DI::But::B1 },{ DIK_NUMPAD9, DI::But::B2 },
		{ DIK_D, DI::But::B3 },{ DIK_F, DI::But::B4 },
		{ DIK_A, DI::But::SE },{ DIK_SPACE, DI::But::ST },
		{ DIK_Q, DI::But::L1 },{ DIK_NUMPAD8, DI::But::R1 },{ DIK_A, DI::But::L2 },
	};
	//ゲームパッドパラメータ
	DI::KeyDatas_GP	but = {
		{ DI::GPB::B02, DI::But::B1 },{ DI::GPB::B03, DI::But::B2 },
		{ DI::GPB::B01, DI::But::B3 },{ DI::GPB::B04, DI::But::B4 },
		{ DI::GPB::B05, DI::But::L1 },{ DI::GPB::B06, DI::But::R1 },
		{ DI::GPB::B07, DI::But::L2 },{ DI::GPB::B08, DI::But::R2 },
		{ DI::GPB::B09, DI::But::SE },{ DI::GPB::B10, DI::But::ST },
		{ DI::GPB::B11, DI::But::L3 },{ DI::GPB::B12, DI::But::R3 },
	};
	DI::GPad_CreateKBGP("P1", ls1, rs, key1, 0, but);
	DI::GPad_CreateKBGP("P2", ls2, rs, key2, 1, but);

	tm.Initialize();
}
//-----------------------------------------------------------------------------
//解放処理
//機能概要：プログラム終了時に１回実行される（素材などの解放を行う）
//-----------------------------------------------------------------------------
void  MyGameMain_Finalize()
{
	tm.Finalize();
}
//更新処理
//機能概要：ゲームの１フレームに当たる処理
//-----------------------------------------------------------------------------
void  MyGameMain_UpDate()
{
	tm.Update();
}
//-----------------------------------------------------------------------------
//描画処理
//機能概要：ゲームの１フレームに当たる表示処理
//-----------------------------------------------------------------------------
void  MyGameMain_Render2D()
{
	tm.Render();
}
