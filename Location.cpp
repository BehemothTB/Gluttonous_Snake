#include "pch.h"

Location::Location(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Location::SetLocation(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Location::SetLocation(Location locate)
{
	this->x = locate.GetX();
	this->y = locate.GetY();
}

int Location::GetX()//获取x坐标
{
	return x;
}

int Location::GetY()//获取y坐标
{
	return y;
}

Location Location::operator+(Direction direct)
{
	Location sum;
	sum.SetLocation(x + direct.GetX(), y + direct.GetY());
	return sum;
}

Location Location::operator+=(Direction direct)
{
	x += direct.GetX();
	y += direct.GetY();
	return *this;
}

Location Location::operator-(Direction direct)
{
	Location sum;
	sum.SetLocation(x - direct.GetX(), y - direct.GetY());
	return sum;
}

Location Location::operator-=(Direction direct)
{
	x -= direct.GetX();
	y -= direct.GetY();
	return *this;
}

bool Location::operator==(Location locate)
{
	if (x == locate.GetX() && y == locate.GetY())
	{
		return true;
	}
	else
	{
		return false;
	}
}