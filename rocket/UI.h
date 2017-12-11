#pragma once
#include "MyPG.h"
#include "Camera.h"
#include "Position.h"
#include "Rocket.h"

//�Q�[�W
class Gauge
{
private:

	PositionI posE;
	PositionI posT;
	float r, g, b;
	int beforeEGauge;

	bool max;
	int time;
	float animation;

public:

	//������
	void Initialize(PositionI posEG, PositionI posTG)
	{
		posE = posEG;
		posT = posTG;
		r = 255.f;
		g = 0.f;
		b = 0.f;
		beforeEGauge = 0;
		max = false;
		time = 0;
		animation = 40.f;
	}

	//�G�l���M�[�Q�[�W�̐F�ω�
	void ColorTransition(const Rocket& rkt)
	{
		if (beforeEGauge > rkt.showEnergy)
		{
			if (b > 0.f)
				b -= beforeEGauge - rkt.showEnergy;
			else if (r < 255.f)
				r += beforeEGauge - rkt.showEnergy;
			else if (g > 0.f)
				g -= beforeEGauge - rkt.showEnergy;
		}

		if (beforeEGauge < rkt.showEnergy)
		{
			if (g < 255.f)
				g += rkt.showEnergy - beforeEGauge;
			else if (r > 0.f)
				r -= rkt.showEnergy - beforeEGauge;
			else if (b < 255.f)
				b += rkt.showEnergy - beforeEGauge;
		}

		beforeEGauge = rkt.showEnergy;
	}

	//�^�[�{�Q�[�W�̐F�̕ω�
	void ColorAnimation(const Rocket& rkt)
	{
		if (rkt.showTurboGage >= rkt.TurboMax)
		{
			max = true;
			++time;
			if ((time / 30) % 2)
				animation -= 0.6f;
			else
				animation += 0.6f;

			if (rkt.state == Turbo)
			{
				animation = 40.f;
				max = false;
			}

			return;
		}
		else if (rkt.state == Turbo)
		{
			++time;
			if ((time / 15) % 2)
				animation -= 0.75f;
			else
				animation += 0.75f;

			return;
		}
		animation = 40.f;
	}

	//�X�V
	void Update(const Rocket& rkt)
	{
		ColorTransition(rkt);
		ColorAnimation(rkt);
	}

	//�`��
	void Render(const Rocket& rkt)
	{
		//�G�l���M�[�Q�[�W
		int miniE = 3;
		{//�w�i
			ML::Box2D src(0, 0, 100, 80);
			ML::Box2D draw(0, 0, 100 / miniE, 1000 / miniE);
			draw.Offset(posE.x, posE.y);
			DG::Image_Draw("Gauge", draw, src);
		//�Q�[�W
			src.x += 100;
			draw = ML::Box2D(0, 1000 / miniE, 100 / miniE, rkt.showEnergy / miniE);
			draw.y -= rkt.showEnergy / miniE;
			draw.Offset(posE.x, posE.y);
			DG::Image_Draw("Gauge", draw, src, 
						   ML::Color(0.8f, r / 255.f, g / 255.f, b / 255.f));
		//��ɔ킹��
			src.x += 100;
			draw = ML::Box2D(0, 0, 100 / miniE, 1000 / miniE);
			draw.Offset(posE.x, posE.y);
			DG::Image_Draw("Gauge", draw, src);
		}
		{//��g�Ɖ��g
			ML::Box2D src(0, 80, 100, 40);
			ML::Box2D draw(0, -5, 100 / miniE, 40 / miniE);
			draw.Offset(posE.x, posE.y);
			DG::Image_Draw("Gauge", draw, src);

			src.y += 40;
			draw = ML::Box2D(0, 985 / miniE, 100 / miniE, 40 / miniE);
			draw.Offset(posE.x, posE.y);
			DG::Image_Draw("Gauge", draw, src);
		}

		//�^�[�{�Q�[�W
		int miniT = 4;
		{//�w�i
			ML::Box2D src(0, 0, 100, 80);
			ML::Box2D draw(0, 0, 100 / miniT, 1000 / miniT);
			draw.Offset(posT.x, posT.y);
			DG::Image_Draw("Gauge", draw, src);
			//�Q�[�W
			src.x += 100;
			draw = ML::Box2D(0, 1000 / miniT, 100 / miniT, rkt.showTurboGage / miniT);
			draw.Offset(posT.x, posT.y);
			draw.y -= rkt.showTurboGage / miniT;
			if (max)
				DG::Image_Draw("Gauge", draw, src, ML::Color(animation / 60.f, 1.f, 0.8f, 0.f));
			else if (rkt.state == Turbo)
				DG::Image_Draw("Gauge", draw, src, ML::Color(animation / 60.f, 1.f, 0.2f, 0.2f));
			else
				DG::Image_Draw("Gauge", draw, src, ML::Color(0.8f, 1.f, 0.5f, 0.f));
			//��ɔ킹��
			src.x += 100;
			draw = ML::Box2D(0, 0, 100 / miniT, 1000 / miniT);
			draw.Offset(posT.x, posT.y);
			DG::Image_Draw("Gauge", draw, src);
		}
		{//��g�Ɖ��g
			ML::Box2D src(100, 80, 100, 40);
			ML::Box2D draw(0, -5, 100 / miniT, 40 / miniT);
			draw.Offset(posT.x, posT.y);
			DG::Image_Draw("Gauge", draw, src);

			src.y += 40;
			draw = ML::Box2D(0, 985 / miniT, 100 / miniT, 40 / miniT);
			draw.Offset(posT.x, posT.y);
			DG::Image_Draw("Gauge", draw, src);
		}
	}
};

//-----------------------------------------------------------------------------
//��ʌ���
class ScreenEffect
{
private:
	enum EffectName
	{
		SpeedEffect,
		DangerEffect,
		EmptyEffect,
	};
	bool effect[3];
	unsigned int time;
	int ePercent;
	float visible;

public:
	//������
	void Initialize()
	{
		for (int i = 0; i < 3; ++i)
		{
			effect[i] = false;
		}
		time = 0;
		visible = 0.f;
		ePercent = 0;
	}

	//�X�V(�G�t�F�N�g�̍X�V)
	void Update(const Rocket& rkt)
	{
		++time;
		if ((time / 30) % 2)
			visible -= 2.f;
		else
			visible += 2.f;

		ePercent = (rkt.time[Nomal] * 100) / rkt.EnergyMax;

		if (rkt.speed.y < -13.f)
			effect[SpeedEffect] = true;
		else
			effect[SpeedEffect] = false;

		if (ePercent <= 25 && rkt.state != Empty)
			effect[DangerEffect] = true;
		else
			effect[DangerEffect] = false;

		if (rkt.state == Empty)
			effect[EmptyEffect] = true;
		else
			effect[EmptyEffect] = false;

	}

	//�`��
	void Render(const Camera& camera)
	{
		ML::Box2D src(0, 0, 360, 405);
		ML::Box2D draw((int)camera.view.x, (int)camera.view.y, 360, 405);

		if (effect[SpeedEffect])
			DG::Image_Draw("Speed" + to_string(time % 4), draw, src);

		if (effect[DangerEffect])
			DG::Image_Draw("Danger", draw, src, ML::Color(visible / 60.f, 1.f, 1.f, 1.f));

		if (effect[EmptyEffect])
			DG::Image_Draw("Empty", draw, src);

	}
};

//-----------------------------------------------------------------------------
//�~�j�}�b�v�p�v���C���[
class MiniPlayer
{
private:
	PositionI pos;
	float playerHeight;

	ML::Color color;
	float visible;
	unsigned int time;

public:
	//������
	void Initialize(PositionI posMP, ML::Color setColor)
	{
		color = setColor;
		pos = posMP;
		playerHeight = 0.f;
		visible = 30.f;
		time = 0;
	}

	//�X�V
	void Update(const Rocket rkt, const int MapLength)
	{
		++time;
		if ((time / 60) % 2)
			visible -= 0.5f;
		else
			visible += 0.5f;

		playerHeight = (rkt.pos.y / ((float)MapLength * 360.f)) * 325.f;
	}

	//�`��(�v���C���[)
	void Render()
	{
		ML::Box2D src(0, 0, 40, 40);
		ML::Box2D draw(-20, -20, 40, 40);
		draw.Offset(pos.x, 375 + (int)playerHeight);
		color.c[3] = 1.f;
		DG::Image_Draw("MiniPlayer", draw, src, color);

		src.x += 40;
		color.c[3] = visible / 60.f;
		DG::Image_Draw("MiniPlayer", draw, src, color);
	}
};

//-----------------------------------------------------------------------------
//�^�C�}�[�ƃ~�j�}�b�v(��ʉE)
class Timer
{
private:
	PositionI pos;
	ML::Box2D number[10];
	ML::Box2D colon;

	unsigned int time;
	unsigned int minute[2]; //�\�̈ʂƈ�̈ʂɕ�����
	unsigned int second[2];

public:

	//������
	void Initialize(PositionI posT)
	{
		pos = posT;
		for (int i = 0; i < 10; ++i)
		{
			number[i] = ML::Box2D(30 * (i % 5), 45 * (i / 5), 30, 45);
		}
		colon = ML::Box2D(150, 0, 15, 45);

		time = 0;
		for (int i = 0; i < 2; ++i)
		{
			minute[i] = 0;
			second[i] = 0;
		}
	}

	//�X�V
	void Update(bool onoff)
	{
		if (!onoff || minute[0] >= 99)
			return;

		++time;
		minute[0] = ((time / 3600) / 10) % 10;
		minute[1] = (time / 3600) % 10;
		second[0] = (((time / 60) / 10) % 6) % 10;
		second[1] = (time / 60) % 10;
	}

	//���ݎ��Ԃ�Ԃ�
	unsigned int PutTime()
	{
		return time;
	}

	//�`��
	void Render()
	{
		//�~�j�}�b�v
		{
			ML::Box2D src(80, 0, 12, 40);
			ML::Box2D draw(-6, 0, 12, 405);
			draw.Offset(pos.x + 67, 0);
			DG::Image_Draw("MiniPlayer", draw, src);
		}
		{
			ML::Box2D src(0, 0, 185, 80);
			ML::Box2D draw(pos.x - 23, 0, 185, 75);
			DG::Image_Draw("MiniMoon", draw, src);

			src.y += 80;
			draw.y = 365;
			DG::Image_Draw("MiniMoon", draw, src);
		}

		int i = 0;
		//��
		for (; i < 2; ++i)
		{
			ML::Box2D draw(30 * i, 0, 30, 45);
			draw.Offset(pos.x, pos.y);
			DG::Image_Draw("Timer", draw, number[minute[i]]);
		}
		//�Ԃ̃R����
		{
			ML::Box2D draw(30 * i, 0, 15, 45);
			draw.Offset(pos.x, pos.y);
			DG::Image_Draw("Timer", draw, colon);
		}
		//�b
		for (; i < 4; ++i)
		{
			ML::Box2D draw((30 * i) + 15, 0, 30, 45);
			draw.Offset(pos.x, pos.y);
			DG::Image_Draw("Timer", draw, number[second[i - 2]]);
		}
	}
};


//-----------------------------------------------------------------------------
//UI�Ǘ�(1�v���C���[�ɂ����)
class UI
{
private:
	Gauge			gauge;
	MiniPlayer		mPlayer;
	ScreenEffect	scEffect;

public:
	void Initialize(PositionI eGaugePos, PositionI tGaugePos,
					PositionI mpPos, ML::Color mPcolor)
	{
		gauge.Initialize(eGaugePos, tGaugePos);
		mPlayer.Initialize(mpPos, mPcolor);
		scEffect.Initialize();
	}

	void Update(const Rocket& rkt,
				const int MapLength)
	{
		gauge.Update(rkt);
		mPlayer.Update(rkt, MapLength);
		scEffect.Update(rkt);
	}

	void Render(const Rocket& rkt, const Camera& camera)
	{
		gauge.Render(rkt);
		mPlayer.Render();
		if (rkt.state != Non)
		{
			scEffect.Render(camera);
		}
	}
};

//-----------------------------------------------------------------------------
//UI�Ǘ�(��̂ݍ쐬)
class StageUI
{
private:
	Timer timer;

public:
	void Initialize(PositionI timePos)
	{
		timer.Initialize(timePos);
	}

	void Update(bool timerOn)
	{
		timer.Update(timerOn);
	}

	int PutTime()
	{
		return timer.PutTime();
	}

	void Render()
	{
		timer.Render();
	}
};
