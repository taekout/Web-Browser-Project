#if !defined(AFX_URLDLG_H__56FCF2DF_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_URLDLG_H__56FCF2DF_EB7F_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UrlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg dialog

class CUrlDlg : public CDialog
{
// Construction
public:
	BOOL GetURLComboFocus();
	BOOL m_bFocus;
	CUrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUrlDlg)
	enum { IDD = IDR_MAINFRAME };
	CString	m_strURL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUrlDlg)
	afx_msg void OnKillfocusCombourl();
	afx_msg void OnSetfocusCombourl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLDLG_H__56FCF2DF_EB7F_11D6_A4DC_00010297914C__INCLUDED_)
