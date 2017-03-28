// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "NetOmok.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_INFOBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_INFOBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_CHATDLG, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_CHATDLG, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK,OnSendMessage)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
//		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
//	{
//		TRACE0("Failed to create toolbar\n");
//		return -1;      // fail to create
//	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "ChatDlg":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_CHATDLG
	//   5. Assign the item a Caption: ChatDlg

	// TODO: Change the value of CG_ID_VIEW_CHATDLG to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndChatDlg
		if (!m_wndChatDlg.Create(this, CG_IDD_CHATDLG,
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_CHATDLG))
		{
			TRACE0("Failed to create dialog bar m_wndChatDlg\n");
			return -1;		// fail to create
		}

		m_wndChatDlg.EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndChatDlg);

	}

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "InfoBar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_INFOBAR
	//   5. Assign the item a Caption: InfoBar

	// TODO: Change the value of CG_ID_VIEW_INFOBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndInfoBar
		if (!m_wndInfoBar.Create(this, CG_IDD_INFOBAR,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_INFOBAR))
		{
			TRACE0("Failed to create dialog bar m_wndInfoBar\n");
			return -1;		// fail to create
		}

		m_wndInfoBar.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		//EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndInfoBar);

	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx=500;
	cs.cy=530;
	cs.style &=~WS_MINIMIZEBOX;
	cs.style &=~WS_MAXIMIZEBOX;
	cs.style &=~ WS_THICKFRAME;
	cs.style &=~ FWS_ADDTOTITLE;
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

#include "NetOmokDoc.h"
#include "NetOmokView.h"
#include "CLientSocket.h"
#include "Data.h"
void CMainFrame::OnSendMessage()
{
    UpdateData(1);
	
	CNetOmokDoc* pDoc = (CNetOmokDoc*)GetActiveDocument();
	CNetOmokView* pView = (CNetOmokView*)GetActiveView();
	
	CData *pData = new CData;
    CEdit* pEditUrl;
	
	if(pView->m_pClientSocket==NULL){AfxMessageBox("메세지를 보낼 수 없습니다.\n먼저 접속하세요.");return;}

	pEditUrl =  (CEdit*) m_wndChatDlg.GetDlgItem(IDC_EDIT_SEND_MSG);
	CString strUrl;
	pEditUrl->GetWindowText(strUrl);
	pData->m_strChat = strUrl;
	pData->m_nGubun=2;
	pData->Serialize(*pView->m_pClientSocket->m_pArchiveOut);
	pView->m_pClientSocket->m_pArchiveOut->Flush();
	pEditUrl->SetWindowText("");
	UpdateData(0);
}
