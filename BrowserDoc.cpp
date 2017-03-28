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
	m_nPos = 1;	// ó�� ���� ����Ʈ ����.
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

	//	alarm �� ������Ʈ������ �о�ͼ� �ʱ�ȭ...
	if((nHour = pApp ->GetProfileInt(strTimeSection, strHours, -17)) == -17)
	{	// ������Ʈ���� �˶� �ð� ������ ����
		m_alarm.nHours = 8;
	}
	else
	{	// ����
		m_alarm.nHours = nHour;
	}
	if((nMinute = pApp ->GetProfileInt(strTimeSection, strMinutes, -17)) == -17)
	{	// �˶� �� ������ ����
		m_alarm.nMinutes = 30;
	}
	else
	{	// ����
		m_alarm.nMinutes = nMinute;
	}
	//	alarm �� ������Ʈ���� ����ϴ� �ڵ� �ۼ� (���Ŀ�...)
	//	alarm ���� �ɼ� ÷��*/
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
	if(m_pImage)	// m_pImage �� �ε�����..
		delete	m_pImage;	// �Ұ�
	strViewPath.MakeLower();	// �ҹ��ڷ� ��ȯ
	INT nIndex[4];
	// Find �Լ��� ���н� -1 �� ����..
	nIndex[0] = strViewPath.Find("bmp", strViewPath.GetLength() - 3);
	nIndex[1] = strViewPath.Find("jpg", strViewPath.GetLength() - 3);
	nIndex[2] = strViewPath.Find("jpeg", strViewPath.GetLength() - 4);
	nIndex[3] = strViewPath.Find("gif", strViewPath.GetLength() - 4);
	if(nIndex[0] != -1 || nIndex[1] != -1 || nIndex[2] != -1)
		// ���� ������ BMP JPG GIF ���� �ϳ��� �ɸ���
	{
		//	OK!!
	}
	else
	{
		AfxMessageBox("��Ʈ�� ���ϰ� JPEG ����, GIF ���ϸ� �ε��� �� �ֽ��ϴ�.");
		return	FALSE;
	}

	if(nIndex[0] != -1)
	{
		m_pImage = new CBaseBitmap;	// ���Ҵ�
		m_pImage ->LoadBmp(strViewPath);
	}
	else if(nIndex[1] != -1)
	{
		m_pImage = new CBaseJPG; // ���Ҵ�
		m_pImage ->LoadJpg(strViewPath);
	}
	else if(nIndex[2] != -1)
	{
		m_pImage = new CBaseJPG;
		m_pImage ->LoadJpg(strViewPath);
	}
	else if(nIndex[3] != -1)
	{
		AfxMessageBox(_T("GIF �� ���� ����"));
	}
	else
	{
		AfxMessageBox("��Ʈ�� ���ϰ� JPEG ����, GIF���ϸ� �ε��� �� �ֽ��ϴ�.");
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
			// browser View �� ã���� ����
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

//	m_nPos �� �ڿ������� �����ϹǷ� ������ ��!
HRESULT CBrowserDoc::AddList(CString	&url)
{
	//1. ���� ����Ʈ ���� ����Ʈ ����
	//2. Add List

	//	������ ��ó�� �ؾ��ϳ�, ����� ������ �׳� 2. ������ ����..

/*	// 1 process
	if(m_nPos == 1)
		;
	else
		//	Back �� �Ͼ ���,
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
		{	// ���� URL �� ����ÿ�...
			return	E_FAIL;
		}
	}
	m_listURL.AddHead(url);
	//	���� ������ ����Ʈ �޴��� 2��° �޴����ٰ� ���ο� URL �̸��� �����Ѵ�.
	CMenu *pPop = AfxGetMainWnd() ->GetMenu() ->GetSubMenu(1);
	nAddedCount ++;
	pPop ->AppendMenu(MF_STRING, MENU_ID_ADDEDURL + nAddedCount, url);
	//	URL ���� �޴����� ���ο� URL �̸��� �����Ѵ�.
	//	.... �׳� URL ���� �޴� ���� ��� ���ο� URL �̸� �����ؼ� �ѷ��ֱ�� �ߴ�.

	return	S_OK;
}

HRESULT CBrowserDoc::MovPointInList()
{
	//1. ����Ʈ �ȿ��� ������ ������
	// EX > BACK ��ư Ŭ���� nPos ++
	//	�׳� ���� ���� �Լ�
	m_nPos ++;
	return	S_OK;
}

HRESULT CBrowserDoc::DeleteList()
{
	// ���� ������ �ڷ� ����Ʈ ���� ����
	return	S_OK;
}

void CBrowserDoc::OnConfirm() 
{
	// TODO: Add your command handler code here
	//	����!!
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
		AfxMessageBox(_T("�߸��� ������ ������ �����Ͽ����ϴ�."));
		break;
	case ERROR_FILE_NOT_FOUND :
		nResult = WinExec(_T("..\\NetOmok\\Debug\\NetOmok.exe") ,SW_SHOW);
		if(nResult == ERROR_FILE_NOT_FOUND)
			AfxMessageBox(_T("�������� �ʴ� ������ �����Ͽ����ϴ�."));
		break;
	case ERROR_PATH_NOT_FOUND :
		AfxMessageBox(_T("�߸��� ����� ������ �����Ͽ����ϴ�."));
		break;
	}
}