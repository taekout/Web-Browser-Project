// NetOmokView.h : interface of the CNetOmokView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETOMOKVIEW_H__EFD62BAD_1198_11D6_9871_004854839105__INCLUDED_)
#define AFX_NETOMOKVIEW_H__EFD62BAD_1198_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListenSocket;
class CClientSocket;
class CNetOmokDoc;
class CNetOmokView : public CView
{
protected: // create from serialization only
	CNetOmokView();
	DECLARE_DYNCREATE(CNetOmokView)

// Attributes
public:
	CNetOmokDoc* GetDocument();

// Operations
public:
	int colorState[15][15];

public:
	int m_nStartX;		
	int m_nStartY;		
	int m_nBoardUnit;	
	int m_nBoardSize;	
	int m_nCurCol;		
	int m_nCurRow;		

	int m_nMyStone;	
	int m_colorWinner;
					
public:
	CPoint m_lastStone;
	int m_nCurrentStone;

	enum {EMPTY=2, WHITE=1, BLACK=0};

public:


public:
	CListenSocket* m_pListenSocket;
	CClientSocket* m_pClientSocket;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetOmokView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL threeMthress(int m_nCurCol,int m_nCurRow);
	int x;	BOOL m_IsGameOver;
	void whatSuIsItNow();
	
	
	
	void displayGameOver();
	int m_suCount;
	BOOL isGameOver(int m_nCurCol,int m_nCurRow);
	int takeTurn;
	BOOL isThereStone(int m_nCurCol,int m_nCurRow);
	void ReceiveData();
	void CloseClient();
	void AcceptClient();
	void DrawCross(CDC* pDC, int row, int col);
	void DrawStone(CDC* pDC, int row, int col, int color);
	virtual ~CNetOmokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNetOmokView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnConnectIp();
	afx_msg void OnConnectDisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NetOmokView.cpp
inline CNetOmokDoc* CNetOmokView::GetDocument()
   { return (CNetOmokDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETOMOKVIEW_H__EFD62BAD_1198_11D6_9871_004854839105__INCLUDED_)
