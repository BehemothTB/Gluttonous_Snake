// HelpBox.cpp: 实现文件
//

#include "pch.h"
#include "Gluttonous_Snake.h"
#include "HelpBox.h"
#include "afxdialogex.h"


// HelpBox 对话框

IMPLEMENT_DYNAMIC(HelpBox, CDialog)

HelpBox::HelpBox(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HELPBOX, pParent)
{

}

HelpBox::~HelpBox()
{
}

void HelpBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpBox, CDialog)
END_MESSAGE_MAP()


// HelpBox 消息处理程序
