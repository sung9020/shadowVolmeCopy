
// shadow_utilView.h : Cshadow_utilView Ŭ������ �������̽�
//

#pragma once


class Cshadow_utilView : public CView
{
protected: // serialization������ ��������ϴ�.
	Cshadow_utilView();
	DECLARE_DYNCREATE(Cshadow_utilView)

// Ư���Դϴ�.
public:
	Cshadow_utilDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~Cshadow_utilView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // shadow_utilView.cpp�� ����� ����
inline Cshadow_utilDoc* Cshadow_utilView::GetDocument() const
   { return reinterpret_cast<Cshadow_utilDoc*>(m_pDocument); }
#endif

