// DialogOption.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "clock.h"
#include "DialogOption.h"


// CDialogOption �Ի���

IMPLEMENT_DYNAMIC(CDialogOption, CDialog)

CDialogOption::CDialogOption(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOption::IDD, pParent)
	, CheckHalfHour(FALSE)
	, CheckRun(FALSE)
	, CheckHour(FALSE)
{

}

CDialogOption::~CDialogOption()
{
}

void CDialogOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECKHALFHOUR, CheckHalfHour);
	DDX_Check(pDX, IDC_CHECKRUN, CheckRun);
	DDX_Check(pDX, IDC_CHECKHOUR, CheckHour);
}


BEGIN_MESSAGE_MAP(CDialogOption, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogOption::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogOption ��Ϣ�������

BOOL CDialogOption::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int temp=AfxGetApp()->GetProfileInt("Sound","hoursound",0);
	if(temp==1)
		CheckHour=true;
	else
		CheckHour=false;
	temp=AfxGetApp()->GetProfileInt("Sound","halfhoursound",0);
	if(temp==1)
		CheckHalfHour=true;
	else
		CheckHalfHour=false;
	temp=AfxGetApp()->GetProfileInt("Run","run",0);
	if(temp==1)
		CheckRun=true;
	else
		CheckRun=false;
	this->UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogOption::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	int temp;
	if(CheckHour)
		temp=1;
	else
		temp=0;
	AfxGetApp()->WriteProfileInt("Sound","hoursound",temp);
	if(CheckHalfHour)
		temp=1;
	else
		temp=0;
	AfxGetApp()->WriteProfileInt("Sound","halfhoursound",temp);
	if(CheckRun)
		temp=1;
	else
		temp=0;
	AfxGetApp()->WriteProfileInt("Run","run",temp);


	if(CheckRun)
	{
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(__argv[0],drive,dir,fname,ext);//����ļ�����������·�����Ϊ�ĸ����֣��ֱ���
		if(drive[0]>96&&drive[0]<123)
			drive[0]-=32;
		CString path(drive);
		path+=dir;
		path+="����ʱ��.exe";
		TCHAR m_path[MAX_PATH];
		wsprintf(m_path,path);

		//���ñ�����Ϊ��������
		HKEY hkey;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\Currentversion\\Run",0,KEY_WRITE,& hkey);//��ע�����
		RegSetValueEx(hkey,"����ʱ��",0,REG_SZ,(LPBYTE)m_path,lstrlen(m_path)+1);//����ע����ֵ
		RegCloseKey(hkey);							//�ͷ�ָ��ע����ľ��
	}
	else
	{
		HKEY hkey;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_WRITE,&hkey)   ;   
		RegDeleteValue(hkey,"����ʱ��");   
		RegCloseKey(hkey);   
	}

	OnOK();
}
