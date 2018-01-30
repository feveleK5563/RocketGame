#pragma once
#include "TaskFlag.h"
#include "CountDown.h"
#include "ResultManager.h"

//-----------------------------------------------------------------------------
//�v���C���[
struct Player
{
	Rocket	rocket;
	MoveCameraData*	camData;
	UI		ui;
};

//-----------------------------------------------------------------------------
//�Q�[���{�ҊǗ�
struct GameManager
{
	//�Q�[���p�b�h
	DI::VGamePad* in[2];
	//���[�h
	int*		mode;
	//�v���C���[��
	int*		playerNum;
	//�e�v���C���[�̎��f�[�^
	Player		player[2];
	//��ʂɈ�����\������UI
	StageUI		sUI;
	//�J��������̏I����`����
	bool* endMove;

	//�摜�ǂݍ��݂�����
	ImageManager img;
	//�Q�[���J�n�܂ł̃J�E���g�_�E���ƃQ�[���I���̓���
	CountDown count;
	//�����Ă�v���C���[
	bool winPlayer;
	//�Q�[���{�҂ƃ��U���g��ʂ̑J��(true�ŃQ�[���{�ҁAfalse�Ń��U���g���)
	bool gameORresult;
	//���U���g��ʂ̊Ǘ�
	ResultManager rm;

	GameManager(DI::VGamePad* pad, int* md, int* pn, MoveCameraData* camD, MapManager* mapM, bool* em) :
		playerNum(pn),
		mode(md),
		winPlayer(0),
		endMove(em)
	{
		for (int i = 0; i < 2; ++i)
		{
			player[i].camData = &camD[i];
			in[i] = pad + i;
		}
	}

	//------------------------------------------------------------------------------------------------
	//����������
	void Initialize(int MapLength)
	{
		img.RocketImageCreate();
		img.UIImageCreate();
		img.CountDownImageCreate();

		count.Initialize();
		gameORresult = true;

		for (int i = 0; i < *playerNum; ++i)
		{
			//UI(�v���C���[�p)
			Position rktPos;
			PositionI egauge, tgauge, mPlayer;
			if (*playerNum == 1)
			{
				//���P�b�g�̏�����
				rktPos = Position(230.f, 0.f);

				egauge = PositionI(115, 10);
				tgauge = PositionI(149, 10);
				mPlayer = PositionI(632, 10);
			}
			else
			{
				rktPos = Position(160.f + (i * 140.f), 0.f);

				egauge = PositionI(-10 + i * 707, 55);
				tgauge = PositionI(20 + (i * 655), 146);
				mPlayer = PositionI(355 + (i * 10), 10);
			}
			player[i].rocket.InitializeRocket(rktPos, i);
			ML::Color mColor;
			switch (i)
			{
			case 0:
				mColor = ML::Color(1.f, 1.f, 0.f, 0.f);
				break;

			case 1:
				mColor = ML::Color(1.f, 0.f, 0.f, 1.f);
				break;
			}
			player[i].ui.Initialize(egauge, tgauge, mPlayer, mColor);
			player[i].camData->swingCamera = true;
		}
		player[0].rocket.state = Nomal;
		player[1].rocket.state = Nomal;

		//UI(�Q�[���S�̗p)//565
		PositionI timer;
		if (*playerNum == 1)
			timer = PositionI(565, 10);
		else
			timer = PositionI(293, 10);
		sUI.Initialize(timer);

		winPlayer = 0;
	}

	//------------------------------------------------------------------------------------------------
	//�I������
	void Finalize()
	{
		img.RocketImageErase();
		img.UIImageErase();
		img.CountDownImageErase();
		for (int i = 0; i < 2; ++i)
		{
			player[i].rocket.state = Non;
			player[i].rocket.EndRocket();
		}
	}

	//------------------------------------------------------------------------------------------------
	//�Q�[���{�҂̍X�V����
	void GameUpdate(TaskFlag& tf, MapManager& mapManager, int MapLength, MapOrder* mapOrder, Fade& fade)
	{
		//���P�b�g��������󂯕t���邩�ۂ�
		bool canMove = false;
		//�Q�[���J�n���̎��Ԍv��
		canMove = count.GameStart(*endMove);

		//�Q�[���I������FINISH�̕\��
		if (player[0].rocket.state == Non || player[1].rocket.state == Non)
			if (canMove = count.GameEnd())
			{
				gameORresult = false;
				for (int i = 0; i < 2; ++i)
				{
					player[i].camData->swingCamera = false;
					player[i].rocket.state = Non;
				}
				rm.Initialize();
			}

		for (int i = 0; i < *playerNum; ++i)
		{
			//���P�b�g�̓��͎󂯕t��
			player[i].rocket.JetRocket(*in[i], canMove);
			//�ǏՓ˔���
			mapManager.WallHit(MapLength, mapOrder, player[i].rocket, fade);
		}

		//�v���C���[����l�ȏ� && ���P�b�g���m����苗���ȉ��܂ŋߕt���Ă��� && �����P�b�g�̏�Ԃ�Non����Ȃ� �Ƃ���
		//���P�b�g���m�̓����蔻�菈�����s��
		bool toRocketHit =
			!(*playerNum < 2 ||
				fabsf(player[0].rocket.pos.y - player[1].rocket.pos.y) > 76.f) &&
			player[0].rocket.state != Non && player[1].rocket.state != Non;

		//���P�b�g���m�̓����蔻��(toRocketHit��true�̂Ƃ��̂�)
		if (toRocketHit)
			ToRocketHit(player[0].rocket, player[1].rocket);

		for (int i = 0; i < *playerNum; ++i)
		{
			//���P�b�g�̍X�V(����X�V�ƈړ��ʔ��]�ƃA�j���[�V����)
			player[i].rocket.UpdateRocket(player[i].camData->camera, *in[i], toRocketHit, canMove);
			player[i].rocket.LoopPositionX(-9.f, 469.f);

			//�J�����̒ǔ�
			player[i].camData->SetGameCamera(Position(player[i].rocket.pos.x - 180.f, player[i].rocket.pos.y - 290.f), 7.f);

			//UI�̍X�V
			player[i].ui.Update(player[i].rocket, MapLength);
		}
		sUI.Update(canMove);

		if (in[0]->ST.down || in[1]->ST.down)
			tf = Task_Title;

		winPlayer = !(player[0].rocket.pos.y < player[1].rocket.pos.y);

	}

	//------------------------------------------------------------------------------------------------
	//���U���g��ʂ̍X�V����
	void ResultUpdate(Fade& fade, TaskFlag& tf)
	{
		if (rm.Animation(fade, *in[0]))
		{
			for (int i = 0; i < 2; ++i)
			{
				player[i].camData->swingCamera = true;
			}
			fade.FadeSwitch(true, 120);
			tf = Task_Title;
		}
	}

	//------------------------------------------------------------------------------------------------
	//�X�V����
	TaskFlag Update(MapManager& mapManager, int MapLength, MapOrder* mapOrder, Fade& fade)
	{
		TaskFlag tf = Task_Game;

		if (gameORresult)
			GameUpdate(tf, mapManager, MapLength, mapOrder, fade);
		else
			ResultUpdate(fade, tf);

		return tf;
	}
	
	//------------------------------------------------------------------------------------------------
	//�`�揈��
	void RenderRocket(int i)
	{
		for (int j = *playerNum < 2 ? 0: !winPlayer, k = 0; k < *playerNum; j = !j, ++k)
		{
			player[j].rocket.RenderRocket(player[i].camData->camera);
		}
	}

	void RenderUI(int i)
	{
		player[i].ui.Render(player[i].rocket, player[i].camData->camera);
	}

	void RenderCount()
	{
		count.Render();
	}

	void RenderStageUI()
	{
		sUI.Render();
	}
};