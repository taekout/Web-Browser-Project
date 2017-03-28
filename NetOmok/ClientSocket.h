#if !defined(AFX_CLIENTSOCKET_H__8D93E9A4_11A7_11D6_9871_004854839105__INCLUDED_)
#define AFX_CLIENTSOCKET_H__8D93E9A4_11A7_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target
#include "NetOmokView.h"
class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();

// Overrides
public:
	void Init();
	CNetOmokView* m_pView;
	CClientSocket(CNetOmokView* pView);
	CSocketFile* m_pSocketFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__8D93E9A4_11A7_11D6_9871_004854839105__INCLUDED_)
