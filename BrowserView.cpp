// BrowserView.cpp : implementation of the CBrowserView class
//

#include "stdafx.h"
#include "Browser.h"
#include "MainFrm.h"
#include "avi.h"

#include "BrowserDoc.h"
#include "BrowserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserView

IMPLEMENT_DYNCREATE(CBrowserView, CHtmlView)

BEGIN_MESSAGE_MAP(CBrowserView, CHtmlView)
	//{{AFX_MSG_MAP(CBrowserView)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserView construction/destruction

UINT	g_TimerID;

CBrowserView::CBrowserView() : m_bBrowserView(TRUE)
{
	// TODO: add construction code here
//	m_strHome = _T("http://www.daum.net");
	// m_strHome 을 Registry 에서 읽어서 초기화
	CWinApp *pApp = AfxGetApp();
	CString HomeSection = _T("Explore Option");
	CString HomeEntry = _T("Home Page"), strRet;
	strRet = pApp ->GetProfileString(HomeSection, HomeEntry, _T("AABCDAMVMMDfkkdfs#@F43#Tg d"));
	if(strRet.Compare(_T("AABCDAMVMMDfkkdfs#@F43#Tg d")) == 0)
		strRet = _T("http://www.daum.net");
	m_strHome = strRet;

	CTime	time = CTime::GetCurrentTime();		//	?
}

CBrowserView::~CBrowserView()
{
}

BOOL CBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView drawing

void CBrowserView::OnDraw(CDC* pDC)
{
	CBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CBrowserView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.daum.net"),NULL,NULL);
	g_TimerID = SetTimer(1, 3000, 0);


	//	Menu 를 Inactive 로..
//	CMenu menu;
//	menu.LoadMenu(IDR_FUTURE);
///	menu.EnableMenuItem(ID_BACK, FALSE);
//	menu.EnableMenuItem(ID_NEXT, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView printing


/////////////////////////////////////////////////////////////////////////////
// CBrowserView diagnostics

#ifdef _DEBUG
void CBrowserView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBrowserView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CBrowserDoc* CBrowserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrowserDoc)));
	return (CBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserView message handlers


BOOL CBrowserView::Explore(CString &strURL)
{
	BOOL	bResult = TRUE;
	try
	{
		Navigate2(strURL, NULL, NULL);
		AfxGetMainWnd() ->SetWindowText(strURL);
	}
	catch(CException *e)
	{
		e ->ReportError(MB_OK);
		e ->Delete();
		bResult = FALSE;
	}
	if(bResult)
	{
		((CMainFrame *)AfxGetMainWnd()) ->m_wndStatusBar.SetPaneText(1, strURL);
		CBrowserDoc	* pDoc = NULL;
		pDoc = (CBrowserDoc *)GetDocument();
		ASSERT_VALID(pDoc);
//		pDoc ->m_nPos = 1;
		pDoc ->AddList(strURL);
		pDoc ->m_strNowURL = strURL;
		((CMainFrame *)AfxGetMainWnd()) ->m_urlDlg ->m_strURL = strURL;
		((CMainFrame *)AfxGetMainWnd()) ->UpdateData(FALSE);
	}
	return	bResult;
}

LPCTSTR CBrowserView::GetHomePage()
{
	//	Option property dialog 의 홈페이지 설정 다이얼로그의 m_strHomePage 에 저장되어 있음.
	return	m_strHome.GetBuffer(0);
}
/*
void CBrowserView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrowserDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc ->m_pImage)
		pDoc ->m_pImage ->PaintImage(0, 0, dc.GetSafeHdc());
	
	// Do not call CHtmlView::OnPaint() for painting messages
//	CHtmlView::OnPaint();
}*/

CMyVideo	*g_pVideo;

void CBrowserView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CTime time = CTime::GetCurrentTime();
	CBrowserDoc *pDoc = (CBrowserDoc *) GetDocument();
	ASSERT_VALID(pDoc);
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT_VALID(pFrame);

	if(pFrame ->m_alarm.bAlarm == TRUE &&				// Short Cut... 을 이용.
		time.GetHour() == pFrame ->m_alarm.nHours &&
		time.GetMinute() == pFrame ->m_alarm.nMinutes)
	{
		if(!pDoc ->m_bPlaying)
		{
			pDoc ->m_bPlaying = TRUE;
			CRect	rt;
			g_pVideo = new CMyVideo(rt.left, rt.top, rt.Width(), rt.Height(),
				_T("C:\\Documents and Settings\\종현\\바탕 화면\\Browser\\res\\애국가.wav"),
				  this ->GetSafeHwnd());
			g_pVideo ->Play();
			MessageBox(_T("알람입니다."));
		}
	}
	else
	{	//	알람 FLAG 가 FALSE 로 맞춰지거나 시간이 지나서 안 맞게 될 경우...
		if(g_pVideo)
		{
			g_pVideo ->Close();
			delete	g_pVideo;
			g_pVideo = NULL;
		}
	}

	CHtmlView::OnTimer(nIDEvent);
}

void CBrowserView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MessageBox("a");
	CHtmlView::OnLButtonDown(nFlags, point);
}
