// BrowserDoc.h : interface of the CBrowserDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROWSERDOC_H__56FCF2D2_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_BROWSERDOC_H__56FCF2D2_EB7F_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBaseImage;
class CBrowserView;
class CLeftView;
class CBaseBitmap;
//class List;

typedef enum
{
	FRAME = 0,
	DOC,
	VIEW
} Focus;

class COmokFrame;

class CBrowserDoc : public CDocument
{
protected: // create from serialization only
	CBrowserDoc();
	DECLARE_DYNCREATE(CBrowserDoc)

// Attributes
public:
	COmokFrame  *m_pOmokView;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	Focus	m_focus;
	BOOL	m_bPlaying;
	CString	m_strNowURL;
	CString m_strServerPath;	// init!
	BOOL m_bConnected;			// init!
	CString m_strLocalPath;		// init!
	CList<CString, CString &> m_listURL;
	INT	m_nPos;
	HRESULT DeleteList();
	HRESULT MovPointInList();
	HRESULT AddList(CString	&url);
	CLeftView * GetLeftView(void);
	CBrowserView * GetView(void);
	CBaseImage	* m_pImage;
	BOOL MenuView(CString strViewPath);
	virtual ~CBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
//	List *m_listURL;
	//{{AFX_MSG(CBrowserDoc)
	afx_msg void OnConfirm();
	afx_msg void OnGamemenu();
	afx_msg void OnGameOmok();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERDOC_H__56FCF2D2_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
