#pragma once


// CCommentDlg �Ի���

class CCommentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommentDlg)

public:
	CCommentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommentDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_comment;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
