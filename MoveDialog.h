#if !defined(AFX_MOVEDIALOG_H__87D6CF24_F8D6_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_MOVEDIALOG_H__87D6CF24_F8D6_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoveDialog dialog

class CMyVideo;

class CMoveDialog : public CDialog
{
// Construction
public:
	BOOL DeleteAVI();
	BOOL m_bPlaying;
	CMoveDialog(CWnd* pParent = NULL);   // standard constructor
	~CMoveDialog();

// Dialog Data
	//{{AFX_DATA(CMoveDialog)
	enum { IDD = IDD_MOVIEPLAY };
	CSliderCtrl	m_sliderMovie;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nTimer;
	CString m_strFileName;
	CRect m_rect;
	CMyVideo * m_pVideo;

	// Generated message map functions
	//{{AFX_MSG(CMoveDialog)
	afx_msg void OnFileload();
	afx_msg void OnPlay();
	virtual BOOL OnInitDialog();
	afx_msg void OnPause();
	afx_msg void OnEnd();
	virtual void OnOK();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnddialog();
	afx_msg void OnNcLButtonDown( UINT nHitTest, CPoint point );
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReleasedcapturePlayslider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEDIALOG_H__87D6CF24_F8D6_11D6_A4DC_00010297914C__INCLUDED_)
