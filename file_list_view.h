#pragma once

#include "afxcmn.h"
#include "shadow_util.h"
#include "volume_shadow_util.h"
#include "vss_class.h"
#include "file_drag.h"

// file_list_view 대화 상자입니다.
struct IDropTargetHelper;

class file_list_view : public  CDialogEx
{
	DECLARE_DYNAMIC(file_list_view)

public:
	file_list_view(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~file_list_view();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	HICON m_hIcon;
	COleDataSource m_DataSrc;
	//file_drag m_droptarget;
	DECLARE_MESSAGE_MAP()
public:
	
	CTreeCtrl tree_directory;
	CListCtrl file_view;
	FILE_Tree* tree;
	WCHAR* drive;
	 HACCEL    m_hAccel;
	static CString wchar_to_CString(WCHAR* source);
	void searchChildren(Node* Current,WCHAR* Parent_NAME, WCHAR* drive_p = L"");
	CHAR* select(Node* Current, CHAR* c_path);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	void directory_order(Node* Current,WCHAR* drive_p = L"");
	char* ConvertUnicodeToMultybyte(WCHAR *strUnicode);
	void SetMainListPtr(FILE_Tree *directory);
	afx_msg void OnBnClickedButton1();
	void OnSelect(NMHDR *pNMHDR,LRESULT* pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBeginDrag(NMHDR *pNMHDR, LRESULT *pResult);
	UINT g_uCustomClipbrdFormat;
	shadow_prop* prop;
	CImageList* m_smallImage;
	HIMAGELIST hSystemSmall;
	SHFILEINFOW shFileInfo;
	//afx_msg void OnHdnEnddragList1(NMHDR *pNMHDR, LRESULT *pResult);
};
