// AddDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "main_client.h"
#include "AddDialog.h"
#include "afxdialogex.h"


// CAddDialog �Ի���

IMPLEMENT_DYNAMIC(CAddDialog, CDialogEx)

CAddDialog::CAddDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddDialog::IDD, pParent)
	, m_name(_T(""))
	, m_id(_T(""))
	, m_phone(_T(""))
	, m_type(_T(""))
{

}

CAddDialog::~CAddDialog()
{
}

void CAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_phone);
	DDX_Text(pDX, IDC_EDIT4, m_type);
}


BEGIN_MESSAGE_MAP(CAddDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddDialog ��Ϣ�������


void CAddDialog::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CAddDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
