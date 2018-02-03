#pragma once
#include "MyPG.h"
#include "Wall.h"

struct ImageManager
{
	//��̉摜��ǂݍ��ނ�I
	void SkyImageCreate()
	{
		DG::Image_Create("Sky", "./data/image/Sky.png");
	}

	//��̉摜����������I
	void SkyImageErase()
	{
		DG::Image_Erase("Sky");
	}

	//----------------------------------------------------------------------------
	//�ǂ̉摜��ǂݍ��ނ�I
	void WallImageCreate(const int imgNum, MapData* mapData)
	{
		for (int i = 0; i < imgNum; ++i)
		{
			string num = to_string(i);
			if (num.length() < 2)
			{
				num = "0" + num;
			}
			DG::Image_Create("Wall" + num, "./data/image/wall/Wall" + num + ".png");
			mapData[i].chip = "Wall" + num;
		}

		DG::Image_Create("RedLight", "./data/image/Object/Light.png");
		DG::Image_Create("Umiyama", "./data/image/Object/Umiyama.png");
	}

	//�ǂ̉摜����������I
	void WallImageErase(const int imgNum)
	{
		for (int i = 0; i < imgNum; ++i)
		{
			string num = to_string(i);
			if (num.length() < 2)
			{
				num = "0" + num;
			}
			DG::Image_Erase("Wall" + num);
		}
	}

	//----------------------------------------------------------------------------
	//UI�p�摜��ǂݍ��ނ�I
	void UIImageCreate()
	{
		DG::Image_Create("Gauge", "./data/image/UI/Gauge.png");				//�Q�[�W
		DG::Image_Create("Timer", "./data/image/UI/Timer.png");				//�^�C�}�[
		DG::Image_Create("MiniMoon", "./data/image/UI/MiniMoon.png");		//�~�j�}�b�v�p�̌�
		DG::Image_Create("MiniPlayer", "./data/image/UI/MiniPlayer.png");	//�~�j�}�b�v�p�̃v���C���[
																			//�X�s�[�h��
		for (int i = 0; i < 4; ++i)
		{
			DG::Image_Create("Speed" + to_string(i), "./data/image/UI/Speed" + to_string(i) + ".png");
		}
		DG::Image_Create("Danger", "./data/image/UI/Danger.png");	//�댯
		DG::Image_Create("Empty", "./data/image/UI/Empty.png");		//�G�l���M�[�؂�
	}

	//UI�p�摜����������I
	void UIImageErase()
	{
		DG::Image_Erase("Gauge");
		DG::Image_Erase("Timer");
		DG::Image_Erase("MiniMoon");
		DG::Image_Erase("MiniPlayer");
		for (int i = 0; i < 4; ++i)
		{
			DG::Image_Erase("Speed" + to_string(i));
		}
		DG::Image_Erase("Danger");
		DG::Image_Erase("Empty");
	}

	//----------------------------------------------------------------------------
	//���P�b�g�p�摜��ǂݍ��ނ�I
	void RocketImageCreate()
	{
		DG::Image_Create("Rocket", "./data/image/Rocket.png");			//�v���C���[
		DG::Image_Create("Jet", "./data/image/Jet.png");				//�W�F�b�g����
		DG::Image_Create("Explosion", "./data/image/Explosion.png");	//����
	}

	//���P�b�g�p�摜����������I
	void RocketImageErase()
	{
		DG::Image_Erase("Rocket");
		DG::Image_Erase("Jet");
		DG::Image_Erase("Explosion");
	}

	//----------------------------------------------------------------------------
	//�^�C�g���Ƃ��̉摜��ǂݍ��ނ�I
	void TitleExeImageCreate()
	{
		DG::Image_Create("Title", "./data/image/Title.png");
		DG::Image_Create("Mode", "./data/image/Mode.png");
		DG::Image_Create("HowTo0", "./data/image/HowTo0.png");
		DG::Image_Create("HowTo1", "./data/image/HowTo1.png");
	}

	//�^�C�g���Ƃ��̉摜����������I
	void TitleExeImageErase()
	{
		DG::Image_Erase("Title");
		DG::Image_Erase("Mode");
		DG::Image_Erase("HowTo0");
		DG::Image_Erase("HowTo1");
	}

	//�Q�[���J�n�O�̃J�E���g�_�E���ƏI�����p�摜��ǂݍ��ނ�I
	void CountDownImageCreate()
	{
		DG::Image_Create("Count", "./data/image/StartEnd.png");
	}

	//�J�E���g�_�E���ƏI�����p�摜����������I
	void CountDownImageErase()
	{
		DG::Image_Erase("Count");
	}

	//���ʉ�ʂŎg�p����摜��ǂݍ��ނ�I
	void ResultImageCreate()
	{
		DG::Image_Create("Result", "./data/image/UI/Result.png");
	}

	//���ʉ�ʂŎg�p����摜����������I
	void ResultImageErase()
	{
		DG::Image_Erase("Result");
	}
};