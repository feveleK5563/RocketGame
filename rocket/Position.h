#pragma once
#include "MyPG.h"

//floatå^
struct Position
{
	float x, y;

	Position() :
		x(0.f), y(0.f) {}

	Position(float ax, float ay) :
		x(ax), y(ay) {}

	Position operator +(const Position &A)
	{
		Position pos;
		pos.x = x + A.x;
		pos.y = y + A.y;
		return pos;
	}

	Position operator +=(const Position &A)
	{
		x += A.x;
		y += A.y;
		return *this;
	}

	Position operator -(const Position &A)
	{
		Position pos;
		pos.x = x - A.x;
		pos.y = y - A.y;
		return pos;
	}

	Position operator -=(const Position &A)
	{
		x -= A.x;
		y -= A.y;
		return *this;
	}
};

//intå^
struct PositionI
{
	int x, y;

	PositionI() :
		x(0), y(0) {}

	PositionI(int ax, int ay) :
		x(ax), y(ay) {}

	PositionI operator +(const PositionI &A)
	{
		PositionI pos;
		pos.x = x + A.x;
		pos.y = y + A.y;
		return pos;
	}

	PositionI operator +=(const PositionI &A)
	{
		x += A.x;
		y += A.y;
		return *this;
	}

	PositionI operator -(const PositionI &A)
	{
		PositionI pos;
		pos.x = x - A.x;
		pos.y = y - A.y;
		return pos;
	}

	PositionI operator -=(const PositionI &A)
	{
		x -= A.x;
		y -= A.y;
		return *this;
	}
};

