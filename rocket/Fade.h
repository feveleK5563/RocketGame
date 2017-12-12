#pragma once
#include "MyPG.h"
#include "Position.h"

//�w��摜�Ńt�F�[�h�C���A�t�F�[�h�A�E�g����
class Fade
{
private:
	enum FadeState
	{
		Off,
		FadeIn,
		FadeOut,
	};
	FadeState fadestate;

	float	visible;
	float	visibleLimit; //-1 = Non
	float	fadeTime;

	string	 imgName;
	PositionI	pos;
	ML::Box2D	src;

public:

	bool	endFade;
	
	Fade() :
		visible(0.f),
		fadeTime(0),
		fadestate(Off),
		endFade(false),
		imgName(""),
		pos(PositionI()),
		src(ML::Box2D()){}

	//�摜�̃Z�b�g
	//�����F�摜�̕\���ʒu(PositionI), �摜��(string), �摜��ǂݍ��ޑ傫��(ML::Box2D)
	void ImageSet(PositionI setpos, string imgnm, ML::Box2D img2d)
	{
		pos = setpos;
		imgName = imgnm;
		src = img2d;
	}

	//�t�F�[�h�t���O
	//�����F�t�F�[�h�C�����t�F�[�h�A�E�g(bool, true�ŃC�� false�ŃA�E�g), �t�F�[�h�����܂ł̃t���[����(int, �f�t�H���g��60)
	//	�@�@�t�F�[�h�F����(float, �f�t�H���g��-1.f(0.f��1.f))
	void FadeSwitch(bool InOut, int time = 60, float limit = -1.f)
	{
		if (InOut)
		{
			fadestate = FadeIn;
			visible = 1.f;
			if (limit == -1.f)
				visibleLimit = 0.f;
			else
				visibleLimit = limit;
		}
		else
		{
			fadestate = FadeOut;
			visible = 0.f;
			if (limit == -1.f)
				visibleLimit = 1.f;
			else
				visibleLimit = limit;
		}
		fadeTime = (float)time;
		endFade = false;
	}

	//�X�V
	bool Update()
	{
		switch (fadestate)
		{
		case Off:
			endFade = true;
			break;

		case FadeIn:
			visible -= 1.f / fadeTime;
			if (visible <= visibleLimit)
			{
				fadestate = Off;
				endFade = true;
			}
			break;

		case FadeOut:
			visible += 1.f / fadeTime;
			if (visible >= visibleLimit)
			{
				fadestate = Off;
				endFade = true;
			}
			break;
		}
		return endFade;
	}

	//�`��
	void Render()
	{
		ML::Box2D draw = src.OffsetCopy(pos.x, pos.y);
		DG::Image_Draw(imgName, draw, src, ML::Color(visible, 1.f, 1.f, 1.f));
	}
};
