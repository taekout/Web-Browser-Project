#if !defined(AFX_ALARMDLG_H__37F92998_6D31_473D_B2DE_1F1393E779BB__INCLUDED_)
#define AFX_ALARMDLG_H__37F92998_6D31_473D_B2DE_1F1393E779BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog

class CAlarmDlg : public CDialog
{
// Construction
public:
	CAlarmDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmDlg)
	enum { IDD = IDD_ALARMOPTION };
	CSpinButtonCtrl	m_spinMinute;
	CSpinButtonCtrl	m_spinHour;
	CString	m_strHour;
	CString	m_strMinute;
	CString m_strAlarmFile;
	BOOL	m_checkAlarm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetAlarmMusic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDLG_H__37F92998_6D31_473D_B2DE_1F1393E779BB__INCLUDED_)
