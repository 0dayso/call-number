// CommentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "win_client.h"
#include "CommentDlg.h"
#include "afxdialogex.h"


// CCommentDlg �Ի���

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


// CCommentDlg ��Ϣ�������


void CCommentDlg::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CCommentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
