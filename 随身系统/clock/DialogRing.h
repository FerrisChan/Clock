#pragma once
#include "afxwin.h"


// CDialogRing �Ի���

class CDialogRing : public CDialog
{
	DECLARE_DYNAMIC(CDialogRing)

public:
	CDialogRing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRing();

// �Ի�������
	enum { IDD = IDD_DIALOGRING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list1;
	virtual BOOL OnInitDialog();
	int ringnum;
	afx_msg void OnBnClickedOk();
	COleDateTime m_ringtime;
	afx_msg void OnBnClickedDelete();
};
