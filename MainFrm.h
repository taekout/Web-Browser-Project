// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__56FCF2D0_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_MAINFRM_H__56FCF2D0_EB7F_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UrlDlg.h"
#include "MoveDialog.h"	// Added by ClassView
//#include "List_LPSTR.h"	// Added by ClassView
//#include "FrameDecoration.h"	// Added by ClassView

class CBrowserView;
class CBrowserDoc;
class CFTPDlg;

#define		WM_USER_DIALOG_DESTROYED	0x8888


class CMainFrame : public CFrameWnd
{
protected:
	CBrowserDoc *m_pDoc;

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWnd m_wndSplitter;

public:
	CUrlDlg		*m_urlDlg;
	struct Alarm
	{
		BOOL	bAlarm;
		CString	strAlarmFile;
		INT		nHours;
		INT		nMinutes;
	} m_alarm;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL DeleteMovieDialog();
	CBrowserView * GetView(void);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public :	// control bar not embedded members
	void OnProperties();
	INT m_nCountFavorites;
	HRESULT SetDropDownToolBar();
	HRESULT ChangePosList();
	HRESULT InsertList();
	HRESULT DeleteList();
	CStatusBar  m_wndStatusBar;

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar	m_wndDlgBar;

// Generated message map functions
protected:
	
	BOOL m_bTray;
	CFTPDlg * m_pFTPDlg;
	CToolBar m_wndLinkBar;
	CMenu m_Menu;
	CMoveDialog *m_pMovieDlg;
	BOOL m_bFullScreen;
	BOOL IsExistComboString(CString &str);
	BOOL m_bFocus;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnBack();
	afx_msg void OnNext();
	afx_msg void OnHome();
	afx_msg void OnFresh();
	afx_msg void OnStop();
	afx_msg void OnMenuViewer();
	afx_msg void OnFullscreen();
	afx_msg void OnUpdateFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnClearleftview();
	afx_msg void OnAvi();
	afx_msg void OnAviEnd();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
	afx_msg void OnDropDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchDaum();
	afx_msg void OnSearchNaver();
	afx_msg void OnSearchEmpas();
	afx_msg void OnSearchGoogle();
	afx_msg void OnSearchAltavista();
	afx_msg void OnSearchLycos();
	afx_msg void OnSearchMsn();
	afx_msg void OnSearchYahoo();
	afx_msg void OnSearchChol();
	afx_msg void OnSearchDreamwiz();
	afx_msg void OnSearchHanmir();
	afx_msg void OnUpdateSearchsite(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFavoritesite(CCmdUI* pCmdUI);
	afx_msg void OnSejongsite();
	afx_msg void OnDaumsite();
	afx_msg void OnInterfacesite();
	afx_msg void OnAllftp();
	afx_msg void OnAddfavorite();
	afx_msg void OnOption();
	afx_msg void OnTrayIcon();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGamemenu();
	//}}AFX_MSG
	afx_msg void OnAddedFavorites(UINT nId);
	afx_msg void OnAddedURL(UINT nId);

	//	USER Defined Message Handler
	LONG TrayIconSetting(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__56FCF2D0_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
