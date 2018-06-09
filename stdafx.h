
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#pragma comment (lib, "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64/vssapi.lib")
#include <SDKDDKVer.h>

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <WinBase.h>
#include <shlwapi.h>
#include <afxadv.h>
#include <afxole.h>
#include <afxcview.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

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
	Node* pid; //�θ��� �ּ�
	Node* cid[200];	// �ڽĳ�� �ּ�
	WCHAR FNAME[100]; //�����̸�
//	WCHAR* namepath; //�̸������� ���Ѱ� 
//	WCHAR* path; // �θ� ��� �����н�
//	WCHAR* NETPATH; // ��Ʈ��ũ ���ӿ�
	int type; //0�� ��� ��Ʈ, 1�ϰ�� ���丮 2�� ��� ���� 
	ULONGLONG file_size;  //���� ������
	WCHAR CREATED_DATE[40]; // ������¥ 
	HTREEITEM pitem;
	

	Node()//���ʴ�� �����̸� ������, �̸��н�, �����н�, ���н�
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

	Node* root; // ��Ʈ �ּ� 
	

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
