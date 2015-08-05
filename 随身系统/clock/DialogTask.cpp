// DialogTask.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "clock.h"
#include "DialogTask.h"


// CDialogTask �Ի���

IMPLEMENT_DYNAMIC(CDialogTask, CDialog)

CDialogTask::CDialogTask(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTask::IDD, pParent)
	, tasknum(0)
	, m_taskdate(COleDateTime::GetCurrentTime())
	, m_tasktime(COleDateTime::GetCurrentTime())
{

}

CDialogTask::~CDialogTask()
{
}

void CDialogTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_task);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_taskdate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_tasktime);
}


BEGIN_MESSAGE_MAP(CDialogTask, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogTask::OnBnClickedOk)
	ON_BN_CLICKED(IDDELETE, &CDialogTask::OnBnClickedDelete)
END_MESSAGE_MAP()


// CDialogTask ��Ϣ�������

BOOL CDialogTask::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ע����ж�ȡ��ʱ�����ʼ���Ի���
	m_task.SetCurSel(0);
	tasknum=AfxGetApp()->GetProfileIntA("task","tasknum",0);
	CString temp;
	CString task;
	CString taskdate;
	CString tasktime;
	int taskt;
	for(int i=1;i<=tasknum;i++)
	{
		temp.Format("task%d",i);
		taskt=AfxGetApp()->GetProfileIntA("task",temp,0);
		switch(taskt)
		{
		case 0:task="0:δѡ�����";break;
		case 1:task="1:�رռ����";break;
		case 2:task="2:�������������";break;
		case 3:task="3:�������";break;
		case 4:task="4:���ļ���";break;
		case 5:task="5:�򿪳���";break;
		case 6:task="6:���������Ƭ";break;
		case 7:task="7:�򿪹���";break;
		case 8:task="8:ɨ�財��";break;
		case 9:task="9: �رռ����(����ʱ30������)";break;
		case 10:task="10: �������������(����ʱ30������)";break;
		case 11:task="11: ע��";break;
		case 12:task="12: ��������";break;
		case 13:task="13: �������";break;
		case 14:task="14: ��������";break;
		case 15:task="15: �ر���ʾ��";break;
		case 16:task="16: �ر����д���";break;
		default:task="?:????";break;
		}
		temp.Format("taskdate%d",i);
		taskdate=AfxGetApp()->GetProfileStringA("taskdate",temp);
		temp.Format("tasktime%d",i);
		tasktime=AfxGetApp()->GetProfileStringA("tasktime",temp);
		taskdate+="  ";
		taskdate+=tasktime;
		taskdate+="  ִ�в���";
		taskdate+=task;
		m_list1.InsertString(i-1,taskdate);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogTask::OnBnClickedOk()//ȷ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	if(tasknum>=20)
	{
		AfxMessageBox("�Բ������ֻ�����20������");
		return;
	}
	tasknum++;
	AfxGetApp()->WriteProfileInt("task","tasknum",tasknum);
	CString temp;
	CString temp2;
	CString task;
	temp=m_taskdate.Format("%Y-%m-%d");
	task+=temp;
	task+="  ";
	temp2.Format("taskdate%d",tasknum);
	AfxGetApp()->WriteProfileStringA("taskdate",temp2,temp);
	temp=m_tasktime.Format("%H:%M:%S");
	task+=temp;
	task+="  ִ�в���";
	temp2.Format("tasktime%d",tasknum);
	AfxGetApp()->WriteProfileStringA("tasktime",temp2,temp);
	int index=m_task.GetCurSel();
	temp2.Format("task%d",tasknum);
	AfxGetApp()->WriteProfileInt("task",temp2,index);
	switch(index)
	{
		case 0:task+="0: δѡ�����";break;
		case 1:task+="1: �رռ����";break;
		case 2:task+="2: �������������";break;
		case 3:task+="3: �������";break;
		case 4:task+="4: ���ļ���";break;
		case 5:task+="5: �򿪳���";break;
		case 6:task+="6: ���������Ƭ";break;
		case 7:task+="7: �򿪹���";break;
		case 8:task+="8: ɨ�財��";break;
		case 9:task+="9: �رռ����(����ʱ30������)";break;
		case 10:task+="10: �������������(����ʱ30������)";break;
		case 11:task+="11: ע��";break;
		case 12:task+="12: ��������";break;
		case 13:task+="13: �������";break;
		case 14:task+="14: ��������";break;
		case 15:task+="15: �ر���ʾ��";break;
		case 16:task+="16: �ر����д���";break;
		default:task+="?: ????";break;
	}
	m_list1.InsertString(tasknum-1,task);
	this->UpdateData(FALSE);
	//OnOK();
}

void CDialogTask::OnBnClickedDelete()//ɾ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	CString temp;
	CString task;
	char date[12];
	char time[10];
	int curtask;
	int i,j;
	for(i=1;i<=tasknum;i++)
	{
		temp.Format("task%d",i);
		AfxGetApp()->WriteProfileInt("task",temp,NULL);
		temp.Format("taskdate%d",i);
		AfxGetApp()->WriteProfileStringA("taskdate",temp,NULL);
		temp.Format("tasktime%d",i);
		AfxGetApp()->WriteProfileStringA("tasktime",temp,NULL);
	}
	tasknum--;
	AfxGetApp()->WriteProfileInt("task","tasknum",tasknum);
	int t=m_list1.GetCurSel();
	m_list1.DeleteString(t);
	for(i=0;i<tasknum;i++)
	{
		m_list1.GetText(i,task);
		for(j=0;j<10;j++)
		{
			date[j]=task[j];
		}
		date[10]='\0';
		for(j=12;j<=19;j++)
		{
			time[j-12]=task[j];
		}
		time[8]='\0';
		if(task[31]==':')
			curtask=task[30]-48;
		else
			curtask=(task[30]-48)*10+task[31]-48;
		temp.Format("task%d",i+1);
		AfxGetApp()->WriteProfileInt("task",temp,curtask);
		temp.Format("taskdate%d",i+1);
		AfxGetApp()->WriteProfileStringA("taskdate",temp,date);
		temp.Format("tasktime%d",i+1);
		AfxGetApp()->WriteProfileStringA("tasktime",temp,time);
	}
	this->UpdateData(FALSE);

}
