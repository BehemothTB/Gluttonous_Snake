#include "pch.h"

SnakeData::SnakeData(int count, int L_x, int L_y, int direct)
{
	this->count = count;
	SnakeNow[0].SetLocation(L_x, L_y);
	this->SetHeadDirection(direct);
	for (int i = 0; i < count; i++)
	{
		SnakeDirection[i].SetLocation(HeadDirection);
		if (i != 0)
		{
			SnakeNow[i].SetLocation(SnakeNow[i - 1] - HeadDirection);
		}
		SnakeNew[i] = SnakeNow[i] + HeadDirection;
	}

}

void SnakeData::SetSnake(int count, int L_x, int L_y, int direct)
{
	this->count = count;
	SnakeNow[0].SetLocation(L_x, L_y);
	this->SetHeadDirection(direct);
	for (int i = 0; i < count; i++)
	{
		SnakeDirection[i].SetLocation(HeadDirection);
		if (i != 0)
		{
			SnakeNow[i].SetLocation(SnakeNow[i - 1] - HeadDirection);
		}
		SnakeNew[i] = SnakeNow[i] + HeadDirection;
	}
}

void SnakeData::Update()//更新每一节的位置
{
	for (int i = 0; i < count; i++)
	{
		SnakeNow[i] = SnakeNew[i];
	}
	for (int i = count; i > 0; i--)
	{
		SnakeDirection[i] = SnakeDirection[i - 1];
	}
	SnakeDirection[0] = HeadDirection;
	for (int i = 0; i < count; i++)
	{
		SnakeNew[i] = SnakeNow[i] + SnakeDirection[i];
	}
}

Direction SnakeData::GetHeadDirection()//获取头部运动方向
{
	return HeadDirection;
}

void SnakeData::SetHeadDirection(int direct)//设置头部运动方向
{
	switch (direct)
	{
	case UP: HeadDirection.SetLocation(0, -LENGTH); break;
	case RIGHT: HeadDirection.SetLocation(LENGTH, 0); break;
	case DOWN: HeadDirection.SetLocation(0, LENGTH); break;
	case LEFT: HeadDirection.SetLocation(-LENGTH, 0); break;
	}
}

void SnakeData::Add()//贪吃蛇加长一节
{
	SnakeNow[count] = SnakeNow[count - 1] - SnakeDirection[count];
	SnakeNew[count] = SnakeNow[count - 1];
	count++;
}

bool SnakeData::IsDead()//判断是否死亡
{
	if (SnakeNew[0].GetX() < FRAME || SnakeNew[0].GetX() > (BORDER - 1) * LENGTH + FRAME || SnakeNew[0].GetY() < FRAME + THIGHT || SnakeNew[0].GetY() > (BORDER - 1) * LENGTH + FRAME + THIGHT)
	{
		return true;
	}
	for (int i = 1; i < count; i++)
	{
		if (SnakeNew[0] == SnakeNow[i])
		{
			return true;
		}
	}
	return false;
}

bool SnakeData::IsWin()//判断是否胜利
{
	if (count == SUM)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SnakeData::GetDirection(int i)//获取某一节的运动方向
{
	if (SnakeDirection[i].GetX() == LENGTH)
	{
		return RIGHT;
	}
	else if (SnakeDirection[i].GetX() == -LENGTH)
	{
		return LEFT;
	}
	else if (SnakeDirection[i].GetY() == LENGTH)
	{
		return DOWN;
	}
	else
	{
		return UP;
	}
}

void SnakeData::OverMoveUpdate()
{
	// TODO: 在此处添加实现代码.

	Location locate_x(BORDER * LENGTH, 0);
	Location locate_y(0, BORDER * LENGTH);

	for (int i = 0; i < count; i++)
	{
		if (SnakeNew[i].GetX() < FRAME)
		{
			SnakeNew[i] += locate_x;
		}
		else if (SnakeNew[i].GetX() > (BORDER - 1) * LENGTH + FRAME)
		{
			SnakeNew[i] -= locate_x;
		}
		else if (SnakeNew[i].GetY() < FRAME + THIGHT)
		{
			SnakeNew[i] += locate_y;
		}
		else if (SnakeNew[i].GetY() > (BORDER - 1) * LENGTH + FRAME + THIGHT)
		{
			SnakeNew[i] -= locate_y;
		}
	}

}
