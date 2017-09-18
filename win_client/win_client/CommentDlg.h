#pragma once


// CCommentDlg 对话框

class CCommentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommentDlg)

public:
	CCommentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommentDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_comment;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
