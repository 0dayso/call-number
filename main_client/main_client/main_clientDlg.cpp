
// main_clientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "main_client.h"
#include "main_clientDlg.h"
#include "afxdialogex.h"
#include "python_support.h"
#include "AddDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

Cmain_clientDlg *g_pdlg = nullptr;


void list_add_column(int n, WCHAR *s,int wid)
{
	if (!g_pdlg)return;
	g_pdlg->m_list.InsertColumn(n, s, 0, wid);
}

void clear_list()
{
	if (!g_pdlg)return;
	g_pdlg->m_list.DeleteAllItems();
}

void list_set_item(int nitm, int nsub, WCHAR *s)
{
	if (!g_pdlg)return;
	if (nsub==0)
	{
		g_pdlg->m_list.InsertItem(nitm, s);
	}
	else
	{
		g_pdlg->m_list.SetItemText(nitm, nsub, s);
	}
}

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


// Cmain_clientDlg 对话框



Cmain_clientDlg::Cmain_clientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmain_clientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmain_clientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
}

BEGIN_MESSAGE_MAP(Cmain_clientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cmain_clientDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST3, &Cmain_clientDlg::OnColumnclickList3)
	ON_BN_CLICKED(IDC_BUTTON1, &Cmain_clientDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &Cmain_clientDlg::OnRclickList3)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmain_clientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cmain_clientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Cmain_clientDlg 消息处理程序

BOOL Cmain_clientDlg::OnInitDialog()
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
	g_pdlg = this;
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格

	if (!PyExecA("import autorun"))AfxMessageBox(PyGetStr());
	REG_EXE_FUN(list_add_column, "#lSl", "");
	REG_EXE_FUN(clear_list, "#", "");
	REG_EXE_FUN(list_set_item, "#llS", "");


	if (!PyExecA("autorun.get_title()"))AfxMessageBox(PyGetStr());
	PyExecA("autorun.refresh()");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmain_clientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmain_clientDlg::OnPaint()
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
HCURSOR Cmain_clientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmain_clientDlg::OnBnClickedOk()
{
	PyEvalA("autorun.get_title()");
	AfxMessageBox(PyGetStr());
}


void Cmain_clientDlg::OnColumnclickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CString str;
	str.Format(_T("%d"), pNMLV->iSubItem);
	//AfxMessageBox(str);
	*pResult = 0;
}


void Cmain_clientDlg::OnBnClickedButton1()
{
	CAddDialog cad;
	if (cad.DoModal()==IDOK)
	{
		PySetStrW(cad.m_name.GetBuffer(), 0);
		PySetStrW(cad.m_id.GetBuffer(), 1);
		PySetStrW(cad.m_phone.GetBuffer(), 2);
		PySetStrW(cad.m_type.GetBuffer(), 3);
		PyExecA("autorun.new_number()");
		PyExecA("autorun.refresh()");
		PyExecA("autorun.print_number()");
	}
}


void Cmain_clientDlg::OnRclickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem == -1)return;
	CMenu Menu;
	Menu.CreatePopupMenu();
	Menu.AppendMenu(MF_STRING, 1, _T("打印号票"));
	CPoint pt;
	::GetCursorPos(&pt);
	int sel = (int)Menu.TrackPopupMenuEx(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, pt.x, pt.y, this, nullptr);
	if (sel == 1)
	{
		PyExecA("autorun.print_number()");
	}
	*pResult = 0;
}


void Cmain_clientDlg::OnBnClickedButton2()
{
	PyExecA("autorun.refresh()");
}


void Cmain_clientDlg::OnBnClickedButton3()
{
	if (MessageBoxA(m_hWnd,"初始化会清空当前所有记录，并将新号码复位为1，用于新的一天工作开始，被清空数据会存入历史记录。\n\r你确认继续吗？","警告",MB_YESNO)==IDYES)
	{
		PyExecA("autorun.init_new_day()");
		PyExecA("autorun.refresh()");
	}
}
