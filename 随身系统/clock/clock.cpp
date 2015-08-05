// clock.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "clock.h"
#include "clockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CclockApp

BEGIN_MESSAGE_MAP(CclockApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
//	ON_COMMAND(ID_CLOSE, &CclockApp::OnClose)
END_MESSAGE_MAP()


// CclockApp ����

CclockApp::CclockApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CclockApp ����

CclockApp theApp;


// CclockApp ��ʼ��

BOOL CclockApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("����ʱ��"));
	LoadStdProfileSettings(1000);			//ȷ�����Ҽ������ʹ�õ��ļ�����������״̬

	CclockDlg dlg;
	//this->SetDialogBkColor(RGB(0,0,0));
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
//	m_hwndDlg=NULL;
	return FALSE;
}

/*BOOL CclockApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	//if(m_hwndDlg!=NULL)
	{
		//�ж���Ϣ�������Ϣ�ǴӶԻ��򷢳��Ļ������ӿؼ������ģ����Ǿͽ��д���sunxin
		if((lpMsg->hwnd==m_hwndDlg)||::IsChild(m_hwndDlg,lpMsg->hwnd))
		{
			//�����Ϣ��WM_KEYDOWN�����Ǿ͵���һ����Ϣ��sunxin
			if(lpMsg->message==WM_RBUTTONDOWN)
			{
				AfxMessageBox(L"����ɹ���");
			}
		}
	}
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
*/
BOOL CclockApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
//	if(pMsg->message==WM_NCRBUTTONDOWN)
//		AfxMessageBox(L"�Ҽ���Ϣ"); 
	if(pMsg->message==WM_KEYDOWN)
		return FALSE;
//	theApp
//	if(pMsg->message==WM_KEYUP)
//		AfxMessageBox(L"�����Ϣ"); 
//	if(pMsg->message==WM_NCMOUSELEAVE)
//		AfxMessageBox(L"�����Ϣ"); 
//	if(pMsg->message==WM_MOUSELEAVE)
//		AfxMessageBox(L"����뿪��Ϣ"); 

	return CWinApp::PreTranslateMessage(pMsg);
}

//void CclockApp::OnClose()
//{
	// TODO: �ڴ���������������
//}
