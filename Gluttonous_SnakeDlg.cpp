
// Gluttonous_SnakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Gluttonous_Snake.h"
#include "Gluttonous_SnakeDlg.h"
#include "afxdialogex.h"

#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	void ToolBar();
//	afx_msg void OnAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CREATE()
//ON_COMMAND(IDC_ABOUT, &CAboutDlg::OnAbout)
END_MESSAGE_MAP()


// CGluttonousSnakeDlg 对话框



CGluttonousSnakeDlg::CGluttonousSnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLUTTONOUS_SNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGluttonousSnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGluttonousSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
ON_WM_TIMER()
ON_BN_CLICKED(IDC_STARTBUTTON, &CGluttonousSnakeDlg::OnClickedStartbutton)
ON_WM_KEYDOWN()
ON_COMMAND(ID_HELP, &CGluttonousSnakeDlg::OnHelp)
ON_COMMAND(ID_ABOUT, &CGluttonousSnakeDlg::OnAbout)
END_MESSAGE_MAP()


// CGluttonousSnakeDlg 消息处理程序

BOOL CGluttonousSnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGluttonousSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGluttonousSnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGluttonousSnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CGluttonousSnakeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//调整窗口的位置大小
	this->SetWindowPos(NULL, 0, 0, W_X, H_Y, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	this->CenterWindow();

	m_Menu.LoadMenuW(IDR_MENU1);
	this->SetMenu(&m_Menu);

	this->SetTimer(STARTBUTTON_INITTIMER, STARTBUTTON_INITTICK, NULL);

	this->SetTimer(STARTTIMER,STICK,NULL);

	PlaySoundW(MAKEINTRESOURCE(IDR_WAVE1), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	this->SetTimer(SSNDLOOPTIMER, SSNDLOOPTICK, NULL);

	return 0;
}

void CGluttonousSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == STARTBUTTON_INITTIMER && this->StartButtonInit() == true)
	{
		this->KillTimer(STARTBUTTON_INITTIMER);
	}

	if (nIDEvent == STARTTIMER)
	{
		this->StartBackground();
		this->StartSnake();
	}

	if (nIDEvent == SSNDLOOPTIMER)
	{
		PlaySoundW(MAKEINTRESOURCE(IDR_WAVE2), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		this->KillTimer(SSNDLOOPTIMER);
	}

	CDialogEx::OnTimer(nIDEvent);
}

//用于初始化开始按钮
bool CGluttonousSnakeDlg::StartButtonInit()
{
	// TODO: 在此处添加实现代码.

	CWnd* pStart;
	pStart = GetDlgItem(IDC_STARTBUTTON);
	if (pStart)
	{
		pStart->SetWindowPos(NULL, START_X, START_Y, START_W, START_H, SWP_NOZORDER);
	}
	else
	{
		return false;
	}
	CBbutton_start.LoadBitmaps(IDB_STARTU, IDB_STARTD, IDB_STARTU, IDB_STARTD);
	CBbutton_start.SubclassDlgItem(IDC_STARTBUTTON,this);
	CBbutton_start.SizeToContent();
	return true;
}


// 用于绘画开始界面的蛇并更新位置
void CGluttonousSnakeDlg::StartSnake()
{
	// TODO: 在此处添加实现代码.

	static SnakeData LittleSnake(LITTLESNAKE, LENGTH * (LITTLESNAKE - 1), 0, RIGHT);
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap* BitmapOld;
	BITMAP bp;
	for (int i = 0; i < LITTLESNAKE; i++)
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
		BitmapOld = MemDC.SelectObject(this->BitmapLoader(part, LittleSnake.GetDirection(i), bp));
		dc.BitBlt(LittleSnake.SnakeNow[i].GetX(), LittleSnake.SnakeNow[i].GetY(), bp.bmWidth, bp.bmHeight, &MemDC, 0, 0, SRCCOPY);
		dc.SelectObject(BitmapOld);
	}
	MemDC.DeleteDC();

	if (LittleSnake.SnakeNew[0].GetX() == START_W + LENGTH)
	{
		if (LittleSnake.SnakeNew[0].GetY() == 0)
		{
			LittleSnake.SetHeadDirection(DOWN);
		}
		else if (LittleSnake.SnakeNew[0].GetY() == START_H + LENGTH)
		{
			LittleSnake.SetHeadDirection(LEFT);
		}
	}
	else if (LittleSnake.SnakeNew[0].GetX() == 0)
	{
		if (LittleSnake.SnakeNew[0].GetY() == 0)
		{
			LittleSnake.SetHeadDirection(RIGHT);
		}
		else if (LittleSnake.SnakeNew[0].GetY() == START_H + LENGTH)
		{
			LittleSnake.SetHeadDirection(UP);
		}
	}
	LittleSnake.Update();

}


void CGluttonousSnakeDlg::StartBackground()
{
	// TODO: 在此处添加实现代码.

	static int count = 0;
	CBitmap backblue, backred;
	backblue.LoadBitmapW(IDB_SBACKB);
	backred.LoadBitmapW(IDB_SBACKR);
	CBrush* BrushOld, BrushNew;
	if (count >= (SBACKTICKS / 2))
	{
		BrushNew.CreatePatternBrush(&backblue);
	}
	else
	{
		BrushNew.CreatePatternBrush(&backred);
	}
	CClientDC dc(this);
	BrushOld = dc.SelectObject(&BrushNew);
	CWnd* pStart;
	pStart = this->GetDlgItem(IDC_STARTBUTTON);
	pStart->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
	dc.Rectangle(0, 0, WIDTH, HIGHT);
	pStart->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	dc.SelectObject(BrushOld);
	BrushNew.DeleteObject();
	backblue.DeleteObject();
	backred.DeleteObject();
	count = count == (SBACKTICKS - 1) ? 0 : ++count;

}

//用于加载正确的位图
CBitmap* CGluttonousSnakeDlg::BitmapLoader(int part, int direct, BITMAP &bp)
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


void CGluttonousSnakeDlg::OnClickedStartbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	for (; 1;)
	{
		GamePlayDlg Gameplay;
		if (Gameplay.DoModal() == IDCANCEL)
		{
			break;
		}
	}
	this->ShowWindow(SW_SHOW);
}

void CGluttonousSnakeDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码

	CAboutDlg CAbout;
	CAbout.DoModal();

}


void CGluttonousSnakeDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nChar == VK_SPACE)
	{
		this->OnClickedStartbutton();
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGluttonousSnakeDlg::OnHelp()
{
	// TODO: 在此添加命令处理程序代码

	HelpBox Help;
	Help.DoModal();

}

