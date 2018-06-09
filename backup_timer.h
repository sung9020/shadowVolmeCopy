#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "vss_class.h"
#pragma comment (lib, "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64/WinMM.lib")

// backup_timer ��ȭ �����Դϴ�.

class backup_timer : public CDialogEx
{
	DECLARE_DYNAMIC(backup_timer)

public:
	backup_timer(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~backup_timer();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public: 
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
		
	
	int txt_C_count;
	int txt_D_count;
	int txt_F_count;
	CListCtrl volume_list;
	vss_class Vss_class;
	CString wchar_to_CString(WCHAR* source);
	void insertitems(CListCtrl& volume_list, int xml_count, CString drive, CString c_date);
	
	static void CALLBACK TimeProcC(UINT,UINT,DWORD_PTR,DWORD_PTR,DWORD_PTR);
	static void CALLBACK TimeProcD(UINT,UINT,DWORD_PTR,DWORD_PTR,DWORD_PTR);
	static void CALLBACK TimeProcF(UINT,UINT,DWORD_PTR,DWORD_PTR,DWORD_PTR);
	UINT timerid;
	CString drive;
	
	int n_radio;
	int d_radio;
};
