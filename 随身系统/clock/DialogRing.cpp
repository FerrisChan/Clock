// DialogRing.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "clock.h"
#include "DialogRing.h"


// CDialogRing �Ի���

IMPLEMENT_DYNAMIC(CDialogRing, CDialog)

CDialogRing::CDialogRing(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRing::IDD, pParent)
	, ringnum(0)
	, m_ringtime(COleDateTime::GetCurrentTime())
{

}

CDialogRing::~CDialogRing()
{
}

void CDialogRing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_ringtime);
}


BEGIN_MESSAGE_MAP(CDialogRing, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogRing::OnBnClickedOk)
	ON_BN_CLICKED(IDDELETE, &CDialogRing::OnBnClickedDelete)
END_MESSAGE_MAP()


// CDialogRing ��Ϣ�������

BOOL CDialogRing::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ע����ж�ȡ���ݳ�ʼ�����öԻ���
	ringnum=AfxGetApp()->GetProfileIntA("ring","ringnum",0);
	CString temp;
	CString time;
	for(int i=1;i<=ringnum;i++)
	{
		temp.Format("ring%d",i);
		time=AfxGetApp()->GetProfileStringA("ring",temp);
		m_list1.InsertString(i-1,time);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogRing::OnBnClickedOk()//ȷ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ñ�����ע�����
	this->UpdateData(TRUE);
	if(ringnum>=20)
	{
		AfxMessageBox("�Բ������ֻ�����20�����ӣ�");
		return;
	}
	ringnum++;
	AfxGetApp()->WriteProfileInt("ring","ringnum",ringnum);
	CString temp;
	CString time;
	time=m_ringtime.Format("%H:%M:%S");
	temp.Format("ring%d",ringnum);
	AfxGetApp()->WriteProfileStringA("ring",temp,time);
	m_list1.InsertString(ringnum-1,time);
	//OnOK();
}

void CDialogRing::OnBnClickedDelete()//ɾ������
{
	CString temp;
	CString time;
	int i;
	for(i=1;i<=ringnum;i++)
	{
		temp.Format("ring%d",i);
		AfxGetApp()->WriteProfileStringA("ring",temp,NULL);
	}
	ringnum--;
	AfxGetApp()->WriteProfileInt("ring","ringnum",ringnum);
	int t=m_list1.GetCurSel();
	m_list1.DeleteString(t);
	for(i=0;i<ringnum;i++)
	{
		m_list1.GetText(i,time);
		temp.Format("ring%d",i+1);
		AfxGetApp()->WriteProfileStringA("ring",temp,time);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
