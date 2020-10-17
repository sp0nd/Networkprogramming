
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

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


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
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

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

short id = 100;
int day = 20200925;
int tm = 181723;
short temp = 25;
short hum = 70;
short press = 1000;

int dt[2] = { 20200925, 181723 };
short data[3] = { 25, 70, 1000 };

// text
void CMFCApplication1Dlg::OnBnClickedOk()
{
	//// FILE 구조체를 이용한 방법 - txt
	//FILE* fp;
	//errno_t er = fopen_s(&fp, "test.txt", "wt");

	//for (int i = 0; i < 100; i++)
	//{
	//	fprintf(fp, "%d,%d,%d,%d,%d,%d\n", id+i, day, tm, temp + i, hum + i, press + i);
	//}
	//fclose(fp);


	//// FILE 구조체를 이용한 방법 - bin
	//er = fopen_s(&fp, "test.bin", "wb");

	//for (int i = 0; i < 100; i++)
	//{
	//	short id1 = id + i;
	//	short temp1 = temp + i;
	//	short hum1 = hum + i;
	//	short press1 = press + i;

	//	fwrite(&id1,	sizeof(short), 1, fp);
	//	fwrite(&day,	sizeof(int), 1, fp);
	//	fwrite(&tm,		sizeof(int), 1, fp);
	//	fwrite(&temp1,	sizeof(short), 1, fp);
	//	fwrite(&hum1,	sizeof(short), 1, fp);
	//	fwrite(&press1,	sizeof(short), 1, fp);
	//}
	//fclose(fp);

	// CStdioFile 클래스를 사용한 Text 파일 쓰기
	//CStdioFile sfile;
	//CString str;
	//if (!sfile.Open("test.txt", CFile::modeWrite|CFile::modeCreate))	return;
	//for (int i = 0; i < 100; i++)
	//{
	//	str.Format("%d,%d,%d,%d,%d,%d\n", id+i, day, tm, temp + i, hum + i, press + i);
	//	sfile.WriteString(str);
	//}
	//sfile.Close();

	// CFile 클래스를 사용한 Binary 파일 쓰기 (bin 텍스트로 보기F3 누른후 3번)
	//CFile file;
	//if (!file.Open("test.bin", CFile::modeWrite|CFile::modeCreate))	return;
	//for (int i = 0; i < 100; i++)
	//{
	//	short id1 = id + i;
	//	short temp1 = temp + i;
	//	short hum1 = hum + i;
	//	short press1 = press + i;

	//	file.Write(&id1,	sizeof(short));
	//	file.Write(&day,	sizeof(int));
	//	file.Write(&tm,		sizeof(int));
	//	file.Write(&temp1,	sizeof(short));
	//	file.Write(&hum1,	sizeof(short));
	//	file.Write(&press1,	sizeof(short));
	//}
	//file.Close();

	//int dt[2] = { 20200925, 181723 };
	//short data[3] = { 25, 70, 1000 };
	// CFile 클래스와 배열 데이터를 사용한 Binary 파일 쓰기
	CFile file;
	if (!file.Open("test.bin", CFile::modeWrite|CFile::modeCreate))	return;

	for (int i = 0; i < 100; i++)
	{
		short id1 = id + i;
		short data1[3];

		for (int j = 0 ; j < 3 ; j++)
			data1[j] = data[j] + i;

		file.Write(&id1,	sizeof(short));
		file.Write(dt,		sizeof(int)*2);
		file.Write(data1,	sizeof(short)*3);
	}
	file.Close();
}

// binary
void CMFCApplication1Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
