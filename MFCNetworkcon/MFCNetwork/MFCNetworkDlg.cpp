
// MFCNetworkDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCNetwork.h"
#include "MFCNetworkDlg.h"
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


// CMFCNetworkDlg 대화 상자



CMFCNetworkDlg::CMFCNetworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNETWORK_DIALOG, pParent)
	, m_message(_T(""))
	, m_msg(_T(""))
	, m_port(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_IpPort, m_port);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS1, m_ipaddr);
	DDX_Text(pDX, IDC_Message, m_message);
	DDX_Control(pDX, IDC_IPADDR, m_ipaddr);
	DDX_Text(pDX, IDC_MSG, m_msg);
	DDX_Text(pDX, IDC_Port, m_port);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);
}

BEGIN_MESSAGE_MAP(CMFCNetworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Add, &CMFCNetworkDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Send, &CMFCNetworkDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_DELETE, &CMFCNetworkDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_RESET, &CMFCNetworkDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_RESETMSG, &CMFCNetworkDlg::OnBnClickedResetmsg)
	ON_BN_CLICKED(IDC_DELETEMSG, &CMFCNetworkDlg::OnBnClickedDeletemsg)
	ON_BN_CLICKED(IDC_FILEOPENMSG, &CMFCNetworkDlg::OnBnClickedFileopenmsg)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDR, &CMFCNetworkDlg::OnIpnFieldchangedIpaddr)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFCNetworkDlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CMFCNetworkDlg 메시지 처리기

BOOL CMFCNetworkDlg::OnInitDialog()
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

void CMFCNetworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCNetworkDlg::OnPaint()
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
HCURSOR CMFCNetworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//	/		/	/	/	 버튼		/		/		/	 ///

void CMFCNetworkDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	
	CString strIP, strPort;
	BYTE ip0, ip1, ip2, ip3; //1바이트로 표현할수있는 숫자가 0~255 2^8이니까 255.255.255.255까지 모두 표현할수있다
	m_ipaddr.GetAddress(ip0, ip1, ip2, ip3);
	strIP.Format("%d.%d.%d.%d", ip0, ip1, ip2, ip3);
	strPort.Format("%d", m_port);
	CString str = strIP + ":" + strPort;
	if (m_ctrlList1.FindString(0,str)== LB_ERR)//findstring로 str을 검색을 하는데 LB_ERR가 뜨면 str을 검색할 수 없다는 뜻이니까 str을 추가해준다
		m_ctrlList1.AddString(strIP + ":" + strPort);
}

void CMFCNetworkDlg::OnBnClickedDelete()
{
	int stridx = m_ctrlList1.GetCurSel();//선택한 스트링의 인덱스를 변수에 넣는다
	if ((stridx == LB_ERR))//stridx가 없으면(-1이면) 메세지 박스 띄우고 리턴
	{
		AfxMessageBox("선택한 IP가 없습니다.");
		return;
	}
	else //strdix(스트링 인덱스)가 있으면 선택한 스트링 삭제
		m_ctrlList1.DeleteString(stridx); 
}


void CMFCNetworkDlg::OnBnClickedReset()
{
	m_ctrlList1.ResetContent();//리스트 박스리셋 함수
}


void CMFCNetworkDlg::OnBnClickedResetmsg()
{
	m_ctrlList2.ResetContent();//리스트 박스리셋 함수
}


void CMFCNetworkDlg::OnBnClickedDeletemsg()
{
	int stridx = m_ctrlList2.GetCurSel();
	if ((stridx == LB_ERR))
	{
		AfxMessageBox("선택한 메세지가 없습니다.");
		return;
	}
	else
		m_ctrlList2.DeleteString(stridx);
}


void CMFCNetworkDlg::OnBnClickedFileopenmsg()
{
	static TCHAR BASED_CODE szFilter[] = _T("텍스트 파일(*.txt)| *.txt|모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() != IDOK)return;

	CString pathName = dlg.GetPathName();

	CStdioFile file;
	if (!file.Open(pathName, CFile::modeRead))
	{
		AfxMessageBox("Error");
		return;
	}
	CString rstr;
	while (file.ReadString(rstr))
	{
		m_ctrlList2.AddString(rstr);
	}
	file.Close();
}
   
void CMFCNetworkDlg::OnBnClickedSend()
{
	UpdateData(TRUE);
	//메세지가 없을경우
	if (m_message.IsEmpty()) return;
	m_ctrlList2.AddString(m_message);

	CString str;
	int count = m_ctrlList1.GetCount();//리스트에 있는 스트링 한줄을 1count로 해서 변수에 넣는다
	for (int i = 0; i < count; i++)// 리스트에 있는 스트링을 전부 사용하기위한 루프
	{
		CSocket soc;
		CString strIP;
		
		m_ctrlList1.GetText(i, str);//리스트에 있는 i번째에 있는 스트링을 선택
		int idx = str.Find(':'); //스트링변수 str에서 ':'의 위치를 찾아서 그 위치(str[9])를 idx에 넣어준다 127.0.0.1 : 2500 Find(찾을문자,시작인덱스(0이면 생략가능))
		strIP = str.Left(idx);// idx의 위치를 기준으로 왼쪽에 있는 스트링을 strIP 변수에 넣는다.
		int idx1 = str.Find(":", idx + 1);//스트링 str에서 두번쨰 ':'의 위치를 찾기위한 코드
		int port;
		if (idx1 == -1)
			port = atoi(str.Mid(idx + 1)); 
		else
			port = atoi(str.Mid(idx + 1, idx1 - idx - 1));

		CString msgstr="Success";

		if (!soc.Create(0, SOCK_STREAM))
		{
			msgstr.Format("Create() failed !!! [%d]", GetLastError());
		}
		else
		{
			if (!soc.Connect(strIP, port))
			{
				msgstr.Format("Connect() failed !!! [%d]", GetLastError());
			}
			else
			{
				if (soc.Send(m_message, m_message.GetLength(), 0) == SOCKET_ERROR)
				{
					soc.Close();
					msgstr.Format("Send() failed !!! [%d]", GetLastError());
				}
			}
		}
		soc.Close();
		str.Format("%s:%d:%s", strIP, port, msgstr);
		m_ctrlList1.DeleteString(i);
		m_ctrlList1.InsertString(i,str);
	}
	m_msg = "Success";
	UpdateData(FALSE);
}





void CMFCNetworkDlg::OnIpnFieldchangedIpaddr(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCNetworkDlg::OnLbnSelchangeList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
