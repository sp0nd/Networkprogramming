
// std2WinDlg.h: 헤더 파일
//

#pragma once


// Cstd2WinDlg 대화 상자
class Cstd2WinDlg : public CDialogEx
{
// 생성입니다.
public:
	Cstd2WinDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STD2WIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	CSocket* m_pSocket;		// 서버와 연결된 소켓

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnsend();
	afx_msg void OnBnClickedOk2();
	// 전송할 문자열
	CString m_strMsg;
	// 전송결과
	CString m_strResult;
	short m_snPort;
	CIPAddressCtrl m_ctrlIPAddress;

};
