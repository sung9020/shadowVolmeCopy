
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#pragma comment (lib, "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64/vssapi.lib")
#include <SDKDDKVer.h>

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <WinBase.h>
#include <shlwapi.h>
#include <afxadv.h>
#include <afxole.h>
#include <afxcview.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

#define HILONG(ll) (ll >> 32 & LONG_MAX)
#define LOLONG(ll) ((long)(ll))


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


struct shadow_prop
{
	wchar_t sid[100];
	wchar_t sgid[100];
	wchar_t pid[100];
	wchar_t v_name[100];
	wchar_t v_path[100];
	wchar_t d_object[100];
	wchar_t create_date[100];
	wchar_t network_date[100];
	
	
};


class Node
{
public:
	int Numofchild;
	Node* pid; //부모노드 주소
	Node* cid[200];	// 자식노드 주소
	WCHAR FNAME[100]; //파일이름
//	WCHAR* namepath; //이름정보만 더한것 
//	WCHAR* path; // 부모 노드 파일패스
//	WCHAR* NETPATH; // 네트워크 접속용
	int type; //0일 경우 루트, 1일경우 디렉토리 2일 경우 파일 
	ULONGLONG file_size;  //파일 사이즈
	WCHAR CREATED_DATE[40]; // 생성날짜 
	HTREEITEM pitem;
	

	Node()//차례대로 파일이름 사이즈, 이름패스, 파일패스, 넷패스
	{
		pid = 0;
		for(int i= 0; i<200;i++)
		{
			cid[i] = 0;
		}	
	for(int i= 0; i<100;i++)
		{
			FNAME[i] = 0;
		}	
	//	for(int r= 0; r<n_size;r++)
	//	{
	//		namepath[r] = 0;
	//	}	
	//	for(int q= 0; q<p_size;q++)
	//	{
	//		path[q] = 0;
	//	}
	//	for(int z= 0; z<e_size;z++)
	//	{
	//		NETPATH[z] = 0;
	//	}	
	for(int i= 0; i<40;i++)
		{
			CREATED_DATE[i] = 0;
		}	
		type = 0;
		pitem = NULL;
		Numofchild = 0;
		file_size = 0;

	}

	~Node()
	{
	
	
	
	
	}
};

 class FILE_Tree
{
public:

	Node* root; // 루트 주소 
	

	FILE_Tree::FILE_Tree()
	{
		
		root = new Node();
		
	}
	
	FILE_Tree::~FILE_Tree()
	{
		
		

	}

	bool freetree(Node* Current)
	{
		int i = 0;
		Node* element;
		int count = Current->Numofchild;
		
		while(i < count)
		{
			if(Current->cid[i]->type == 1)
			{
				if(Current->cid[i]->Numofchild == 0)
					delete Current->cid[i];
				else freetree(Current->cid[i]);
			}
			else if(Current->cid[i]->type == 2)
			{
				delete Current->cid[i];
			}
			i++;
		}
		return true;
	}

 };
