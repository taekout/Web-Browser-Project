#if !defined(AFX_FTPDLG_H__45285D1A_5386_4DFA_838C_088C693BB754__INCLUDED_)
#define AFX_FTPDLG_H__45285D1A_5386_4DFA_838C_088C693BB754__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg dialog

#include <afxinet.h>
#include "MyListBox.h"

class CBrowserDoc;

class CFTPDlg : public CDialog
{
// Construction / Destruction
public:
	CFTPDlg(CWnd* pParent = NULL);   // standard constructor
	~CFTPDlg();

// Dialog Data
	//{{AFX_DATA(CFTPDlg)
	enum { IDD = IDD_FTP };
	CComboBox	m_comboName;
	CListBox	m_listManageAddress;
	CLocalListBox	m_listLocal;
	CServerListBox	m_listServer;
	CComboBox	m_comboAddress;
	CString	m_strPassword;
	//}}AFX_DATA
	CBitmapButton	m_uploadButton, m_downloadButton;

	CFtpFileFind	*m_pFileFind;	// FTP 파일 검색 용도 클래스
	CInternetSession	m_Session;	// 세션 클래스
	CFtpConnection	*m_pConnect;		// FTP 명령 연결 컨트롤 클래스

	CBrowserDoc *m_pDoc;

public:
	CBrowserDoc* GetDocument();
	void	EnumerateFolder();
	HRESULT	DownloadFile( CString  dwnFile );
	HRESULT	UploadFile( CString upFile );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFTPDlg)
	afx_msg void OnDownloadButton();
	afx_msg void OnUploadButton();
	afx_msg void OnConnectButton();
	afx_msg void OnDblclkFilelistListbox();
	afx_msg void OnDblclkLocallistListbox();
	afx_msg void OnDblclkManageaddressList();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPDLG_H__45285D1A_5386_4DFA_838C_088C693BB754__INCLUDED_)
