// NetOmok.h : main header file for the NETOMOK application
//

#if !defined(AFX_NETOMOK_H__EFD62BA5_1198_11D6_9871_004854839105__INCLUDED_)
#define AFX_NETOMOK_H__EFD62BA5_1198_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetOmokApp:
// See NetOmok.cpp for the implementation of this class
//

class CNetOmokApp : public CWinApp
{
public:
	CNetOmokApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetOmokApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNetOmokApp)
	afx_msg void OnAppAbout();
	afx_msg LONG OnNotifiedQuitFromOwner(UINT wParam, LONG lParam);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETOMOK_H__EFD62BA5_1198_11D6_9871_004854839105__INCLUDED_)
