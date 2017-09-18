// DlgSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "win_client.h"
#include "DlgSetting.h"
#include "afxdialogex.h"


// CDlgSetting �Ի���

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


// CDlgSetting ��Ϣ�������


void CDlgSetting::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CDlgSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
