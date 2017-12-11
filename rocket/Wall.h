#pragma once
#include "Camera.h"
#include "Rocket.h"
#include "Fade.h"

//マップの番号を格納
//マップの種類だけ作成してね！！！
struct MapData
{
	string		chip;		//チップ番号
	MapData() : chip(""){}
};

//-------------------------------------------------------------------------------------------------

//マップの並び順と当たり判定データをうんたらかんたら
//マップ枚数分作成してね！！！
struct MapOrder
{
	int		id;			//表示画像番号
	int		height;		//高さ
	int		time;		//時間
	float	visible;	//薄さ

	bool	endUpdate;	//更新を終えたか否か

	MapOrder() : id(0), height(0), time(0), endUpdate(false) {};

	//マップの初期化をするよ！
	void MapInitializeOne(int num, int i)
	{
		id = num;
		height = i;
		time = 0;
		visible = 1.f;
		endUpdate = false;
	}

	//マップを初期化、ランダム生成するよ！
	//0と1は手動で初期化
	void MapInitialize(const int Underground, const int toB, const int toS, const int MapLength,
						int underId, int twoUnderId, int i)
	{
		height = i;
		endUpdate = false;
		switch (underId)
		{
			//◆◆◆◆◆地下ステージ◆◆◆◆◆
		case 1:
			if (i < Underground - 1)
				id = rand() % 2 + 2;
			else if (i < Underground)
				id = 1;
			else
				id = 10;
			break;

		case 2:
			if (i < Underground - 1)
				id = (rand() % 2 + 1) * 2 + 2;
			else
				id = 8;
			break;

		case 3:
			if (i < Underground - 1)
				id = (rand() % 2 + 1) * 2 + 3;
			else
				id = 9;
			break;

		case 4:
			if (i < Underground - 1)
			{
				if (twoUnderId != 4)
					id = rand() % 3 * 2 + 4;
				else
					id = rand() % 2 * 2 + 6;
			}
			else
				id = 8;
			break;

		case 5:
			if (i < Underground - 1)
			{
				if (twoUnderId != 5)
					id = rand() % 3 * 2 + 5;
				else
					id = rand() % 2 * 2 + 7;
			}
			else
				id = 9;
			break;

		case 6:
			if (i < Underground - 1)
				id = 5;
			else
				id = 9;
			break;

		case 7:
			if (i < Underground - 1)
				id = 4;
			else
				id = 8;
			break;

		case 8:
		case 9:
			if (i < Underground - 1)
				id = rand() % 3 + 1;
			else if (i < Underground)
				id = 1;
			else
				id = 10;
			break;
			//◆◆◆◆◆◆◆◆◆◆

			//■■■■■ビルステージ■■■■■
		case 10:
			id = rand() % 3 + 11;
			break;

		case 11:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 2 + 14;
			else
				id = 17;
			break;

		case 12:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 3 + 14;
			else
				id = 17;
			break;

		case 13:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 2 + 15;
			else
				id = 17;
			break;

		case 14:
			if (i < toB - 1)
				id = (rand() % 2 * 3) + 14;
			else if (i < toB)
				id = 14;
			else
				id = 18;
			break;

		case 15:
			if (i < toB - 1)
				id = (rand() % 2 * 2) + 15;
			else if (i < toB)
				id = 15;
			else
				id = 18;
			break;

		case 16:
			if (i < toB - 1)
				id = rand() % 2 + 16;
			else if (i < toB)
				id = 16;
			else
				id = 18;
			break;

		case 17:
			if (i < toB - 1)
				id = rand() % 3 + 11;
			else
				id = rand() % 3 + 14;
			break;
			//■■■■■■■■■■

			//〇〇〇〇〇空ステージ〇〇〇〇〇
		case 18:
			id = 19;
			break;

		case 19:
			if (i < toS - 2)
			{
				if (rand() % 2)
				{
					if (twoUnderId != 19)
						id = (rand() % 2 * 5) + 19;
					else
						id = 24;
				}
				else
				{
					id = rand() % 2 + 20;
				}
			}
			else if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 20:
			if (i < toS - 2)
				id = 22;
			else
				id = 30;
			break;

		case 21:
			if (i < toS - 2)
				id = 23;
			else
				id = 28;
			break;

		case 22:
			if (i < toS - 2 && twoUnderId != 22)
				id = (rand() % 2 * 8) + 22;
			else
				id = 30;
			break;

		case 23:
			if (i < toS - 2 && twoUnderId != 23)
				id = (rand() % 2 * 5) + 23;
			else
				id = 28;
			break;

		case 24:
			id = 25;
			break;

		case 25:
			if (i < toS - 2)
			{
				if (int num = rand() % 3)
				{
					if (num - 1)
						id = (rand() % 2 * 2) + 27;
					else
						id = (rand() % 2 * 3) + 31;
				}
				else
				{
					if (twoUnderId != 25)
						id = rand() % 2 + 25;
					else
						id = 26;
				}
			}
			else
				id = 26;
			break;

		case 26:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 27:
			if (i < toS - 2)
				id = 23;
			else
				id = 28;
			break;

		case 28:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 29:
			if (i < toS - 2)
				id = 22;
			else
				id = 30;
			break;

		case 30:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 31:
		case 32:
			if (id < toS - 2 && twoUnderId != 32)
				id = rand() % 2 + 32;
			else
				id = 33;
			break;

		case 33:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 34:
		case 35:
			if (id < toS - 2 && twoUnderId != 35)
				id = rand() % 2 + 35;
			else
				id = 36;
			break;

		case 36:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 37:
			id = 39;
			break;
			//〇〇〇〇〇〇〇〇〇〇

			//☆☆☆☆☆宇宙ステージ☆☆☆☆☆
		case 39:
			if (i < MapLength - 1)
				id = 39;
			else
				id = 38;
			break;

		case 38:
			break;
			//☆☆☆☆☆☆☆☆☆☆

		}
	}

	//マップを更新するよ！
	void MapUpdate()
	{
		if (endUpdate)
			return;

		++time;
		if (id <= 9)
		{
			if ((time / 60) % 2)
				visible -= 1.f;
			else
				visible += 1.f;
		}
		endUpdate = true;
	}

	//壁とアニメーションを表示するよ！
	void WallRender(const int imgNum, Camera& camera, const MapData *mapdata, bool rktSide)
	{
		int setposY = (height + 1) * -360;

		if (id >= imgNum)
			return;
		ML::Box2D src;
		ML::Box2D draw;
		
		if (!rktSide)
		{
			//壁
			src = ML::Box2D(0, 0, 460, 360);
			draw = ML::Box2D(0, setposY, 460, 360);
			camera.Image_Draw(mapdata[id].chip, draw, src);

			//アニメーション画像
			switch (id)
			{
			case 0:
			case 1:
				for (int i = 0; i < 2; ++i)
				{
					src = ML::Box2D(20 * i, 0, 20, 20);
					draw = ML::Box2D(70 + 300 * i, setposY + 50, 20, 20);
					camera.Image_Draw("RedLight", draw, src);
					src = ML::Box2D(20 * i, 20, 20, 20);
					camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				}
				break;

			case 2:
			case 4:
			case 8:
				src = ML::Box2D(0, 0, 20, 20);
				draw = ML::Box2D(70, setposY + 100, 20, 20);
				camera.Image_Draw("RedLight", draw, src);
				src = ML::Box2D(0, 20, 20, 20);
				camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				break;

			case 3:
			case 5:
			case 9:
				src = ML::Box2D(20, 0, 20, 20);
				draw = ML::Box2D(370, setposY + 100, 20, 20);
				camera.Image_Draw("RedLight", draw, src);
				src = ML::Box2D(20, 20, 20, 20);
				camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				break;
			}
			return;
		}

		switch (id)
		{
		case 10:
			src = ML::Box2D(0, 0, 38, 120);
			draw = ML::Box2D(385, setposY + 20, 38, 120);
			camera.Image_Draw("Umiyama", draw, src);
			break;
		}
	}

	//壁との当たり判定をするよ！
	//引数：ロケット名、対象のセンサー、斜面のスタート位置、終了位置、右(上)か左(下)か
	void HitFormal(Rocket& rkt, Position& sensor, Position start, Position end, bool LUorRD)
	{
		//判定範囲外にいたら処理無し
		if (start.x != end.x && (rkt.pos.x + sensor.x < start.x || end.x < rkt.pos.x + sensor.x))
			return;

		//左右壁(傾きが存在しないため別処理)
		if (!(start.x - end.x))
		{
			if (rkt.pos.y + sensor.y > start.y || end.y > rkt.pos.y + sensor.y)
				return;

			if (LUorRD)
			{
				while (rkt.pos.x + sensor.x < start.x)
				{
					rkt.hit[LorLR] = true;
					rkt.pos.x += 0.1f;
				}
			}
			else
			{
				while (start.x < rkt.pos.x + sensor.x)
				{
					rkt.hit[LorLR] = true;
					rkt.pos.x -= 0.1f;
				}
			}
			return;
		}

		//微妙な引っ掛かりを消す
		start.x += rkt.speed.x;
		end.x += rkt.speed.x;

		//判定範囲外にいたら処理無し
		if (start.y > end.y)	//右上がり
		{
			if (rkt.pos.y + sensor.y > start.y || end.y > rkt.pos.y + sensor.y)
				return;
		}
		else					//左上がり
		{
			if (start.y != end.y && (rkt.pos.y + sensor.y < start.y || end.y < rkt.pos.y + sensor.y))
				return;
		}

		//傾き
		float slope = (start.y - end.y) / (start.x - end.x);
		//切片
		float intercept = start.y - start.x * slope;

		//変更する判定方向を選択
		int hitname = 0;
		if (!(start.y - end.y))
			hitname = RorUD;		//上下
		else if (start.y > end.y)
		{
			if (LUorRD)
				hitname = UL;	//左上
			else
				hitname = DR;	//右下
		}
		else
		{
			if (LUorRD)
				hitname = UR;	//右上
			else
				hitname = DL;	//左下
		}

		//以下当たり判定
		if (LUorRD)
		{
			while (rkt.pos.y + sensor.y < (rkt.pos.x + sensor.x) * slope + intercept)
			{
				rkt.hit[hitname] = true;
				switch (hitname)
				{
				case RorUD:
					rkt.pos.y += 1.f;
					break;

				case UL:
					rkt.pos.x += 1.f;
					rkt.pos.y += 1.f;
					break;

				case UR:
					rkt.pos.x -= 1.f;
					rkt.pos.y += 1.f;
					break;
				}
			}
		}
		else
		{
			while (rkt.pos.y + sensor.y > (rkt.pos.x + sensor.x) * slope + intercept)
			{
				rkt.hit[hitname] = true;
				switch (hitname)
				{
				case RorUD:
					rkt.pos.y -= 0.2f;
					break;

				case DR:
					rkt.pos.x -= 1.f;
					rkt.pos.y -= 1.f;
					break;

				case DL:
					rkt.pos.x += 1.f;
					rkt.pos.y -= 1.f;
					break;
				}
			}
		}
	}

	//月とのあたり判定をするよ！
	void HitMoon(Rocket& rkt, Position sensor, Fade& fade)
	{
		if (((rkt.pos.x + sensor.x) - 230.f) * ((rkt.pos.x + sensor.x) - 230.f) +
			((rkt.pos.y + sensor.y) + 300.f) * ((rkt.pos.y + sensor.y) + 300.f)
			<= (240.f * 240.f))
		{
			rkt.state = Non;
			rkt.explode.SwitchOn(fade);
		}
	}

	//壁とロケットの当たり判定をするよ！
	void NomalWallHit(Rocket& rkt, Position sensor, int lrud, Fade& fade)
	{
		Position start, end;
		//現在のマップチップでの当たり判定
		switch (id)
		{
			//◆◆◆◆◆地下ステージ◆◆◆◆◆
		case 0:
			//地面
			start = { 70.f, -80.f };
			end = { 390.f, -80.f };
			HitFormal(rkt, sensor, start, end, false);
			//左壁
			start = { 70.f, -80.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 390.f, -80.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 1:
			//左壁
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 2:
			//左壁
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//斜め右上壁
			start = { 170.f, -360.f };
			end = { 390.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 3:
			//右壁
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//斜め左上壁
			start = { 70.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 4:
			//左壁
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 170.f, 0.f };
			end = { 170.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 5:
			//左壁
			start = { 290.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 6:
			//斜め左上壁
			start = { 70.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//斜め右下壁
			start = { 170.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 7:
			//斜め左下壁
			start = { 70.f, -360.f };
			end = { 290.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//斜め右上壁
			start = { 170.f, -360.f };
			end = { 390.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 8:
			//左壁
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//斜め右下壁
			start = { 170.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 9:
			//斜め左下壁
			start = { 70.f, -360.f };
			end = { 290.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右壁
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//◆◆◆◆◆◆◆◆◆◆

			//■■■■■ビルステージ■■■■■
		case 10:
			//地面
			start = { 50.f, 0.f };
			end = { 70.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			start = { 390.f + rkt.speed.x, 0.f };
			end = { 410.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//左壁
			start = { 50.f, 0.f };
			end = { 50.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 410.f, 0.f };
			end = { 410.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 11:
			//左壁
			start = { 80.f, 0.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 320.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 12:
			//左壁
			start = { 110.f, 0.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 350.f, 0.f };
			end = { 350.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 13:
			//左壁
			start = { 140.f, 0.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 14:
			//左壁
			start = { 110.f, 0.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 200.f, 0.f };
			end = { 200.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 15:
			//左壁
			start = { 190.f, 0.f };
			end = { 190.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 270.f, 0.f };
			end = { 270.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 16:
			//左壁
			start = { 260.f, 0.f };
			end = { 260.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 350.f, 0.f };
			end = { 350.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 17:
			//左壁
			start = { 80.f, 0.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//■■■■■■■■■■

			//〇〇〇〇〇空ステージ〇〇〇〇〇
		case 18:
			//左下壁
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//左上壁
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//右上壁
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 19:
			//左壁
			start = { 180.f, 0.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 20:
			//左斜め
			start = { 40.f, -280.f };
			end = { 180.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 140.f, -280.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			//左壁
			start = { 40.f, -280.f };
			end = { 40.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 140.f, -280.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 21:
			//左斜め
			start = { 180.f, 0.f };
			end = { 320.f, -280.f };
			HitFormal(rkt, sensor, start, end, true);
			//右斜め
			start = { 280.f, 0.f };
			end = { 420.f, -280.f };
			HitFormal(rkt, sensor, start, end, false);
			//左壁
			start = { 320.f, -280.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 420.f, -280.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 22:
			//左壁
			start = { 40.f, 0.f };
			end = { 40.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 140.f, 0.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 23:
			//左壁
			start = { 320.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 420.f, 0.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 24:
			//左下壁
			start = { 180.f, 0.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 80.f, -240.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//左上壁
			start = { 80.f, -240.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 280.f, 0.f };
			end = { 280.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -140.f };
			end = { 380.f, -240.f };
			HitFormal(rkt, sensor, start, end, false);
			//右上壁
			start = { 380.f, -240.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//中左台形
			start = { 180.f, -360.f };
			end = { 210.f, -330.f };
			HitFormal(rkt, sensor, start, end, true);
			//中右台形
			start = { 250.f, -330.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//中台形
			start = { 210.f, -330.f };
			end = { 250.f, -330.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 25:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//左左壁
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右壁
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//右左壁
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右右壁
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 26:
			//左下壁
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//左上壁
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//右上壁
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//中左台形
			start = { 180.f, 0.f };
			end = { 210.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			//中右台形
			start = { 250.f, -30.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//中台形
			start = { 210.f, -30.f };
			end = { 250.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 27:
			//左斜め
			start = { 80.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 380.f, 0.f };
			end = { 380.f, -300.f };
			HitFormal(rkt, sensor, start, end, false);
			//右上斜め
			start = { 380.f, -300.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			if (lrud >= 2 && rkt.pos.y + sensor.y <= -60.f + rkt.speed.y)
			{
				//中台形
				start = { 220.f, -60.f };
				end = { 280.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (rkt.pos.x + sensor.x < 240.f)
			{
				//中左台形
				start = { 180.f, 0.f };
				end = { 220.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (lrud >= 2)
			{
				//中右台形
				start = { 280.f, 0.f };
				end = { 280.f, -60.f };
				HitFormal(rkt, sensor, start, end, true);
			}
			break;

		case 28:
			//左斜め
			start = { 180.f, -280.f };
			end = { 320.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -280.f };
			end = { 420.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			//左壁
			start = { 180.f, -280.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 280.f, -280.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 29:
			//左上斜め
			start = { 40.f, -360.f };
			end = { 80.f, -300.f };
			HitFormal(rkt, sensor, start, end, false);
			//左壁
			start = { 80.f, 0.f };
			end = { 80.f, -300.f };
			HitFormal(rkt, sensor, start, end, true);
			//右斜め
			start = { 140.f, -360.f };
			end = { 380.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			if (rkt.pos.y + sensor.y <= -60.f + rkt.speed.y)
			{
				//中台形
				start = { 180.f, -60.f };
				end = { 240.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (rkt.pos.x + sensor.x > 220.f)
			{
				//中右台形
				start = { 240.f, -60.f };
				end = { 280.f, 0.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else
			{
				//中左台形
				start = { 180.f, 0.f };
				end = { 180.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			break;

		case 30:
			//左斜め
			start = { 40.f, 0.f };
			end = { 180.f, -280.f };
			HitFormal(rkt, sensor, start, end, true);
			//右斜め
			start = { 140.f, 0.f };
			end = { 280.f, -280.f };
			HitFormal(rkt, sensor, start, end, false);
			//左壁
			start = { 180.f, -280.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右壁
			start = { 280.f, -280.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 31:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//左左壁
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右下壁
				start = { 180.f, 0.f };
				end = { 180.f, -130.f };
				HitFormal(rkt, sensor, start, end, false);
				//左右中斜め
				start = { 130.f, -180.f };
				end = { 180.f, -130.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右上壁
				start = { 130.f, -180.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//右左下壁
			start = { 280.f, 0.f };
			end = { 280.f, -130.f };
			HitFormal(rkt, sensor, start, end, true);
			//右左中斜め
			start = { 280.f, -130.f };
			end = { 330.f, -180.f };
			HitFormal(rkt, sensor, start, end, true);
			//右左上壁
			start = { 330.f, -180.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右右壁
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 32:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//左左壁
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右壁
				start = { 130.f, 0.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//右左壁
			start = { 330.f, 0.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右右壁
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 33:
			//左下壁
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//左上壁
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//右上壁
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//中左台形
			start = { 130.f, 0.f };
			end = { 190.f, -60.f };
			HitFormal(rkt, sensor, start, end, false);
			//中右台形
			start = { 270.f, -60.f };
			end = { 330.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//中台形
			start = { 190.f, -60.f };
			end = { 270.f, -60.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 34:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//左左下壁
				start = { 80.f, 0.f };
				end = { 80.f, -130.f };
				HitFormal(rkt, sensor, start, end, true);
				//左左中斜め
				start = { 80.f, -130.f };
				end = { 130.f, -180.f };
				HitFormal(rkt, sensor, start, end, true);
				//左左上壁
				start = { 130.f, -180.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右壁
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//右左壁
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右右下壁
			start = { 380.f, 0.f };
			end = { 380.f, -130.f };
			HitFormal(rkt, sensor, start, end, false);
			//右左中斜め
			start = { 330.f, -180.f };
			end = { 380.f, -130.f };
			HitFormal(rkt, sensor, start, end, true);
			//右左上壁
			start = { 330.f, -180.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 35:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//左左壁
				start = { 130.f, 0.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//左右壁
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//右左壁
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右右壁
			start = { 330.f, 0.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);

			break;

		case 36:
			//左下壁
			start = { 130.f, 0.f };
			end = { 130.f, -170.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 130.f, -170.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//左上壁
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 330.f, 0.f };
			end = { 330.f, -170.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -220.f };
			end = { 330.f, -170.f };
			HitFormal(rkt, sensor, start, end, true);
			//右上壁
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//中左台形
			start = { 180.f, 0.f };
			end = { 210.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			//中右台形
			start = { 250.f, -30.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//中台形
			start = { 210.f, -30.f };
			end = { 250.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 37:
			//左下壁
			start = { 180.f, 0.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, true);
			//左斜め
			start = { 80.f, -240.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//左上壁
			start = { 80.f, -240.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右下壁
			start = { 280.f, 0.f };
			end = { 280.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//右斜め
			start = { 280.f, -140.f };
			end = { 380.f, -240.f };
			HitFormal(rkt, sensor, start, end, false);
			//右上壁
			start = { 380.f, -240.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//〇〇〇〇〇〇〇〇〇〇

			//月
		case 38:
			HitMoon(rkt, sensor, fade);
			break;
		}
}
	void UnderWallHit(Rocket& rkt, Position sensor)
	{
		Position start, end;
		//地面判定
		switch (id)
		{
		case 11:
			//左地面
			start = { 0.f, 0.f };
			end = { 80.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 320.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 12:
			//左地面
			start = { 0.f, 0.f };
			end = { 110.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 350.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 13:
			//左地面
			start = { 0.f, 0.f };
			end = { 140.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 380.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 14:
			//左地面
			start = { 0.f, 0.f };
			end = { 110.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 200.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 15:
			//左地面
			start = { 0.f, 0.f };
			end = { 190.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 270.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 16:
			//左地面
			start = { 0.f, 0.f };
			end = { 260.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 350.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 37:
			//左地面
			start = { -100.f, 0.f };
			end = { 80.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//右地面
			start = { 380.f, 0.f };
			end = { 560.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
		}

	}
	void HighWallHit(Rocket& rkt, Position sensor)
	{
		Position start, end;
		//天井判定
		switch (id)
		{
		case 11:
			//左天井
			start = { 0.f, -360.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 320.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 12:
			//左天井
			start = { 0.f, -360.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 350.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 13:
			//左天井
			start = { 0.f, -360.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 380.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 14:
			//左天井
			start = { 0.f, -360.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 200.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 15:
			//左天井
			start = { 0.f, -360.f };
			end = { 190.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 270.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 16:
			//左天井
			start = { 0.f, -360.f };
			end = { 260.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//右天井
			start = { 350.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;
	}
};
};
//-------------------------------------------------------------------------------------------------

//マップ全体の管理
struct MapManager
{
	//マップ0番と1番を割り当てる
	void WallZero(MapOrder* mapOrder)
	{
		mapOrder[0].MapInitializeOne(0, 0);
		mapOrder[1].MapInitializeOne(1, 1);
	}

	//初期化
	void WallInitialize(const int Underground, const int toB, const int toS,
		const int MapLength, MapOrder* mapOrder)
	{
		WallZero(mapOrder);
		for (int i = 2; i < MapLength; ++i)
		{
			mapOrder[i].MapInitialize(Underground, toB, toS, MapLength,
				mapOrder[i - 1].id, mapOrder[i - 2].id, i);
		}
	}

	//壁の更新処理
	void WallUpdate(const int MapLength, MapOrder* mapOrder,
					const MoveCameraData camData)
	{
		int checkNum;
		//更新
		for (int i = -1; i < 1; ++i)
		{
			checkNum = ((int)camData.camera.pos.y / -360) + i;
			if (checkNum < 0 || MapLength <= checkNum)
				continue;

			mapOrder[checkNum].MapUpdate();
		}
	}

	//更新終了状態を解除
	void ResetUpdate(MapOrder* mapOrder, int MapLength)
	{
		for (int i = 0; i < MapLength; ++i)
		{
			mapOrder[i].endUpdate = false;
		}
	}

	//ロケットと壁の当たり判定
	void WallHit(const int MapLength, MapOrder* mapOrder, Rocket& rkt, Fade& fade)
	{
		for (int lrud = 0; lrud < 6; ++lrud)
		{
			int chipNum = int(rkt.pos.y + rkt.sensor[lrud].y) / -360;
			Position sensor = rkt.sensor[lrud];
			sensor += rkt.speed;
			sensor.y += chipNum * 360.f;

			if (0 <= chipNum && chipNum < MapLength)
				mapOrder[chipNum].NomalWallHit(rkt, sensor, lrud, fade);	//現マップの当たり判定

																			//以下、左右当たり判定は不要なのでやらない
			if (lrud < 2)
				continue;

			if (0 <= chipNum - 1)
				mapOrder[chipNum - 1].UnderWallHit(rkt, sensor);	//当たり判定下
			if (chipNum + 1 < MapLength)
				mapOrder[chipNum + 1].HighWallHit(rkt, sensor);		//当たり判定上
		}
	}

	//壁の表示
	void WallRender(const int imgNum, const int MapLength, MapOrder* mapOrder, const MapData* mapData,
		Camera& camera, bool side = false)
	{
		for (int i = -2; i <= 1; ++i)
		{
			int cnum = ((int)camera.pos.y / -360) + i;
			if (cnum < 0 || MapLength <= cnum)
				continue;

			mapOrder[cnum].WallRender(imgNum, camera, mapData, side);
		}
	}
};