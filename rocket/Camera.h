#pragma once
#include "MyPG.h"
#include "Position.h"

//���ӁI�I�I
//���ނ���摜�͓��{�Ŏg�p���ĂˁI�I
//���Z����Ƃ̖񑩂���I�I

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
	float moveX, moveY, //����(��)
		  moveW, moveH; //����(�E)
	Position vec;		//�x�N�g��
	unsigned int time;	//���Ԍv��

public:
	Position pos;			//���W(����)
	Box2Df view;     //�\���ʒu�ƕ\����
	
	Camera() : pos(Position()),
			   vec(Position()),
			   view(0.f, 0.f, 0.f, 0.f),
			   time(0) {}

	//������
	void InitializeCamera()
	{
		pos = Position();
		vec = Position();
		time = 0;
		view = Box2Df(0.f, 0.f, 0.f, 0.f);
	}

	//�\���ʒu�ƕ\����̐ݒ�
	//�����Fx���W, y���W, x�����̃T�C�Y, y�����̃T�C�Y
	void SetViewPort(float xS, float yS, float wS, float hS)
	{
		view = Box2Df(xS, yS, wS, hS);
	}

	//�\���ʒu���w����W�ւ������ړ�
	//�����F���W(Position), �ړ�����
	//�Ԃ茌�F�ړ��������������ۂ�(�}1�h�b�g�ȓ�)
	bool MoveViewPort(Position sv, float slowTime)
	{
		view.x += (sv.x - view.x) / slowTime;
		view.y += (sv.y - view.y) / slowTime;

		if (sv.x - 1 <= view.x && view.x <= sv.x + 1 &&
			sv.y - 1 <= view.y && view.y <= sv.y + 1)
			return true;

		return false;
	}

	//����̐ݒ�
	//�����Fx�n�_, y�n�_, x�I�_, y�I�_
	void SetExcursion(float xM, float yM, float wM, float hM)
	{
		moveX = xM;
		moveY = yM;
		moveW = wM;
		moveH = hM;
	}

	//���W�̐ݒ�
	//�����Fx���W, y���W
	void SetCPos(Position setPos)
	{
		pos = setPos;
	}

	//�w����W�ɂ������ړ�
	//�����Fx���W, y���W, �ړ�����
	//�߂�l�F
	bool SlowSetCPos(Position sg, float slowTime)
	{
		pos.x += (sg.x - pos.x) / slowTime;
		pos.y += (sg.y - pos.y) / slowTime;

		if (sg.x - 10 <= pos.x && pos.x <= sg.x + 10 &&
			sg.y - 10 <= pos.y && pos.y <= sg.y + 10)
			return true;

		return false;
	}

	//�x�N�g���̐ݒ�
	//�����Fx�����̃x�N�g��, y�����̃x�N�g��
	void SetVector(Position vp)
	{
		vec = vp;
	}

	//�J������h�炷(���W�𒆐S�ɏ�������]�^��)
	void SwayPosition()
	{
		++time;
		if (time > 360)
			time = 0;
		vec.x = cos(ML::ToRadian((float)time));
		vec.y = sin(ML::ToRadian((float)time));
	}

	//�x�N�g�����̓���
	void AddVector()
	{
		pos += vec;
	}

	//����O�ɏo�����̏���
	//�߂�l�F����O�ɏo��ʒu�ɂ��邩�ۂ�
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

	//�J�����@�\���g�p�����摜�\��
	//�����F�摜��
	//�@�@�@�\����
	//�@�@�@�\����
	//�@�@�@�\���F(�����͂�1.f)
	void Image_Draw(string imageName,
				   ML::Box2D draw,
				   ML::Box2D src,
				   ML::Color color = ML::Color(1.f, 1.f, 1.f, 1.f))
	{
		//�摜�̕\���ʒu�𒲐�
		draw.x -= int(pos.x - view.x);
		draw.y -= int(pos.y - view.y);

		ML::Box2D viewCopy = ML::Box2D((int)view.x, (int)view.y, (int)view.w, (int)view.h);

		//��ʊO�ɏo�Ă���摜�ɂ͉������Ȃ�
		if (!viewCopy.Hit(draw))
			return;

		//�\����O�̉摜��؂�
		if (draw.x < viewCopy.x) //��
		{
			src.x += viewCopy.x - draw.x;
			src.w -= viewCopy.x - draw.x;
			draw.w -= viewCopy.x - draw.x;
			draw.x = viewCopy.x;
		}
		if (draw.y < viewCopy.y) //��
		{
			src.y += viewCopy.y - draw.y;
			src.h -= viewCopy.y - draw.y;
			draw.h -= viewCopy.y - draw.y;
			draw.y = viewCopy.y;
		}
		if (draw.x + draw.w >viewCopy.x + viewCopy.w) //�E
		{
			src.w -= (draw.x + draw.w) - (viewCopy.x + viewCopy.w);
			draw.w -= (draw.x + draw.w) - (viewCopy.x + viewCopy.w);
		}
		if (draw.y + draw.h > viewCopy.y + viewCopy.h) //��
		{
			src.h -= (draw.y + draw.h) - (viewCopy.y + viewCopy.h);
			draw.h -= (draw.y + draw.h) - (viewCopy.y + viewCopy.h);
		}

		DG::Image_Draw(imageName, draw, src, color);
	}
};

//---------------------------------------------------------------------------------------
//�J�����̎��̂Ɖ�ʏ���W�̓�����ꏏ�ɂ�����I
struct MoveCameraData
{
	Position setViewPos;
	Position setGamePos;
	float moveviewTime;
	float movegameTime;

	//�X�C���O�ړ�
	bool swingCamera;

	Camera camera;

	MoveCameraData() :
		camera(Camera()),
		setViewPos(Position()),
		setGamePos(Position()),
		moveviewTime(0.f),
		movegameTime(0.f),
		swingCamera(true){}

	//��ʏ�J�����ݒ�
	//�����F��ʏ���W(Position), ��ʏ���W�ւ̈ړ�����(float)
	void SetViewCamera(Position svp, float mvt)
	{
		setViewPos = svp;
		moveviewTime = mvt;
	}

	//�Q�[�����J�����ݒ�
	//�����F�Q�[�������W(Position), �Q�[�������W�ւ̈ړ�����
	void SetGameCamera(Position sgp, float mgt)
	{
		setGamePos = sgp;
		movegameTime = mgt;
	}

	//�J�����̉�ʏ���W���w����W�܂ňړ�������
	//�߂�l�F���삪�����������ۂ�(bool)
	bool MoveCamera()
	{
		bool endViewMove, endGameMove;
		endViewMove = camera.MoveViewPort(setViewPos, moveviewTime);
		endGameMove = camera.SlowSetCPos(setGamePos, movegameTime);
		if (swingCamera)
			camera.SwayPosition();
		camera.AddVector();
		endGameMove = camera.BackPosition() || endGameMove;
		return endViewMove && endGameMove;
	}
};
