// UrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Browser.h"
#include "UrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg dialog


CUrlDlg::CUrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUrlDlg)
	m_bFocus = FALSE;
	m_strURL = _T("");
	//}}AFX_DATA_INIT
}


void CUrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUrlDlg)
	DDX_CBString(pDX, IDC_COMBOURL, m_strURL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUrlDlg, CDialog)
	//{{AFX_MSG_MAP(CUrlDlg)
	ON_CBN_KILLFOCUS(IDC_COMBOURL, OnKillfocusCombourl)
	ON_CBN_SETFOCUS(IDC_COMBOURL, OnSetfocusCombourl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg message handlers

void CUrlDlg::OnKillfocusCombourl() 
{
	// TODO: Add your control notification handler code here
	m_bFocus = FALSE;
}

void CUrlDlg::OnSetfocusCombourl() 
{
	// TODO: Add your control notification handler code here
	m_bFocus = TRUE;
}

BOOL CUrlDlg::GetURLComboFocus()
{
	return	m_bFocus;
}
