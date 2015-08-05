// clockDlg.h : ͷ�ļ�
//

#pragma once
#include "atltypes.h"
#include "afxwin.h"
#include "DialogRing.h"
#include "DialogOption.h"
#include "DialogTask.h"


// CclockDlg �Ի���
class CclockDlg : public CDialog
{
// ����
public:
	CclockDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	// ʱ�Ӵ�����
	UINT m_timer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CPoint point1;
	CPoint point2;
	int ss;
	float m;
	float h;
	CBrush m_brush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// ��ʱ����
	bool SoundTime(void);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// �Ҽ������˵�������
	void OnContextMenu(CWnd* pWnd);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnSound();
	afx_msg void OnSetRingTime();
	afx_msg void OnOperation();
	afx_msg void OnSetTask();
	bool hoursound;
	bool halfhoursound;
	struct mytime
	{
		int hour;
		int minute;
		int second;
	};
	mytime mytimearray[20];

protected:
	int ringnum;
	int tasknum;
public:
	struct mytasktime
	{
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		int typle;
	};
	mytasktime mytaskarray[20];
};
	static CWinThread* pThread;
	static CWinThread* pThread2;
	static CWinThread* pThread3;
	static int tasktyple=0;
	UINT ThreadProc(LPVOID pParam);
	UINT ThreadProc2(LPVOID pParam);
	UINT ThreadProc3(LPVOID pParam);
	LRESULT CALLBACK keyproc(int code,WPARAM wParam,LPARAM lParam);
	BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM IParam);
