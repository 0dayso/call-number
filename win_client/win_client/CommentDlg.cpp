// CommentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "win_client.h"
#include "CommentDlg.h"
#include "afxdialogex.h"


// CCommentDlg 对话框

IMPLEMENT_DYNAMIC(CCommentDlg, CDialogEx)

CCommentDlg::CCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommentDlg::IDD, pParent)
	, m_comment(_T(""))
{

}

CCommentDlg::~CCommentDlg()
{
}

void CCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_comment);
}


BEGIN_MESSAGE_MAP(CCommentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCommentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCommentDlg 消息处理程序


void CCommentDlg::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CCommentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
