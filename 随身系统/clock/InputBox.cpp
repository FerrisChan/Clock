// InputBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "clock.h"
#include "InputBox.h"


// CInputBox �Ի���

IMPLEMENT_DYNAMIC(CInputBox, CDialog)

CInputBox::CInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(CInputBox::IDD, pParent)
	, InputStr(_T(""))
{

}

CInputBox::~CInputBox()
{
}

void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITINPUT, InputStr);
}


BEGIN_MESSAGE_MAP(CInputBox, CDialog)
END_MESSAGE_MAP()


// CInputBox ��Ϣ�������
