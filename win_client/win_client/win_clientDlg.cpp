
// win_clientDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cwin_clientDlg 对话框



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


// Cwin_clientDlg 消息处理程序

BOOL Cwin_clientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	PyExecA("import autorun");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cwin_clientDlg::OnPaint()
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
HCURSOR Cwin_clientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cwin_clientDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
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
		AfxMessageBox(_T("请完成当前任务再叫下一号码。"));
		return;
	}
	m_info = ret;
	UpdateData(FALSE);
}


void Cwin_clientDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
}
