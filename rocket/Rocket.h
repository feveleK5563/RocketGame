#pragma once
#include "MyPG.h"
#include "Position.h"
#include "Camera.h"
#include "Fade.h"

//�����A�j���[�V����
class ExplodeAnimation
{
private:
	int time;
	int animation;
	bool onoff;
	bool end;

public:

	//������
	void InitializeExplode()
	{
		time = 0;
		animation = 0;
		onoff = false;
		end = false;
	}

	//�����t���O�𗧂Ă�
	void SwitchOn(Fade& fade)
	{
		if (!onoff)
		{
			onoff = true;
			fade.ImageSet(PositionI(0, 0), "FlashImg", ML::Box2D(0, 0, 720, 405));
			fade.FadeSwitch(true, 30);
		}
	}

	//�X�V
	bool UpdateExplode()
	{
		if (onoff && animation < 11)
		{
			++time;
			animation = time / 5;

			if (animation >= 6)
				end = true;
		}
		return end;
	}

	//�`��
	void RenderExplode(Position pos, Camera& camera)
	{
		if (onoff)
		{
			ML::Box2D src(animation * 200, 0, 200, 200);
			ML::Box2D draw(-100, -100, 200, 200);
			draw.Offset(pos.x, pos.y);
			camera.Image_Draw("Explosion", draw, src);
		}
	}
};

//���A�j���[�V����
class SmokeAnimation
{
private:
	int time;
	Position pos;
	Position speed;

public:
	SmokeAnimation():		//�f�t�H
		time(0),
		pos(Position(0.f, 0.f)),
		speed(Position(0.f, 0.f)){}

	SmokeAnimation(Position rktpos):	//�ĂԂ̂͂�����
		time(40),
		pos(rktpos)
	{
		speed.x = float((rand() % 10) - 5) / 10.f;
		speed.y = float((rand() % 6) - 3) / 10.f;
	}

	//�X�V
	bool UpdateSmoke()
	{
		if (time > 0)
		{
			--time;
			pos += speed;
			return false;
		}
		return true;
	}

	//�`��
	void RenderSmoke(Camera& camera)
	{
		ML::Box2D src(0, 10, 20, 20);
		ML::Box2D draw(-10, -10, 20, 20);
		draw.Offset(pos.x, pos.y);
		DG::Image_Rotation("Jet", ML::ToRadian((float)time), ML::Vec2(10, 10));
		camera.Image_Draw("Jet", draw, src, ML::Color(float(time) / 40.f, 1.f, 1.f, 1.f));
	}
};

//�W�F�b�g���˃A�j���[�V����
class JetAnimation
{
private:
	bool active[8];					//�\���̗L��
	Position pos[8];				//�ʒu
	vector<SmokeAnimation*> smoke;	//��

public:
	//������
	void InitializeJet()
	{
		for (int i = 0; i < 8; ++i)
		{
			pos[i] = Position(0, 0);
			active[i] = false;
		}
	}

	//�\���t���O
	void SetJetAnim(bool onoff)
	{
		active[0] = onoff;
		if (active[0] && (rand() % 3 + 1) % 2)
		{
			smoke.emplace_back(new SmokeAnimation(pos[0]));
		}
	}

	//�A�j���[�V�����X�V
	void UpdateJet(Position rktpos, Position rktspd)
	{
		for (int i = 0; i < 8; ++i)
		{
			pos[i].x = rktpos.x - ((rktspd.x * i) / 10.f);
			pos[i].y = (rktpos.y + 10.f) - (rktspd.y / 2.f) * i;

			if (i > 0 && pos[i].y < pos[i - 1].y)
				pos[i].y = pos[i - 1].y;
		}

		for (int i = 7; i > 0; --i)
		{
			active[i] = active[i - 1];
		}

		//��
		int size = (int)smoke.size();
		for (int i = 0; i < size;)
		{
			if (smoke[i]->UpdateSmoke())
			{
				delete smoke[i];
				smoke[i] = smoke.back();
				smoke.pop_back();
				--size;
			}
			else
			{
				++i;
			}
		}
		smoke.shrink_to_fit();
	}

	//�\��
	void RenderJet(Camera& camera)
	{
		for (int i = 0; i < (int)smoke.size(); ++i)
			smoke[i]->RenderSmoke(camera);

		for (int i = 7; i >= 0; --i)
		{
			if (!active[i])
				continue;

			ML::Box2D src(i * 10, 0, 10, 10);
			ML::Box2D draw(-5, -5, 10, 10);
			draw.Offset(pos[i].x, pos[i].y);
			DG::Image_Rotation("Jet", ML::ToRadian(float(rand() / 360)), ML::Vec2(7, 5));
			camera.Image_Draw("Jet", draw, src);
		}
	}

	//�����������(�Q�[���N���A���ɌĂяo��)
	void EndJet()
	{
		smoke.clear();
		smoke.shrink_to_fit();
	}
};


enum HitSensor
{
	LorLR,		//���E
	RorUD,		//�㉺
	UL,			//�΂ߍ���
	UR,			//�΂߉E��
	DL,			//�΂ߍ���
	DR,			//�΂߉E��
};
enum RocketState
{
	Non,		//����s��
	Empty,		//�G�l���M�[�؂�
	Nomal,		//�ʏ�(�G�l���M�[�L)
	Spin,		//�X�s��
	Turbo,		//�^�[�{
	Wait,		//�ҋ@
};
class Rocket
{
public:
	Position	pos;		//���W
	Position	speed;		//���x
	RocketState state;		//���P�b�g�̏��
	int showEnergy,		//�G�l���M�[�\��
		showTurboGage;	//�^�[�{�Q�[�W�\��

	Position	sensor[6];	//�Փ˔���Z���T�[
	ML::Box2D hitbase;		//�����蔻���`

	bool		hit[6];		//���˕���

	Rocket(): pos(Position()), speed(Position()), state(Non),
			  showEnergy(0), showTurboGage(0) {}

	const int EnergyMax = 1000; //�G�l���M�[���
	const int TurboMax = 1000;	//�^�[�{���
	int time[5];				//���ԂƂ��v��(�e���)

	ExplodeAnimation explode;	//�����A�j���[�V����

private:
	int rktanim;			//�A�j���[�V�����摜�ԍ�
	ML::Box2D rktsrc[8];	//�A�j���[�V�����摜

	bool noRender;				//�摜�\�������Ȃ�

	JetAnimation jetAnim;		//�W�F�b�g���˃A�j���[�V����

	//���P�b�g�̍��W�ړ�
	void MoveRocket()
	{
		pos += speed;
	}

	//�Z���T�[�ʒu��ݒ�
	void SetSensor()
	{
		sensor[LorLR]  = { -9.f,   0.f };
		sensor[RorUD]  = {  8.f,   0.f };
		sensor[UL]	   = { -9.f, -14.f };
		sensor[UR]	   = {  8.f, -14.f };
		sensor[DL]	   = { -9.f,  12.f };
		sensor[DR]	   = {  8.f,  12.f };
		hitbase = { 0, 0, 18, 32 };
	}

	//�Z���T�[�����ׂăI�t
	void HitOff()
	{
		for (int i = 0; i < 6; ++i)
		{
			hit[i] = false;
		}
	}

	//�J�����̔���
	//�����F�J�������AX�����̔����AY�����̔����A
	//�@�@�@�����̑傫���A�����̔��������𔽓]
	void RecoilXY(Camera& camera, bool xon, bool yon,
				  float powor = 3.f, bool turn = false)
	{
		if (xon)
		{
			if (speed.x > 0.f || (turn && speed.x < 0.f))
				camera.view.x -= powor;
			else if (speed.x < 0.f || (turn && speed.x > 0.f))
				camera.view.x += powor;
		}

		if (yon)
		{
			if (speed.y > 0.f || (turn && speed.y < 0.f))
				camera.view.y -= powor;
			else if (speed.y < 0.f || (turn && speed.y > 0.f))
				camera.view.y += powor;
		}
	}

	//���P�b�g�̈ړ��͕ύX�ƃJ�����ւ̔���
	void ChangeSpeed(Camera& camera)
	{
		if (hit[LorLR])		//���E
		{
			if (state < Spin
				&& fabsf(speed.x) > 0.25f)
				speed.x *= -0.5f;
			else
				speed.x = 0.f;

			RecoilXY(camera, true, false);
		}

		if (hit[RorUD])		//�㉺
		{
			if (fabs(speed.y) > 0.2f)
				speed.y *= -0.25f;
			else
				speed.y = 0.f;

			RecoilXY(camera, false, true);
		}

		//�X�s�����ƃ^�[�{���͔����Ȃ�
		if (state >= Spin)
		{
			if (hit[LorLR] || state == Turbo)	//���E�̕ǂɐڐG���������
			{
				speed.y = -15.f;
				RecoilXY(camera, false, true, 8.f, true);
				if (time[Turbo] < TurboMax)
					time[Turbo] += 2;
			}
			else if (hit[UL] || hit[UR]) //�΂߂̕ǂɐڐG������傫������
			{
				speed.y = -17.f;
				RecoilXY(camera, false, true, 10.f, true);
				if (time[Turbo] < TurboMax)
					time[Turbo] += 10;
			}
			HitOff();
		}

		if (hit[UL])		//�΂ߍ���
		{
			if (speed.x < 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += -1.f * speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		if (hit[DR])		//�΂߉E��
		{
			if (speed.x > 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x -= speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		if (hit[UR])	//�΂߉E��
		{
			if (speed.x > 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += speed.y * 0.3f;
				speed.y *= 0.3f;
			}
			
			RecoilXY(camera, true, true);
		}

		if (hit[DL])	//�΂ߍ���
		{
			if (speed.x < 0.f)
			{
				speed.x *= -0.5f;
			}
			else if (fabsf(speed.x) < fabsf(speed.y))
			{
				speed.x += speed.y * 0.3f;
				speed.y *= 0.3f;
			}

			RecoilXY(camera, true, true);
		}

		HitOff(); //������I�t
	}

	//�A�j���[�V����
	void Animation()
	{
		if (state < Spin || state == Wait)
			rktanim += int(speed.x);
		else
			rktanim += 25;
		
		if (rktanim >= 80)
			rktanim = 0;
		if (rktanim < 0)
			rktanim = 79;
	}

	//������Ƃ������𑝂₷
	void AddNumberSlow(int& addNum, int& copyNum, const int Max)
	{
		if (copyNum > Max)
			copyNum = Max;

		if (addNum == copyNum)
			return;

		if (addNum < copyNum)
		{
			addNum += 10;
			if (addNum > copyNum)
				addNum = copyNum;
			return;
		}
		
		addNum -= 10;
		if (addNum < copyNum)
			addNum = copyNum;
		if (addNum < 0)
			addNum = 0;
	}

	//��ԊǗ�
	void ChangeState(const DI::VGamePad& GP, bool canMove)
	{
		switch (state)
		{
		case Non:		//�s���s��
			break;

		case Empty:		//�G�l���M�[�؂�
			if (time[Empty] > 240)
			{
				state = Nomal;
				time[Empty] = 0;
				time[Nomal] = EnergyMax;
			}
			else
			{
				/**/++time[Empty];/*
				time[Empty] = 241;/**/
			}
			break;

		case Nomal:		//�ʏ���
			//�G�l���M�[����
			if (!canMove)
				break;

			if (GP.R1.on)
			{
				--time[Nomal];
				if (time[Turbo] < TurboMax)
					++time[Turbo];
			}
			else if (time[Nomal] < EnergyMax)
			{
				if (fabsf(speed.y) <= 0.2f)
					time[Nomal] += 2;
				else
					++time[Nomal];
			}

			//�X�s���ڍs
			if (time[Nomal] > 20 && GP.B2.down && fabsf(speed.y) > 0.f)
			{
				state = Spin;
				time[Nomal] -= 30;
				break;
			}

			//�G�l���M�[�؂�ڍs
			if (time[Nomal] <= 0)
				state = Empty;

			//�^�[�{�ڍs
			if (GP.B1.down &&
				time[Turbo] >= TurboMax)
			{
				state = Turbo;
			}
			break;

		case Spin:		//�X�s�����
			if (time[Spin] < 15)
			{
				++time[Spin];
				break;
			}
			time[Spin] = 0;
			state = Nomal;
			break;

		case Turbo:		//�^�[�{���
			if (time[Turbo] <= 0)
			{
				state = Nomal;
				time[Turbo] = 0;
			}
			time[Turbo] -= 10;
			break;
		}

		//�\���p
		AddNumberSlow(showEnergy, time[Nomal], EnergyMax);
		AddNumberSlow(showTurboGage, time[Turbo], TurboMax);
	}

public:
	//������
	//�����F���P�b�g�̏����ʒu(Position), ���P�b�g�̐F���(int)
	void InitializeRocket(Position cpos, int rktcolor)
	{
		speed = { 0.f, 0.f };
		pos = cpos;
		SetSensor();
		HitOff();
		state = Non;
		for (int i = 0; i < 5; ++i)
		{
			time[i] = 0;
		}
		time[Nomal] = EnergyMax;
		showEnergy = 0;
		showTurboGage = 0;

		rktanim = 0;
		for (int i = 0; i < 8; ++i)
		{
			rktsrc[i] = ML::Box2D(i * 30, rktcolor * 38, 30, 38);
		}

		jetAnim.InitializeJet();
		explode.InitializeExplode();
		noRender = false;
	}

	//�ʏ퓮��
	void JetRocket(const DI::VGamePad& pad, bool canMove)
	{
		if (state == Non)
		{
			jetAnim.SetJetAnim(false);
			return;
		}

		//�㉺�^��
		if (canMove &&
			(state == Nomal || state == Spin) && 
			pad.R1.on && speed.y > -10.f)
		{
			speed.y -= 0.2f;			//�����Ă���Ԃ͏㏸����
		}
		else if (state == Turbo && speed.y > -20.f)
		{
			speed.y -= 0.3f;			//�^�[�{���͋}����
		}
		else if (speed.y < 10.f)
		{
			speed.y += 0.2f;		//�����Ă���Ԃ͉��~����
		}
		jetAnim.SetJetAnim(canMove &&
							(pad.R1.on && (state == Nomal || state == Spin))||
							speed.y <= -10.f ||
							state == Turbo);

		//���E�ړ�
		if (fabsf(speed.y) > 0.2f && canMove)
		{
			if (pad.LStick.R.on)
			{
				if (speed.x < 4.f)
					speed.x += 0.15f;		//�E������
				return;
			}
			if (pad.LStick.L.on)
			{
				if (speed.x > -4.f)
					speed.x -= 0.15f;		//��������
				return;
			}
		}
		//���E���x���҂�����0�ɂ���
		if (speed.x > 0.f)
		{
			speed.x -= 0.05f;
			if (speed.x < 0.f)
				speed.x = 0.f;
			return;
		}
		if (speed.x < 0.f)
		{
			speed.x += 0.05f;
			if (speed.x > 0.f)
				speed.x = 0.f;
			return;
		}
	}

	//�X�V
	void UpdateRocket(Camera& camera, DI::VGamePad GP, bool toRocketHit, bool canMove)
	{
		Animation();
		if (state != Non)
		{
			if (!toRocketHit)
				MoveRocket();
			ChangeSpeed(camera);
		}
		ChangeState(GP, canMove);
		
		jetAnim.UpdateJet(pos, speed);
		noRender = explode.UpdateExplode();
	}

	//X���������[�v
	//�����F���[��X���W, �E�[��X���W
	void LoopPositionX(float L, float R)
	{
		if (L > pos.x)
			pos.x = R;

		if (pos.x > R)
			pos.x = L;
	}

	//���P�b�g�̕`��
	void RenderRocket(Camera& camera)
	{
		if (!noRender)
		{
			jetAnim.RenderJet(camera);

			ML::Box2D src = rktsrc[rktanim / 10];
			ML::Box2D draw(-15, -26, 30, 38);
			draw.Offset(pos.x, pos.y);
			camera.Image_Draw("Rocket", draw, src);
		}

		explode.RenderExplode(pos, camera);
	}

	//���P�b�g�̏I������
	void EndRocket()
	{
		jetAnim.EndJet();
	}
};

//��̃��P�b�g�̏d�Ȃ��Ԃ��������ړ��ʂ𔽓]����
void ToRocketHit(Rocket& rocket1, Rocket& rocket2)
{
	Rocket* rkt[2] = { &rocket1, &rocket2 };
	Position spd[2] = { rkt[0]->speed, rkt[1]->speed };

	ML::Box2D hb[2] = { rkt[0]->hitbase.OffsetCopy(rkt[0]->pos.x, rkt[0]->pos.y),
					    rkt[1]->hitbase.OffsetCopy(rkt[1]->pos.x, rkt[1]->pos.y) };
	//������s���O����d�Ȃ��Ă������������
	while (hb[0].Hit(hb[1]))
	{
		for (int i = 0; i < 2; ++i)
		{
			if (rkt[i]->pos.x > rkt[!i]->pos.x)
			{
				rkt[i]->pos.x += 1.f;
			}
			else
			{
				rkt[i]->pos.x -= 1.f;
			}
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
	}

	//X�������蔻��
	while (spd[0].x != 0.f || spd[1].x != 0.f)
	{
		float posX[2] = { rkt[0]->pos.x, rkt[1]->pos.x };
		for (int i = 0; i < 2; ++i)
		{
			if(spd[i].x >= 1.f)			{ rkt[i]->pos.x += 1.f; spd[i].x -= 1.f; }
			else if (spd[i].x <= -1.f)	{ rkt[i]->pos.x -= 1.f; spd[i].x += 1.f; }
			else						{ rkt[i]->pos.x += spd[i].x; spd[i].x = 0.f; }
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
		if (hb[0].Hit(hb[1]))
		{
			for (int i = 0; i < 2; ++i)
			{
				rkt[i]->pos.x = posX[i];
				rkt[!i]->speed.x -= (rkt[i]->speed.x * 2) / 3;
				rkt[i]->hit[LorLR] = true;
			}
			break;
		}
	}

	//Y�������蔻��
	while (spd[0].y != 0.f || spd[1].y != 0.f)
	{
		float posY[2] = { rkt[0]->pos.y, rkt[1]->pos.y };
		for (int i = 0; i < 2; ++i)
		{
			if (spd[i].y >= 1.f) { rkt[i]->pos.y += 1.f; spd[i].y -= 1.f; }
			else if (spd[i].y <= -1.f) { rkt[i]->pos.y -= 1.f; spd[i].y += 1.f; }
			else { rkt[i]->pos.y += spd[i].y; spd[i].y = 0.f; }
			hb[i] = rkt[i]->hitbase.OffsetCopy(rkt[i]->pos.x, rkt[i]->pos.y);
		}
		if (hb[0].Hit(hb[1]))
		{
			for (int i = 0; i < 2; ++i)
			{
				rkt[i]->speed.y = 0.f;
				rkt[i]->hit[LorLR] = true;
			}
			break;
		}
	}
}