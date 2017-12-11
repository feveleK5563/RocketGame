#pragma once
#include "TaskFlag.h"

struct ResultManager
{
	//�Q�[���p�b�h
	DI::VGamePad* in[2];
	//���[�h
	int* mode;
	//�v���C���[��
	int* playerNum;
	//�ǂ�������������
	bool winPlayer;
	//�N���A����
	int clearTime;

	ResultManager(DI::VGamePad* pad, int* md, int* pn):
		mode(md),
		playerNum(pn)
	{
		for (int i = 0; i < 2; ++i)
		{
			in[i] = pad + i;
		}
	}

	//----------------------------------------------------------------------------
	//����������
	void Initialize(int cleart, bool winp)
	{
		winPlayer = winp;
		clearTime = cleart;
	}
};