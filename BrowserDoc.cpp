// BrowserDoc.cpp : implementation of the CBrowserDoc class
//
#include "stdafx.h"
#include "Browser.h"

#include "BrowserDoc.h"
#include "BrowserView.h"
#include "LeftView.h"
#include "BaseBitmap.h"
#include "MainFrm.h"
#include "BaseJPG.h"
//#include "List_LPSTR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef		BROWSER_DOC_CPP__
#define		BROWSER_DOC_CPP__

#define		MENU_ID_ADDEDURL		58171

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc

IMPLEMENT_DYNCREATE(CBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CBrowserDoc)
	ON_COMMAND(ID_CONFIRM, OnConfirm)
	ON_COMMAND(ID_GAMEMENU, OnGamemenu)
	ON_COMMAND(ID_GAME_OMOK, OnGameOmok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc construction/destruction

CBrowserDoc::CBrowserDoc()
{
	// TODO: add one-time construction code here
	m_pImage = NULL;
	//m_listURL = new List();
	m_nPos = 1;	// 처음 다음 사이트 들어간다.
	m_strServerPath = _T("");
	m_strLocalPath = _T("");
	m_bConnected = FALSE;
	m_strNowURL = _T("www.daum.net");
	m_bPlaying = FALSE;
	m_focus = FRAME;
	m_pOmokView = NULL;
//	m_alarm.nHours = g_alarm.nHours;
//	m_alarm.nMinutes = g_alarm.nMinutes;
//	m_alarm.bAlarm = g_alarm.bAlarm;
//	m_alarm.strAlarmFile = g_alarm.strAlarmFile;
}

CBrowserDoc::~CBrowserDoc()
{
//	delete	m_listURL;
}

BOOL CBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
/*	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	CWinApp *pApp = AfxGetApp();
	INT		nHour, nMinute;
	CString	strTimeSection = _T("Alarm");
	CString strHours = _T("Alarm Hours");
	CString strMinutes = _T("Alarm Minutes");

	//	alarm 을 레지스트리에서 읽어와서 초기화...
	if((nHour = pApp ->GetProfileInt(strTimeSection, strHours, -17)) == -17)
	{	// 레지스트리서 알람 시간 얻어오기 실패
		m_alarm.nHours = 8;
	}
	else
	{	// 성공
		m_alarm.nHours = nHour;
	}
	if((nMinute = pApp ->GetProfileInt(strTimeSection, strMinutes, -17)) == -17)
	{	// 알람 분 얻어오기 실패
		m_alarm.nMinutes = 30;
	}
	else
	{	// 성공
		m_alarm.nMinutes = nMinute;
	}
	//	alarm 을 레지스트리에 등록하는 코드 작성 (이후에...)
	//	alarm 설정 옵션 첨가*/
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc serialization

void CBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc diagnostics

#ifdef _DEBUG
void CBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc commands

BOOL CBrowserDoc::MenuView(CString  strViewPath)
{
	BOOL	bResult = FALSE;
	if(m_pImage)	// m_pImage 가 로딩상태..
		delete	m_pImage;	// 소거
	strViewPath.MakeLower();	// 소문자로 변환
	INT nIndex[4];
	// Find 함수는 실패시 -1 를 리턴..
	nIndex[0] = strViewPath.Find("bmp", strViewPath.GetLength() - 3);
	nIndex[1] = strViewPath.Find("jpg", strViewPath.GetLength() - 3);
	nIndex[2] = strViewPath.Find("jpeg", strViewPath.GetLength() - 4);
	nIndex[3] = strViewPath.Find("gif", strViewPath.GetLength() - 4);
	if(nIndex[0] != -1 || nIndex[1] != -1 || nIndex[2] != -1)
		// 파일 형식이 BMP JPG GIF 중의 하나로 걸리면
	{
		//	OK!!
	}
	else
	{
		AfxMessageBox("비트맵 파일과 JPEG 파일, GIF 파일만 로드할 수 있습니다.");
		return	FALSE;
	}

	if(nIndex[0] != -1)
	{
		m_pImage = new CBaseBitmap;	// 재할당
		m_pImage ->LoadBmp(strViewPath);
	}
	else if(nIndex[1] != -1)
	{
		m_pImage = new CBaseJPG; // 재할당
		m_pImage ->LoadJpg(strViewPath);
	}
	else if(nIndex[2] != -1)
	{
		m_pImage = new CBaseJPG;
		m_pImage ->LoadJpg(strViewPath);
	}
	else if(nIndex[3] != -1)
	{
		AfxMessageBox(_T("GIF 곧 개선 예정"));
	}
	else
	{
		AfxMessageBox("비트맵 파일과 JPEG 파일, GIF파일만 로드할 수 있습니다.");
		return	FALSE;
	}

	CLeftView * pView = NULL;
	pView = GetLeftView();
//	pView ->SetAddressBar(FALSE);
	if(!pView)	// pView == NULL
		return	FALSE;
	::PatBlt(pView ->GetDC() ->GetSafeHdc(), 0, 0, GetSystemMetrics(SM_CXSCREEN)
		, GetSystemMetrics(SM_CYSCREEN), WHITENESS);
	bResult = m_pImage ->PaintImage(0, 0, pView ->GetDC() ->GetSafeHdc());
//	this ->GetLeftView() ->SetWindowPos(NULL, 0, 0,
//		m_pImage ->GetSize().cx + 20, m_pImage ->GetSize().cy + 60, SWP_SHOWWINDOW);

	return	bResult;
}

CBrowserView * CBrowserDoc::GetView()
{
	/*
	CBrowserView *pView = NULL;
	POSITION	pos;
	pos = GetFirstViewPosition();
	while( pos != NULL )
	{
		pView = (CBrowserView *)GetNextView(pos);
		if( pView ->m_bBrowserView == TRUE )
			// browser View 를 찾으면 리턴
			break;
	}
	*/
	CBrowserView *pView;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pView = (CBrowserView *)pFrame ->m_wndSplitter.GetPane(0 , 1);
	return	pView;
}

CLeftView * CBrowserDoc::GetLeftView()
{
	CLeftView *pView;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pView = (CLeftView *)pFrame ->m_wndSplitter.GetPane(0 , 0);
	return	pView;
}

//	m_nPos 는 뒤에서부터 시작하므로 주의할 것!
HRESULT CBrowserDoc::AddList(CString	&url)
{
	//1. 현재 포인트 뒤의 리스트 삭제
	//2. Add List

	//	원래는 위처럼 해야하나, 잡다한 문제로 그냥 2. 과정만 하자..

/*	// 1 process
	if(m_nPos == 1)
		;
	else
		//	Back 이 일어난 경우,
		m_listURL ->DeleteFromPos(m_nPos);
	// 2 process
	m_listURL ->insertNode(url.GetBuffer(0));
	m_nPos = 1;*/
	static INT nAddedCount = 0;
	POSITION	pos = m_listURL.GetHeadPosition();
	while(pos != NULL)
	{
		CString	str;
		str = m_listURL.GetNext(pos);
		if(url.Compare(str) == 0)
		{	// 같은 URL 이 존재시엔...
			return	E_FAIL;
		}
	}
	m_listURL.AddHead(url);
	//	메인 프레임 디폴트 메뉴의 2번째 메뉴에다가 새로운 URL 이름을 삽입한다.
	CMenu *pPop = AfxGetMainWnd() ->GetMenu() ->GetSubMenu(1);
	nAddedCount ++;
	pPop ->AppendMenu(MF_STRING, MENU_ID_ADDEDURL + nAddedCount, url);
	//	URL 전용 메뉴에도 새로운 URL 이름을 삽입한다.
	//	.... 그냥 URL 전용 메뉴 생성 즉시 새로운 URL 이름 삽입해서 뿌려주기로 했다.

	return	S_OK;
}

HRESULT CBrowserDoc::MovPointInList()
{
	//1. 리스트 안에서 포인터 움직임
	// EX > BACK 버튼 클릭시 nPos ++
	//	그냥 쓰지 않을 함수
	m_nPos ++;
	return	S_OK;
}

HRESULT CBrowserDoc::DeleteList()
{
	// 현재 포인터 뒤로 리스트 전부 삭제
	return	S_OK;
}

void CBrowserDoc::OnConfirm() 
{
	// TODO: Add your command handler code here
	//	문제!!
	ASSERT(GetLeftView() ->IsKindOf(RUNTIME_CLASS(CBrowserView)));
}

#endif

void CBrowserDoc::OnGamemenu() 
{
	// TODO: Add your command handler code here
	CMenu * menu, *pPopup;
	POINT pt;
	pt.x = 1000;
	pt.y = 80;
	menu = new CMenu;
	menu ->LoadMenu(IDR_GAMEMENU);
	pPopup = menu ->GetSubMenu(0);
	//	At this point, that pPopup menu is completed...
	pPopup ->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
		pt.x, pt.y + 1 , AfxGetApp() ->m_pMainWnd);
}

void CBrowserDoc::OnGameOmok() 
{
	// TODO: Add your command handler code here
	UINT	nResult = -1;
	nResult = WinExec(_T(".\\NetOmok\\Debug\\NetOmok.exe") ,SW_SHOW);
	switch(nResult)
	{
	case 0 :
		AfxMessageBox("a");
		break;
	case ERROR_BAD_FORMAT :
		AfxMessageBox(_T("잘못된 형식의 파일을 실행하였습니다."));
		break;
	case ERROR_FILE_NOT_FOUND :
		nResult = WinExec(_T("..\\NetOmok\\Debug\\NetOmok.exe") ,SW_SHOW);
		if(nResult == ERROR_FILE_NOT_FOUND)
			AfxMessageBox(_T("존재하지 않는 파일을 실행하였습니다."));
		break;
	case ERROR_PATH_NOT_FOUND :
		AfxMessageBox(_T("잘못된 경로의 파일을 실행하였습니다."));
		break;
	}
}