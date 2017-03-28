// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Browser.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "BrowserView.h"
#include "BrowserDoc.h"
#include "BaseImage.h"
#include "MoveDialog.h"
#include "FTPDlg.h"
#include "AlarmDlg.h"
#include "Splash.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		MENU_ID_ADDEDFAVORITE	39216
#define		MENU_ID_ADDEDURL		58171
#define		WM_MY_TASKBAR			WM_USER+9
#define		WM_NOTIFIED_QUIT_FROM_OWNER		WM_USER+103

//		#define		_tcsncmp	StrCmp

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_NEXT, OnNext)
	ON_COMMAND(ID_HOME, OnHome)
	ON_COMMAND(ID_FRESH, OnFresh)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_MENU_VIEWER, OnMenuViewer)
	ON_COMMAND(ID_FULLSCREEN, OnFullscreen)
	ON_UPDATE_COMMAND_UI(ID_FULLSCREEN, OnUpdateFullscreen)
	ON_COMMAND(ID_CLEARLEFTVIEW, OnClearleftview)
	ON_COMMAND(ID_AVI, OnAvi)
	ON_MESSAGE(WM_USER_DIALOG_DESTROYED, OnAviEnd)	//  User defined Message...
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_BACK, OnUpdateBack)
	ON_UPDATE_COMMAND_UI(ID_NEXT, OnUpdateNext)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropDown)
	ON_COMMAND(ID_SEARCH_DAUM, OnSearchDaum)
	ON_COMMAND(ID_SEARCH_NAVER, OnSearchNaver)
	ON_COMMAND(ID_SEARCH_EMPAS, OnSearchEmpas)
	ON_COMMAND(ID_SEARCH_GOOGLE, OnSearchGoogle)
	ON_COMMAND(ID_SEARCH_ALTAVISTA, OnSearchAltavista)
	ON_COMMAND(ID_SEARCH_LYCOS, OnSearchLycos)
	ON_COMMAND(ID_SEARCH_MSN, OnSearchMsn)
	ON_COMMAND(ID_SEARCH_YAHOO, OnSearchYahoo)
	ON_COMMAND(ID_SEARCH_CHOL, OnSearchChol)
	ON_COMMAND(ID_SEARCH_DREAMWIZ, OnSearchDreamwiz)
	ON_COMMAND(ID_SEARCH_HANMIR, OnSearchHanmir)
	ON_UPDATE_COMMAND_UI(ID_SEARCHSITE, OnUpdateSearchsite)
	ON_UPDATE_COMMAND_UI(ID_FAVORITESITE, OnUpdateFavoritesite)
	ON_COMMAND(ID_SEJONGSITE, OnSejongsite)
	ON_COMMAND(ID_DAUMSITE, OnDaumsite)
	ON_COMMAND(ID_INTERFACESITE, OnInterfacesite)
	ON_COMMAND(ID_ALLFTP, OnAllftp)
	ON_COMMAND(ID_ADDFAVORITE, OnAddfavorite)
	ON_COMMAND(ID_OPTION, OnOption)
	ON_COMMAND(ID_TRAY_ICON, OnTrayIcon)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_GAMEMENU, OnGamemenu)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MY_TASKBAR, TrayIconSetting)	// This msg is defined by user.
	ON_COMMAND_RANGE(MENU_ID_ADDEDFAVORITE, MENU_ID_ADDEDFAVORITE + 100, OnAddedFavorites)
	ON_COMMAND_RANGE(MENU_ID_ADDEDURL, MENU_ID_ADDEDURL + 100, OnAddedURL)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_WEBSITE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

INT	StrCmp(LPTSTR szDest, LPTSTR szSrc, INT  sizeT)
{
	while(*szSrc == *szDest && sizeT--)
	{
		if(szSrc == '\0')
			break;
		szSrc ++;
		szDest++;
	}
	return	*szDest - *szSrc;
}

//	이것을 ID_FILE_NEW 로 바꾸니 아이콘 활성화...
//	즉 문제는 ID_BACK 등을 ID_FIlE_NEW 와 같이 정규 리소스 아이디로 등록하는 것!

//	#define	ID_BACK		61447
//	#define	ID_NEXT		61448
//	#define	ID_HOME		61449
//	#define	ID_STOP		61450
//	#define	ID_FRESH	61451

UINT	g_pButtonInfo[] =
{
	ID_BACK,
	ID_NEXT,
	ID_HOME,
	ID_STOP,
	ID_FRESH,
	ID_MENU_VIEWER,
	ID_AVI,
	ID_ALLFTP,
	ID_TRAY_ICON,
	ID_FULLSCREEN,
	ID_GAMEMENU
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() : m_pDoc(NULL), m_bFullScreen(FALSE), m_pMovieDlg(NULL),
					m_pFTPDlg(NULL), m_bFocus(FALSE), m_bTray(FALSE)
{
	// TODO: add member initialization code here
	m_urlDlg = new CUrlDlg(this);
}

CMainFrame::~CMainFrame()
{
	if(m_urlDlg)
		delete	m_urlDlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	HANDLE	handle = LoadImage(AfxGetApp() ->m_hInstance, MAKEINTRESOURCE(IDB_TOOLBARBITMAP)
		, IMAGE_BITMAP, NULL, NULL, 0);
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE |
		CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS |CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_wndToolBar.LoadBitmap(IDB_TOOLBARBITMAP))	// ToolBar를 비트맵에서 로드
		!m_wndToolBar.SetBitmap((HBITMAP)handle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetWindowText(_T("도구바"));
	//	툴바 경계 영역 설정
	m_wndToolBar.SetBorders(1, 1, 1, 1);
	//	툴바의 버튼 사이즈 설정
	m_wndToolBar.SetSizes(CSize(69,65), CSize(60,49));
	//	툴바의 버튼수 설정
	m_wndToolBar.SetButtons(g_pButtonInfo, sizeof(g_pButtonInfo) / sizeof(UINT));

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME,
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if(!m_wndLinkBar.CreateEx(this, TBSTYLE_LIST | TBSTYLE_FLAT) ||
		!m_wndLinkBar.LoadToolBar(IDR_LINKBAR))
	{
		AfxMessageBox("Creating link bar is failed!");
		return	-1;
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar, RGB(255,0,0), GetSysColor(COLOR_BTNFACE), "주소") ||
		!m_wndReBar.AddBar(&m_wndLinkBar, RGB(0,0,255), GetSysColor(COLOR_BTNFACE), "연결"))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetButtonText(0, _T("Back"));
	m_wndToolBar.SetButtonText(1, _T("Next"));
	m_wndToolBar.SetButtonText(2, _T("Home"));
	m_wndToolBar.SetButtonText(3, _T("Stop"));
	m_wndToolBar.SetButtonText(4, _T("Refresh"));
	m_wndToolBar.SetButtonText(5, _T("Viwer"));
	m_wndToolBar.SetButtonText(6, _T("사시미"));		// 이것은 Combo 로 만들 예정.. Bible P.751 참조
	m_wndToolBar.SetButtonText(7, _T("올 FTP"));
	m_wndToolBar.SetButtonText(8, _T("브라우저 숨기기"));
	m_wndToolBar.SetButtonText(9, _T("Fullscreen"));
	m_wndToolBar.SetButtonText(10, _T("게 임"));

	m_wndToolBar.SetSizes(CSize(69,65), CSize(60,49));
	m_wndDlgBar.SetDlgItemText(IDC_COMBOURL, _T("http://www.daum.net"));

//	m_urlDlg.m_comboUrl.AddString(_T("http://www.daum.net"));	// Error!

	// Floating Tool Bar
/*
	if( !m_wndToolBar.IsFloating() )
		//	If Not Floating...
	{
		RECT	rect;
//		GetClientRect(&rect);
		// Floating...
		FloatControlBar(&m_wndToolBar, //CPoint(rect.left + 30, rect.top+30));
			CPoint(65, 49));
	}*/

	//	Set Link Bar
	//	툴팁과 상태바 문자열 출력 enabling
	m_wndLinkBar.SetBarStyle(m_wndLinkBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	//	드롭 다운 버튼 설정
	m_wndLinkBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	//	Link 바에 텍스트 추가
	m_wndLinkBar.SetButtonInfo(0, ID_SEARCHSITE, TBSTYLE_BUTTON | TBSTYLE_DROPDOWN, 0);
	m_wndLinkBar.SetButtonText(0, _T("검색 사이트"));
	m_wndLinkBar.SetButtonInfo(1, ID_FAVORITESITE, TBSTYLE_BUTTON | TBSTYLE_DROPDOWN, 0);
	m_wndLinkBar.SetButtonText(1, _T("즐겨찾기"));
	m_wndLinkBar.SetButtonInfo(2, ID_INTERFACESITE, TBSTYLE_BUTTON, 0);
	m_wndLinkBar.SetButtonText(2, _T("인터페이스!!"));

	m_wndToolBar.EnableWindow(TRUE);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_wndLinkBar.EnableWindow(TRUE);
	m_wndLinkBar.EnableDocking(CBRS_ALIGN_LEFT);
	SetDropDownToolBar();
//	m_wndStatusBar.SetPaneInfo(1, ID_WEBSITE, SBPS_STRETCH, 3);
//	DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_LEFT);
//	FloatControlBar(&m_wndToolBar, CPoint(69,65));

	//	Registry 에서 URL 들을 읽어서 즐겨찾기에 추가!
	CString strSection = _T("My Favorites");
	CString strURLItem = _T("URL");
	CString	strURL = _T("");
	CString	strCount = _T("Favorites Count");
	CString	strCountItem = _T("Count");
	INT		nCountFavorites = -10;

	//	즐겨찾기 등록하는 부분
	CWinApp *pApp = AfxGetApp();
	if((nCountFavorites = pApp ->GetProfileInt(strCount, strCountItem, -10)) != -10)
	{	//	즐겨찾기 URL 이 존재!
		m_nCountFavorites = nCountFavorites;
		for(INT i = 1 ; i <= nCountFavorites ; i++)
		{
			CString str = _T("");
			strURLItem = _T("URL");
			CString	strAddFavorites;
			str.Format("%d", i);
			strURLItem += str;
			strAddFavorites = pApp ->GetProfileString(strSection, strURLItem, _T("---##!GF3 "));
			if(strAddFavorites.Compare(_T("---##!GF3 ")) != 0)
			{	//	정상적으로 열림
				//	즐겨찾기 메뉴에 추가!
				CMenu  *pPopup = GetMenu() ->GetSubMenu(4);
				pPopup ->AppendMenu(MF_STRING, MENU_ID_ADDEDFAVORITE + i, strAddFavorites);
			}
			else
			{	//	Section 이 존재하지 않음. ==> Error!
				AfxMessageBox(_T("Registry Loading error"));
				break;
			}
		}
	}
	//	즐겨찾기 등록이 끝나면 알람 설정을 등록
	CString		strAlarmSection = _T("Alarm");
	CString		strAlarmEntry1 = _T("Alarm Enable");
	CString		strAlarmEntry2 = _T("Alarm Play File");
	CString		strAlarmEntry3 = _T("Hours");
	CString		strAlarmEntry4 = _T("Minutes");
	CString		str = _T("");

	str = pApp ->GetProfileString(strAlarmSection, strAlarmEntry1, _T("#Zfth41^! ^Y90"));
	if(str.Compare(_T("#Zfth41^! ^Y90")) == 0)
		m_alarm.bAlarm = TRUE;
	else	// normal
		m_alarm.bAlarm = (str.Compare(_T("TRUE"))) ? TRUE : FALSE;

	str = pApp ->GetProfileString(strAlarmSection, strAlarmEntry2, _T("#Zfth41^! ^Y90"));
	if(str.Compare(_T("#Zfth41^! ^Y90")) == 0)
		//	error
		m_alarm.strAlarmFile = _T("C:\\Documents and Settings\\종현\\바탕 화면\\Browser\\res\\애국가.wav");
	else//	normal
		m_alarm.strAlarmFile = str;

	str = pApp ->GetProfileString(strAlarmSection, strAlarmEntry3, _T("#Zfth41^! ^Y90"));
	if(str.Compare(_T("#Zfth41^! ^Y90")) == 0)
		//	error
		m_alarm.nHours = 8;
	else//	normal
		m_alarm.nHours = atoi(str);

	str = pApp ->GetProfileString(strAlarmSection, strAlarmEntry4, _T("#Zfth41^! ^Y90"));
	if(str.Compare(_T("#Zfth41^! ^Y90")) == 0)
		m_alarm.nMinutes = 30;
	else
		m_alarm.nMinutes = atoi(str);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CBrowserView), CSize(0, 0), pContext) ||
		!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(0, 0), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
//	m_wndStatusBar.SetPaneStyle(1, SBPS_STRETCH);
	return TRUE;
//	m_wndSplitter.Create(this, 2, 2, CSize(10,10), pContext);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//  주의! m_urlDlg 즉... DoDataExchange 에서 연결된 콤보박스 멤버변수는 쓸모가 없다
//	다이얼로그바 멤버변수를 통하여 접근하여야 한다.
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    int bHandleNow = FALSE;
	CBrowserDoc * pDoc = (CBrowserDoc *)GetActiveDocument();
	ASSERT_VALID(pDoc);

    if(pMsg->message == WM_KEYDOWN)
    {
		if(pMsg ->wParam == VK_RETURN && GetFocus() ->GetDlgCtrlID() == IDC_COMBOURL)
		{
			CString		strURL;
			m_wndDlgBar.GetDlgItemText(IDC_COMBOURL, strURL);
			
			//	앞에 http://www 설정 되어있는가 확인해서 추가..
			if(_tcsncmp("www", strURL.GetBuffer(0), 3) == NULL)
			{	// 맨 처음이 "www" 일 때...
				strURL.Insert(0, "http://");
			}
			else	// 처음이 "http://" 이거나 바로 "daum.net" 이 나올 때.. 또는 정상 입력
			{
				if(_tcsncmp("http://", strURL.GetBuffer(0), 7) != NULL)
				{	//	앞에 "http://"가 들어있지 않을 때...
					strURL.Insert(0, "http://");
				}
				else	// 바로 주소가 나오 거나.. Ex> "daum.net" 또는 정상적으로 입력 "http://www.daum.net"
				{
					if(_tcsncmp("http://www", strURL.GetBuffer(0), 10) == NULL)
					{	// 정상적으로 입력
					}
					else	// 바로 주소 나올 시...
						strURL.Insert(0, "httP//www");
				}
			}
			
			if( ! IsExistComboString(strURL) )
			{
				CComboBox*	pBox = (CComboBox *)m_wndDlgBar.GetDlgItem(IDC_COMBOURL);
				pBox ->AddString(strURL);
			}
			//				if(AfxGetMainWnd() -> == GetActiveView())
			GetView() ->Explore(strURL);
		}
	}

/*	else if(pMsg->message == WM_COMMAND)
	{
		if(LOWORD(pMsg ->wParam) > MENU_ID &&
			LOWORD(pMsg ->wParam) < MENU_ID +
			((CBrowserDoc *)GetActiveDocument()) ->m_nCountFavorites + 1)
		{
			CMenu		menu;
			CString		strURL;
			CMenu *pPop = GetMenu() ->GetSubMenu(4);
			
			pPop ->GetMenuString(pPop ->GetMenuItemID(18), strURL, MF_BYCOMMAND);
//			TCHAR	lpszURL[100];
//			::GetWindowText(pMsg ->hwnd, lpszURL, -1);
		}
	}
*/
    if (bHandleNow)
        OnKeyDown(pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)); 

    return bHandleNow;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	m_bFocus = TRUE;
}

void CMainFrame::OnKillFocus(CWnd* pNewWnd) 
{
	CFrameWnd::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	m_bFocus = FALSE;
}

void CMainFrame::OnBack() 
{
	// TODO: Add your command handler code here
//	m_wndStatusBar.SetPaneText(1, );
	GetView() ->GoBack();
}

void CMainFrame::OnNext() 
{
	// TODO: Add your command handler code here
	GetView() ->GoForward();
}

void CMainFrame::OnHome() 
{
	// TODO: Add your command handler code here
	CBrowserView *pView = GetView();
	if( pView ->GetBusy() )
		pView ->Stop();
	CString	strURL = pView ->GetHomePage();
	pView ->Explore(strURL);
}

void CMainFrame::OnFresh() 
{
	// TODO: Add your command handler code here
	GetView() ->Refresh();
}

void CMainFrame::OnStop() 
{
	// TODO: Add your command handler code here
	GetView() ->Stop();
}

CBrowserView * CMainFrame::GetView()
{
	CBrowserView *pView = NULL;
	CBrowserDoc	*pDoc = NULL;
//	POSITION	pos;
//	pView = (CBrowserView *)GetActiveView();
	// 여기에 CLeftView 와 pView 가 동일한지를 체크하여야 한다.
	pDoc = (CBrowserDoc *)GetActiveDocument();
	pView = pDoc ->GetView();
	// 문제점.. Doc 에서 CLeftView 뒤에 CBrowserView 가 안 나오고 바로 끝남..;
	return	pView;
}

BOOL CMainFrame::IsExistComboString(CString &str)
{
	CComboBox *pBox = (CComboBox *)m_wndDlgBar.GetDlgItem(IDC_COMBOURL);
	BOOL		bEqual = FALSE;
	if(pBox ->GetCurSel() != CB_ERR)	// 그냥 ComboBox 에서 고를시에
	{
		bEqual = TRUE;
	}
	// 그냥 입력 아닐 시엔 그냥 bEqual 이 초기화 된대로 FALSE..

	return	bEqual;
}

/*
static char BASED_CODE szFilter[] =
"Chart Files (*.xlc)|*.xlc|Worksheet Files \
(*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc;\
 *.xls|All Files (*.*)|*.*||";
*/

void CMainFrame::OnMenuViewer() 
{
	// TODO: Add your command handler code here
	//	File Dialog Error Handler Class  -->  CommDlgExtendedError

	CFileDialog		fileDlg(TRUE, _T("bmp;jpg"), _T("*.BMP;*.JPG"));
	INT				iIndex = CB_ERR;
	POSITION		pos = NULL;
	CString			strFilePath;
	strFilePath.Empty();
	iIndex = fileDlg.DoModal();
	switch(iIndex)
	{
	case IDOK :
		if(!m_pDoc)
		{
			m_pDoc = (CBrowserDoc *)GetActiveDocument();
			// Document m_pDoc 함수에 파일 경로나 기타 정보 저장
			// 그리고 나서 연산 ==> Doc 에다가 파일 경로의 BMP 출력 기능 넣는다..
		}
		strFilePath = fileDlg.GetPathName();
//		m_wndSplitter.SetColumnInfo(0, 100, 10);
//		m_wndSplitter.SetColumnInfo(1, 100, 10);
		m_pDoc ->MenuView(strFilePath);
		GetView() ->Explore(strFilePath);
		break;
	case IDCANCEL :
	default:
		break;
	}
}

void CMainFrame::OnFullscreen() 
{
	// TODO: Add your command handler code here
//	CBrowserView * pView = GetView();
//	pView ->SetFullScreen(m_bFullScreen = !pView ->GetFullScreen());
	if(m_bFullScreen)
	{	//	If current mode is NOT Fullscreen Mode.
		m_bFullScreen = FALSE;
		ModifyStyle(0, WS_CAPTION);
		ModifyStyle(0, WS_THICKFRAME);
		ShowWindow(SW_SHOWMAXIMIZED);
		SetMenu(&m_Menu);
		m_Menu.Detach();
		//	Show address bar, link bar and status bar.
		ShowControlBar(&m_wndDlgBar, TRUE, FALSE);
		ShowControlBar(&m_wndLinkBar, TRUE, FALSE);
		ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
	}
	else
	{	//	If Current Mode is fullscreen mode.
		m_bFullScreen = TRUE;
		//	Save current menu handle.
		m_Menu.Attach(GetMenu() ->m_hMenu);
		ModifyStyle(WS_CAPTION, 0);
		ModifyStyle(WS_THICKFRAME, 0);
		//	Eliminate default menu
		SetMenu(NULL);
		//	Show full screen window not to involve menu and frame
		ShowWindow(SW_MAXIMIZE);
		//	Hide bars..
		ShowControlBar(&m_wndDlgBar, FALSE, FALSE);
		ShowControlBar(&m_wndLinkBar, FALSE, FALSE);
		ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
	}
}

void CMainFrame::OnUpdateFullscreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI ->SetCheck(m_bFullScreen);
}

void CMainFrame::OnClearleftview() 
{
	// TODO: Add your command handler code here
	CBrowserDoc *pDoc = (CBrowserDoc *)GetActiveDocument();
	if(pDoc ->m_pImage)
	{
		delete	pDoc ->m_pImage;
		pDoc ->m_pImage = NULL;
	}
	CLeftView *pView = pDoc ->GetLeftView();
	CClientDC	dc(pView);
	::PatBlt(dc.GetSafeHdc(), 0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		WHITENESS);
}

void CMainFrame::OnAvi() 
{
	// TODO: Add your command handler code here
	if(m_pMovieDlg)
		delete	m_pMovieDlg;
	m_pMovieDlg = new CMoveDialog();
	m_pMovieDlg ->Create(IDD_MOVIEPLAY);
	m_pMovieDlg ->ShowWindow(SW_SHOW);
}

//  동영상 보기 다이얼로그가 없어진 직후 이 메세지 핸들러로 연결..
void CMainFrame::OnAviEnd()
{
/*
	이 때 m_pDlg::NcDestroy() 에서 delete this 가 아직 안 된 상태...
	왜 그런지는 모름... 따라서 m_pDlg 에 delete 를 실행하면 안 된다..
	==> OK! 이유를 알았다.. CMoveDialog::PostNCDestroy() 를 정상적으로 고쳤음..
	==> 다시 수정! 이때는 delete this 가 된 상태인 것 같다..
	==> CMoveDialog::PostNCDestroy() 에서 delete this; 를 실행 안 하고
	                        그냥 여기서 delete m_pDlg 를 실행하게 했음
*/
	delete	m_pMovieDlg;
	m_pMovieDlg = NULL;
}

BOOL CMainFrame::DeleteMovieDialog()
{
	if(m_pMovieDlg)
	{
		delete	m_pMovieDlg;
		m_pMovieDlg = NULL;
	}
	return	TRUE;
}

//	메인 프레임 뷰에 컨텍스트 메뉴 띄우기
void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu	*pMenu = new CMenu();
	CMenu	*pSubMenu = NULL;

	pMenu ->LoadMenu(IDR_MAINFRAME);
	pSubMenu = pMenu ->GetSubMenu(1);
	pSubMenu ->InsertMenu(pSubMenu ->GetMenuItemCount()
		, MF_BYPOSITION, ID_APP_ABOUT, _T("About Me? You must click this"));
	pSubMenu ->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	delete	pMenu;
	//	pSubMenu 는 delete 시키면 안 된다. You must not delete this pSubMenu...
	//	because GetSubMenu Method returns a pointer of submenu involved in real menu... not the copied object.
	//	So, if deletes the pointer, the real menu is broken...
//	delete	pSubMenu;
}

HRESULT CMainFrame::DeleteList()
{
	return	S_OK;
}

HRESULT CMainFrame::InsertList()
{
	return	S_OK;
}

HRESULT CMainFrame::ChangePosList()
{
	return	S_OK;
}

void CMainFrame::OnUpdateBack(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//	개량.. 요지
	//	List 없을 경우 무효화
	//	List 있을 경우 유효화
	pCmdUI ->Enable(TRUE);
}

void CMainFrame::OnUpdateNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//	개량.. 요지
	//	뒤로 리스트 있을 경우 유효화
	//	없으면 무효화
	pCmdUI ->Enable(TRUE);
}

HRESULT CMainFrame::SetDropDownToolBar()
{
//	SetBandHeight();
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	//	Set styles TBSTYLE_DROPDOWN of toolbar button.
	m_wndToolBar.SetButtonInfo(0, ID_BACK, TBSTYLE_BUTTON | TBSTYLE_DROPDOWN, 0);
//	m_wndLinkBar.SetButtonInfo(0, ID_SEARCHSITE, TBSTYLE_BUTTON | TBSTYLE_DROPDOWN, 0);
	return	S_OK;
}

void  CMainFrame::OnDropDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTOOLBAR *  pNMToolBar = (NMTOOLBAR*)pNMHDR;
	CRect	rect;
	CBrowserDoc *pDoc = (CBrowserDoc *)GetActiveDocument();
	ASSERT_VALID(pDoc);

	//	SetBandHeight()
	if(m_wndReBar.GetSafeHwnd())
	{	//	Investigate the creation of rebar or not..
		REBARBANDINFO	rbi;
		CSize	size;
		rbi.cbSize = sizeof(REBARBANDINFO);
		rbi.fMask = RBBIM_CHILDSIZE;
		size =  m_wndToolBar.GetToolBarCtrl().GetButtonSize();
		rbi.cyMinChild = size.cy;	//	minimum size of child window.
		m_wndReBar.GetReBarCtrl().SetBandInfo(0, &rbi);
	}

	//	manage dropdown button attached on MainToolBar
	//	메인 툴바의 드롭다운 버튼 처리
	m_wndToolBar.GetToolBarCtrl().GetRect(pNMToolBar ->iItem, &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar ->hdr.hwndFrom, &rect.TopLeft());
	if(pNMToolBar ->iItem == ID_BACK)
	{
		//	메뉴를 변환시켜라!
		//	지금 메뉴 그대로 사용 X
		//	string URL 들이 나오도록 해야...
		/*
			일단은, 메뉴를 직접 생성한다..
			그래서, MAINFRAME MENU 의 2번째 서브 메뉴 의 뒤 쪽에 URL 이 붙어 있으므로
			이것의 아이디와 스트링 고대로 가져와서 새로운 메뉴에 붙여넣는다. 그래서
			새로운 메뉴 완성하면, TrackPopupMenu 로 띄워주기만 하면 될 듯..
			2번째 서브 메뉴의 15번째... 즉 14 Index 부터 URL 들이 쭈루룩 붙어있을 것이다..
		*/
		CMenu * pPopup = NULL, * pMainMenu = GetMenu() ->GetSubMenu(1);
		pPopup = new CMenu();
		pPopup ->CreatePopupMenu();
		const INT	nStartIndex = 14;
		const INT	nMaxIndex = pMainMenu ->GetMenuItemCount();
		for(INT i = nStartIndex ; i < nMaxIndex ; i++)
		{
			CString str;
			INT nNewID = pMainMenu ->GetMenuItemID(i);
			pMainMenu ->GetMenuString(i, str, MF_BYPOSITION);

			// Push to new Menu
			pPopup ->AppendMenu(MF_STRING, nNewID, str);
		}
		//	At this point, that pPopup menu is completed...
		pPopup ->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
			rect.left, rect.top + 1 , this);
//		delete	pPopup;
	}

	//	Link Bar 의 드롭 다운 버튼 처리
	m_wndLinkBar.GetToolBarCtrl().GetRect(pNMToolBar ->iItem, &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar ->hdr.hwndFrom, &rect.TopLeft());
	CMenu	menu;
	CMenu * pPopup = NULL;
	menu.LoadMenu(IDR_LINKMENU);
	
	switch(pNMToolBar ->iItem)
	{
	case ID_SEARCHSITE :
		pPopup = menu.GetSubMenu(0);
		pPopup ->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, rect.top + 1, this);
		*pResult = TBDDRET_DEFAULT;
		
		break;
		
	case ID_FAVORITESITE :
		pPopup = GetMenu() ->GetSubMenu(4);
		pPopup ->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, rect.top + 1, this);
		*pResult = TBDDRET_DEFAULT;
		
		break;
		
/*	case ID_INTERFACESITE :
		pPopup = menu.GetSubMenu(2);
		break;*/

	default :
		break;
	}
}


void CMainFrame::OnSearchDaum() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.daum.net");
	CBrowserView * pView = NULL;
	//	문제점... GetView 가 LEftVIew 의 포인터를 반환하고 있다.
	//	CBrowserView 의 포인터를 반환해야 정상적으로 동작한다.
	pView = GetView();
	pView ->Explore(url);
}

void CMainFrame::OnSearchNaver() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.naver.com");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchEmpas() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.empas.com");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchGoogle() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.google.co.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchAltavista() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.altavista.co.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchLycos() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.lycos.co.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchMsn() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.msn.co.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchYahoo() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.yahoo.co.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchChol() 
{
	// TODO: Add your command handler code here
	CString	url = _T("search.chol.com");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchDreamwiz() 
{
	// TODO: Add your command handler code here
	CString	url = _T("search.dreamwiz.com");
	GetView() ->Explore(url);
}

void CMainFrame::OnSearchHanmir() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.hanmir.com");
	GetView() ->Explore(url);
}

void CMainFrame::OnUpdateSearchsite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI ->Enable();
}


void CMainFrame::OnUpdateFavoritesite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI ->Enable();
}

/*void CMainFrame::OnUpdateInterfacesite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI ->Enable();
}*/

void CMainFrame::OnSejongsite() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.sejong.ac.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnDaumsite() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.daum.net");
	GetView() ->Explore(url);
}

void CMainFrame::OnInterfacesite() 
{
	// TODO: Add your command handler code here
	CString	url = _T("www.interface.or.kr");
	GetView() ->Explore(url);
}

void CMainFrame::OnAllftp() 
{
	// TODO: Add your command handler code here
//	CFTPDlg	dlg;
//	dlg.DoModal();
	//	Modaless dialog 로 변환
	if(m_pFTPDlg)
		delete	m_pFTPDlg;
	m_pFTPDlg = new CFTPDlg ();
	m_pFTPDlg ->Create(IDD_FTP, this);
	m_pFTPDlg ->ShowWindow(SW_SHOW);
}

void CMainFrame::OnAddfavorite() 
{
	// TODO: Add your command handler code here
	if(MessageBox(_T("현재 사이트를 즐겨찾기에 추가하시겠습니까?"), _T("즐겨찾기 추가"), MB_YESNO)
		== IDNO)
		return;

	CString strSection       = _T("My Favorites");
	CString strURLItem    = _T("URL");
	CString	strURL;
	CString	strCount = _T("Favorites Count");
	CString	strCountItem = _T("Count");
	INT		nCountFavorites = -10;

	CWinApp* pApp = AfxGetApp();
	if(pApp ->GetProfileInt(strCount, strCountItem, -10) == -10)
	{	//	Section 이 발견되지 않았으므로, Favorites 처음 등록시...
		//	이제 1개의 엔트리가 들어가므로 Count 는 1이 된다.
		pApp ->WriteProfileInt(strCount, strCountItem, 1);
		//	현재 URL 을 얻어서 첫 번째 레지스트리(==URL1)에 등록
		strURL = ((CBrowserDoc *)GetActiveDocument()) ->m_strNowURL;
		strURLItem += "1";
		pApp ->WriteProfileString(strSection, strURLItem, strURL);
		//	더불어 리스트에도 추가로 등록
		CMenu * pPopup = GetMenu() ->GetSubMenu(4);
		pPopup ->AppendMenu(MF_STRING, MENU_ID_ADDEDFAVORITE + 1, strURL);
	}
	else
	{	//	이미 엔트리가 들어가있는 경우
		//	Count 값을 1 증가시켜준다..
		nCountFavorites = pApp ->GetProfileInt(strCount, strCountItem, -10);
		nCountFavorites ++;
		pApp ->WriteProfileInt(strCount, strCountItem, nCountFavorites);
		//	그런 후 새로운 URL 을 추가로 등록!
		CString	str;
		str.Format("%d", nCountFavorites);
		strURLItem += str;
		strURL = ((CBrowserDoc *) GetActiveDocument()) ->m_strNowURL;
		pApp ->WriteProfileString(strSection, strURLItem, strURL);
		//	더불어 리스트에도 추가로 등록
		CMenu * pPopup = GetMenu() ->GetSubMenu(4);
		pPopup ->AppendMenu(MF_STRING, MENU_ID_ADDEDFAVORITE + nCountFavorites, strURL);

//		m_pDoc ->AddList(strURL);
	}
}
/*

void CMainFrame::OnCapturescreen() 
{
	// TODO: Add your command handler code here
	HBITMAP	hBit , hOldBitmap;
	HDC	SrcDC;
	HDC MemDC;
	CWindowDC	dc(this);
	CRect		rt;
	::GetClientRect(dc.GetWindow() ->m_hWnd, &rt);
	SrcDC = ::CreateDC("DISPLAY" , NULL, NULL, NULL);
	MemDC = ::CreateCompatibleDC(SrcDC);
	hBit = CreateCompatibleBitmap(SrcDC, rt.right - rt.left, rt.bottom - rt.top);
	hOldBitmap = (HBITMAP) SelectObject(MemDC, hBit);

	BitBlt(MemDC, 0, 0, rt.right-rt.left, rt.bottom-rt.top,
		SrcDC, rt.left, rt.top, SRCCOPY);
	SelectObject(MemDC, hOldBitmap);
//	DeleteDC(MemDC);
//	DeleteDC(SrcDC);

	CBaseImage image;
	CRect		rt2;
	dc.GetWindow() ->GetClientRect(&rt2);
	HDC MemDC2;
	HBITMAP hOldBitmap2;

//	image.AllocBmpInfo(0);
//	SIZE s ;
//	s.cx = rt2.right-rt2.left;
//	s.cy = rt2.top-rt2.bottom;
//	image.SetBmpInfo(s , 0);

}
*/

void CMainFrame::OnOption() 
{
	// TODO: Add your command handler code here
	CMyPropertySheet	dlg;
	CWinApp * pApp = AfxGetApp();
	if(dlg.DoModal() == IDOK)
	{
		CString	strAlarmSection = _T("Alarm");
		CString	strAlarmEntry1 = _T("Alarm Enable");
		CString	strAlarmEntry2_1 = _T("Hours");
		CString	strAlarmEntry2_2 = _T("Minutes");
		CString strAlarmEntry2_3 = _T("Alarm Play File");
		CString	strEnableAlarm;
		//	Check Alarm 전달
		if(dlg.m_Page1.m_checkAlarm == TRUE)
			strEnableAlarm = _T("TRUE");
		else
			strEnableAlarm = _T("FALSE");
		//	Alarm File Name 전달 => 직접 전달
		//	Hours 시간 전달 => 직접 전달
		//	Minutes 분 전달 => 직접 전달

		pApp ->WriteProfileString(strAlarmSection, strAlarmEntry1, strEnableAlarm);
		pApp ->WriteProfileString(strAlarmSection, strAlarmEntry2_1, dlg.m_Page1.m_strHour);
		pApp ->WriteProfileString(strAlarmSection, strAlarmEntry2_2, dlg.m_Page1.m_strMinute);
		pApp ->WriteProfileString(strAlarmSection, strAlarmEntry2_3, dlg.m_Page1.m_strAlarmFile);

		m_alarm.bAlarm = (strEnableAlarm.Compare(_T("TRUE")) == 0) ? TRUE : FALSE;
		m_alarm.nHours = atoi(dlg.m_Page1.m_strHour);
		m_alarm.nMinutes = atoi(dlg.m_Page1.m_strMinute);
		m_alarm.strAlarmFile = dlg.m_Page1.m_strAlarmFile;
	}
}

void CMainFrame::OnAddedFavorites(UINT nID)
{
	CMenu *pFav = GetMenu() ->GetSubMenu(4);
	CString		selURL;
	pFav ->GetMenuString(nID, selURL, MF_BYCOMMAND);
	GetView() ->Explore(selURL);
}

void CMainFrame::OnAddedURL(UINT nID)
{
	CMenu *pUrl = GetMenu() ->GetSubMenu(1);
	CString		selURL;
	pUrl ->GetMenuString(nID, selURL, MF_BYCOMMAND);
	GetView() ->Explore(selURL);
}

void CMainFrame::OnTrayIcon() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);

	NOTIFYICONDATA  nId;
	nId.cbSize = sizeof(nId);
	nId.hWnd = m_hWnd;
	nId.uID = IDR_MAINFRAME;
	nId.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;	// set flags
	nId.uCallbackMessage = WM_MY_TASKBAR;			// set callback message
	nId.hIcon = AfxGetApp() ->LoadIcon(IDR_MAINFRAME);	// load resource icon

	TCHAR strTitle[256];
	GetWindowText(strTitle, sizeof(strTitle));	// get the string printed on caption bar
	_tcscpy(nId.szTip, strTitle);	// set tooltip
	// insert icon at the tray region of taskbar
	// or if deleted send message to windows system
	Shell_NotifyIcon(NIM_ADD, &nId);
	// set Icon at the tray region of taskbar
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nId.hIcon);
	m_bTray = TRUE;
}

LONG CMainFrame::TrayIconSetting(WPARAM wParam, LPARAM lParam)
{
	if(lParam == WM_LBUTTONDBLCLK)
	{	// If user dblclk the tray icon...
		ShowWindow(SW_SHOW);
	}
	return	0L;
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_bTray)
	{
		NOTIFYICONDATA	nId;
		nId.cbSize = sizeof(nId);
		nId.hWnd = m_hWnd;	// main window handle
		nId.uID = IDR_MAINFRAME;
		//delete icon at the status region of taskbar
		Shell_NotifyIcon(NIM_DELETE, &nId);
	}
	// 여기에 오목 종료 코드 너어야 한다.
	// 잘 안 되는데, 일단 삭제해놓자...
//	CWnd * pWnd = CWnd::FindWindow(NULL, _T("NetOmok"));
//	if(pWnd != NULL)
//		pWnd ->SendMessage(WM_NOTIFIED_QUIT_FROM_OWNER, (WPARAM) /*dc.GetSafeHdc()*/ pWnd ->GetDC() ->GetSafeHdc(), 0);
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	MessageBox("c");
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnProperties()
{
	// TODO: The property sheet attached to your project
	// via this function is not hooked up to any message
	// handler.  In order to actually use the property sheet,
	// you will need to associate this function with a control
	// in your project such as a menu item or tool bar button.

	CMyPropertySheet propSheet;

	propSheet.DoModal();

	// This is where you would retrieve information from the property
	// sheet if propSheet.DoModal() returned IDOK.  We aren't doing
	// anything for simplicity.
}

void CMainFrame::OnGamemenu() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu;
	pMenu = new CMenu();
	pMenu ->LoadMenu(IDR_GAMEMENU);
	pMenu ->TrackPopupMenu(TPM_LEFTALIGN, 1000, 300, this);
}
