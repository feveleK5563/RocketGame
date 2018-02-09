#pragma once
#include "TaskFlag.h"
#include "TitleManager.h"
#include "GameManager.h"

//�n���X�e�[�W
const int Underground = 40; //40
//�r���X�e�[�W
const int Building = 40; //40
//��X�e�[�W
const int Sky = 50; //50
//�F���X�e�[�W
const int Space = 17; //17
//�e�X�e�[�W�Ԃ̒���
const int toB = Underground + Building;	//�r���X�e�[�W�I���܂ł̒���
const int toS = toB + Sky;				//��X�e�[�W�I���܂ł̍���
const int MapLength = toS + Space;		//�}�b�v�̑S��

//�}�b�v�摜
//�n���X�e�[�W �� 0~9(�v10)
//�r���X�e�[�W �� 10~17(�v8)
//��X�e�[�W �� 18~37(�v16)
//�F���X�e�[�W �� 38,(39�͉摜����)
const int imgNum = 39;

MapData		mapData[imgNum];		//�}�b�v�̉摜�f�[�^
MapOrder	mapOrder[MapLength];	//�}�b�v�ꏊ�A�����蔻��

struct TaskManager
{
	//�Q�[���p�b�h
	DI::VGamePad  in[2];

	ImageManager	img;			//�摜�̓ǂݍ���
	MapManager		mapManager;		//�}�b�v�̊Ǘ�
	Back				back[2];		//�w�i(��)�̊Ǘ�
	MoveCameraData		camData[2];		//�e�v���C���[�p�J�����ƃJ�����̐ݒu���W

	TaskFlag	actTask, nextTask;	//���݂̃^�X�N���Ǝ��̃^�X�N��
	int			mode;				//���[�h�ԍ�		(0�F��l�v���C, 1�F��l�v���C)
	int			playerNum;			//�v���C���[��	(1�F��l, 2�F��l)
	Fade		fade;				//�t�F�[�h

	TitleManager	tm;	//�^�C�g���}�l�[�W���[
	GameManager		gm;	//�Q�[���}�l�[�W���[

	bool endMove;	//���͂�F�߂邩�ۂ�

	//----------------------------------------------------------------------------
	TaskManager() :
		actTask(Task_Non),
		nextTask(Task_Non),
		mode(0),
		playerNum(0),
		tm(in, camData, &mode, &playerNum, &endMove),
		gm(in, &mode, &playerNum, camData, &mapManager, &endMove){}

	//------------------------------------------------------------------------------------------------
	//����������
	void Initialize()
	{
		DG::Image_Create("Back", "./data/image/BackImg.png");		//�w�i
		DG::Image_Create("FadeImg", "./data/image/FadeImg.png");	//�t�F�[�h�p���摜
		DG::Image_Create("FlashImg", "./data/image/FlashImg.png");	//�t���b�V���p���摜

		img.SkyImageCreate();
		img.WallImageCreate(imgNum, mapData);

		//�t�F�[�h�̐ݒ�
		ML::Box2D fadesrc(0, 0, ge->screenWidth, ge->screenHeight);
		fade.ImageSet(PositionI(0, 0), "FadeImg", fadesrc);		//�t�F�[�h�摜��ݒ�
		fade.FadeSwitch(true, 60);								//30�t���[���Ńt�F�[�h�C������

		//�}�b�v��������������
		mapManager.WallInitialize(Underground, toB, toS, MapLength, mapOrder);

		//�J����
		for (int i = 0; i < 2; ++i)
		{
			//���������
			back[i].Initialize(0, 0);
			//�J������������
			camData[i].camera.InitializeCamera();
			camData[i].camera.SetCPos(Position(50.f, MapLength * -360.f));
			camData[i].camera.SetViewPort(180, 0, 360, 405);
			camData[i].camera.SetExcursion(0.f, MapLength * -360.f, 460.f, 0.f);
			camData[i].SetViewCamera(Position(180, 0), 1.f);
			camData[i].SetGameCamera(Position(50.f, MapLength * -360.f), 1.f);
		}

		//�v���C���[��
		playerNum = 1;

		endMove = false;

		actTask = Task_Non;		//�ŏ��̃^�X�N�͖���
		nextTask = Task_Title;	//���̃^�X�N
	}

	//------------------------------------------------------------------------------------------------
	//�I������
	void Finalize()
	{
		DI::GPad_Erase("P1");
		DI::GPad_Erase("P2");

		DG::Image_Erase("Back");
		DG::Image_Erase("FadeImg");
		DG::Image_Erase("Flashimg");
		img.SkyImageErase();
		img.WallImageErase(imgNum);
	}

	//------------------------------------------------------------------------------------------------
	//�X�V����
	void Update()
	{
		if (playerNum <= 0 || playerNum > 2)
			exit(0);

		in[0] = DI::GPad_GetState("P1");
		in[1] = DI::GPad_GetState("P2");

		if (actTask != nextTask)
		{
			//�I������
			switch (actTask)
			{
			case Task_Title:
				tm.Finalize();

			case Task_Game:
				gm.Finalize();
				break;
			}
			
			//���݂̃^�X�N�Ɏ��̃^�X�N����
			actTask = nextTask;

			//����������
			switch (actTask)
			{
			case Task_Title:
				tm.Initialize(MapLength);
				break;
			
			case Task_Game:
				gm.Initialize(MapLength);
				mapManager.WallInitialize(Underground, toB, toS, MapLength, mapOrder);
				break;
			}
		}
		//�X�V����
		switch (actTask)
		{
		case Task_Title:
			nextTask = tm.Update(MapLength);
			break;

		case Task_Game:
			nextTask = gm.Update(mapManager, MapLength, mapOrder, fade);
			break;
		}

		//�J�����̓���ƕǂ̍X�V
		bool endCameraMove;
		for (int i = 0; i < playerNum; ++i)
		{
			endCameraMove = camData[i].MoveCamera();
			//�󂪃J������ǔ�
			back[i].PosTracking(camData[i].camera.pos.y);

			//�ǂ̍X�V
			mapManager.WallUpdate(MapLength, mapOrder, camData[i]);
		}
		mapManager.ResetUpdate(mapOrder, MapLength);

		endMove = fade.Update() && endCameraMove;
	}

	//------------------------------------------------------------------------------------------------
	//�`�揈��
	void Render()
	{
		//�w�i
		{
			ML::Box2D draw(0, 0, ge->screenWidth, ge->screenHeight);
			ML::Box2D src(0, 0, ge->screenWidth, ge->screenHeight);
			DG::Image_Draw("Back", draw, src);
		}

		for (int i = 0; i < playerNum; ++i)
		{
			//��
			back[i].Render(camData[i].camera);
			
			//��
			mapManager.WallRender(imgNum, MapLength, mapOrder, mapData, camData[i].camera, false);

			//�^�C�g��
			if (actTask == Task_Title)
				tm.Render(MapLength, i);

			//���P�b�g
			if (actTask == Task_Game)
			{
				gm.RenderRocket(i);
			}

			//���P�b�g����O�ɂ��鑕��
			mapManager.WallRender(imgNum, MapLength, mapOrder, mapData, camData[i].camera, true);
		}

		//�S��UI
		if (actTask == Task_Game)
			gm.RenderStageUI();

		for (int i = 0; i < playerNum; ++i)
		{
			//UI
			if (actTask == Task_Game)
				gm.RenderUI(i);
		}

		//�J�E���g�_�E���ƃ��b�Z�[�W�\��
		if (actTask == Task_Game)
			gm.RenderCount();

		//�t�F�[�h
		fade.Render();

		if (actTask == Task_Game)
			gm.RenderResult();
	}
};