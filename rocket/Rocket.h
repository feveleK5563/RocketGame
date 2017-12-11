#pragma once
#include "MyPG.h"
#include "Position.h"
#include "Camera.h"
#include "Fade.h"

//爆発アニメーション
class ExplodeAnimation
{
private:
	int time;
	int animation;
	bool onoff;
	bool end;

public:

	//初期化
	void InitializeExplode()
	{
		time = 0;
		animation = 0;
		onoff = false;
		end = false;
	}

	//爆発フラグを立てる
	void SwitchOn(Fade& fade)
	{
		if (!onoff)
		{
			onoff = true;
			fade.ImageSet(PositionI(0, 0), "FlashImg", ML::Box2D(0, 0, 720, 405));
			fade.FadeSwitch(true, 30);
		}
	}

	//更新
	bool UpdateExplode()
	{
		if (onoff && animation < 11)
		{
			++time;
			animation = time / 5;

			if (animation >= 6)
				end = true;
		}
		return end;
	}

	//描画
	void RenderExplode(Position pos, Camera& camera)
	{
		if (onoff)
		{
			ML::Box2D src(animation * 200, 0, 200, 200);
			ML::Box2D draw(-100, -100, 200, 200);
			draw.Offset(pos.x, pos.y);
			camera.Image_Draw("Explosion", draw, src);
		}
	}
};

//煙アニメーション
class SmokeAnimation
{
private:
	int time;
	Position pos;
	Position speed;

public:
	SmokeAnimation():		//デフォ
		time(0),
		pos(Position(0.f, 0.f)),
		speed(Position(0.f, 0.f)){}

	SmokeAnimation(Position rktpos):	//呼ぶのはこっち
		time(40),
		pos(rktpos)
	{
		speed.x = float((rand() % 10) - 5) / 10.f;
		speed.y = float((rand() % 6) - 3) / 10.f;
	}

	//更新
	bool UpdateSmoke()
	{
		if (time > 0)
		{
			--time;
			pos += speed;
			return false;
		}
		return true;
	}

	//描画
	void RenderSmoke(Camera& camera)
	{
		ML::Box2D src(0, 10, 20, 20);
		ML::Box2D draw(-10, -10, 20, 20);
		draw.Offset(pos.x, pos.y);
		DG::Image_Rotation("Jet", ML::ToRadian((float)time), ML::Vec2(10, 10));
		camera.Image_Draw("Jet", draw, src, ML::Color(float(time) / 40.f, 1.f, 1.f, 1.f));
	}
};

//ジェット噴射アニメーション
class JetAnimation
{
private:
	bool active[8];					//表示の有無
	Position pos[8];				//位置
	vector<SmokeAnimation*> smoke;	//煙

public:
	//初期化
	void InitializeJet()
	{
		for (int i = 0; i < 8; ++i)
		{
			pos[i] = Position(0, 0);
			active[i] = false;
		}
	}

	//表示フラグ
	void SetJetAnim(bool onoff)
	{
		active[0] = onoff;
		if (active[0] && (rand() % 3 + 1) % 2)
		{
			smoke.emplace_back(new SmokeAnimation(pos[0]));
		}
	}

	//アニメーション更新
	void UpdateJet(Position rktpos, Position rktspd)
	{
		for (int i = 0; i < 8; ++i)
		{
			pos[i].x = rktpos.x - ((rktspd.x * i) / 10.f);
			pos[i].y = (rktpos.y + 10.f) - (rktspd.y / 2.f) * i;

			if (i > 0 && pos[i].y < pos[i - 1].y)
				pos[i].y = pos[i - 1].y;
		}

		for (int i = 7; i > 0; --i)
		{
			active[i] = active[i - 1];
		}

		//煙
		int size = (int)smoke.size();
		for (int i = 0; i < size;)
		{
			if (smoke[i]->UpdateSmoke())
			{
				delete smoke[i];
				smoke[i] = smoke.back();
				smoke.pop_back();
				--size;
			}
			else
			{
				++i;
			}
		}
		smoke.shrink_to_fit();
	}

	//表示
	void RenderJet(Camera& camera)
	{
		for (int i = 0; i < (int)smoke.size(); ++i)
			smoke[i]->RenderSmoke(camera);

		for (int i = 7; i >= 0; --i)
		{
			if (!active[i])
				continue;

			ML::Box2D src(i * 10, 0, 10, 10);
			ML::Box2D draw(-5, -5, 10, 10);
			draw.Offset(pos[i].x, pos[i].y);
			DG::Image_Rotation("Jet", ML::ToRadian(float(rand() / 360)), ML::Vec2(7, 5));
			camera.Image_Draw("Jet", draw, src);
		}
	}

	//煙メモリ解放(ゲームクリア時に呼び出す)
	void EndJet()
	{
		smoke.clear();
		smoke.shrink_to_fit();
	}
};


enum HitSensor
{
	LorLR,		//左右
	RorUD,		//上下
	UL,			//斜め左上
	UR,			//斜め右上
	DL,			//斜め左下
	DR,			//斜め右下
};
enum RocketState
{
	Non,		//操作不可
	Empty,		//エネルギー切れ
	Nomal,		//通常(エネルギー有)
	Spin,		//スピン
	Turbo,		//ターボ
	Wait,		//待機
};
class Rocket
{
public:
	Position	pos;		//座標
	Position	speed;		//速度
	RocketState state;		//ロケットの状態
	int showEnergy,		//エネルギー表示
		showTurboGage;	//ターボゲージ表示

	Position	sensor[6];	//衝突判定センサー
	ML::Box2D hitbase;		//あたり判定矩形

	bool		hit[6];		//反射方向

	Rocket(): pos(Position()), speed(Position()), state(Non),
			  showEnergy(0), showTurboGage(0) {}

	const int EnergyMax = 1000; //エネルギー上限
	const int TurboMax = 1000;	//ターボ上限
	int time[5];				//時間とか計る(各状態)

	ExplodeAnimation explode;	//爆発アニメーション

private:
	int rktanim;			//アニメーション画像番号
	ML::Box2D rktsrc[8];	//アニメーション画像

	bool noRender;				//画像表示させない

	JetAnimation jetAnim;		//ジェット噴射アニメーション

	//ロケットの座標移動
	void MoveRocket()
	{
		pos += speed;
	}

	//センサー位置を設定
	void SetSensor()
	{
		sensor[LorLR]  = { -9.f,   0.f };
		sensor[RorUD]  = {  8.f,   0.f };
		sensor[UL]	   = { -9.f, -14.f };
		sensor[UR]	   = {  8.f, -14.f };
		sensor[DL]	   = { -9.f,  12.f };
		sensor[DR]	   = {  8.f,  12.f };
		hitbase = { 0, 0, 18, 32 };
	}

	//センサーをすべてオフ
	void HitOff()
	{
		for (int i = 0; i < 6; ++i)
		{
			hit[i] = false;
		}
	}

	//カメラの反動
	//引数：カメラ名、X方向の反動、Y方向の反動、
	//　　　反動の大きさ、反動の発生方向を反転
	void RecoilXY(Camera& camera, bool xon, bool yon,
				  float powor = 3.f, bool turn = false)
	{
		if (xon)
		{
			if (speed.x > 0.f || (turn && speed.x < 0.f))
				camera.view.x -= powor;
			else if (speed.x < 0.f || (turn && speed.x > 0.f))
				camera.view.x += powor;
		}

		if (yon)
		{
			if (speed.y > 0.f || (turn && speed.y < 0.f))
				camera.view.y -= powor;
			else if (speed.y < 0.f || (turn && speed.y > 0.f))
				camera.view.y += powor;
		}
	}

	//ロケットの移動力変更とカメラへの反動
	void ChangeSpeed(Camera& camera)
	{
		if (hit[LorLR])		//左右
		{
			if (state < Spin
				&& fabsf(speed.x) > 0.25f)
				speed.x *= -0.5f;
			else
				speed.x = 0.f;

			RecoilXY(camera, true, false);
		}

		if (hit[RorUD])		//上下
		{
			if (fabs(speed.y) > 0.2f)
				speed.y *= -0.25f;
			else
				speed.y = 0.f;

			RecoilXY(camera, false, true);
		}

		//スピン時とターボ時は反動なし
		if (state >= Spin)
		{
			if (hit[LorLR] || state == Turbo)	//左右の壁に接触したら加速
			{
				speed.y = -15.f;
				RecoilXY(camera, false, true, 8.f, true);
				if (time[Turbo] < TurboMax)
					time[Turbo] += 2;
			}
			else if (hit[UL] || hit[UR]) //斜めの壁に接触したら大きく加速
			{
				speed.y = -17.f;
				RecoilXY(camera, false, true, 10.f, true);
				if (time[Turbo] < TurboMax)
					time[Turbo] += 10;
			}
			HitOff();
		}

		if (hit[UL])		//斜め左上
		{
			if (speed.x < 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += -1.f * speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		if (hit[DR])		//斜め右下
		{
			if (speed.x > 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x -= speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		if (hit[UR])	//斜め右上
		{
			if (speed.x > 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += speed.y * 0.3f;
				speed.y *= 0.3f;
			}
			
			RecoilXY(camera, true, true);
		}

		if (hit[DL])	//斜め左下
		{
			if (speed.x < 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		HitOff(); //判定をオフ
	}

	//アニメーション
	void Animation()
	{
		if (state < Spin || state == Wait)
			rktanim += int(speed.x);
		else
			rktanim += 25;
		
		if (rktanim >= 80)
			rktanim = 0;
		if (rktanim < 0)
			rktanim = 79;
	}

	//ちょっとずつ数字を増やす
	void AddNumberSlow(int& addNum, int& copyNum, const int Max)
	{
		if (copyNum > Max)
			copyNum = Max;

		if (addNum == copyNum)
			return;

		if (addNum < copyNum)
		{
			addNum += 10;
			if (addNum > copyNum)
				addNum = copyNum;
			return;
		}
		
		addNum -= 10;
		if (addNum < copyNum)
			addNum = copyNum;
		if (addNum < 0)
			addNum = 0;
	}

	//状態管理
	void ChangeState(const DI::VGamePad& GP, bool canMove)
	{
		switch (state)
		{
		case Non:		//行動不可
			break;

		case Empty:		//エネルギー切れ
			if (time[Empty] > 240)
			{
				state = Nomal;
				time[Empty] = 0;
				time[Nomal] = EnergyMax;
			}
			else
			{
				/**/++time[Empty];/*
				time[Empty] = 241;/**/
			}
			break;

		case Nomal:		//通常状態
			//エネルギー増減
			if (!canMove)
				break;

			if (GP.R1.on)
			{
				--time[Nomal];
				if (time[Turbo] < TurboMax)
					++time[Turbo];
			}
			else if (time[Nomal] < EnergyMax)
			{
				if (fabsf(speed.y) <= 0.2f)
					time[Nomal] += 2;
				else
					++time[Nomal];
			}

			//スピン移行
			if (time[Nomal] > 20 && GP.B2.down && fabsf(speed.y) > 0.f)
			{
				state = Spin;
				time[Nomal] -= 30;
				break;
			}

			//エネルギー切れ移行
			if (time[Nomal] <= 0)
				state = Empty;

			//ターボ移行
			if (GP.B1.down &&
				time[Turbo] >= TurboMax)
			{
				state = Turbo;
			}
			break;

		case Spin:		//スピン状態
			if (time[Spin] < 15)
			{
				++time[Spin];
				break;
			}
			time[Spin] = 0;
			state = Nomal;
			break;

		case Turbo:		//ターボ状態
			if (time[Turbo] <= 0)
			{
				state = Nomal;
				time[Turbo] = 0;
			}
			time[Turbo] -= 10;
			break;
		}

		//表示用
		AddNumberSlow(showEnergy, time[Nomal], EnergyMax);
		AddNumberSlow(showTurboGage, time[Turbo], TurboMax);
	}

public:
	//初期化
	//引数：ロケットの初期位置(Position), ロケットの色種類(int)
	void InitializeRocket(Position cpos, int rktcolor)
	{
		speed = { 0.f, 0.f };
		pos = cpos;
		SetSensor();
		HitOff();
		state = Non;
		for (int i = 0; i < 5; ++i)
		{
			time[i] = 0;
		}
		time[Nomal] = EnergyMax;
		showEnergy = 0;
		showTurboGage = 0;

		rktanim = 0;
		for (int i = 0; i < 8; ++i)
		{
			rktsrc[i] = ML::Box2D(i * 30, rktcolor * 38, 30, 38);
		}

		jetAnim.InitializeJet();
		explode.InitializeExplode();
		noRender = false;
	}

	//通常動作
	void JetRocket(const DI::VGamePad& pad, bool canMove)
	{
		if (state == Non)
		{
			jetAnim.SetJetAnim(false);
			return;
		}

		//上下運動
		if (canMove &&
			(state == Nomal || state == Spin) && 
			pad.R1.on && speed.y > -10.f)
		{
			speed.y -= 0.2f;			//押している間は上昇加速
		}
		else if (state == Turbo && speed.y > -20.f)
		{
			speed.y -= 0.3f;			//ターボ時は急加速
		}
		else if (speed.y < 10.f)
		{
			speed.y += 0.2f;		//離している間は下降加速
		}
		jetAnim.SetJetAnim(canMove &&
							(pad.R1.on && (state == Nomal || state == Spin))||
							speed.y <= -10.f ||
							state == Turbo);

		//左右移動
		if (fabsf(speed.y) > 0.2f && canMove)
		{
			if (pad.LStick.R.on)
			{
				if (speed.x < 4.f)
					speed.x += 0.15f;		//右方加速
				return;
			}
			if (pad.LStick.L.on)
			{
				if (speed.x > -4.f)
					speed.x -= 0.15f;		//左方加速
				return;
			}
		}
		//左右速度をぴったり0にする
		if (speed.x > 0.f)
		{
			speed.x -= 0.05f;
			if (speed.x < 0.f)
				speed.x = 0.f;
			return;
		}
		if (speed.x < 0.f)
		{
			speed.x += 0.05f;
			if (speed.x > 0.f)
				speed.x = 0.f;
			return;
		}
	}

	//更新
	void UpdateRocket(Camera& camera, DI::VGamePad GP, bool toRocketHit, bool canMove)
	{
		Animation();
		if (state != Non)
		{
			if (!toRocketHit)
				MoveRocket();
			ChangeSpeed(camera);
			jetAnim.UpdateJet(pos, speed);
		}
		ChangeState(GP, canMove);
		noRender = explode.UpdateExplode();
	}

	//X軸方向ループ
	//引数：左端のX座標, 右端のX座標
	void LoopPositionX(float L, float R)
	{
		if (L > pos.x)
			pos.x = R;

		if (pos.x > R)
			pos.x = L;
	}

	//ロケットの描画
	void RenderRocket(Camera& camera)
	{
		if (!noRender)
		{
			jetAnim.RenderJet(camera);

			ML::Box2D src = rktsrc[rktanim / 10];
			ML::Box2D draw(-15, -26, 30, 38);
			draw.Offset(pos.x, pos.y);
			camera.Image_Draw("Rocket", draw, src);
		}

		explode.RenderExplode(pos, camera);
	}

	//ロケットの終了処理
	void EndRocket()
	{
		jetAnim.EndJet();
	}
};

//二つのロケットの重なり状態を解除し移動量を反転する
void ToRocketHit(Rocket& rocket1, Rocket& rocket2)
{
	Rocket* rkt[2] = { &rocket1, &rocket2 };
	Position spd[2] = { rkt[0]->speed, rkt[1]->speed };

	ML::Box2D hb[2] = { rkt[0]->hitbase.OffsetCopy(rkt[0]->pos.x, rkt[0]->pos.y),
					    rkt[1]->hitbase.OffsetCopy(rkt[1]->pos.x, rkt[1]->pos.y) };
	//動作を行う前から重なっていたら解除する
	while (hb[0].Hit(hb[1]))
	{
		for (int i = 0; i < 2; ++i)
		{
			if (rkt[i]->pos.x > rkt[!i]->pos.x)
			{
				rkt[i]->pos.x += 1.f;
			}
			else
			{
				rkt[i]->pos.x -= 1.f;
			}
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
	}

	//X軸当たり判定
	while (spd[0].x != 0.f || spd[1].x != 0.f)
	{
		float posX[2] = { rkt[0]->pos.x, rkt[1]->pos.x };
		for (int i = 0; i < 2; ++i)
		{
			if(spd[i].x >= 1.f)			{ rkt[i]->pos.x += 1.f; spd[i].x -= 1.f; }
			else if (spd[i].x <= -1.f)	{ rkt[i]->pos.x -= 1.f; spd[i].x += 1.f; }
			else						{ rkt[i]->pos.x += spd[i].x; spd[i].x = 0.f; }
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
		if (hb[0].Hit(hb[1]))
		{
			for (int i = 0; i < 2; ++i)
			{
				rkt[i]->pos.x = posX[i];
				rkt[!i]->speed.x -= (rkt[i]->speed.x * 2) / 3;
				rkt[i]->hit[LorLR] = true;
			}
			break;
		}
	}

	//Y軸当たり判定
	while (spd[0].y != 0.f || spd[1].y != 0.f)
	{
		float posY[2] = { rkt[0]->pos.y, rkt[1]->pos.y };
		for (int i = 0; i < 2; ++i)
		{
			if (spd[i].y >= 1.f) { rkt[i]->pos.y += 1.f; spd[i].y -= 1.f; }
			else if (spd[i].y <= -1.f) { rkt[i]->pos.y -= 1.f; spd[i].y += 1.f; }
			else { rkt[i]->pos.y += spd[i].y; spd[i].y = 0.f; }
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
		if (hb[0].Hit(hb[1]))
		{
			for (int i = 0; i < 2; ++i)
			{
				rkt[i]->speed.y = 0.f;
				rkt[i]->hit[LorLR] = true;
			}
			break;
		}
	}
}