#pragma once
#include "afxwin.h"


// CDialogTask �Ի���

class CDialogTask : public CDialog
{
	DECLARE_DYNAMIC(CDialogTask)

public:
	CDialogTask(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogTask();

// �Ի�������
	enum { IDD = IDD_DIALOGTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_task;
	virtual BOOL OnInitDialog();
	int tasknum;
	CListBox m_list1;
	COleDateTime m_taskdate;
	COleDateTime m_tasktime;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDelete();
};
