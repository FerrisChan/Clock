#include "clockDlg.h"
#pragma once


// CDialogOption �Ի���

class CDialogOption : public CDialog
{
	DECLARE_DYNAMIC(CDialogOption)

public:
	CDialogOption(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogOption();

// �Ի�������
	enum { IDD = IDD_DIALOGOPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	BOOL CheckHalfHour;
protected:
	BOOL CheckRun;

public:
	BOOL CheckHour;
public:
	afx_msg void OnBnClickedOk();
};
//CString PATH;