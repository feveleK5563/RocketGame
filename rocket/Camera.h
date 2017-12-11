#pragma once
#include "MyPG.h"
#include "Position.h"

//注意！！！
//頼むから画像は等倍で使用してね！！
//お兄さんとの約束だよ！！

class Box2Df
{
public:
	float x, y, w, h;
	Box2Df():
		x(0.f), y(0.f), w(0.f), h(0.f){}
	Box2Df(float xf, float yf, float wf, float hf):
		x(xf), y(yf), w(wf), h(hf){}

	bool Hit(const  ML::Box2D& b_) const
	{
		if ((int)x		< b_.x + b_.w	&&
			b_.x	< (int)x + (int)w	&&
			(int)y		< b_.y + b_.h	&&
			b_.y	< (int)y + (int)h) {
			return true;
		}
		return false;
	}
};

class Camera
{
private:
	float moveX, moveY, //可動域(左)
		  moveW, moveH; //可動域(右)
	Position vec;		//ベクトル
	unsigned int time;	//時間計測

public:
	Position pos;			//座標(左上)
	Box2Df view;     //表示位置と表示域
	
	Camera() : pos(Position()),
			   vec(Position()),
			   view(0.f, 0.f, 0.f, 0.f),
			   time(0) {}

	//初期化
	void InitializeCamera()
	{
		pos = Position();
		vec = Position();
		time = 0;
		view = Box2Df(0.f, 0.f, 0.f, 0.f);
	}

	//表示位置と表示域の設定
	//引数：x座標, y座標, x方向のサイズ, y方向のサイズ
	void SetViewPort(float xS, float yS, float wS, float hS)
	{
		view = Box2Df(xS, yS, wS, hS);
	}

	//表示位置を指定座標へゆっくり移動
	//引数：座標(Position), 移動時間
	//返り血：移動が完了したか否か(±1ドット以内)
	bool MoveViewPort(Position sv, float slowTime)
	{
		view.x += (sv.x - view.x) / slowTime;
		view.y += (sv.y - view.y) / slowTime;

		if (sv.x - 1 <= view.x && view.x <= sv.x + 1 &&
			sv.y - 1 <= view.y && view.y <= sv.y + 1)
			return true;

		return false;
	}

	//可動域の設定
	//引数：x始点, y始点, x終点, y終点
	void SetExcursion(float xM, float yM, float wM, float hM)
	{
		moveX = xM;
		moveY = yM;
		moveW = wM;
		moveH = hM;
	}

	//座標の設定
	//引数：x座標, y座標
	void SetCPos(Position setPos)
	{
		pos = setPos;
	}

	//指定座標にゆっくり移動
	//引数：x座標, y座標, 移動時間
	//戻り値：
	bool SlowSetCPos(Position sg, float slowTime)
	{
		pos.x += (sg.x - pos.x) / slowTime;
		pos.y += (sg.y - pos.y) / slowTime;

		if (sg.x - 10 <= pos.x && pos.x <= sg.x + 10 &&
			sg.y - 10 <= pos.y && pos.y <= sg.y + 10)
			return true;

		return false;
	}

	//ベクトルの設定
	//引数：x方向のベクトル, y方向のベクトル
	void SetVector(Position vp)
	{
		vec = vp;
	}

	//カメラを揺らす(座標を中心に小さく回転運動)
	void SwayPosition()
	{
		++time;
		if (time > 360)
			time = 0;
		vec.x = cos(ML::ToRadian((float)time));
		vec.y = sin(ML::ToRadian((float)time));
	}

	//ベクトル分の動作
	void AddVector()
	{
		pos += vec;
	}

	//可動域外に出た時の処理
	//戻り値：可動域外に出る位置にいるか否か
	bool BackPosition()
	{
		bool bp = false;
		if (pos.x < moveX) {
			pos.x = moveX;
			bp = true;
		}
		if (pos.x > moveW - view.w) {
			pos.x = moveW - view.w;
			bp = true;
		}
		if (pos.y < moveY) {
			pos.y = moveY;
			bp = true;
		}
		if (pos.y > moveH - view.h){
			pos.y = moveH - view.h;
			bp = true;
		}
		return bp;
	}

	//カメラ機能を使用した画像表示
	//引数：画像名
	//　　　表示先
	//　　　表示元
	//　　　表示色(未入力で1.f)
	void Image_Draw(string imageName,
				   ML::Box2D draw,
				   ML::Box2D src,
				   ML::Color color = ML::Color(1.f, 1.f, 1.f, 1.f))
	{
		//画像の表示位置を調整
		draw.x -= int(pos.x - view.x);
		draw.y -= int(pos.y - view.y);

		ML::Box2D viewCopy = ML::Box2D((int)view.x, (int)view.y, (int)view.w, (int)view.h);

		//画面外に出ている画像には何もしない
		if (!viewCopy.Hit(draw))
			return;

		//表示域外の画像を切る
		if (draw.x < viewCopy.x) //左
		{
			src.x += viewCopy.x - draw.x;
			src.w -= viewCopy.x - draw.x;
			draw.w -= viewCopy.x - draw.x;
			draw.x = viewCopy.x;
		}
		if (draw.y < viewCopy.y) //上
		{
			src.y += viewCopy.y - draw.y;
			src.h -= viewCopy.y - draw.y;
			draw.h -= viewCopy.y - draw.y;
			draw.y = viewCopy.y;
		}
		if (draw.x + draw.w >viewCopy.x + viewCopy.w) //右
		{
			src.w -= (draw.x + draw.w) - (viewCopy.x + viewCopy.w);
			draw.w -= (draw.x + draw.w) - (viewCopy.x + viewCopy.w);
		}
		if (draw.y + draw.h > viewCopy.y + viewCopy.h) //下
		{
			src.h -= (draw.y + draw.h) - (viewCopy.y + viewCopy.h);
			draw.h -= (draw.y + draw.h) - (viewCopy.y + viewCopy.h);
		}

		DG::Image_Draw(imageName, draw, src, color);
	}
};

//---------------------------------------------------------------------------------------
//カメラの実体と画面上座標の動作を一緒にしたよ！
struct MoveCameraData
{
	Position setViewPos;
	Position setGamePos;
	float moveviewTime;
	float movegameTime;

	Camera camera;

	MoveCameraData() :
		camera(Camera()),
		setViewPos(Position()),
		setGamePos(Position()),
		moveviewTime(0.f),
		movegameTime(0.f){}

	//カメラ設定
	//引数：画面上座標(Position), 画面上座標への移動時間(float)
	void SetViewCamera(Position svp, float mvt)
	{
		setViewPos = svp;
		moveviewTime = mvt;
	}

	//ぬわぁぁん疲れたもぉぉぉん
	//引数：ゲーム内座標(Position), ゲーム内座標への移動時間
	void SetGameCamera(Position sgp, float mgt)
	{
		setGamePos = sgp;
		movegameTime = mgt;
	}

	//カメラの画面上座標を指定座標まで移動させる
	//戻り値：動作が完了したか否か(bool)
	bool MoveCamera()
	{
		bool endViewMove, endGameMove;
		endViewMove = camera.MoveViewPort(setViewPos, moveviewTime);
		endGameMove = camera.SlowSetCPos(setGamePos, movegameTime);
		camera.SwayPosition();
		camera.AddVector();
		endGameMove = camera.BackPosition() || endGameMove;
		return endViewMove && endGameMove;
	}
};
