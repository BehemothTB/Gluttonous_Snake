#pragma once

#include "Location.h"
#include "Gluttonous_SnakeDlg.h"



class SnakeData
{
protected:
	int count;//贪吃蛇节数
	Location SnakeNow[SUM], SnakeNew[SUM];//每一节的新旧位置
	Direction SnakeDirection[SUM];//每一节的运动方向
	Direction HeadDirection;//头部的运动方向

public:
	friend void CGluttonousSnakeDlg::StartSnake();
	friend class GamePlayDlg;

	SnakeData(int count = 0, int L_x = 0, int L_y = 0, int direct = UP);
	void SetSnake(int count = 0, int L_x = 0, int L_y = 0, int direct = UP);
	void Update();//更新每一节的位置
	Direction GetHeadDirection();//获取头部运动方向
	void SetHeadDirection(int direct);//设置头部运动方向
	void Add();//贪吃蛇加长一节
	bool IsDead();//判断是否死亡
	bool IsWin();//判断是否胜利
	int GetDirection(int i);//获取某一节的运动方向
	void OverMoveUpdate();
};

