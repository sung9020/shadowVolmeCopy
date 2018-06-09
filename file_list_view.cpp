// file_list_view.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "file_list_view.h"
#include "afxdialogex.h"
#include "MAPIUtil.h"
#include "Psapi.h"
#include "MAPIDefS.h"

// file_list_view 대화 상자입니다.

IMPLEMENT_DYNAMIC(file_list_view, CDialogEx)

	file_list_view::file_list_view(CWnd* pParent /*=NULL*/)
	: CDialogEx(file_list_view::IDD, pParent)
//m_droptarget(&file_view, g_uCustomClipbrdFormat)
{
	drive = new WCHAR[10];
	g_uCustomClipbrdFormat = RegisterClipboardFormat ( _T("MY_STYLE") );
	m_smallImage = new CImageList;
}

file_list_view::~file_list_view()
{
	if(m_smallImage != NULL)
		delete m_smallImage;
}
BOOL file_list_view::PreTranslateMessage(MSG* pMsg) 
{
	if ( NULL != m_hAccel && 
		pMsg->message >= WM_KEYFIRST  &&  pMsg->message <= WM_KEYLAST )
	{
		return TranslateAccelerator ( m_hWnd, m_hAccel, pMsg );
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}

BOOL file_list_view::OnInitDialog()
{
	CDialog::OnInitDialog();
	ZeroMemory(&shFileInfo, sizeof(SHFILEINFOW));
	hSystemSmall = (HIMAGELIST)SHGetFileInfoW((LPCWSTR)L"C:\\", 0, &shFileInfo, sizeof(SHFILEINFOW),SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	m_smallImage->Attach(hSystemSmall);
	tree_directory.SetImageList(m_smallImage, LVSIL_SMALL);
	file_view.SetImageList(m_smallImage,LVSIL_SMALL);

	file_view.InsertColumn(0,"이름", LVCFMT_CENTER, 100, -1);
	file_view.InsertColumn(1,"수정한날짜",LVCFMT_CENTER,100,-1);
	file_view.InsertColumn(2,"파일 크기",LVCFMT_CENTER,100,-1);
	file_view.InsertColumn(3,"파일 경로",LVCFMT_CENTER,500,-1);
	file_view.DeleteAllItems();
	tree_directory.DeleteAllItems();

	directory_order(tree->root,drive);

	HTREEITEM parent, child;
	parent = tree_directory.GetRootItem();
	tree_directory.Expand(parent,TVE_EXPAND);

	child = tree_directory.GetNextItem(parent, TVGN_CHILD);

	tree_directory.Expand(child,TVE_EXPAND);

	while(child != NULL)
	{
		child = tree_directory.GetNextItem(child, TVGN_NEXT);
		tree_directory.Expand(child,TVE_EXPAND);
	}

//	m_droptarget.Register(&file_view);


	return true;
}

void file_list_view::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, tree_directory);
	DDX_Control(pDX, IDC_LIST1, file_view);
}


BEGIN_MESSAGE_MAP(file_list_view, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &file_list_view::OnBnClickedButton1)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &file_list_view::OnTvnSelchangedTree1)
	//	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &file_list_view::OnLvnBegindragList1)
	//	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &file_list_view::OnBeginDrag)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &file_list_view::OnLvnBegindragList1)
	//	ON_NOTIFY(LVN_END, 0, &file_list_view::onlvn)

END_MESSAGE_MAP()


// file_list_view 메시지 처리기입니다.




void file_list_view::directory_order(Node* Current,WCHAR* drive)
{	
	int i=0;

	if(!wcscmp(Current->FNAME,L"ROOT")) // 루트의 경우
	{
		if(!wcscmp(drive,L"C:"))
		{
			TVINSERTSTRUCT ROOT;
			ROOT.hParent = TVI_ROOT;
			ROOT.hInsertAfter = TVI_LAST;
			ROOT.item.mask = TVIF_TEXT;
			ROOT.item.pszText = "드라이브(C:)";

			Current->pitem = tree_directory.InsertItem(&ROOT);
		}

		else if(!wcscmp(drive,L"D:"))
		{
			TVINSERTSTRUCT ROOT;
			ROOT.hParent = TVI_ROOT;
			ROOT.hInsertAfter = TVI_LAST;
			ROOT.item.mask = TVIF_TEXT ;
			ROOT.item.pszText = "드라이브(D:)";

			Current->pitem = tree_directory.InsertItem(&ROOT);
		}

		else if(!wcscmp(drive,L"F:"))
		{
			TVINSERTSTRUCT ROOT;
			ROOT.hParent = TVI_ROOT;
			ROOT.hInsertAfter = TVI_LAST;
			ROOT.item.mask = TVIF_TEXT ;
			ROOT.item.pszText = "드라이브(F:)";

			Current->pitem = tree_directory.InsertItem(&ROOT);
		}
	}
	while(i < Current->Numofchild)
	{
		if(Current->cid[i]->type == 1) 
		{
			TVINSERTSTRUCT dir_tvi;
			dir_tvi.hParent = Current->pitem; //디렉토리 일경우 
			dir_tvi.hInsertAfter = TVI_LAST;
			dir_tvi.item.mask = TVIF_TEXT ;
			dir_tvi.item.pszText = ConvertUnicodeToMultybyte(Current->cid[i]->FNAME);

			Current->cid[i]->pitem = tree_directory.InsertItem(&dir_tvi);
			directory_order(Current->cid[i]);
			i++;
		}
		else
		{
			TVINSERTSTRUCT file;
			file.hParent = Current->pitem;
			file.hInsertAfter = TVI_LAST;
			file.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			file.item.pszText = ConvertUnicodeToMultybyte(Current->cid[i]->FNAME);

			i++;
		}
	}


}

/*
else if(Current->type == 1)
{

TVINSERTSTRUCT dir_tvi;
dir_tvi.hParent = Current->pid->pitem; //디렉토리 일경우 
dir_tvi.hInsertAfter = TVI_LAST;
dir_tvi.item.mask = TVIF_TEXT;
dir_tvi.item.pszText = ConvertUnicodeToMultybyte(Current->FNAME);
Current->pitem = tree_directory.InsertItem(&dir_tvi);
if(Current->cid != NULL)		
{Current = Current->cid; directory_order(Current);}
else return;

}
else // 파일일 경우 
{
TVINSERTSTRUCT file;
file.hParent = Current->pid->pitem;
file.hInsertAfter = TVI_LAST;
file.item.mask = TVIF_TEXT;
file.item.pszText = ConvertUnicodeToMultybyte(Current->FNAME);
tree_directory.InsertItem(&file);
if(Current->sid != NULL) {Current = Current->sid; directory_order(Current);}
else return;

}
*/
CString file_list_view::wchar_to_CString(WCHAR* source)
{
	CString temp(source);
	CString result;
	result = temp;

	return result;
}


char* file_list_view::ConvertUnicodeToMultybyte(WCHAR *strUnicode)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,strUnicode,-1,NULL,0,NULL,NULL);
	char* pMultibyte = new char[nLen];
	memset(pMultibyte,0x00,(nLen)*sizeof(char));
	WideCharToMultiByte(CP_ACP,0,strUnicode,-1,pMultibyte,nLen,NULL,NULL);
	return pMultibyte;
}



void file_list_view::OnBnClickedButton1() //닫기버튼
{
	OnDestroy();
	OnOK();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
/*
void file_list_view::SetMainListPtr(FILE_Tree *directory)
{
tree = directory;
}
*/

//현 트리뷰에서 트리하나가 선택되었을때
void file_list_view::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	USES_CONVERSION;
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	file_view.DeleteAllItems();

	HTREEITEM  hNewitem;
	hNewitem = pNMTreeView->itemNew.hItem;

	//CString STR 
	WCHAR* parent_name = T2W(tree_directory.GetItemText(hNewitem).GetBuffer(0));
	searchChildren(tree->root, parent_name, drive);
	tree_directory.GetItemText(hNewitem).ReleaseBuffer();
	//tree_directory.SelectDropTarget(hNewitem);




	*pResult = 0;
}


//리스트뷰에서 현재 폴더의 하위 파일들을 불러온다.
void file_list_view::searchChildren(Node* Current,WCHAR* Parent_NAME, WCHAR* drive)
{
	int i = 0;
	int j = 0;

	
	CHAR date[MAX_PATH] = {0};
	CHAR path[500]= {0};

	if(!wcscmp(Current->FNAME,Parent_NAME)) // 선택한 폴더 이름
	{
		while(i< Current->Numofchild)
		{
			if(Current->cid[i]->type==2)
			{
				if(!wcscmp(drive,L"C:"))
				{


					file_view.InsertItem(j,"");
					file_view.SetItemText(j,0,ConvertUnicodeToMultybyte(Current->cid[i]->FNAME));
					file_view.SetItemText(j,1,ConvertUnicodeToMultybyte(Current->cid[i]->CREATED_DATE));
					CString size;
					size.Format("%dKB",Current->cid[i]->file_size);
					file_view.SetItemText(j,2,size);
					strcpy_s(path,strlen("\\\\localhost\\C$\\@GMT-")+1,"\\\\localhost\\C$\\@GMT-");
					strcat_s(path,strlen(path)+strlen(ConvertUnicodeToMultybyte(prop->network_date))+1,ConvertUnicodeToMultybyte(prop->network_date));
					strcat_s(path,strlen(path)+strlen("\\")+1,"\\");
					strcat_s(path,strlen(path)+strlen(select(Current->cid[i],""))+1,select(Current->cid[i],""));					
					
					file_view.SetItemText(j,3,path);

					j++;
				}
				else if(!wcscmp(drive,L"D:"))
				{
					file_view.InsertItem(j,"");
					file_view.SetItemText(j,0,ConvertUnicodeToMultybyte(Current->cid[i]->FNAME));
					file_view.SetItemText(j,1,ConvertUnicodeToMultybyte(Current->cid[i]->CREATED_DATE));
					CString size;
					size.Format("%dKB",Current->cid[i]->file_size);
					file_view.SetItemText(j,2,size);
					strcpy_s(path,strlen("\\\\localhost\\D$\\@GMT-")+1,"\\\\localhost\\D$\\@GMT-");
					strcat_s(path,strlen(path)+strlen(ConvertUnicodeToMultybyte(prop->network_date))+1,ConvertUnicodeToMultybyte(prop->network_date));
					strcat_s(path,strlen(path)+strlen("\\")+1,"\\");
					strcat_s(path,strlen(path)+strlen(select(Current->cid[i],""))+1,select(Current->cid[i],""));					
					
					file_view.SetItemText(j,3,path);


					j++;
				}
				else if(!wcscmp(drive,L"F:"))
				{
					file_view.InsertItem(j,"");
					file_view.SetItemText(j,0,ConvertUnicodeToMultybyte(Current->cid[i]->FNAME));
					file_view.SetItemText(j,1,ConvertUnicodeToMultybyte(Current->cid[i]->CREATED_DATE));
					CString size;
					size.Format("%dKB",Current->cid[i]->file_size);
					file_view.SetItemText(j,2,size);
					strcpy_s(path,strlen("\\\\localhost\\F$\\@GMT-")+1,"\\\\localhost\\F$\\@GMT-");
					strcat_s(path,strlen(path)+strlen(ConvertUnicodeToMultybyte(prop->network_date))+1,ConvertUnicodeToMultybyte(prop->network_date));
					strcat_s(path,strlen(path)+strlen("\\")+1,"\\");
					strcat_s(path,strlen(path)+strlen(select(Current->cid[i],""))+1,select(Current->cid[i],""));					
					file_view.SetItemText(j,3,path);


					j++;
				}
			}
			i++;

		}
	}
	else
	{
		while(i< Current->Numofchild)
		{

			if(Current->cid[i]->type == 1)// 폴더일 경우
				searchChildren(Current->cid[i],Parent_NAME,drive);
			i++;
		}
	}



}
CHAR* file_list_view::select(Node* Current, CHAR* c_path)
{
	CHAR path[MAX_PATH] = {0};

	if(!wcscmp(Current->pid->FNAME,L"ROOT")) 
		{
			wsprintf(path,"%s%s",ConvertUnicodeToMultybyte(Current->FNAME),c_path);
			return path;	
		}
	else
	{
		wsprintf(path,"\\%s%s",ConvertUnicodeToMultybyte(Current->FNAME),c_path);
		select(Current->pid,path);
	}
	



}




void file_list_view::OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	int nSelItem;
	CString UNCFile;
	CString sFile;
	CStringList IsDraggedFiles;
	TCHAR* pszBuff;
	int uBuffSize = 0;
	HGLOBAL hgDrop;
	DROPFILES* pDrop;
	COleDataSource* datasrc = new COleDataSource;
	FORMATETC  etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };


	

	pos = file_view.GetFirstSelectedItemPosition();


	while(NULL != pos)
	{
		nSelItem = file_view.GetNextSelectedItem(pos);
		sFile = file_view.GetItemText(nSelItem,3);
		//	sFile = "\\\\localhost\\F$\\@GMT-2014.11.17-15.34.27\\오목눈이\\Desert.jpg";
		IsDraggedFiles.AddTail(sFile);

		uBuffSize += lstrlen(sFile) + 1;

	}
	uBuffSize = sizeof(DROPFILES) + sizeof(TCHAR) + (uBuffSize + 1);
	hgDrop = GlobalAlloc ( GHND | GMEM_SHARE, uBuffSize );

	if(hgDrop == NULL)
		return;

	pDrop = (DROPFILES *) GlobalLock(hgDrop);

	if(pDrop == NULL)
	{
		GlobalFree(hgDrop);
		return;
	}

	pDrop->pFiles = sizeof(DROPFILES);
	
#ifdef _UNICODE
	pDrop->fWide =TRUE;
#endif
	pos = IsDraggedFiles.GetHeadPosition();
	pszBuff = (TCHAR*) (LPBYTE(pDrop) + sizeof(DROPFILES));

	while (NULL != pos)
	{
		lstrcpy(pszBuff,(LPCTSTR) IsDraggedFiles.GetNext(pos));
		pszBuff = 1 + strchr(pszBuff, '\0');

	}
	GlobalUnlock ( hgDrop );

	// Put the data in the data source.

	datasrc->CacheGlobalData ( CF_HDROP, hgDrop, &etc );

	HGLOBAL hgBool;

	hgBool = GlobalAlloc(GHND | GMEM_SHARE, sizeof(bool));

	if(NULL==hgBool)
	{
		GlobalFree(hgDrop);
		return;
	}
	etc.cfFormat = g_uCustomClipbrdFormat;

	datasrc->CacheGlobalData ( g_uCustomClipbrdFormat, hgBool, &etc );

	DROPEFFECT dwEffect = datasrc->DoDragDrop (DROPEFFECT_COPY| DROPEFFECT_MOVE|DROPEFFECT_NONE);
	
	switch (dwEffect)
	{
	case DROPEFFECT_COPY:
		{

			//CopyFile(sFile,
		}
	case DROPEFFECT_MOVE:
		break;
	case DROPEFFECT_NONE:
		{
				GlobalFree(hgDrop);
				GlobalFree(hgBool);
		}
		break;
	}
	datasrc->InternalRelease();
	*pResult = 0;
}

/*
void file_list_view::OnBeginDrag(NMHDR *pNMHDR, LRESULT *pResult)
{
LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
POSITION pos;
int nSelItem;
CString sFile;
CStringList IsDraggedFiles;
TCHAR* pszBuff;
int uBuffSize = 0;
HGLOBAL hgDrop;
DROPFILES* pDrop;
COleDataSource datasrc;
FORMATETC  etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

*pResult = 0;
pos = file_view.GetFirstSelectedItemPosition();

while(NULL != pos)
{
nSelItem = file_view.GetNextSelectedItem(pos);
sFile = file_view.GetItemText(nSelItem,3);

IsDraggedFiles.AddTail(sFile);

uBuffSize += lstrlen(sFile) + 1;

}
uBuffSize = sizeof(DROPFILES) + sizeof(TCHAR) + (uBuffSize + 1);
hgDrop = GlobalAlloc ( GHND | GMEM_SHARE, uBuffSize );

if(hgDrop == NULL)
return;

pDrop = (DROPFILES *) GlobalLock(hgDrop);

if(pDrop == NULL)
{
GlobalFree(hgDrop);
return;
}

pDrop->pFiles = sizeof(DROPFILES);

#ifdef _UNICODE
pDrop->fWide =TRUE;

#endif
pos = IsDraggedFiles.GetHeadPosition();
pszBuff = (TCHAR*) (LPBYTE(pDrop) + sizeof(DROPFILES));

while (NULL != pos)
{
lstrcpy(pszBuff,(LPCTSTR) IsDraggedFiles.GetNext(pos));
pszBuff = 1 + strchr(pszBuff, '\0');

}
GlobalUnlock ( hgDrop );

// Put the data in the data source.

datasrc.CacheGlobalData ( CF_HDROP, hgDrop, &etc );

HGLOBAL hgBool;

hgBool = GlobalAlloc(GHND | GMEM_SHARE, sizeof(bool));

if(NULL==hgBool)
{
GlobalFree(hgDrop);
return;
}
etc.cfFormat = g_uCustomClipbrdFormat;

datasrc.CacheGlobalData ( g_uCustomClipbrdFormat, hgBool, &etc );

DROPEFFECT dwEffect = datasrc.DoDragDrop (DROPEFFECT_COPY| DROPEFFECT_MOVE);

switch (dwEffect)
{
case DROPEFFECT_COPY:
{
//CopyFile(IsDraggedFiles.GetHead(),);
}
case DROPEFFECT_MOVE:
break;
case DROPEFFECT_NONE:
{
GlobalFree(hgDrop);
GlobalFree(hgBool);
}
break;
}

}

*/
