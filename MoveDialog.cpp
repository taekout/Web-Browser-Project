// MoveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Browser.h"
#include "MoveDialog.h"
#include "Avi.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		WM_USER_DIALOG_DESTROYED	0x8888
#define		MAX_SLIDER_RANGE			1000

/////////////////////////////////////////////////////////////////////////////
// CMoveDialog dialog


//	후일 슬라이더를 쓰레드로 갱신
UINT DrawSlider(LPVOID Param)
{
	return	TRUE;
}

CMoveDialog::CMoveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveDialog::IDD, pParent), m_pVideo(NULL)
{
	//{{AFX_DATA_INIT(CMoveDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMoveDialog::~CMoveDialog()
{
	if(m_bPlaying)
	{
		if(m_pVideo)
		{
			delete	m_pVideo;
			m_pVideo = NULL;
		}
		//	KillTimer 하면 에러 난다. 왜 에러가 나는지 원인 규명할 것..
//		KillTimer(m_nTimer);
	}
}


void CMoveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoveDialog)
	DDX_Control(pDX, IDC_PLAYSLIDER, m_sliderMovie);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveDialog, CDialog)
	//{{AFX_MSG_MAP(CMoveDialog)
	ON_BN_CLICKED(IDFILELOAD, OnFileload)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_END, OnEnd)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEnddialog)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_TIMER()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PLAYSLIDER, OnReleasedcapturePlayslider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveDialog message handlers

//	Play + File Load + Progress

void CMoveDialog::OnFileload() 
{
	// TODO: Add your control notification handler code here
//	CFileDialog		fileDlg(TRUE, _T("AVI"), _T("*.AVI"),
//		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("동영상 파일(*.AVI)|*.AVI|"));
	CFileDialog	fileDlg( TRUE, NULL, _T("*.AVI;*.MPG;*.MPEG"), OFN_HIDEREADONLY
		, _T("동영상 파일 (*.AVI) |*.AVI|"), this );
	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		if(m_pVideo != NULL)
			DeleteAVI();

		m_pVideo = new CMyVideo(m_rect.left, m_rect.top, m_rect.Width(),
			m_rect.Height(), m_strFileName.GetBuffer(0), this ->GetSafeHwnd());
		GetDlgItem(IDC_PLAY) ->EnableWindow(TRUE);
		GetDlgItem(IDC_END) ->EnableWindow(TRUE);
		GetDlgItem(IDC_PAUSE) ->EnableWindow(TRUE);
//		GetDlgItem(IDC_PLAYSLIDER) ->EnableWindow(TRUE);
	}
}

void CMoveDialog::OnPlay()
{
	// TODO: Add your control notification handler code here
	if(m_pVideo)
	{
		m_bPlaying = TRUE;
		m_pVideo ->Play();
		m_nTimer = SetTimer(1, 2000, 0);
		INT  err = GetLastError();
//		SetTimer(0, 
	}
	else
	{
		MessageBox("먼저 재생할 파일을 선택해주세요.", "에러");
	}
}

/*
void CMainFrame::OnStartTimer()
{
  m_nTimer = SetTimer(1, 2000, 0);
}

void CMainFrame::OnStopTimer()
{
  KillTimer(m_nTimer);  
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
  MessageBeep(0xFFFFFFFF);  // Beep

  // Call base class handler.
  CMDIFrameWnd::OnTimer(nIDEvent);
}
*/

BOOL CMoveDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_PLAY) ->EnableWindow(FALSE);
	GetDlgItem(IDC_END) ->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE) ->EnableWindow(FALSE);
	GetDlgItem(IDC_PLAYSLIDER) ->EnableWindow(FALSE);

	CWnd * pWnd = GetDlgItem(IDC_VIDEO);
	pWnd ->GetWindowRect(&m_rect);
	ScreenToClient(&m_rect);

	m_sliderMovie.SetRange(0, MAX_SLIDER_RANGE, TRUE);
	m_sliderMovie.SetPos(0);
	m_sliderMovie.SetTicFreq(50);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoveDialog::OnPause() 
{
	// TODO: Add your control notification handler code here
	if(m_pVideo)
	{
		m_bPlaying = FALSE;
		m_pVideo ->Pause();
//		KillTimer(m_nTimer);
	}
}

void CMoveDialog::OnEnd() 
{
	// TODO: Add your control notification handler code here
	if(m_pVideo)
	{
		m_pVideo ->Pause();
		m_pVideo ->Rewind();
		KillTimer(m_nTimer);
		m_sliderMovie.SetPos(0);
	}
}

void CMoveDialog::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pVideo)
	{
		DeleteAVI();
	}

	CDialog::PostNcDestroy();
//	delete	this;
	AfxGetMainWnd() ->SendMessage(WM_USER_DIALOG_DESTROYED, 0, 0);
}

//  End_Dialog 호출을 막기 위해 고의적으로  Overriding OnOK()
void CMoveDialog::OnOK()
{
	// TODO: Add extra validation here
	DestroyWindow();
}

BOOL CMoveDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//	if(pMsg->message == WM_NCHITTEST)
//	{
//		return	TRUE;
//	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMoveDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	// Enter Key 나 Space Bar 가 눌렸을 경우
	if(nChar == VK_SPACE || nChar == VK_RETURN)
	{
		if(m_bPlaying == TRUE)
		{
			OnPause();
		}
		else
		{
			OnPlay();
		}
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMoveDialog::OnEnddialog() 
{
	// TODO: Add your control notification handler code here
	DestroyWindow();
	// 이 뒤에 함수 실행 순서를 알아야 한다..
	// 1. OnEnddialog()
	// 2. OnAviEnd()	!! 중요 !! ==> 이 때는 delete this 가 실행 안 된 상태..
	// 3. PostNcDestroy()
	// 4. OnAviEnd()	!! 이렇게 되도록 SendMessage 수순을 바꾸자..
}

void CMoveDialog::OnNcLButtonDown( UINT nHitTest, CPoint point )
{
	//  Exit Mark click 시 조정..
	//	519,-18  --  539,-3  ; NC 영역의 X 마크의 좌표
	CRect	rt(517, -20, 541, -1);
	ScreenToClient(&point);
	if(rt.PtInRect(point))
		DestroyWindow();
	else
		CDialog::OnNcLButtonDown(nHitTest, point);
}

BOOL CMoveDialog::DeleteAVI()
{
	if(m_pVideo)
	{
		delete	m_pVideo;
		m_pVideo = NULL;
	}
	return	TRUE;
}
/*
void CMoveDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pVideo)
	{
		UINT		nMax = m_sliderMovie.GetRangeMax();
		nPos = m_sliderMovie.GetPos();
		DOUBLE	dbRate = (DOUBLE)nPos / nMax;
		DWORD	dwFrame;
		dwFrame = m_pVideo ->GetTotalLength();	// 전체 프레임 수 구함
		dwFrame = (DWORD)(dwFrame * dbRate);
		m_pVideo ->MoveCursor(dwFrame, this ->GetSafeHwnd());
		if(m_bPlaying)
			m_pVideo ->Play();
		else
			m_pVideo ->Pause();
//		switch(nSBCode)
//		{
//		case SB_THUMBPOSITION :
//			pScrollBar ->SetScrollPos(nPos);
//			m_sliderMovie.SetPos(nPos);
//			break;
//		case SB_THUMBTRACK :
//			pScrollBar ->SetScrollPos(nPos);
//			m_sliderMovie.SetPos(nPos);
//			break;
//		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}*/  

void CMoveDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	DWORD	dwFrame, dwTotalFrame ;
	DOUBLE	dbRates;
	if(m_pVideo)
	{
		dwFrame = m_pVideo ->GetCurPosition();
		dwTotalFrame = m_pVideo ->GetTotalLength();
	}
	dbRates = (DOUBLE)dwFrame / dwTotalFrame;
	m_sliderMovie.SetPos((INT)(dbRates * MAX_SLIDER_RANGE));

	CDialog::OnTimer(nIDEvent);
}

void CMoveDialog::OnReleasedcapturePlayslider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

BOOL CMoveDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TBS_AUTOTICKS;
	return CDialog::PreCreateWindow(cs);
}
