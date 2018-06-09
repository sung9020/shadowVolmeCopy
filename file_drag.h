
/*
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct IDropTargetHelper;
class file_drag : public COleDropTarget  
{
	public:
	DROPEFFECT OnDragEnter ( CWnd* pWnd, COleDataObject* pDataObject,
		                     DWORD dwKeyState, CPoint point );

	DROPEFFECT OnDragOver ( CWnd* pWnd, COleDataObject* pDataObject,
		                    DWORD dwKeyState, CPoint point );

//	BOOL OnDrop ( CWnd* pWnd, COleDataObject* pDataObject,
	//	          DROPEFFECT dropEffect, CPoint point );

	void OnDragLeave ( CWnd* pWnd );
	
	file_drag ( CListCtrl* pList, UINT uCustomClipbrdFormat );
	virtual ~file_drag();
	
protected:
    CListCtrl*         file_view;
    IDropTargetHelper* m_piDropHelper;
    bool               m_bUseDnDHelper;
	UINT			   g_uCustomClipbrdFormat;
//   BOOL ReadHdropData ( COleDataObject* pDataObject );
};
*/