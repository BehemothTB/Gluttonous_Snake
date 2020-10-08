#pragma once


// GamePlayDlg 对话框

class GamePlayDlg : public CDialog
{
	DECLARE_DYNAMIC(GamePlayDlg)

public:
	GamePlayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GamePlayDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 绘制计分板
	void ToolBar();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void TickTimer();
	// 将数字转换为位图句柄
	int BmpTrans(int num);
	void Background();
protected:
	SnakeData GSnake;
public:
	void PaintSnake();
	CBitmap* BitmapLoader(int part, int direct, BITMAP& bp);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	int time;
public:
	Location food;
	void FoodGenerate();
	void FoodPaint();
protected:
	int score;
public:
	void ScorePaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
