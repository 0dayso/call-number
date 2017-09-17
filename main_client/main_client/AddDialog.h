#pragma once


// CAddDialog 对话框

class CAddDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDialog)

public:
	CAddDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	CString m_phone;
	CString m_type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
