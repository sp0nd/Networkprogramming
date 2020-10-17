
// MFCprotocolstudyDlg.h: 헤더 파일
//

#pragma once

#include <vector>
#define DATASIZE 16
using namespace std;

typedef struct _DATA// 변수를 갖고있는 구조체
{
	short id;
	int day;
	int tm;
	short temp;
	short hum;
	short pres;
}DATA, *LPDATA;

class DataManager
{
	vector<LPDATA> array;
public:
	DataManager() {}
	~DataManager() // 메모리 할당 해제
	{
		for (int i = 0; i < array.size(); i++)//벡터는 가변길이 배열 size()=>array에 몇개의 배열이 있는지 알려주는 함수
		{
			free(array[i]); // i번째 배열에 있는 주소의 메모리 할당된걸 제거한다.
		}
	}

	void AddData(LPDATA pd)//새로 만든 데이터에 시간을 더해주는 함수
	{
		SetData(pd);
		array.push_back(pd);
	}

	LPDATA GetData(int id)//vector에 시간이외의 데이터를 집어넣는다.
	{
		for (int i = 0; i < array.size(); i++)
		{
			if (array[i]->id == id) return array[i];
		}
		return NULL;
	}
	void SetData(LPDATA pd)// 데이터에 있는 시간을 변경하는 함수
	{
		// 시간과 날짜를 설정
		CTime tm = CTime::GetCurrentTime();
		int y = tm.GetYear();
		int m = tm.GetMonth();
		int d = tm.GetDay();
		int h = tm.GetHour();
		int M = tm.GetMinute();
		int s = tm.GetSecond();

		pd->day = y * 10000 + m * 100 + d;
		pd->tm = h * 10000 + M * 100 + s;
	}

	CString GetString(LPDATA pd)
	{
		CString str;
		str.Format("%d,%d,%d,%d,%d,%d", pd->id, pd->day, pd->tm, pd->temp, pd->hum, pd->pres);

		return str;
	}
};


// CMFCprotocolstudyDlg 대화 상자
class CMFCprotocolstudyDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCprotocolstudyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	void writeData(FILE* fp, CStringArray& arr);
	void sendData(SOCKET soc, CStringArray& arr);
	int GetCountData(int seq, int start);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROTOCOLSTUDY_DIALOG };
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
	afx_msg void OnBnClickedBtngen();
	afx_msg void OnLbnSelchangeList1();
	CListBox m_ctrlList1;
	afx_msg void OnBnClickedBtnsaveas();
	afx_msg void OnBnClickedBtnconnect();
	afx_msg void OnBnClickedBtnsend();
	afx_msg void OnBnClickedBtnadd();
	CListBox m_ctrlIPaddr;
	CIPAddressCtrl m_straddr;
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnreset();
	
	
	short m_Pport;
};