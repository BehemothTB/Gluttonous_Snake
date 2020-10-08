// GamePlayDlg.cpp: 实现文件
//

#include "pch.h"
#include "Gluttonous_Snake.h"
#include "GamePlayDlg.h"
#include "afxdialogex.h"


// GamePlayDlg 对话框

IMPLEMENT_DYNAMIC(GamePlayDlg, CDialog)

GamePlayDlg::GamePlayDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GAMEPLAY, pParent)
{
	GSnake.SetSnake(4, LENGTH + FRAME, LENGTH * 4 + FRAME + THIGHT, DOWN);
	time = 1;
	score = 0;
}

GamePlayDlg::~GamePlayDlg()
{
}

void GamePlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GamePlayDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
//	ON_WM_CHAR()
END_MESSAGE_MAP()


// GamePlayDlg 消息处理程序


int GamePlayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	this->SetWindowPos(NULL, 0, 0, GW_F, GH_F, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	this->CenterWindow();

	this->ToolBar();

	this->SetTimer(TTIMER, TTICK, NULL);

	this->FoodGenerate();

	this->SetTimer(GAMETIMER, GTICK, NULL);

	return 0;
}


// 游戏界面初始化
void GamePlayDlg::ToolBar()
{
	// TODO: 在此处添加实现代码.

	CClientDC dc(this);
	CBitmap Bmp;
	CBrush* pBrushOld, BrushNew;

	Bmp.LoadBitmapW(IDB_FRAME);
	BrushNew.CreatePatternBrush(&Bmp);
	pBrushOld = dc.SelectObject(&BrushNew);
	dc.Rectangle(0, 0, GW_F, GH_F);
	Bmp.DeleteObject();
	BrushNew.DeleteObject();
	dc.SelectObject(pBrushOld);

	Bmp.LoadBitmapW(IDB_BACKUP);
	BrushNew.CreatePatternBrush(&Bmp);
	pBrushOld = dc.SelectObject(&BrushNew);
	dc.Rectangle(FRAME, FRAME, GWIDTH + FRAME, THIGHT + FRAME);
	Bmp.DeleteObject();
	BrushNew.DeleteObject();
	dc.SelectObject(pBrushOld);

	CDC MemDC;
	CBitmap* pBmpOld;
	BITMAP bm;
	Bmp.LoadBitmapW(IDB_SCORE);
	Bmp.GetBitmap(&bm);
	MemDC.CreateCompatibleDC(&dc);
	pBmpOld = MemDC.SelectObject(&Bmp);
	dc.BitBlt(FRAME, FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(IDB_TIME);
	MemDC.SelectObject(&Bmp);
	Bmp.GetBitmap(&bm);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 3 - bm.bmWidth), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	pBmpOld = MemDC.SelectObject(&Bmp);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 3), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	MemDC.SelectObject(&Bmp);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 2), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	MemDC.SelectObject(&Bmp);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 1), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	MemDC.SelectObject(&Bmp);
	dc.BitBlt((FRAME + LENGTH * 6), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	pBmpOld = MemDC.SelectObject(&Bmp);
	dc.BitBlt((FRAME + LENGTH * 7), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	Bmp.LoadBitmapW(this->BmpTrans(0));
	Bmp.GetBitmap(&bm);
	MemDC.SelectObject(&Bmp);
	dc.BitBlt((FRAME + LENGTH * 8), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	Bmp.DeleteObject();

	dc.SelectObject(pBmpOld);
	MemDC.DeleteDC();

}


void GamePlayDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == TTIMER)
	{
		this->TickTimer();
	}

	if (nIDEvent == GAMETIMER)
	{
		this->Background();

		GSnake.Update();

#ifdef INVINCEBLE
		GSnake.OverMoveUpdate();
#endif // INVINCEBLE

		this->PaintSnake();
		this->FoodPaint();

#ifndef INVINCEBLE
		if (GSnake.IsDead())
		{
			this->KillTimer(TTIMER);
			this->KillTimer(GAMETIMER);
			time = 1;
			score = 0;
		}
#endif // !INVINCEBLE

		if (GSnake.SnakeNew[0] == food)
		{
			GSnake.Add();
			this->FoodGenerate();
			this->ScorePaint();
		}

	}

	if (nIDEvent == KEYUPLOOP && GSnake.HeadDirection.GetY() == 0)
	{
		GSnake.SetHeadDirection(UP);
	}
	if (nIDEvent == KEYLEFTLOOP && GSnake.HeadDirection.GetX() == 0)
	{
		GSnake.SetHeadDirection(LEFT);
	}
	if (nIDEvent == KEYDOWNLOOP && GSnake.HeadDirection.GetY() == 0)
	{
		GSnake.SetHeadDirection(DOWN);
	}
	if (nIDEvent == KEYRIGHTLOOP && GSnake.HeadDirection.GetX() == 0)
	{
		GSnake.SetHeadDirection(RIGHT);
	}

	CDialog::OnTimer(nIDEvent);
}


void GamePlayDlg::TickTimer()
{
	// TODO: 在此处添加实现代码.

	int a, b, c;
	a = time / 100;
	b = (time - a * 100) / 10;
	c = time % 10;
	CBitmap* pBmpOld, BmpNew;
	CDC MemDC;
	CClientDC dc(this);
	BITMAP bm;

	BmpNew.LoadBitmapW(this->BmpTrans(a));
	BmpNew.GetBitmap(&bm);
	MemDC.CreateCompatibleDC(&dc);
	pBmpOld = MemDC.SelectObject(&BmpNew);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 3), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	BmpNew.LoadBitmapW(this->BmpTrans(b));
	BmpNew.GetBitmap(&bm);
	MemDC.SelectObject(&BmpNew);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 2), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	BmpNew.LoadBitmapW(this->BmpTrans(c));
	BmpNew.GetBitmap(&bm);
	MemDC.SelectObject(&BmpNew);
	dc.BitBlt((GWIDTH + FRAME - LENGTH * 1), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	dc.SelectObject(pBmpOld);
	MemDC.DeleteDC();

	time++;

}


// 将数字转换为位图句柄
int GamePlayDlg::BmpTrans(int num)
{
	// TODO: 在此处添加实现代码.

	switch (num)
	{
	case 0:return IDB_0;
	case 1:return IDB_1;
	case 2:return IDB_2;
	case 3:return IDB_3;
	case 4:return IDB_4;
	case 5:return IDB_5;
	case 6:return IDB_6;
	case 7:return IDB_7;
	case 8:return IDB_8;
	case 9:return IDB_9;
	default:return 0;
	}

}



void GamePlayDlg::Background()
{
	// TODO: 在此处添加实现代码.

	static int count = 0;
	CBitmap backblue, backred;
	backblue.LoadBitmapW(IDB_GBACKB);
	backred.LoadBitmapW(IDB_GBACKR);
	CBrush* BrushOld, BrushNew;
	if (count >= (GBACKTICKS / 2))
	{
		BrushNew.CreatePatternBrush(&backblue);
	}
	else
	{
		BrushNew.CreatePatternBrush(&backred);
	}
	CClientDC dc(this);
	BrushOld = dc.SelectObject(&BrushNew);
	dc.Rectangle(FRAME, THIGHT + FRAME, GWIDTH + FRAME, GHIGHT + FRAME);
	dc.SelectObject(BrushOld);
	BrushNew.DeleteObject();
	backblue.DeleteObject();
	backred.DeleteObject();
	count = count == (GBACKTICKS - 1) ? 0 : ++count;

}

void GamePlayDlg::PaintSnake()
{
	// TODO: 在此处添加实现代码.

	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap* BitmapOld;
	BITMAP bp;
	for (int i = GSnake.count - 1; i >= 0; i--)
	{
		int part;
		if (i == 0)
		{
			part = HEAD;
		}
		else
		{
			part = BODY;
		}
		BitmapOld = MemDC.SelectObject(this->BitmapLoader(part, GSnake.GetDirection(i), bp));
		dc.BitBlt(GSnake.SnakeNow[i].GetX(), GSnake.SnakeNow[i].GetY(), bp.bmWidth, bp.bmHeight, &MemDC, 0, 0, SRCCOPY);
		dc.SelectObject(BitmapOld);
	}
	MemDC.DeleteDC();

}


CBitmap* GamePlayDlg::BitmapLoader(int part, int direct, BITMAP& bp)
{
	// TODO: 在此处添加实现代码.

	static CBitmap bm;
	bm.DeleteObject();
	if (part == BODY)
	{
		switch (direct)
		{
		case UP:bm.LoadBitmapW(IDB_BODYU); break;
		case LEFT:bm.LoadBitmapW(IDB_BODYL); break;
		case DOWN:bm.LoadBitmapW(IDB_BODYD); break;
		case RIGHT:bm.LoadBitmapW(IDB_BODYR); break;
		default:return NULL;
		}
	}
	else if (part == HEAD)
	{
		switch (direct)
		{
		case UP:bm.LoadBitmapW(IDB_HEADU); break;
		case LEFT:bm.LoadBitmapW(IDB_HEADL); break;
		case DOWN:bm.LoadBitmapW(IDB_HEADD); break;
		case RIGHT:bm.LoadBitmapW(IDB_HEADR); break;
		default:return NULL;
		}
	}
	else
	{
		return NULL;
	}
	bm.GetBitmap(&bp);
	return &bm;
}


void GamePlayDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
	case 'W':this->SetTimer(KEYUPLOOP,KEYTICK,NULL); break;
	case 'A':this->SetTimer(KEYLEFTLOOP, KEYTICK, NULL); break;
	case 'S':this->SetTimer(KEYDOWNLOOP, KEYTICK, NULL); break;
	case 'D':this->SetTimer(KEYRIGHTLOOP, KEYTICK, NULL); break;
	case 'R':this->OnOK(); break;
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


void GamePlayDlg::FoodGenerate()
{
	// TODO: 在此处添加实现代码.

	int x, y;
	Location Locate;
loop:
	x = rand() % BORDER;
	y = rand() % BORDER;
	Locate.SetLocation(x * LENGTH + FRAME, y * LENGTH + FRAME + THIGHT);
	for (int i = 0; i < GSnake.count; i++)
	{
		if (Locate == GSnake.SnakeNow[i])
		{
			goto loop;
		}
	}
	food = Locate;

}


void GamePlayDlg::FoodPaint()
{
	// TODO: 在此处添加实现代码.

	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap* BitmapOld,BmpNew;
	BITMAP bp;
	BmpNew.LoadBitmapW(IDB_FOOD);
	BmpNew.GetBitmap(&bp);
	BitmapOld = MemDC.SelectObject(&BmpNew);
	dc.BitBlt(food.GetX(), food.GetY(), bp.bmWidth, bp.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();
	dc.SelectObject(BitmapOld);
	MemDC.DeleteDC();

}


void GamePlayDlg::ScorePaint()
{
	// TODO: 在此处添加实现代码.

	score++;

	int a, b, c;
	a = score / 100;
	b = (score - a * 100) / 10;
	c = score % 10;
	CBitmap* pBmpOld, BmpNew;
	CDC MemDC;
	CClientDC dc(this);
	BITMAP bm;

	BmpNew.LoadBitmapW(this->BmpTrans(a));
	BmpNew.GetBitmap(&bm);
	MemDC.CreateCompatibleDC(&dc);
	pBmpOld = MemDC.SelectObject(&BmpNew);
	dc.BitBlt((FRAME + LENGTH * 6), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	BmpNew.LoadBitmapW(this->BmpTrans(b));
	BmpNew.GetBitmap(&bm);
	MemDC.SelectObject(&BmpNew);
	dc.BitBlt((FRAME + LENGTH * 7), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	BmpNew.LoadBitmapW(this->BmpTrans(c));
	BmpNew.GetBitmap(&bm);
	MemDC.SelectObject(&BmpNew);
	dc.BitBlt((FRAME + LENGTH * 8), FRAME, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
	BmpNew.DeleteObject();

	dc.SelectObject(pBmpOld);
	MemDC.DeleteDC();

}


void GamePlayDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
	case 'W':this->KillTimer(KEYUPLOOP); break;
	case 'A':this->KillTimer(KEYLEFTLOOP); break;
	case 'S':this->KillTimer(KEYDOWNLOOP); break;
	case 'D':this->KillTimer(KEYRIGHTLOOP); break;
	}

	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}


