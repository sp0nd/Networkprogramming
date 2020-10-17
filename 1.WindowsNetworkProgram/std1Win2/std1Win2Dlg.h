
// std1Win2Dlg.h: 헤더 파일
//

#pragma once


// Cstd1Win2Dlg 대화 상자
class Cstd1Win2Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cstd1Win2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STD1WIN2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CString GetErrorMessage(int errcode);

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Server IP Address
	CIPAddressCtrl m_ctrlIPAddress;
	CString m_strFileName;
	short m_snPort;
	CListBox m_ctrlList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CString m_strResult;
};
