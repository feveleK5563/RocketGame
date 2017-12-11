#pragma once
#include "Camera.h"
#include "Rocket.h"
#include "Fade.h"

//�}�b�v�̔ԍ����i�[
//�}�b�v�̎�ނ����쐬���ĂˁI�I�I
struct MapData
{
	string		chip;		//�`�b�v�ԍ�
	MapData() : chip(""){}
};

//-------------------------------------------------------------------------------------------------

//�}�b�v�̕��я��Ɠ����蔻��f�[�^�����񂽂炩�񂽂�
//�}�b�v�������쐬���ĂˁI�I�I
struct MapOrder
{
	int		id;			//�\���摜�ԍ�
	int		height;		//����
	int		time;		//����
	float	visible;	//����

	bool	endUpdate;	//�X�V���I�������ۂ�

	MapOrder() : id(0), height(0), time(0), endUpdate(false) {};

	//�}�b�v�̏������������I
	void MapInitializeOne(int num, int i)
	{
		id = num;
		height = i;
		time = 0;
		visible = 1.f;
		endUpdate = false;
	}

	//�}�b�v���������A�����_�����������I
	//0��1�͎蓮�ŏ�����
	void MapInitialize(const int Underground, const int toB, const int toS, const int MapLength,
						int underId, int twoUnderId, int i)
	{
		height = i;
		endUpdate = false;
		switch (underId)
		{
			//�����������n���X�e�[�W����������
		case 1:
			if (i < Underground - 1)
				id = rand() % 2 + 2;
			else if (i < Underground)
				id = 1;
			else
				id = 10;
			break;

		case 2:
			if (i < Underground - 1)
				id = (rand() % 2 + 1) * 2 + 2;
			else
				id = 8;
			break;

		case 3:
			if (i < Underground - 1)
				id = (rand() % 2 + 1) * 2 + 3;
			else
				id = 9;
			break;

		case 4:
			if (i < Underground - 1)
			{
				if (twoUnderId != 4)
					id = rand() % 3 * 2 + 4;
				else
					id = rand() % 2 * 2 + 6;
			}
			else
				id = 8;
			break;

		case 5:
			if (i < Underground - 1)
			{
				if (twoUnderId != 5)
					id = rand() % 3 * 2 + 5;
				else
					id = rand() % 2 * 2 + 7;
			}
			else
				id = 9;
			break;

		case 6:
			if (i < Underground - 1)
				id = 5;
			else
				id = 9;
			break;

		case 7:
			if (i < Underground - 1)
				id = 4;
			else
				id = 8;
			break;

		case 8:
		case 9:
			if (i < Underground - 1)
				id = rand() % 3 + 1;
			else if (i < Underground)
				id = 1;
			else
				id = 10;
			break;
			//��������������������

			//�����������r���X�e�[�W����������
		case 10:
			id = rand() % 3 + 11;
			break;

		case 11:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 2 + 14;
			else
				id = 17;
			break;

		case 12:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 3 + 14;
			else
				id = 17;
			break;

		case 13:
			if (!(i < toB - 1) || rand() % 2)
				id = rand() % 2 + 15;
			else
				id = 17;
			break;

		case 14:
			if (i < toB - 1)
				id = (rand() % 2 * 3) + 14;
			else if (i < toB)
				id = 14;
			else
				id = 18;
			break;

		case 15:
			if (i < toB - 1)
				id = (rand() % 2 * 2) + 15;
			else if (i < toB)
				id = 15;
			else
				id = 18;
			break;

		case 16:
			if (i < toB - 1)
				id = rand() % 2 + 16;
			else if (i < toB)
				id = 16;
			else
				id = 18;
			break;

		case 17:
			if (i < toB - 1)
				id = rand() % 3 + 11;
			else
				id = rand() % 3 + 14;
			break;
			//��������������������

			//�Z�Z�Z�Z�Z��X�e�[�W�Z�Z�Z�Z�Z
		case 18:
			id = 19;
			break;

		case 19:
			if (i < toS - 2)
			{
				if (rand() % 2)
				{
					if (twoUnderId != 19)
						id = (rand() % 2 * 5) + 19;
					else
						id = 24;
				}
				else
				{
					id = rand() % 2 + 20;
				}
			}
			else if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 20:
			if (i < toS - 2)
				id = 22;
			else
				id = 30;
			break;

		case 21:
			if (i < toS - 2)
				id = 23;
			else
				id = 28;
			break;

		case 22:
			if (i < toS - 2 && twoUnderId != 22)
				id = (rand() % 2 * 8) + 22;
			else
				id = 30;
			break;

		case 23:
			if (i < toS - 2 && twoUnderId != 23)
				id = (rand() % 2 * 5) + 23;
			else
				id = 28;
			break;

		case 24:
			id = 25;
			break;

		case 25:
			if (i < toS - 2)
			{
				if (int num = rand() % 3)
				{
					if (num - 1)
						id = (rand() % 2 * 2) + 27;
					else
						id = (rand() % 2 * 3) + 31;
				}
				else
				{
					if (twoUnderId != 25)
						id = rand() % 2 + 25;
					else
						id = 26;
				}
			}
			else
				id = 26;
			break;

		case 26:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 27:
			if (i < toS - 2)
				id = 23;
			else
				id = 28;
			break;

		case 28:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 29:
			if (i < toS - 2)
				id = 22;
			else
				id = 30;
			break;

		case 30:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 31:
		case 32:
			if (id < toS - 2 && twoUnderId != 32)
				id = rand() % 2 + 32;
			else
				id = 33;
			break;

		case 33:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 34:
		case 35:
			if (id < toS - 2 && twoUnderId != 35)
				id = rand() % 2 + 35;
			else
				id = 36;
			break;

		case 36:
			if (i < toS - 1)
				id = 19;
			else
				id = 37;
			break;

		case 37:
			id = 39;
			break;
			//�Z�Z�Z�Z�Z�Z�Z�Z�Z�Z

			//�����������F���X�e�[�W����������
		case 39:
			if (i < MapLength - 1)
				id = 39;
			else
				id = 38;
			break;

		case 38:
			break;
			//��������������������

		}
	}

	//�}�b�v���X�V�����I
	void MapUpdate()
	{
		if (endUpdate)
			return;

		++time;
		if (id <= 9)
		{
			if ((time / 60) % 2)
				visible -= 1.f;
			else
				visible += 1.f;
		}
		endUpdate = true;
	}

	//�ǂƃA�j���[�V������\�������I
	void WallRender(const int imgNum, Camera& camera, const MapData *mapdata, bool rktSide)
	{
		int setposY = (height + 1) * -360;

		if (id >= imgNum)
			return;
		ML::Box2D src;
		ML::Box2D draw;
		
		if (!rktSide)
		{
			//��
			src = ML::Box2D(0, 0, 460, 360);
			draw = ML::Box2D(0, setposY, 460, 360);
			camera.Image_Draw(mapdata[id].chip, draw, src);

			//�A�j���[�V�����摜
			switch (id)
			{
			case 0:
			case 1:
				for (int i = 0; i < 2; ++i)
				{
					src = ML::Box2D(20 * i, 0, 20, 20);
					draw = ML::Box2D(70 + 300 * i, setposY + 50, 20, 20);
					camera.Image_Draw("RedLight", draw, src);
					src = ML::Box2D(20 * i, 20, 20, 20);
					camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				}
				break;

			case 2:
			case 4:
			case 8:
				src = ML::Box2D(0, 0, 20, 20);
				draw = ML::Box2D(70, setposY + 100, 20, 20);
				camera.Image_Draw("RedLight", draw, src);
				src = ML::Box2D(0, 20, 20, 20);
				camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				break;

			case 3:
			case 5:
			case 9:
				src = ML::Box2D(20, 0, 20, 20);
				draw = ML::Box2D(370, setposY + 100, 20, 20);
				camera.Image_Draw("RedLight", draw, src);
				src = ML::Box2D(20, 20, 20, 20);
				camera.Image_Draw("RedLight", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));
				break;
			}
			return;
		}

		switch (id)
		{
		case 10:
			src = ML::Box2D(0, 0, 38, 120);
			draw = ML::Box2D(385, setposY + 20, 38, 120);
			camera.Image_Draw("Umiyama", draw, src);
			break;
		}
	}

	//�ǂƂ̓����蔻��������I
	//�����F���P�b�g���A�Ώۂ̃Z���T�[�A�Ζʂ̃X�^�[�g�ʒu�A�I���ʒu�A�E(��)����(��)��
	void HitFormal(Rocket& rkt, Position& sensor, Position start, Position end, bool LUorRD)
	{
		//����͈͊O�ɂ����珈������
		if (start.x != end.x && (rkt.pos.x + sensor.x < start.x || end.x < rkt.pos.x + sensor.x))
			return;

		//���E��(�X�������݂��Ȃ����ߕʏ���)
		if (!(start.x - end.x))
		{
			if (rkt.pos.y + sensor.y > start.y || end.y > rkt.pos.y + sensor.y)
				return;

			if (LUorRD)
			{
				while (rkt.pos.x + sensor.x < start.x)
				{
					rkt.hit[LorLR] = true;
					rkt.pos.x += 0.1f;
				}
			}
			else
			{
				while (start.x < rkt.pos.x + sensor.x)
				{
					rkt.hit[LorLR] = true;
					rkt.pos.x -= 0.1f;
				}
			}
			return;
		}

		//�����Ȉ����|���������
		start.x += rkt.speed.x;
		end.x += rkt.speed.x;

		//����͈͊O�ɂ����珈������
		if (start.y > end.y)	//�E�オ��
		{
			if (rkt.pos.y + sensor.y > start.y || end.y > rkt.pos.y + sensor.y)
				return;
		}
		else					//���オ��
		{
			if (start.y != end.y && (rkt.pos.y + sensor.y < start.y || end.y < rkt.pos.y + sensor.y))
				return;
		}

		//�X��
		float slope = (start.y - end.y) / (start.x - end.x);
		//�ؕ�
		float intercept = start.y - start.x * slope;

		//�ύX���锻�������I��
		int hitname = 0;
		if (!(start.y - end.y))
			hitname = RorUD;		//�㉺
		else if (start.y > end.y)
		{
			if (LUorRD)
				hitname = UL;	//����
			else
				hitname = DR;	//�E��
		}
		else
		{
			if (LUorRD)
				hitname = UR;	//�E��
			else
				hitname = DL;	//����
		}

		//�ȉ������蔻��
		if (LUorRD)
		{
			while (rkt.pos.y + sensor.y < (rkt.pos.x + sensor.x) * slope + intercept)
			{
				rkt.hit[hitname] = true;
				switch (hitname)
				{
				case RorUD:
					rkt.pos.y += 1.f;
					break;

				case UL:
					rkt.pos.x += 1.f;
					rkt.pos.y += 1.f;
					break;

				case UR:
					rkt.pos.x -= 1.f;
					rkt.pos.y += 1.f;
					break;
				}
			}
		}
		else
		{
			while (rkt.pos.y + sensor.y > (rkt.pos.x + sensor.x) * slope + intercept)
			{
				rkt.hit[hitname] = true;
				switch (hitname)
				{
				case RorUD:
					rkt.pos.y -= 0.2f;
					break;

				case DR:
					rkt.pos.x -= 1.f;
					rkt.pos.y -= 1.f;
					break;

				case DL:
					rkt.pos.x += 1.f;
					rkt.pos.y -= 1.f;
					break;
				}
			}
		}
	}

	//���Ƃ̂����蔻��������I
	void HitMoon(Rocket& rkt, Position sensor, Fade& fade)
	{
		if (((rkt.pos.x + sensor.x) - 230.f) * ((rkt.pos.x + sensor.x) - 230.f) +
			((rkt.pos.y + sensor.y) + 300.f) * ((rkt.pos.y + sensor.y) + 300.f)
			<= (240.f * 240.f))
		{
			rkt.state = Non;
			rkt.explode.SwitchOn(fade);
		}
	}

	//�ǂƃ��P�b�g�̓����蔻��������I
	void NomalWallHit(Rocket& rkt, Position sensor, int lrud, Fade& fade)
	{
		Position start, end;
		//���݂̃}�b�v�`�b�v�ł̓����蔻��
		switch (id)
		{
			//�����������n���X�e�[�W����������
		case 0:
			//�n��
			start = { 70.f, -80.f };
			end = { 390.f, -80.f };
			HitFormal(rkt, sensor, start, end, false);
			//����
			start = { 70.f, -80.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 390.f, -80.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 1:
			//����
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 2:
			//����
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�΂߉E���
			start = { 170.f, -360.f };
			end = { 390.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 3:
			//�E��
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//�΂ߍ����
			start = { 70.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 4:
			//����
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 170.f, 0.f };
			end = { 170.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 5:
			//����
			start = { 290.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 6:
			//�΂ߍ����
			start = { 70.f, 0.f };
			end = { 290.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�΂߉E����
			start = { 170.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 7:
			//�΂ߍ�����
			start = { 70.f, -360.f };
			end = { 290.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�΂߉E���
			start = { 170.f, -360.f };
			end = { 390.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 8:
			//����
			start = { 70.f, 0.f };
			end = { 70.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�΂߉E����
			start = { 170.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 9:
			//�΂ߍ�����
			start = { 70.f, -360.f };
			end = { 290.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E��
			start = { 390.f, 0.f };
			end = { 390.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//��������������������

			//�����������r���X�e�[�W����������
		case 10:
			//�n��
			start = { 50.f, 0.f };
			end = { 70.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			start = { 390.f + rkt.speed.x, 0.f };
			end = { 410.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//����
			start = { 50.f, 0.f };
			end = { 50.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 410.f, 0.f };
			end = { 410.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 11:
			//����
			start = { 80.f, 0.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 320.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 12:
			//����
			start = { 110.f, 0.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 350.f, 0.f };
			end = { 350.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 13:
			//����
			start = { 140.f, 0.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 14:
			//����
			start = { 110.f, 0.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 200.f, 0.f };
			end = { 200.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 15:
			//����
			start = { 190.f, 0.f };
			end = { 190.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 270.f, 0.f };
			end = { 270.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 16:
			//����
			start = { 260.f, 0.f };
			end = { 260.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 350.f, 0.f };
			end = { 350.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 17:
			//����
			start = { 80.f, 0.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//��������������������

			//�Z�Z�Z�Z�Z��X�e�[�W�Z�Z�Z�Z�Z
		case 18:
			//������
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//�����
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E���
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 19:
			//����
			start = { 180.f, 0.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 20:
			//���΂�
			start = { 40.f, -280.f };
			end = { 180.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 140.f, -280.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			//����
			start = { 40.f, -280.f };
			end = { 40.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 140.f, -280.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 21:
			//���΂�
			start = { 180.f, 0.f };
			end = { 320.f, -280.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�΂�
			start = { 280.f, 0.f };
			end = { 420.f, -280.f };
			HitFormal(rkt, sensor, start, end, false);
			//����
			start = { 320.f, -280.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 420.f, -280.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 22:
			//����
			start = { 40.f, 0.f };
			end = { 40.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 140.f, 0.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 23:
			//����
			start = { 320.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 420.f, 0.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 24:
			//������
			start = { 180.f, 0.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 80.f, -240.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//�����
			start = { 80.f, -240.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 280.f, 0.f };
			end = { 280.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -140.f };
			end = { 380.f, -240.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E���
			start = { 380.f, -240.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//������`
			start = { 180.f, -360.f };
			end = { 210.f, -330.f };
			HitFormal(rkt, sensor, start, end, true);
			//���E��`
			start = { 250.f, -330.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//����`
			start = { 210.f, -330.f };
			end = { 250.f, -330.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 25:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//������
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E��
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//�E����
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�E��
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 26:
			//������
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//�����
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E���
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//������`
			start = { 180.f, 0.f };
			end = { 210.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			//���E��`
			start = { 250.f, -30.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//����`
			start = { 210.f, -30.f };
			end = { 250.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 27:
			//���΂�
			start = { 80.f, 0.f };
			end = { 320.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 380.f, 0.f };
			end = { 380.f, -300.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E��΂�
			start = { 380.f, -300.f };
			end = { 420.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			if (lrud >= 2 && rkt.pos.y + sensor.y <= -60.f + rkt.speed.y)
			{
				//����`
				start = { 220.f, -60.f };
				end = { 280.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (rkt.pos.x + sensor.x < 240.f)
			{
				//������`
				start = { 180.f, 0.f };
				end = { 220.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (lrud >= 2)
			{
				//���E��`
				start = { 280.f, 0.f };
				end = { 280.f, -60.f };
				HitFormal(rkt, sensor, start, end, true);
			}
			break;

		case 28:
			//���΂�
			start = { 180.f, -280.f };
			end = { 320.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -280.f };
			end = { 420.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			//����
			start = { 180.f, -280.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 280.f, -280.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 29:
			//����΂�
			start = { 40.f, -360.f };
			end = { 80.f, -300.f };
			HitFormal(rkt, sensor, start, end, false);
			//����
			start = { 80.f, 0.f };
			end = { 80.f, -300.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�΂�
			start = { 140.f, -360.f };
			end = { 380.f, 0.f };
			HitFormal(rkt, sensor, start, end, true);
			if (rkt.pos.y + sensor.y <= -60.f + rkt.speed.y)
			{
				//����`
				start = { 180.f, -60.f };
				end = { 240.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else if (rkt.pos.x + sensor.x > 220.f)
			{
				//���E��`
				start = { 240.f, -60.f };
				end = { 280.f, 0.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			else
			{
				//������`
				start = { 180.f, 0.f };
				end = { 180.f, -60.f };
				HitFormal(rkt, sensor, start, end, false);
			}
			break;

		case 30:
			//���΂�
			start = { 40.f, 0.f };
			end = { 180.f, -280.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�΂�
			start = { 140.f, 0.f };
			end = { 280.f, -280.f };
			HitFormal(rkt, sensor, start, end, false);
			//����
			start = { 180.f, -280.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E��
			start = { 280.f, -280.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 31:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//������
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E����
				start = { 180.f, 0.f };
				end = { 180.f, -130.f };
				HitFormal(rkt, sensor, start, end, false);
				//���E���΂�
				start = { 130.f, -180.f };
				end = { 180.f, -130.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E���
				start = { 130.f, -180.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//�E������
			start = { 280.f, 0.f };
			end = { 280.f, -130.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�����΂�
			start = { 280.f, -130.f };
			end = { 330.f, -180.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�����
			start = { 330.f, -180.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�E��
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 32:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//������
				start = { 80.f, 0.f };
				end = { 80.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E��
				start = { 130.f, 0.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//�E����
			start = { 330.f, 0.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�E��
			start = { 380.f, 0.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 33:
			//������
			start = { 80.f, 0.f };
			end = { 80.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 80.f, -120.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//�����
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 380.f, 0.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -220.f };
			end = { 380.f, -120.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E���
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//������`
			start = { 130.f, 0.f };
			end = { 190.f, -60.f };
			HitFormal(rkt, sensor, start, end, false);
			//���E��`
			start = { 270.f, -60.f };
			end = { 330.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//����`
			start = { 190.f, -60.f };
			end = { 270.f, -60.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 34:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//��������
				start = { 80.f, 0.f };
				end = { 80.f, -130.f };
				HitFormal(rkt, sensor, start, end, true);
				//�������΂�
				start = { 80.f, -130.f };
				end = { 130.f, -180.f };
				HitFormal(rkt, sensor, start, end, true);
				//�������
				start = { 130.f, -180.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E��
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//�E����
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�E����
			start = { 380.f, 0.f };
			end = { 380.f, -130.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�����΂�
			start = { 330.f, -180.f };
			end = { 380.f, -130.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�����
			start = { 330.f, -180.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 35:
			if (rkt.pos.x + sensor.x < 230.f)
			{
				//������
				start = { 130.f, 0.f };
				end = { 130.f, -360.f };
				HitFormal(rkt, sensor, start, end, true);
				//���E��
				start = { 180.f, 0.f };
				end = { 180.f, -360.f };
				HitFormal(rkt, sensor, start, end, false);
				break;
			}
			//�E����
			start = { 280.f, 0.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�E��
			start = { 330.f, 0.f };
			end = { 330.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);

			break;

		case 36:
			//������
			start = { 130.f, 0.f };
			end = { 130.f, -170.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 130.f, -170.f };
			end = { 180.f, -220.f };
			HitFormal(rkt, sensor, start, end, true);
			//�����
			start = { 180.f, -220.f };
			end = { 180.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 330.f, 0.f };
			end = { 330.f, -170.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -220.f };
			end = { 330.f, -170.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E���
			start = { 280.f, -220.f };
			end = { 280.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			//������`
			start = { 180.f, 0.f };
			end = { 210.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			//���E��`
			start = { 250.f, -30.f };
			end = { 280.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//����`
			start = { 210.f, -30.f };
			end = { 250.f, -30.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 37:
			//������
			start = { 180.f, 0.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, true);
			//���΂�
			start = { 80.f, -240.f };
			end = { 180.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//�����
			start = { 80.f, -240.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E����
			start = { 280.f, 0.f };
			end = { 280.f, -140.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�΂�
			start = { 280.f, -140.f };
			end = { 380.f, -240.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E���
			start = { 380.f, -240.f };
			end = { 380.f, -360.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
			//�Z�Z�Z�Z�Z�Z�Z�Z�Z�Z

			//��
		case 38:
			HitMoon(rkt, sensor, fade);
			break;
		}
}
	void UnderWallHit(Rocket& rkt, Position sensor)
	{
		Position start, end;
		//�n�ʔ���
		switch (id)
		{
		case 11:
			//���n��
			start = { 0.f, 0.f };
			end = { 80.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 320.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 12:
			//���n��
			start = { 0.f, 0.f };
			end = { 110.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 350.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 13:
			//���n��
			start = { 0.f, 0.f };
			end = { 140.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 380.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 14:
			//���n��
			start = { 0.f, 0.f };
			end = { 110.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 200.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 15:
			//���n��
			start = { 0.f, 0.f };
			end = { 190.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 270.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 16:
			//���n��
			start = { 0.f, 0.f };
			end = { 260.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 350.f, 0.f };
			end = { 460.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;

		case 37:
			//���n��
			start = { -100.f, 0.f };
			end = { 80.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			//�E�n��
			start = { 380.f, 0.f };
			end = { 560.f, 0.f };
			HitFormal(rkt, sensor, start, end, false);
			break;
		}

	}
	void HighWallHit(Rocket& rkt, Position sensor)
	{
		Position start, end;
		//�V�䔻��
		switch (id)
		{
		case 11:
			//���V��
			start = { 0.f, -360.f };
			end = { 80.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 320.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 12:
			//���V��
			start = { 0.f, -360.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 350.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 13:
			//���V��
			start = { 0.f, -360.f };
			end = { 140.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 380.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 14:
			//���V��
			start = { 0.f, -360.f };
			end = { 110.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 200.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 15:
			//���V��
			start = { 0.f, -360.f };
			end = { 190.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 270.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;

		case 16:
			//���V��
			start = { 0.f, -360.f };
			end = { 260.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			//�E�V��
			start = { 350.f, -360.f };
			end = { 460.f, -360.f };
			HitFormal(rkt, sensor, start, end, true);
			break;
	}
};
};
//-------------------------------------------------------------------------------------------------

//�}�b�v�S�̂̊Ǘ�
struct MapManager
{
	//�}�b�v0�Ԃ�1�Ԃ����蓖�Ă�
	void WallZero(MapOrder* mapOrder)
	{
		mapOrder[0].MapInitializeOne(0, 0);
		mapOrder[1].MapInitializeOne(1, 1);
	}

	//������
	void WallInitialize(const int Underground, const int toB, const int toS,
		const int MapLength, MapOrder* mapOrder)
	{
		WallZero(mapOrder);
		for (int i = 2; i < MapLength; ++i)
		{
			mapOrder[i].MapInitialize(Underground, toB, toS, MapLength,
				mapOrder[i - 1].id, mapOrder[i - 2].id, i);
		}
	}

	//�ǂ̍X�V����
	void WallUpdate(const int MapLength, MapOrder* mapOrder,
					const MoveCameraData camData)
	{
		int checkNum;
		//�X�V
		for (int i = -1; i < 1; ++i)
		{
			checkNum = ((int)camData.camera.pos.y / -360) + i;
			if (checkNum < 0 || MapLength <= checkNum)
				continue;

			mapOrder[checkNum].MapUpdate();
		}
	}

	//�X�V�I����Ԃ�����
	void ResetUpdate(MapOrder* mapOrder, int MapLength)
	{
		for (int i = 0; i < MapLength; ++i)
		{
			mapOrder[i].endUpdate = false;
		}
	}

	//���P�b�g�ƕǂ̓����蔻��
	void WallHit(const int MapLength, MapOrder* mapOrder, Rocket& rkt, Fade& fade)
	{
		for (int lrud = 0; lrud < 6; ++lrud)
		{
			int chipNum = int(rkt.pos.y + rkt.sensor[lrud].y) / -360;
			Position sensor = rkt.sensor[lrud];
			sensor += rkt.speed;
			sensor.y += chipNum * 360.f;

			if (0 <= chipNum && chipNum < MapLength)
				mapOrder[chipNum].NomalWallHit(rkt, sensor, lrud, fade);	//���}�b�v�̓����蔻��

																			//�ȉ��A���E�����蔻��͕s�v�Ȃ̂ł��Ȃ�
			if (lrud < 2)
				continue;

			if (0 <= chipNum - 1)
				mapOrder[chipNum - 1].UnderWallHit(rkt, sensor);	//�����蔻�艺
			if (chipNum + 1 < MapLength)
				mapOrder[chipNum + 1].HighWallHit(rkt, sensor);		//�����蔻���
		}
	}

	//�ǂ̕\��
	void WallRender(const int imgNum, const int MapLength, MapOrder* mapOrder, const MapData* mapData,
		Camera& camera, bool side = false)
	{
		for (int i = -2; i <= 1; ++i)
		{
			int cnum = ((int)camera.pos.y / -360) + i;
			if (cnum < 0 || MapLength <= cnum)
				continue;

			mapOrder[cnum].WallRender(imgNum, camera, mapData, side);
		}
	}
};