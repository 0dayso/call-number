#pragma once


// CAddDialog �Ի���

class CAddDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDialog)

public:
	CAddDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	CString m_phone;
	CString m_type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
