// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Browser.h"

#include "BrowserDoc.h"
#include "LeftView.h"
#include "MainFrm.h"
#include "BaseImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_COMMAND(ID_MENU_VIEWER_INSPLIT, OnMenuViewer)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_bBrowserView = FALSE;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	if(pDoc ->m_pImage)
		pDoc ->m_pImage ->PaintImage(0, 0, pDC ->GetSafeHdc());
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CBrowserDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrowserDoc)));
	return (CBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers


/*
    int bHandleNow = FALSE;

    if(pMsg->message == WM_KEYDOWN)
    {
        switch(pMsg->wParam)
        {
        case VK_RETURN:
            if(GetDlgItem(IDC_SENDMESSAGE) == GetFocus())	// 지금 포커스 상태이면은..
                OnBtnSend();
	        bHandleNow = TRUE;
            break;
        default: break;
        }
    }        
    if (bHandleNow)
		 OnKeyDown(pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)); 

	return bHandleNow;        

	return CFormView::PreTranslateMessage(pMsg);

  */

void CLeftView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrowserDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc ->m_pImage)	// CBaseImage 가 들어있을 경우..
		pDoc ->m_pImage ->PaintImage(0, 0, dc.GetSafeHdc());
	// Do not call CTreeView::OnPaint() for painting messages
}

void CLeftView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CBrowserDoc *pDoc = NULL;
	CMenu	menu;
	CMenu	*pSubMenu;
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	menu.LoadMenu(IDR_CONTEXTGRAPHIC);
	if(! pDoc ->m_pImage)
		pSubMenu = menu.GetSubMenu(1);
	else
		pSubMenu = menu.GetSubMenu(0);
	ClientToScreen(&point);
	pSubMenu ->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, this);
	CTreeView::OnRButtonDown(nFlags, point);
}

void CLeftView::OnClear() 
{
	// TODO: Add your command handler code here
	CBrowserDoc *pDoc = GetDocument();
	if(pDoc ->m_pImage)
	{
		delete	pDoc ->m_pImage;
		pDoc ->m_pImage = NULL;
	}
	CClientDC	dc(this);
	::PatBlt(dc.GetSafeHdc(), 0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		WHITENESS);
}

/*
void CLeftView::OnNextpicture() 
{
	// TODO: Add your command handler code here

	CString	strFile;
	WIN32_FIND_DATA		fd;
	HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

	if( hFind != INVALID_HANDLE_VALUE ) {
		do {
			if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			{	// Is File...
				strFile = fd.cFileName;
				strFile.MakeLower();
				INT  nResult[3] = {0};
				nResult[0] = strFile.Find("bmp", strFile.GetLength() - 3);
				nResult[1] = strFile.Find("jpg", strFile.GetLength() - 3);
				nResult[2] = strFile.Find("jpeg", strFile.GetLength() - 4);
				if(nResult[0] || nResult[1] || nResult[2])
				{
					//	루프문을 끝내고 strFile 의
					//	이름의 그래픽파일을 출력한다..
					CBrowserDoc *pDoc = GetDocument();
					ASSERT_VALID(pDoc);

					pDoc ->MenuView(strFile);
					return;
				}
			}
//			else
				// Is Directory...
//				;
		} while( ::FindNextFile( hFind, &fd ) );
	}
}
*/

void CLeftView::OnMenuViewer() 
{
	// TODO: Add your command handler code here
	WPARAM	wParam = 0;
	wParam = HIWORD(0) + LOWORD(ID_MENU_VIEWER);
	AfxGetMainWnd() ->SendMessage(WM_COMMAND, wParam, 0);
}

void CLeftView::OnSetFocus(CWnd* pOldWnd) 
{
	CTreeView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CBrowserDoc *pDoc = (CBrowserDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->m_focus = VIEW;
}

void CLeftView::OnKillFocus(CWnd* pNewWnd) 
{
	CTreeView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CBrowserDoc *pDoc = (CBrowserDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->m_focus = FRAME;
}

/*
void CLeftView::OnStretchimage() 
{
	// TODO: Add your command handler code here
	return;
}

void CLeftView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CClientDC	dc(this);
	CRect rt;
	GetClientRect(rt);
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(1000, 1000);
	dc.SetViewportExt(rt.Width(), rt.Height());
	CTreeView::OnPrepareDC(pDC, pInfo);
}
*/
