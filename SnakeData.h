#pragma once

#include "Location.h"
#include "Gluttonous_SnakeDlg.h"



class SnakeData
{
protected:
	int count;//̰���߽���
	Location SnakeNow[SUM], SnakeNew[SUM];//ÿһ�ڵ��¾�λ��
	Direction SnakeDirection[SUM];//ÿһ�ڵ��˶�����
	Direction HeadDirection;//ͷ�����˶�����

public:
	friend void CGluttonousSnakeDlg::StartSnake();
	friend class GamePlayDlg;

	SnakeData(int count = 0, int L_x = 0, int L_y = 0, int direct = UP);
	void SetSnake(int count = 0, int L_x = 0, int L_y = 0, int direct = UP);
	void Update();//����ÿһ�ڵ�λ��
	Direction GetHeadDirection();//��ȡͷ���˶�����
	void SetHeadDirection(int direct);//����ͷ���˶�����
	void Add();//̰���߼ӳ�һ��
	bool IsDead();//�ж��Ƿ�����
	bool IsWin();//�ж��Ƿ�ʤ��
	int GetDirection(int i);//��ȡĳһ�ڵ��˶�����
	void OverMoveUpdate();
};

