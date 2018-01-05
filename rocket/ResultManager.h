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

		default:
			break;
		}
		nowFlag = nextFlag;
	}

	//�A�j���[�V��������
	void Animation(Fade& fade)
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
			endFlag = true;
			break;

		default:
			break;
		}

		//�t���O�J��
		if (endFlag)
		{
			time = 0;
			++nextFlag;
		}
	}
};