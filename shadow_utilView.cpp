
// shadow_utilView.cpp : Cshadow_utilView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "shadow_util.h"
#endif

#include "shadow_utilDoc.h"
#include "shadow_utilView.h"




// Cshadow_utilView

IMPLEMENT_DYNCREATE(Cshadow_utilView, CView)

BEGIN_MESSAGE_MAP(Cshadow_utilView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cshadow_utilView ����/�Ҹ�

Cshadow_utilView::Cshadow_utilView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Cshadow_utilView::~Cshadow_utilView()
{
}

BOOL Cshadow_utilView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cshadow_utilView �׸���

void Cshadow_utilView::OnDraw(CDC* /*pDC*/)
{
	Cshadow_utilDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void Cshadow_utilView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cshadow_utilView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cshadow_utilView ����

#ifdef _DEBUG
void Cshadow_utilView::AssertValid() const
{
	CView::AssertValid();
}

void Cshadow_utilView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cshadow_utilDoc* Cshadow_utilView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cshadow_utilDoc)));
	return (Cshadow_utilDoc*)m_pDocument;
}
#endif //_DEBUG


// Cshadow_utilView �޽��� ó����
