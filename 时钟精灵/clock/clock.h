// clock.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "clockdlg.h"
#include "DialogRing.h"
#include "DialogTask.h"
#include "DialogOption.h"

// CclockApp:
// �йش����ʵ�֣������ clock.cpp
//

class CclockApp : public CWinApp
{
public:
	CclockApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
//	HWND m_hwndDlg;

protected:
//	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	CclockDlg dlg;
//	afx_msg void OnClose();
};

extern CclockApp theApp;