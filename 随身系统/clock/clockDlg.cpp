// clockDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "clock.h"
#include "clockDlg.h"
#include "InputBox.h"
#include <cmath>
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")
#define pi 3.1415926535897932384626433832795028841971693993751058209

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CclockDlg �Ի���




CclockDlg::CclockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CclockDlg::IDD, pParent)
	, m_timer(0)
	, point1(0)
	, point2(0)
	, ss(0)
	, m(0)
	, h(0)
	, hoursound(false)
	, halfhoursound(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CclockDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_COMMAND(ID_CLOSE, &CclockDlg::OnClose)
	ON_COMMAND(ID__SOUNDTIME, &CclockDlg::OnSound)
	ON_COMMAND(ID__RING, &CclockDlg::OnSetRingTime)
	ON_COMMAND(ID__OPERATION, &CclockDlg::OnOperation)
	ON_COMMAND(ID__TASK, &CclockDlg::OnSetTask)
END_MESSAGE_MAP()


// CclockDlg ��Ϣ�������

BOOL CclockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���ó�������ʱ��������������������ʾͼ��
	SetWindowLong(this->m_hWnd,GWL_EXSTYLE,WS_EX_TOOLWINDOW); 
	
	//���ÿ���ʱ���߶��Ĵ�����Ϊÿ��һ�Σ�������WM_TIMER��Ϣ��Ƶ����ÿ��һ�Ρ�
	m_timer = this->SetTimer(1, 1000, NULL);
	
/////////////////////////////////////////////////////////////
	//��Բ�ζԻ���
	CRgn  rgn;   
	CRect  rc;   
	GetClientRect(&rc);   
    rgn.CreateEllipticRgn(rc.left,rc.top,rc.right,rc.bottom);   
    SetWindowRgn(rgn,TRUE);   
    rgn.DeleteObject();  
//////////////////////////////////////////////////////////////
	//��ʱ�ӱ���ͼƬ��Բ�ζԻ��򱳾�
	CBitmap   bm;   
	bm.LoadBitmap(IDB_BITMAP1);   //   IDB_BITMAP1ΪBITMAP��ԴID,����ָ��bitmapͼƬ��·��   
	m_brush.CreatePatternBrush(&bm);   

	//SoundTime();
	//sndPlaySoundA("AM.wav",SND_ASYNC);
	//���Ի���ľ�����ݵ�CWinSunApp���С�sunxin
//	((CclockApp*)AfxGetApp())->m_hwndDlg=m_hWnd;



	//������ʱ�߳�
	DWORD dwParam;
	pThread=AfxBeginThread(ThreadProc,&dwParam,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread==NULL)
		AfxMessageBox("�����̴߳���!");


	//���������߳�
	DWORD dwParam2;
	pThread2=AfxBeginThread(ThreadProc2,&dwParam2,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread2==NULL)
		AfxMessageBox("�����̴߳���!");


	//��������ʱ�����߳�
	DWORD dwParam3;
	pThread3=AfxBeginThread(ThreadProc3,&dwParam3,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread3==NULL)
		AfxMessageBox("�����̴߳���!");



	int temp=AfxGetApp()->GetProfileInt("Sound","hoursound",0);
	if(temp==1)				//�ж��Ƿ����㱨ʱ
		hoursound=true;
	else
		hoursound=false;
	temp=AfxGetApp()->GetProfileInt("Sound","halfhoursound",0);
	if(temp==1)				//�ж��Ƿ��㱨ʱ
		halfhoursound=true;
	else
		halfhoursound=false;



	ringnum=AfxGetApp()->GetProfileIntA("ring","ringnum",0);//��������
	CString time;
	CString temps;
	for(int i=0;i<ringnum;i++)//��ע�����ȡ��������Ϣ�����ڽṹ��������
	{
		temps.Format("ring%d",i+1);
		time=AfxGetApp()->GetProfileStringA("ring",temps);
		mytimearray[i].hour=(time[0]-48)*10+time[1]-48;
		mytimearray[i].minute=(time[3]-48)*10+time[4]-48;
		mytimearray[i].second=(time[6]-48)*10+time[7]-48;
	}

	tasknum=AfxGetApp()->GetProfileIntA("task","tasknum",0);//��ʱ��������
	CString taskdate;
	CString tasktime;
	for(int i=0;i<tasknum;i++)		//��ע�����ȡ����ʱ������Ϣ�������ڶ�ʱ����ṹ����
	{
		temps.Format("taskdate%d",i+1);
		taskdate=AfxGetApp()->GetProfileStringA("taskdate",temps);
		temps.Format("tasktime%d",i+1);
		tasktime=AfxGetApp()->GetProfileStringA("tasktime",temps);
		mytaskarray[i].year=(taskdate[0]-48)*1000+(taskdate[1]-48)*100+(taskdate[2]-48)*10+taskdate[3]-48;
		mytaskarray[i].month=(taskdate[5]-48)*10+taskdate[6]-48;
		mytaskarray[i].day=(taskdate[8]-48)*10+taskdate[9]-48;
		mytaskarray[i].hour=(tasktime[0]-48)*10+tasktime[1]-48;
		mytaskarray[i].minute=(tasktime[3]-48)*10+tasktime[4]-48;
		mytaskarray[i].second=(tasktime[6]-48)*10+tasktime[7]-48;
		temps.Format("task%d",i+1);
		mytaskarray[i].typle=AfxGetApp()->GetProfileIntA("task",temps,0);
	}





	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CclockDlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		OnTimer(m_timer);
		CDialog::OnPaint();
	}	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CclockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CclockDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION :CDialog::OnNcHitTest(point);

//	return CDialog::OnNcHitTest(point);
}

void CclockDlg::OnTimer(UINT_PTR nIDEvent)//����ʱ���߶�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�жϴ��ݹ�����ʱ�Ӵ������Ƿ����Լ������ʱ�Ӵ�����
	if(nIDEvent == m_timer) 
	{
		//��õ�ǰϵͳʱ�䡣
		CTime time = CTime::GetCurrentTime();
		int C;							//���ڼ�����ɫ
		CPen *PenOld,PenNew;
		CBrush *BrushOld,BrushNew;
		CClientDC dc(this);
		int S=time.GetSecond();
		float M=float(time.GetMinute()+S/60.0);
		float H=float(time.GetHour()+M/60.0);
		if(H>12)
			H=H-12;
		H=H*5;
		point1.x=103;
		point1.y=102;

//		OnPaint();
		//����Ϊ��ʱ����������
		//����Ϊ��ÿ����ǰ�ñ���ɫ��ȥ��һ�λ����루���ڱ���ɫ���䣬���Լ����˼��㣩
//////////////////////////////////////////////	
		if(h<5)
			C=232;
		else if(h<10)
			C=235;
		else if(h<15)
			C=242;
		else if(h<20)
			C=247;
		else if(h<30)
			C=248;
		else if(h<35)
			C=244;
		else if(h<40)
			C=242;
		else if(h<47)
			C=235;
		else
			C=230;

		PenNew.CreatePen(PS_SOLID,4,RGB(C,C,C));
		BrushNew.CreateSolidBrush(RGB(C,C,C));
		BrushOld=dc.SelectObject(&BrushNew);
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+35*sin(h*pi/30);
		point2.y=102-35*cos(h*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);


		PenNew.DeleteObject();
		PenNew.CreatePen(PS_SOLID,4,RGB(0,0,0));
		PenOld=dc.SelectObject(&PenNew);
		BrushNew.DeleteObject();
		BrushNew.CreateSolidBrush(RGB(0,0,0));
		BrushOld=dc.SelectObject(&BrushNew);
		point2.x=103+35*sin(H*pi/30);
		point2.y=102-35*cos(H*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);
///////////////////////////////////////////////
		if(m<5)
			C=232;
		else if(m<10)
			C=235;
		else if(m<15)
			C=242;
		else if(m<20)
			C=247;
		else if(m<30)
			C=248;
		else if(m<35)
			C=244;
		else if(m<40)
			C=242;
		else if(m<47)
			C=235;
		else
			C=230;

		BrushNew.DeleteObject();
		BrushNew.CreateSolidBrush(RGB(C,C,C));
		BrushOld=dc.SelectObject(&BrushNew);
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_SOLID,4,RGB(C,C,C));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+55*sin(m*pi/30);
		point2.y=102-55*cos(m*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);



		BrushNew.DeleteObject();
		BrushNew.CreateSolidBrush(RGB(0,0,0));
		BrushOld=dc.SelectObject(&BrushNew);
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_SOLID,4,RGB(0,0,0));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+55*sin(M*pi/30);
		point2.y=102-55*cos(M*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);
		
////////////////////////////////////////////	������Ķ���	
		ss=(ss+30)%60;
		S=(S+30)%60;
		if(ss<5)
			C=232;
		else if(ss<10)
			C=235;
		else if(ss<15)
			C=242;
		else if(ss<20)
			C=247;
		else if(ss<30)
			C=248;
		else if(ss<35)
			C=244;
		else if(ss<40)
			C=242;
		else if(ss<47)
			C=235;
		else
			C=230;
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_DASHDOTDOT,2,RGB(C,C,C));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+10*sin(ss*pi/30);
		point2.y=102-10*cos(ss*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);


		PenNew.DeleteObject();
		PenNew.CreatePen(PS_DASHDOTDOT,2,RGB(255,0,0));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+10*sin(S*pi/30);
		point2.y=102-10*cos(S*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);


///////////////////////������ĳ���
		ss=(ss+30)%60;
		S=(S+30)%60;
		if(ss<5)
			C=232;
		else if(ss<10)
			C=235;
		else if(ss<15)
			C=242;
		else if(ss<20)
			C=247;
		else if(ss<30)
			C=248;
		else if(ss<35)
			C=244;
		else if(ss<40)
			C=242;
		else if(ss<47)
			C=235;
		else
			C=230;
//		BrushNew.DeleteObject();
//		BrushNew.CreateSolidBrush(RGB(C,C,C));
//		BrushOld=dc.SelectObject(&BrushNew);
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_DASHDOTDOT,2,RGB(C,C,C));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+63*sin(ss*pi/30);
		point2.y=102-63*cos(ss*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);


//		BrushNew.DeleteObject();
//		BrushNew.CreateSolidBrush(RGB(255,0,0));
//		BrushOld=dc.SelectObject(&BrushNew);
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_DASHDOTDOT,2,RGB(255,0,0));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+63*sin(S*pi/30);
		point2.y=102-63*cos(S*pi/30);
		dc.MoveTo(point1);
		dc.LineTo(point2);



/*//////////////////////////////////////////////////////////////////
		CBrush m_brush_trad_s;
		CBitmap   bm_trad_s;   
		bm_trad_s.LoadBitmap(IDB_Trad_s);   //   IDB_Trad_sΪBITMAP��ԴID,����ָ��bitmapͼƬ��·��   
		m_brush_trad_s.CreatePatternBrush(&bm_trad_s); 
		BrushOld=dc.SelectObject(&m_brush_trad_s);
		PenNew.DeleteObject();
		PenNew.CreatePen(PS_NULL,1,RGB(255,255,255));//(PS_DASHDOTDOT,2,RGB(255,0,0));
		PenOld=dc.SelectObject(&PenNew);
		point2.x=103+63*sin(S*pi/30);
		point2.y=102-63*cos(S*pi/30);
		dc.Rectangle(94,40,107,169);
*///////////////////////////////////////////////////////////////////
		h=H;m=M;ss=S;
//////////////////////////////////////////////////////////////////
		dc.SetPixel(point1,RGB(0,0,0));
		dc.SetPixel(point1.x+1,point1.y,RGB(0,0,0));
		dc.SetPixel(point1.x,point1.y+1,RGB(0,0,0));
		dc.SetPixel(point1.x+1,point1.y+1,RGB(0,0,0));
		dc.SetPixel(point1.x-1,point1.y,RGB(0,0,0));
		dc.SetPixel(point1.x,point1.y-1,RGB(0,0,0));
		dc.SetPixel(point1.x-1,point1.y-1,RGB(0,0,0));





		for(int i=0;i<ringnum;i++)//�ж��Ƿ�������Ӧ��ִ��
		{
			if(time.GetHour()==mytimearray[i].hour&&time.GetMinute()==mytimearray[i].minute&&time.GetSecond()==mytimearray[i].second)
			{
				pThread2->ResumeThread();
				break;
			}
		}



		for(int i=0;i<tasknum;i++)//�ж��Ƿ��ж�ʱ����Ӧ��ִ��
		{
			if(time.GetYear()==mytaskarray[i].year&&time.GetMonth()==mytaskarray[i].month&&time.GetDay()==mytaskarray[i].day)
			{
				if(time.GetHour()==mytaskarray[i].hour&&time.GetMinute()==mytaskarray[i].minute&&time.GetSecond()==mytaskarray[i].second)
				{
					tasktyple=mytaskarray[i].typle;
					pThread3->ResumeThread();
					break;
				}
			}
		}


		if(hoursound&&S==0&&M==0)//�ж��Ƿ����㱨ʱ
			SoundTime();
		//�ж��Ƿ��㱨ʱ
		if(halfhoursound&&S==0&&(M==0||M==30))
			SoundTime();
		this->UpdateData(false);
	}
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CclockDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brush;
}

// ��ʱ����
bool CclockDlg::SoundTime(void)
{
	pThread->ResumeThread();//���ʱ�߳�
	return true;
}

//void CclockDlg::OnRButtonDown(UINT nFlags, CPoint point)
//{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	MessageBox(L"������֮ǰ");
//	OnContextMenu(this);
//	MessageBox(L"������֮��");

//	CDialog::OnRButtonDown(nFlags, point);
//}

// �Ҽ������˵�������
void CclockDlg::OnContextMenu(CWnd* pWnd)
{
	CMenu menu;
	if(menu.LoadMenu(IDR_MENU))
	{
		CMenu * popup=menu.GetSubMenu(0);
		ASSERT(popup!=NULL);
		CPoint mouse;
		GetCursorPos(& mouse);
		//::SetForegroundWindow(data.hWnd);
		popup->TrackPopupMenu(TPM_LEFTALIGN,mouse.x,mouse.y,pWnd,NULL);
	}
}

void CclockDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)//�Ҽ����������Ϣ������
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnContextMenu(this);
	CDialog::OnNcRButtonDown(nHitTest, point);
}

void CclockDlg::OnClose()//�ر�ʱ�ӳ���
{
	// TODO: �ڴ���������������
	pThread->SuspendThread();//�رճ���ǰ�������������߳�
	pThread2->SuspendThread();
	pThread3->SuspendThread();
	exit(0);
}

void CclockDlg::OnSound()
{
	// TODO: �ڴ���������������
	//pThread->ResumeThread();
	SoundTime();
}
UINT ThreadProc(LPVOID pParam)//��ʱ�߳�
{
	while(1)
	{
		pThread3->SuspendThread();//���������߳�
		pThread2->SuspendThread();
		CTime m_NowTime;
		m_NowTime = CTime::GetCurrentTime();
		int n_Hour = m_NowTime.GetHour();
		//����Ϊ��ʱ����,ԭ��Ϊͨ���Ե�ǰʱ����ж�,���ò�ͬ�������ļ�(��Դ�ļ�)������ϲ���,�γɱ�ʱЧ��
		PlaySound(MAKEINTRESOURCE(IDR_WAVETIMENOW),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		Sleep(1550);
		if(n_Hour<8)
			PlaySound(MAKEINTRESOURCE(IDR_WAVEMM),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		else if(n_Hour<13)
			PlaySound(MAKEINTRESOURCE(IDR_WAVEAM),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		else if(n_Hour<19)
			PlaySound(MAKEINTRESOURCE(IDR_WAVEPM),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		else
			PlaySound(MAKEINTRESOURCE(IDR_WAVEEM),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		if (n_Hour>12)
		{
		   n_Hour = n_Hour-12;
		}
		int n_Minute = m_NowTime.GetMinute();
		int n_Second = m_NowTime.GetSecond();

		//PlaySound(("c:\\chs\\4.wav"),NULL, SND_ASYNC|SND_NODEFAULT );

		//sndPlaySound ("c:\\chs\\4.wav",SND_ALIAS);

		Sleep(580);
		switch (n_Hour)
		{
		case 0:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET00),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		case 1:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET01),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 2:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET2),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 3:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET03),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 4:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET04),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 5:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET05),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 6:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET06),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 7:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET07),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 8:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET08),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 9:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET09),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 10:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET10),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 11:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET11),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		case 12:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET12),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		   break;
		}
		if(n_Hour<10)
			Sleep(450);
		else
			Sleep(550);
		PlaySound(MAKEINTRESOURCE(IDR_WAVEPOINT),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		Sleep(500);

		int n_Front_Min;
		int n_Behind_Min;
		int n_FTemp = n_Minute;

		n_Front_Min = n_Minute/10;
		n_Behind_Min = n_Minute%10;

		if (n_Front_Min<=0)
		{
			if(n_FTemp!=0)
				PlaySound(MAKEINTRESOURCE(IDR_WAVET00),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			Sleep(400);
			switch (n_FTemp)
			{
			case 0:
			break;
			case 1:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET01),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 2:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET02),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 3:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET03),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 4:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET04),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 5:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET05),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 6:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET06),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 7:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET07),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 8:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET08),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			case 9:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET09),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
			default:
			break;
			}
			Sleep(500);
			if(n_FTemp!=0)
				PlaySound(MAKEINTRESOURCE(IDR_WAVEMIN),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);

		}
		else
		{
		   switch (n_Front_Min)
		   {
		   case 1:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET10),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 2:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET20),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 3:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET30),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 4:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET40),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 5:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET50),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   }
		   if(n_Front_Min==1)
			   Sleep(470);
		   else if(n_Front_Min==4)
			   Sleep(565);
		   else if(n_Behind_Min>0)
			   Sleep(520);
		   switch (n_Behind_Min)
		   {
		   case 1:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET01),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 2:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET02),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 3:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET03),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 4:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET04),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 5:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET05),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 6:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET06),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 7:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET07),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 8:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET08),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   case 9:
			PlaySound(MAKEINTRESOURCE(IDR_WAVET09),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
			break;
		   }

		   Sleep(560);
			PlaySound(MAKEINTRESOURCE(IDR_WAVEMIN),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		}
		pThread3->ResumeThread();
		pThread->SuspendThread();
	}
	return 0;
}



void CclockDlg::OnSetRingTime()//��������ʱ��
{
	CDialogRing dlg(this);
	dlg.DoModal();//�����������ӶԻ���,�����ñ�����ע�����
	ringnum=AfxGetApp()->GetProfileIntA("ring","ringnum",0);
	CString time;
	CString temps;
	for(int i=0;i<ringnum;i++)//��ע����ж�ȡ�޸ĺ�����ݴ���ṹ������
	{
		temps.Format("ring%d",i+1);
		time=AfxGetApp()->GetProfileStringA("ring",temps);
		mytimearray[i].hour=(time[0]-48)*10+time[1]-48;
		mytimearray[i].minute=(time[3]-48)*10+time[4]-48;
		mytimearray[i].second=(time[6]-48)*10+time[7]-48;
	}
	// TODO: �ڴ���������������
}

void CclockDlg::OnOperation()//ѡ��˵�
{
	CDialogOption dlg(this);
	dlg.DoModal();//ѡ��Ի���
	if(dlg.CheckHour)
		hoursound=true;
	else
		hoursound=false;
	if(dlg.CheckHalfHour)
		halfhoursound=true;
	else
		halfhoursound=false;

	// TODO: �ڴ���������������
}

void CclockDlg::OnSetTask()//���ö�ʱ����
{
	// TODO: �ڴ���������������
	CDialogTask dlg(this);
	dlg.DoModal();//�������ö�ʱ����Ի���,�����ñ�����ע�����
	tasknum=AfxGetApp()->GetProfileIntA("task","tasknum",0);
	CString taskdate;
	CString tasktime;
	CString temps;
	for(int i=0;i<tasknum;i++)//��ע����ж�ȡ�޸ĺ�����ݴ���ṹ������
	{
		temps.Format("taskdate%d",i+1);
		taskdate=AfxGetApp()->GetProfileStringA("taskdate",temps);
		temps.Format("tasktime%d",i+1);
		tasktime=AfxGetApp()->GetProfileStringA("tasktime",temps);
		mytaskarray[i].year=(taskdate[0]-48)*1000+(taskdate[1]-48)*100+(taskdate[2]-48)*10+taskdate[3]-48;
		mytaskarray[i].month=(taskdate[5]-48)*10+taskdate[6]-48;
		mytaskarray[i].day=(taskdate[8]-48)*10+taskdate[9]-48;
		mytaskarray[i].hour=(tasktime[0]-48)*10+tasktime[1]-48;
		mytaskarray[i].minute=(tasktime[3]-48)*10+tasktime[4]-48;
		mytaskarray[i].second=(tasktime[6]-48)*10+tasktime[7]-48;
		temps.Format("task%d",i+1);
		mytaskarray[i].typle=AfxGetApp()->GetProfileIntA("task",temps,0);
	}

}
UINT ThreadProc2(LPVOID pParam)//�����߳�
{
	while(1)
	{
		pThread->SuspendThread();//�������������߳�
		pThread3->SuspendThread();
		PlaySound(MAKEINTRESOURCE(IDR_WAVESOUND),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		Sleep(7000);
		PlaySound(MAKEINTRESOURCE(IDR_WAVESOUND),AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		Sleep(8000);
		pThread->ResumeThread();//�ָ������߳�
		pThread3->ResumeThread();
		pThread2->SuspendThread();
	}
	return 0;
}
UINT ThreadProc3(LPVOID pParam)//����ʱ�����߳�
{
	while(1)
	{
		switch(tasktyple)
		{
		case 1:
			{
				AfxMessageBox("��ע�⣬ϵͳ�����رգ��뱣�湤�����ȷ������");
				system("shutdown -s -t 0");
			}break;
		case 2:
			{
				AfxMessageBox("��ע�⣬ϵͳ���������������뱣�湤�����ȷ������");
				system("shutdown -r -t 0");
			}break;
		case 3:
			{
				CInputBox dlg;
				if(dlg.DoModal()==IDOK)
				{
					CString str;
					str="\"";
					str+=dlg.InputStr;
					str+="\"";
					char szMailAddress[80];
					strcpy(szMailAddress,str);
					ShellExecute(NULL,"open",szMailAddress,NULL,NULL,SW_SHOWNORMAL);
				}
			}break;
		case 4:
			{
				CInputBox dlg;
				if(dlg.DoModal()==IDOK)
				{
					CString str;
					str="\"";
					str+=dlg.InputStr;
					str+="\"";
					char szMailAddress[80];
					strcpy(szMailAddress,str);
					ShellExecute(NULL,"open",szMailAddress,NULL,NULL,SW_SHOWNORMAL);
				}

			}break;
		case 5:
			{
				AfxMessageBox("�Բ��𣬱�ģ�����ڿ����У������ڴ���");
				//AfxMessageBox("�򿪳���");
				//WinExec("notepad.exe",SW_SHOW); //���м��±� 
			}break;
		case 6:
			{
				//OSVERSIONINFO OsVersionInfo;
				//OsVersionInfo.dwPlatformId 
				system("dfrg.msc");			//XP����
				system("defrag -c");		//vista����
				system("dfrgui");			//
			}break;
		case 7:
			{
				mciSendString("Set cdAudio door open wait",NULL,0,NULL);
				AfxMessageBox("��ע�⣬�����Ѿ��򿪣��������̣�װ����̺���ȷ�����رչ�����");
				mciSendString("Set cdAudio door closed wait",NULL,0,NULL);
			}break;
		case 8:
			{
				AfxMessageBox("�Բ��𣬱�ģ�����ڿ����У������ڴ���");
			}break;
		case 9:
			{
				system("shutdown -s -t 30");
			}break;
		case 10:
			{
				system("shutdown -r -t 30");
			}break;
		case 11:
			{
				AfxMessageBox("��ע�⣬ϵͳ����ע�����뱣�湤�����ȷ������");
				system("logoff");
			}break;
		case 12:
			{
				SetWindowsHookEx(WH_KEYBOARD,keyproc,GetModuleHandle(NULL),0);//��װ���̹���

				AfxMessageBox("������������ֻ��XPϵͳ��Ч���������������رձ���������������������");

			}break;
		case 13:
			{
				RECT rect;
				rect.bottom=1;
				rect.right=1;

				ClipCursor(&rect);

				//AfxMessageBox("�������������������뷴�������꣡");

				//::Sleep(36000000);

				//ClipCursor(NULL);//�ͷ�

			}break;
		case 14:
			{
				HWND disk,mask;

				disk=FindWindow("ProgMan",NULL);

				mask=FindWindow("Shell_TrayWnd",NULL);

				ShowWindow(mask,SW_HIDE);//����������

				ShowWindow(disk,SW_HIDE);//��������

				//AfxMessageBox("10���Ӻ���Զ���������.....");

				Sleep(360000000);

				ShowWindow(mask,SW_SHOW);//��ʾ

				ShowWindow(disk,SW_SHOW);//��ʾ


			}break;
		case 15:
			{
				//AfxMessageBox("�ر���ʾ��");
				 SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,2);//�ر�

				 //Sleep(600000);

				 //SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,-1);//��
			}break;
		case 16:
			{
				Sleep(0);
				EnumWindows(EnumWindowsProc,0);//�����ھ�������ص���������

			}break;
		default:break;
		}
		pThread3->SuspendThread();
	}
	return 0;
}
LRESULT CALLBACK keyproc(int code,WPARAM wParam,LPARAM lParam)
{
	return 1;//����1��ʹ����ֹͣ��Ӧ
} 
BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM IParam)//�ص�����

{
	Sleep(0);

    ::PostMessage(hwnd,WM_CLOSE,0,0);//��������

 return (true);//����FALSEʱEnumWindows����

}

