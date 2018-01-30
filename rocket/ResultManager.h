#pragma once
#include "TaskFlag.h"

class ResultManager
{
private:
	//����(�^�C�~���O)�v��
	int time;
	//���݂̃t���O�Ǝ��̃t���O
	int nowFlag;
	int nextFlag;

public:

	//������
	void Initialize()
	{
		time = 0;
		nowFlag = 0;
		nextFlag = 0;
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

		case 5:
			fade.FadeSwitch(false, 120);
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

		case 3: //���������l���Ă���̂���N
				//�N���A�^�C��(���邢�͏����v���C���[)��\�����āA
				//�{�^�����͂���������^�C�g����ʂɑJ�ڂ��Ăق����̂���N
			if (in.B1.down)
			{
				endFlag = true;
			}
			break;

		case 4:
			endFlag = true;
			break;
			
		case 5:
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

			if (nextFlag >= 6)
				return true;
		}
		return false;
	}
};