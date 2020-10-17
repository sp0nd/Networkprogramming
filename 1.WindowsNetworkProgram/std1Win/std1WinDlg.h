
// std1WinDlg.h: 헤더 파일
//

#pragma once


// Cstd1WinDlg 대화 상자
class Cstd1WinDlg : public CDialogEx
{
// 생성입니다.
public:
	Cstd1WinDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STD1WIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	// 전송할 문자열
	CString m_strMsg;
	afx_msg void OnBnClickedOk();
	// 전송결과
	CString m_strResult;
	short m_snPort;
	CIPAddressCtrl m_ctrlIPAddress;
};
