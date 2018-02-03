#pragma once
#include "TaskFlag.h"

class ResultManager
{
private:
	//����(�^�C�~���O)�v��
	int time;

	//�摜�ǂݍ��ݗp��`
	ML::Box2D resultImg;
	Position resultPos;
	SlideMove resultSlide;

	ML::Box2D timeandDotImg[11];
	ML::Box2D winnerImg[2];
	Position twPos;
	SlideMove twSlide;

	//���݂̃t���O�Ǝ��̃t���O
	int nowFlag;
	int nextFlag;

public:

	//�R���X�g���N�^
	ResultManager():
		resultSlide(&resultPos, Position(720, 25), Position(10, 25)),
		twSlide(&twPos, Position(-262, 210), Position(350, 210)){}

	//������
	void Initialize()
	{
		time = 0;
		nowFlag = 0;
		nextFlag = 0;

		resultImg = { 0, 0, 552, 80 };
		for (int i = 0; i < 11; ++i)
		{
			if (i == 10)
				timeandDotImg[i] = { 58 * i, 0, 58, 80 };
			else
				timeandDotImg[i] = { 58 * i, 0, 30, 80 };
		}
		for (int i = 0; i < 2; ++i)
		{
			winnerImg[i] = { 0, 174 * (i + 1), 610, 116 };
		}
		resultSlide.Initialize(5.f);
		twSlide.Initialize(5.f);
	}

	//�A�j���[�V�����ύX���̏���
	void ChangeAnim(Fade& fade)
	{
		switch (nextFlag)
		{
		case 1:
			fade.ImageSet(PositionI(0, 0), "FadeImg", ML::Box2D(0, 0, 720, 405));
			fade.FadeSwitch(false, 50, 0.6f);
			break;

		default:
			break;
		}
		nowFlag = nextFlag;
	}

	//�A�j���[�V��������
	bool Animation(Fade& fade, DI::VGamePad& in)
	{
		//���݂̃t���O�Ǝ��̃t���O���قȂ�ꍇ
		if (nowFlag != nextFlag)
			ChangeAnim(fade);

		//��{�I�ȏ����͂����ɏ���
		bool endFlag = false;
		switch (nowFlag)
		{
		case 0:
			++time;
			endFlag = time > 90;
			break;

		case 1:
			endFlag = fade.endFade;
			break;

		case 2:
			++time;
			endFlag = time > 70;
			break;

		case 3: //�N���A�^�C��(���邢�͏����v���C���[)��\��
			if (resultSlide.ShuMoveStop())
			{
				if (twSlide.ShuMoveStop())
					endFlag = true;
			}
			break;

		case 4: //�{�^�����͂���������^�C�g����ʂɑJ�ڂ���
			if (in.B1.down)
			{
				resultSlide.ChangePosition(resultPos, { resultPos.x, -80.f });
				resultSlide.Initialize(5.f);
				twSlide.ChangePosition(twPos, { twPos.x, 405.f });
				twSlide.Initialize(5.f);
				endFlag = true;
			}
			break;
			
		case 5:
			if (resultSlide.ShuMoveStop() &&
				twSlide.ShuMoveStop())
			{
				fade.FadeSwitch(false, 120);
				endFlag = true;
			}
			break;

		case 6:
			if (fade.endFade)
				++time;
			endFlag = time > 60;
			break;

		default:
			break;
		}

		//�t���O�J��
		if (endFlag)
		{
			endFlag = false;
			time = 0;
			++nextFlag;

			if (nextFlag >= 7)
				return true;
		}
		return false;
	}

	void ResultRender(int timerTime)
	{
		if (nowFlag < 3)
			return;

		{ //"Result-----------"
			ML::Box2D draw = resultImg;
			draw.Offset(resultPos.x, resultPos.y);
			DG::Image_Draw("Result", draw, resultImg);
		}
		{ //�S�[�����Ԃ������v���C���[�̕\��

		}
	}
};