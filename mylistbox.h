#if !defined(AFX_ServerLISTBOX_H__6A305CC1_69C0_11D6_A08B_000021EAA6E1__INCLUDED_)
#define AFX_ServerLISTBOX_H__6A305CC1_69C0_11D6_A08B_000021EAA6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerListBox.h : header file
//


class CBrowserDoc;


/////////////////////////////////////////////////////////////////////////////
// CServerListBox window

class CServerListBox : public CDragListBox
{
// Member variables .. For Globalization
public:
	CFtpConnection		*m_pConnection;
	CFtpFileFind		*m_pFileFind;	// FTP 파일 검색 용도 클래스
	CInternetSession	*m_pSession;	// 세션 클래스
	CBrowserDoc			*m_pDoc;		// Document 포인터

// Construction
public:
	CServerListBox();

// Attributes
public:
	CString  &GetSelString();
	void	EnumerateList();
	BOOL	BeginDrag( CPoint pt );
	void	Dropped( int nSrcIndex, CPoint pt );

public:
// Rgn
	BOOL	m_bDragStartPointInServer;

// SelectFileString
	CString		m_strSel;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CServerListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CServerListBox)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ServerLISTBOX_H__6A305CC1_69C0_11D6_A08B_000021EAA6E1__INCLUDED_)



#if !defined(AFX_LOCALLISTBOX_H__6A305CC7_69C0_11D6_A08B_000021EAA6E1__INCLUDED_)
#define AFX_LOCALLISTBOX_H__6A305CC7_69C0_11D6_A08B_000021EAA6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalListBox window

class CLocalListBox : public CDragListBox
{
// Member variables  For Globalization
public:
	CFtpConnection		*m_pConnection;
	CInternetSession	*m_pSession;
	CFtpFileFind		*m_pFileFind;
	CBrowserDoc			*m_pDoc;
// Construction
public:
	CLocalListBox();

// Attributes
public:
	CString & GetSelString();
	void	EnumerateList();
	BOOL	BeginDrag( CPoint pt );
	void	Dropped( int nSrcIndex, CPoint pt );

public:
	// Rgn
	BOOL	m_bDragStartPointInLocal;

	// Selected String
	CString	m_strSel;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLocalListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocalListBox)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALLISTBOX_H__6A305CC7_69C0_11D6_A08B_000021EAA6E1__INCLUDED_)
