// AlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Browser.h"
#include "BrowserDoc.h"
#include "MainFrm.h"
#include "AlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog


CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDlg)
	m_strHour = _T("");
	m_strMinute = _T("");
	m_strAlarmFile = _T("");
	m_checkAlarm = TRUE;
	//}}AFX_DATA_INIT
}


void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDlg)
	DDX_Control(pDX, IDC_SPINMINUTE, m_spinMinute);
	DDX_Control(pDX, IDC_SPINHOUR, m_spinHour);
	DDX_Text(pDX, IDC_HOUREDIT, m_strHour);
	DDV_MaxChars(pDX, m_strHour, 2);
	DDX_Text(pDX, IDC_MINUTEEDIT, m_strMinute);
	DDV_MaxChars(pDX, m_strMinute, 2);
	DDX_Check(pDX, IDC_ALARMCHECK, m_checkAlarm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmDlg)
	ON_BN_CLICKED(IDC_SETALARMMUSIC, OnSetAlarmMusic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers

BOOL CAlarmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinHour.SetRange(0, 23);
	m_spinMinute.SetRange(0, 59);

	CWinApp *pApp = AfxGetApp();
	CString		resultEnable ;
	CString		resultHours ;
	CString		resultMinutes ;
	CString		resultFileAlarm;
	//	Check Alarm 설정
	resultEnable = pApp ->GetProfileString(_T("Alarm"), _T("Alarm Enable"), _T("3#tgkmgka faT #*#"));
	if(resultEnable.Compare(_T("3#tgkmgka faT #*#")) == 0)
	{	//Is Equal.. ==> 레지스트리 읽어들이는 것 실패!
		resultEnable = _T("TRUE");
	}
	else
	{// 레지스트리 읽어들이는데 성공!
	}
	//	시간 설정
	resultHours = pApp ->GetProfileString(_T("Alarm"), _T("Hours"), _T("3#tgkmgka faT #*#"));
	if(resultHours.Compare(_T("3#tgkmgka faT #*#")) == 0)
	{
		resultHours = _T("8");
	}
	//	분 설정
	resultMinutes = pApp ->GetProfileString(_T("Alarm"), _T("Minutes"), _T("3#tgkmgka faT #*#"));
	if(resultMinutes.Compare(_T("3#tgkmgka faT #*#")) == 0)
	{
		resultMinutes = _T("30");
	}
	//	File Alarm 설정
	resultFileAlarm = pApp ->GetProfileString(_T("Alarm"), _T("Alarm Play File"), _T("3#tgkmgka faT #*#"));
	if(resultFileAlarm.Compare(_T("3#tgkmgka faT #*#")) == 0 ||
		resultFileAlarm.Compare(_T("")) == 0)
	{
		resultFileAlarm = _T("C:\\Documents and Settings\\user\\바탕 화면\\Browser\\res\\애국가.wav");
	}
	else
	{
	}

	m_checkAlarm = (resultEnable.Compare(_T("TRUE")) == 0) ? TRUE : FALSE;
	m_strHour = resultHours;
	m_strMinute = resultMinutes;
	m_strAlarmFile = resultFileAlarm;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmDlg::OnSetAlarmMusic() 
{
	// TODO: Add your control notification handler code here
	CFileDialog	fileDlg(TRUE, _T("*.WAV;*.MP3"), _T("애국가.WAV"));
	// 수정
	if(fileDlg.DoModal() == IDOK)
	{
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		CWinApp *pApp = AfxGetApp();
		ASSERT_VALID(pFrame);
		ASSERT_VALID(pApp);
		//	이 곳 m_strAlarmFile 에 알람 재생 파일 해놓고
		//	나중에 부모 다이얼로그 박스 OK 버튼 눌릴 때 갱신!
		m_strAlarmFile = fileDlg.GetPathName();
//		나중에 부모 다이얼로그 OK 눌릴 때 WriteProfileString...
//		pApp ->WriteProfileString(strAlarmSection, strAlarmEntry, strAlarmFile);
	}
}
