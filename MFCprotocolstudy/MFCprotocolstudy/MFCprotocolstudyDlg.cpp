
// MFCprotocolstudyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCprotocolstudy.h"
#include "MFCprotocolstudyDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <windows.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCprotocolstudyDlg 대화 상자



CMFCprotocolstudyDlg::CMFCprotocolstudyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROTOCOLSTUDY_DIALOG, pParent)
	
	
	, m_Pport(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCprotocolstudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST2, m_ctrlIPaddr);
	DDX_Control(pDX, IDC_IPADDRESS1, m_straddr);
	DDX_Text(pDX, IDC_Pport, m_Pport);
}

BEGIN_MESSAGE_MAP(CMFCprotocolstudyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNGEN, &CMFCprotocolstudyDlg::OnBnClickedBtngen)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCprotocolstudyDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BTNSAVEAS, &CMFCprotocolstudyDlg::OnBnClickedBtnsaveas)
	ON_BN_CLICKED(IDC_BTNCONNECT, &CMFCprotocolstudyDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BTNSEND, &CMFCprotocolstudyDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNADD, &CMFCprotocolstudyDlg::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, &CMFCprotocolstudyDlg::OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_BTNRESET, &CMFCprotocolstudyDlg::OnBnClickedBtnreset)
	
END_MESSAGE_MAP()


// CMFCprotocolstudyDlg 메시지 처리기

BOOL CMFCprotocolstudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCprotocolstudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCprotocolstudyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCprotocolstudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// count	 : 1~5 사이 랜덤생성
// id		 : 100~200 사이 랜덤으로 생성
// day,time  : 현재 일시로 설정
// temperate : -20~35사이 랜덤생성 , 같은 id의 이전 온도와의 차이는 2 이하
// humidity  : 0~100사이 랜덤으로 생성, 같은 id의 이전 습도와의 차이는 5이하
// pressur   : 600~1200사이 랜덤으로 생성, 같은 id의 이전 압력과의 차이는 10이하
//void CMFCprotocolstudyDlg::OnBnClickedBtngen()
//{
//	struct tm* nowtime = localtime(&t);
//	time_t t = time(NULL);
//	int count, id, day,time1, time2, time3, temp, humi, press;
//	
//	CString ntime;
//
//	day = nowtime->tm_mday;
//	time1 = nowtime->tm_hour;
//	time2 = nowtime->tm_min;
//	time3 = nowtime->tm_sec;
//	ntime.Format(_T("%&d : %d-%d-%d"), day, time1, time2, time3);
//
///*	struct tm nowtime = *localtime(&t);
//	day = nowtime.tm_mday;
//	time1 = nowtime.tm_hour;
//	time2 = nowtime.tm_min;
//	time3 = nowtime.tm_sec*/
//	srand((unsigned int)time(NULL));
//	CString str;
//	for (;;)
//	{
//		count = rand() % 5 + 1;
//		id = rand() % 101 + 100;
//		temp = rand() % 56 - 20;
//		humi = rand() % 101;
//		press = rand() % 601 + 600;
//		ntime;
//		if (==id)
//		{
//			m_ctrlList1.GetText(, str);
//
//			cout << str;
//		}
//		else
//			for (int i = 1; i < count; i++)
//			{
//				
//				str.Format(_T("%d > %d : %d ,%d ,%d ,%d"),count, id, ntime, temp, humi, press);
//				Sleep(1000);
//			}
//	}
//}
void CMFCprotocolstudyDlg::OnBnClickedBtngen()
{
	srand((unsigned int)time(NULL));

	DataManager dm;
	CString str;

	int seq = 0;
	while (seq < 10)
	{
		int count = rand() % 5 + 1;
		for (int i = 0; i < count; i++)
		{
			int id = rand() % 101 + 100;//id 랜덤값 생성

			LPDATA pd = dm.GetData(id);// 새로 생긴 데이터의 id를 pd에 넣어준다.
			if (pd == NULL)//id가 NULL이면 데이터가 없다는 뜻
			{
				LPDATA newpd = (LPDATA)malloc(sizeof(DATA));// 데이터를 넣기위해 메모리를 할당해준다.
				newpd->id = id;
				newpd->temp = rand() % 56 - 20;
				newpd->hum = rand() % 101;
				newpd->pres = rand() % 601 + 600;
				dm.AddData(newpd);

				str.Format("%3d:%s", seq, dm.GetString(newpd));
			}
			else
			{
				pd->temp += (rand() % 5 - 3);
				pd->hum += (rand() % 10 - 5);
				pd->pres += (rand() % 20 - 10);
				dm.SetData(pd);

				str.Format("%3d:%s", seq, dm.GetString(pd));
			}
			m_ctrlList1.AddString(str);
		}
		seq++;
	}
}

void CMFCprotocolstudyDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int CMFCprotocolstudyDlg::GetCountData(int seq, int start)
{
	int ret = 0;
	CString str;
	int size = m_ctrlList1.GetCount();
	for (int i = start; i < size; i++)
	{
		m_ctrlList1.GetText(i, str);   // str : 0:100,2020,.mm,.m.
		int idx = str.Find(":");
		int s = atoi(str.Left(idx));   // seq;
		if (s == seq) ret++;
	}
	return ret;
}
 
void CMFCprotocolstudyDlg::writeData(FILE* fp, CStringArray& arr)
{
	int count = arr.GetSize();// 같은 넘버 수
	int len = 2 + count * DATASIZE;//메모리 사이즈 계산

	BYTE* pbuf = (BYTE*)malloc(len);// 메모리 할당

	int offset = 0;
	memcpy(pbuf, &count, sizeof(short));   offset += sizeof(short);
	CString str;
	for (int i = 0; i < count; i++) // 스트링을 나누는 루프
	{
		str = arr.GetAt(i);

		int idx = str.Find(":");   // str 0:100,2020,.mm,.m.

		str = str.Mid(idx + 1);      // str 100,2020,.mm,.m.
		idx = str.Find(",");
		short id = atoi(str.Left(idx));
		memcpy(pbuf + offset, &id, sizeof(short));      offset += sizeof(short);

		str = str.Mid(idx + 1);      // str 2020,.mm,.m.
		idx = str.Find(",");
		int day = atoi(str.Left(idx));
		memcpy(pbuf + offset, &day, sizeof(int));      offset += sizeof(int);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		int tm = atoi(str.Left(idx));
		memcpy(pbuf + offset, &tm, sizeof(int));      offset += sizeof(int);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		short temp = atoi(str.Left(idx));
		memcpy(pbuf + offset, &temp, sizeof(short));   offset += sizeof(short);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		short hum = atoi(str.Left(idx));
		memcpy(pbuf + offset, &hum, sizeof(short));      offset += sizeof(short);

		str = str.Mid(idx + 1);
		short pres = atoi(str);
		memcpy(pbuf + offset, &pres, sizeof(short));   offset += sizeof(short);
	}
	fwrite(pbuf, len, 1, fp);
	free(pbuf);
}

void CMFCprotocolstudyDlg::sendData(SOCKET soc, CStringArray& arr)
{
	int count = arr.GetSize();// 같은 넘버 수
	int len = 2 + count * DATASIZE;//메모리 사이즈 계산

	BYTE* pbuf = (BYTE*)malloc(len);// 메모리 할당

	int offset = 0;
	memcpy(pbuf, &count, sizeof(short));   offset += sizeof(short);
	CString str;
	for (int i = 0; i < count; i++) // 스트링을 나누는 루프
	{
		str = arr.GetAt(i);

		int idx = str.Find(":");   // str 0:100,2020,.mm,.m.

		str = str.Mid(idx + 1);      // str 100,2020,.mm,.m.
		idx = str.Find(",");
		short id = atoi(str.Left(idx));
		memcpy(pbuf + offset, &id, sizeof(short));      offset += sizeof(short);

		str = str.Mid(idx + 1);      // str 2020,.mm,.m.
		idx = str.Find(",");
		int day = atoi(str.Left(idx));
		memcpy(pbuf + offset, &day, sizeof(int));      offset += sizeof(int);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		int tm = atoi(str.Left(idx));
		memcpy(pbuf + offset, &tm, sizeof(int));      offset += sizeof(int);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		short temp = atoi(str.Left(idx));
		memcpy(pbuf + offset, &temp, sizeof(short));   offset += sizeof(short);

		str = str.Mid(idx + 1);
		idx = str.Find(",");
		short hum = atoi(str.Left(idx));
		memcpy(pbuf + offset, &hum, sizeof(short));      offset += sizeof(short);

		str = str.Mid(idx + 1);
		short pres = atoi(str);
		memcpy(pbuf + offset, &pres, sizeof(short));   offset += sizeof(short);
	}
	send(soc,(const char*) pbuf, len, 0);
	free(pbuf);
}
// 리스트에 표시된 데이터를 바이너리 파일로 저장
void CMFCprotocolstudyDlg::OnBnClickedBtnsaveas()
{
	// FILE 구조체를 이용한 방법 - bin
	FILE* fp;
	errno_t er = fopen_s(&fp, "test.bin", "wb");

	int seq;
	CString str;
	int size = m_ctrlList1.GetCount();
	for (int i = 0; i < size; i++)
	{
		CStringArray arr;

		m_ctrlList1.GetText(i, str);   // str : 0:100,2020,.mm,.m.

		int idx = str.Find(":");
		seq = atoi(str.Left(idx));   // seq;

		//fprintf(fp, "%d\t%s\n", seq, str);
		arr.Add(str);

		int count = GetCountData(seq, i);
		for (int j = 1; j < count; j++)
		{
			m_ctrlList1.GetText(++i, str);   // str : 0:100,2020,.mm,.m.

			//fprintf(fp, "%d\t%s\n", seq, str);
			arr.Add(str);
		}
		//fprintf(fp, "\n\n");

		writeData(fp, arr);
	}

	fclose(fp);


}



void CMFCprotocolstudyDlg::OnBnClickedBtnconnect()
{
	CString str;
	int count = m_ctrlIPaddr.GetCount();
	for (int i = 0; i < count; i++)
	{
		CSocket soc;
		CString strIP;
		CString msg = "Success";
		m_ctrlIPaddr.GetText(i, str);
		int idx = str.Find(":");
		strIP = str.Left(idx);
		int idx1 = str.Find(":",idx + 1);
		int port;
		if (idx1 == -1)
			port = atoi(str.Mid(idx + 1));
		else
			port = atoi(str.Mid(idx + 1, idx1 - idx - 1));
		
		if (!soc.Create(0, SOCK_STREAM))
		{
			msg.Format("Create() failed !!! [%d]", GetLastError());
		}
		else
		{
			if (!soc.Connect(strIP, port))
			{
				msg.Format("Connect() failed !!! [%d]", GetLastError());
			}
		}
		soc.Close();
		str.Format("%s:%d:%s", strIP, port, msg);
		m_ctrlIPaddr.DeleteString(i);
		m_ctrlIPaddr.InsertString(i, str);

	}

}

//서버에 데이터를 전송(텍스트 형식이 아니라 바이너리 형식 사용)
void CMFCprotocolstudyDlg::OnBnClickedBtnsend()
{
	// FILE 구조체를 이용한 방법 - bin
	
	/*BOOL Create(
		UINT nSocketPort = 0,
		int nSocketType = SOCK_STREAM,
		LPCTSTR lpszSocketAddress = NULL);*/
	UpdateData(TRUE);
	if (m_ctrlList1.GetCount() == 0)
	{
		AfxMessageBox("데이터가 없습니다.");
		return;
	}
	CString str;
	int IPcount = m_ctrlIPaddr.GetCount();
	for (int i = 0; i < IPcount; i++)
	{
		CSocket soc;
		CString strIP;
		
		m_ctrlIPaddr.GetText(i, str);
		int idx = str.Find(":");
		strIP = str.Left(idx);
		int idx1 = str.Find(":", idx + 1);
		int port;

		if (idx1 == -1)	
			port = atoi(str.Mid(idx + 1));
		else
			port = atoi(str.Mid(idx + 1, idx1 - idx - 1));

		int Datacount = m_ctrlList1.GetCount();
		for (int j = 0; j < Datacount; j++)
		{
			CStringArray arr;

			soc.Create();
			soc.Connect(strIP, port);

			m_ctrlList1.GetText(j, str);		// "  0:100,20200926,438920"
			int Dataidx = str.Find(":");
			int seq = atoi(str.Left(Dataidx));	// 0

			arr.Add(str);

			int count = GetCountData(seq, j+1);
			for (int n = 0; n < count; n++)
			{
				m_ctrlList1.GetText(++j, str);
				arr.Add(str);
			}

			sendData(soc,arr);
			soc.Close();
		}
	}
}


void CMFCprotocolstudyDlg::OnBnClickedBtnadd()
{
	UpdateData(TRUE);

	CString strIP, strPort;
	BYTE ip0, ip1, ip2, ip3;
	m_straddr.GetAddress(ip0, ip1, ip2, ip3);
	strIP.Format("%d.%d.%d.%d", ip0, ip1, ip2, ip3);
	strPort.Format("%d", m_Pport);
	CString str = strIP + ":" + strPort;
	if (m_ctrlIPaddr.FindString(0, str) == LB_ERR)
		m_ctrlIPaddr.AddString(strIP + ":" + strPort);

}


void CMFCprotocolstudyDlg::OnBnClickedBtndelete()
{
	int stridx = m_ctrlIPaddr.GetCurSel();
	if ((stridx == LB_ERR))
	{
		AfxMessageBox("선택한 IP가 없습니다.");
		return;
	}
	else
		m_ctrlIPaddr.DeleteString(stridx);
}


void CMFCprotocolstudyDlg::OnBnClickedBtnreset()
{
	m_ctrlIPaddr.ResetContent();
}


