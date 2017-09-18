// DlgSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "win_client.h"
#include "DlgSetting.h"
#include "afxdialogex.h"


// CDlgSetting 对话框

IMPLEMENT_DYNAMIC(CDlgSetting, CDialogEx)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetting::IDD, pParent)
	, m_ip(_T(""))
	, m_win_no(_T(""))
	, m_types(_T(""))
{

}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ip);
	DDX_Text(pDX, IDC_EDIT2, m_win_no);
	DDX_Text(pDX, IDC_EDIT3, m_types);
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetting 消息处理程序


void CDlgSetting::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CDlgSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT1)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
