
// win_clientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "win_client.h"
#include "win_clientDlg.h"
#include "afxdialogex.h"
#include "python_support.h"
#include "DlgSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cwin_clientDlg �Ի���



Cwin_clientDlg::Cwin_clientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cwin_clientDlg::IDD, pParent)
	, m_info(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cwin_clientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_info);
}

BEGIN_MESSAGE_MAP(Cwin_clientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cwin_clientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON5, &Cwin_clientDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &Cwin_clientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &Cwin_clientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Cwin_clientDlg ��Ϣ�������

BOOL Cwin_clientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	PyExecA("import autorun");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cwin_clientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cwin_clientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cwin_clientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cwin_clientDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void Cwin_clientDlg::OnBnClickedButton5()
{
	CDlgSetting cds;
	PyEvalA("autorun.g_ip");
	cds.m_ip = PyGetStr();
	PyEvalA("autorun.g_win_no");
	cds.m_win_no = PyGetStr();
	PyEvalA("autorun.g_types");
	cds.m_types = PyGetStr();
	if (cds.DoModal() == IDOK)
	{
		PySetStrW(cds.m_ip.GetBuffer(), 0);
		PySetStrW(cds.m_win_no.GetBuffer(), 1);
		PySetStrW(cds.m_types.GetBuffer(), 2);
		PyExecA("autorun.save()");
	}
}


void Cwin_clientDlg::OnBnClickedButton1()
{
	PyEvalA("autorun.call_number()");
	CString ret= PyGetStr();
	if (ret==_T(""))
	{
		AfxMessageBox(_T("����ɵ�ǰ�����ٽ���һ���롣"));
		return;
	}
	m_info = ret;
	UpdateData(FALSE);
}


void Cwin_clientDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
