
// std2WinDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "std2Win.h"
#include "std2WinDlg.h"
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


// Cstd2WinDlg 대화 상자



Cstd2WinDlg::Cstd2WinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STD2WIN_DIALOG, pParent)
	, m_strMsg(_T(""))
	, m_strResult(_T(""))
	, m_snPort(5050)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSocket = NULL;
}

void Cstd2WinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strMsg);
	DDX_Text(pDX, IDC_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT2, m_snPort);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIPAddress);
}

BEGIN_MESSAGE_MAP(Cstd2WinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cstd2WinDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTNSEND, &Cstd2WinDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDOK2, &Cstd2WinDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// Cstd2WinDlg 메시지 처리기

BOOL Cstd2WinDlg::OnInitDialog()
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

	m_ctrlIPAddress.SetAddress(127, 0, 0, 1);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cstd2WinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cstd2WinDlg::OnPaint()
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
HCURSOR Cstd2WinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 소켓연결
void Cstd2WinDlg::OnBnClickedOk()
{
	CString strIP;

	// 이미 연결된 소켓이 있는지 체크
	if (m_pSocket != NULL)
	{
		AfxMessageBox("이미 연결되어 있는 서버가 있습니다.");
		return;
	}

	// 새로운 소켓 생성
	m_pSocket = new CSocket;

	UpdateData(TRUE);

	BYTE f0, f1, f2, f3;
	m_ctrlIPAddress.GetAddress(f0, f1, f2, f3);
	strIP.Format("%d.%d.%d.%d", f0, f1, f2, f3);

	if (!m_pSocket->Create(0, SOCK_STREAM))
	{
		m_strResult.Format("create() failed![%d]", GetLastError());
		UpdateData(FALSE);
		return;
	}

	if (!m_pSocket->Connect(strIP, m_snPort))
	{
		m_strResult.Format("connect() failed![%d]", GetLastError());
		UpdateData(FALSE);
		return;
	}

	m_strResult.Format("서버에 연결되었습니다.!");
	UpdateData(FALSE);
}
// 소켓종료
void Cstd2WinDlg::OnBnClickedOk2()
{
//	m_pSocket->Close();
	m_pSocket->ShutDown();
	delete m_pSocket;
	m_pSocket = NULL;

	m_strResult.Format("연결이 종료되었습니다!");
	UpdateData(FALSE);
}
// 보내기
void Cstd2WinDlg::OnBnClickedBtnsend()
{
	UpdateData(TRUE);

	// 연결된 소켓이 없으면
	if (m_pSocket == NULL)
	{
		AfxMessageBox("연결된 서버가 없습니다.");
		return;
	}

	// m_strMsg가 없을 경우
	if (m_strMsg.IsEmpty())	return;

	if (m_pSocket->Send(m_strMsg, m_strMsg.GetLength(), 0) == SOCKET_ERROR)
	{
		// 실패하면 소켓을 닫고 종료한다.
		OnBnClickedOk2();
		m_strResult.Format("send() failed![%d]", GetLastError());
	}
	else
		m_strResult.Format("success!");

	UpdateData(FALSE);
}
