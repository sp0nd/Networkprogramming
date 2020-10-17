
// MFCNetworkDlg.h: 헤더 파일
//

#pragma once


// CMFCNetworkDlg 대화 상자
class CMFCNetworkDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCNetworkDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCNETWORK_DIALOG };
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
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedSend();
	CString m_message;
	CIPAddressCtrl m_ipaddr;
	CString m_msg;
	short m_port;
	CListBox m_ctrlList1;
	CListBox m_ctrlList2;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedResetmsg();
	afx_msg void OnBnClickedDeletemsg();
	afx_msg void OnBnClickedFileopenmsg();
	afx_msg void OnIpnFieldchangedIpaddr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLbnSelchangeList2();
};
