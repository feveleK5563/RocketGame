#pragma once
#include "TaskFlag.h"

struct TitleManager
{
	//�Q�[���p�b�h
	DI::VGamePad* in[2];
	//�Q�[�����[�h
	int* mode;
	//�v���C���[��
	int* playerNum;
	//�J�����f�[�^
	MoveCameraData* camData[2];
	Position focus[2];
	Position leftSide;
	Position rightSide;
	Position moveGoal;
	bool* endMove;

	ImageManager im;

	TitleManager(DI::VGamePad* pad, MoveCameraData* camD, int* md, int* pn, bool* em):
		mode(md),
		playerNum(pn),
		endMove(em)
	{
		for (int i = 0; i < 2; ++i)
		{
			camData[i] = &camD[i];
			in[i] = &pad[i];
		}
		leftSide = Position(-410.f, 0.f);
		moveGoal = Position(-400.f, 0.f);
		rightSide = Position(770.f, 0.f);
	}

	//------------------------------------------------------------------------------------------------
	//����������
	void Initialize(const int MapLength)
	{
		im.TitleExeImageCreate();

		if (*playerNum == 1)
		{
			camData[0]->camera.view.x = 180.f;
			camData[1]->camera.view.x = leftSide.x;
			focus[0] = Position(50.f, MapLength * -360.f);
		}
		else if (*playerNum == 2)
		{
			for (int i = 0; i < 2; ++i)
			{
				camData[i]->camera.view.x = i * (camData[i]->camera.view.w + 1);
				focus[i] = Position(50.f, MapLength * -360.f);
			}
		}
		else
		{
			exit(0);
		}
	}

	//�I������
	void Finalize()
	{
		im.TitleExeImageErase();
	}

	//------------------------------------------------------------------------------------------------
	//���[�h�ύX
	void ChangeMode(bool change, const int MapLength)
	{
		if (change)
		{
			for (int i = 0; i < 2; ++i)
			{
				//�J��������ʍ��O�Ɉړ�������
				camData[i]->SetViewCamera(leftSide, 10.f);
			}
		}
		
		//�ړ������J�������������ʒu�𒴂�����
		if (camData[0]->camera.view.x < moveGoal.x &&
			camData[1]->camera.view.x < moveGoal.x)
		{
			*mode = (*mode + 1) % 2;
			switch (*mode)
			{
			case 0:
				*playerNum = 1;
				break;

			case 1:
				*playerNum = 2;
				break;

			default:
				exit(0);
				break;
			}

			//�J�������E���ɔz�u���A���[�h�ɉ������ʒu�փJ�������ړ�������
			for (int i = 0; i < *playerNum; ++i)
			{
				focus[i] = Position(50.f, MapLength * -360.f);
				camData[i]->camera.view.x = rightSide.x;
				if (*playerNum == 1)
				{
					camData[i]->SetViewCamera(Position(180.f, 0.f), 10.f);
					break;
				}
				else if (*playerNum == 2)
					camData[i]->SetViewCamera(Position(i * (camData[i]->camera.view.w + 1), 0), 10.f);
				else
					exit(0);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	//�X�V����
	TaskFlag Update(const int MapLength)
	{
		TaskFlag tf = Task_Title;

		for (int i = 0; i < *playerNum; ++i)
		{
			if (in[i]->LStick.D.on)
				focus[i].y = MapLength * -360.f + 400;
			if (in[i]->LStick.D.off)
				focus[i].y = MapLength * -360.f;

			//�w��Q�[�������W�֊��炩�Ɉړ�
			camData[i]->SetGameCamera(focus[i], 10.f);
		}

		ChangeMode(in[0]->LStick.L.down, MapLength);

		//���[�h�̕ύX
		if ((in[0]->L1.on && in[0]->R1.on) &&
			*endMove)
			tf = Task_Game;
		
		return tf;
	}

	//------------------------------------------------------------------------------------------------
	//�`�揈��
	void Render(const int MapLength, int i)
	{
		int height = MapLength * -360;
		//�^�C�g��
		{
			ML::Box2D draw(85, height, 300, 270);
			ML::Box2D src(0, 0, 300, 270);
			camData[i]->camera.Image_Draw("Title", draw, src);
		}

		{
			//���[�h��
			ML::Box2D draw(160, height + 290, 140, 20);
			ML::Box2D src(0, i * 20, 140, 20);
			camData[i]->camera.Image_Draw("Mode", draw, src);
			//���̉�
			if (!i)
			{
				draw.y += 25; draw.h += 20;
				src = ML::Box2D(0, 40, 140, 40);
				camData[i]->camera.Image_Draw("Mode", draw, src);
			}
			//�V�ѕ��ւ̖��
			draw.y += 45;
			draw.h = 35;
			src = ML::Box2D(0, 80, 140, 35);
			camData[i]->camera.Image_Draw("Mode", draw, src);
		}

		//�V�ѕ�
		{
			ML::Box2D draw(75, height += 500, 300, 250);
			ML::Box2D src(0, 0, 300, 250);
			camData[i]->camera.Image_Draw("HowTo" + to_string(i), draw, src);
		}
	}
};