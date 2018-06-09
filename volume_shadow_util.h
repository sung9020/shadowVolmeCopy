#pragma once

#include "stdafx.h"
//#include "vld.h"
#include "vss_class.h"
#include "afxwin.h"
#include "file_list_view.h"
#include <stdlib.h>
#include "afxcmn.h"

// volume_shadow_util 대화 상자입니다.

class volume_shadow_util : public CDialogEx
{
	DECLARE_DYNAMIC(volume_shadow_util)

public:
	volume_shadow_util(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~volume_shadow_util();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	//virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	//afx_msg void OnClose();
	afx_msg void OnBnClickedButton6();
	
	int m_radio;
	char* ConvertUnicodeToMultybyte(WCHAR *strUnicode);
	
	static CString wchar_to_CString(WCHAR* source);
	vss_class Vss_class;
	
	FILE_Tree file_tree;
	BOOL volume_restore(WCHAR *Src, WCHAR *Dest);
	int txt_C_count;
	int txt_D_count;
	int txt_F_count;
	void insertitems(CListCtrl& volume_list, int xml_count, CString drive, CString c_date);
	

	CListCtrl volume_list;
	int GetIndex();
//	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL volume_Copy(WCHAR *Src, WCHAR *Dest);
	void update_list();
	void directory_tree_clean(Node* Current);
	
	static DWORD CALLBACK CopyProgressRoutine( 
	LARGE_INTEGER TotalFileSize, // total file size, in bytes 
	 LARGE_INTEGER TotalBytesTransferred, 
	 // total number of bytes transferred 
	 LARGE_INTEGER StreamSize, // total number of bytes for this stream 
	 LARGE_INTEGER StreamBytesTransferred, 
	 // total number of bytes transferred for 
	  // this stream 
	  DWORD dwStreamNumber, // the current stream 
	DWORD dwCallbackReason, // reason for callback 
	 HANDLE hSourceFile, // handle to the source file 
	HANDLE hDestinationFile, // handle to the destination file 
	LPVOID lpData // passed by CopyFileEx 
	 );

};
