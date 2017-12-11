#pragma once
#include "MyPG.h"
#include "Camera.h"

struct Back
{
	int x, y;
	float r, g, b;
	ML::Box2D srdr;

	//”wŒi‚Ì‰Šú‰»----------------------------------------------------------------------
	void Initialize(int x, int y)
	{
		r = 1.f;
		g = 1.f;
		b = 1.f;
		x = x;
		y = y;
		srdr = ML::Box2D(0, 0, 480, 1010);
	}

	//c•ûŒü–³ŒÀƒ‹[ƒv-----------------------------------------------------------------
	void Loop(float cY)
	{
		if (cY < y)
		{
			y -= srdr.h - 10;
			return;
		}

		if (cY > y + srdr.h - 10)
		{
			y += srdr.h - 10;
		}
	}

	//w’èÀ•W’Ç”ö----------------------------------------------------------------------
	void PosTracking(float cY)
	{
		y = (int)cY;
	}

	//‹ó‚Ì•`‰æ-----------------------------------------------------------------------
	void Render(Camera camera)
	{
		for (int i = 0; i < 3; ++i)
		{
			int bY = y + ((i - 1) * (srdr.h - 10));
			ML::Box2D  draw(x, bY, srdr.w, srdr.h - 10);

			float colorRG = 1000.f / (bY * -0.02f + 700.f); //ã‚És‚­‚½‚Ñ‚ÉˆÃ‚­‚·‚é
			float colorB = colorRG * 1.5f;
			camera.Image_Draw("Sky", draw, srdr, ML::Color(1.f, colorRG, colorRG, colorB));
		}
	}

};