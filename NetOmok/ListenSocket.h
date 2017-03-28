#if !defined(AFX_LISTENSOCKET_H__8D93E9A3_11A7_11D6_9871_004854839105__INCLUDED_)
#define AFX_LISTENSOCKET_H__8D93E9A3_11A7_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target
#include "NetOmokDoc.h"
#include "NetOmokView.h"
class CListenSocket : public CSocket
{
// Attributes
public:
		CNetOmokView* m_pView;
// Operations
public:
	CListenSocket();
	CListenSocket(CNetOmokView* pView);
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__8D93E9A3_11A7_11D6_9871_004854839105__INCLUDED_)
