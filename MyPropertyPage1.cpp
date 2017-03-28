// MyPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyPropertyPage1.h"
#include "MainFrm.h"
#include "BrowserView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyPropertyPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage2, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 property page

CMyPropertyPage1::CMyPropertyPage1() : CPropertyPage(CMyPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage1)
	m_checkAlarm = TRUE;
	m_strHour = _T("");
	m_strMinute = _T("");
	m_back_bmp = NULL;
	//}}AFX_DATA_INIT
}

CMyPropertyPage1::~CMyPropertyPage1()
{
}

void CMyPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage1)
	DDX_Control(pDX, IDC_SPINMINUTE, m_spinMinute);
	DDX_Control(pDX, IDC_SPINHOUR, m_spinHour);
	DDX_Check(pDX, IDC_ALARMCHECK, m_checkAlarm);
	DDX_Text(pDX, IDC_HOUREDIT, m_strHour);
	DDX_Text(pDX, IDC_MINUTEEDIT, m_strMinute);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SETALARMMUSIC, OnSetalarmmusic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

char * CMyPropertyPage1::LoadBMP(char *fn)
{
    CFile f;
    int s = f.Open(fn, CFile::modeRead);
    if(!s) return 0;

    int fl = f.GetLength();
    BITMAPFILEHEADER bfh;

    f.Read(&bfh, sizeof(bfh));
    char *buf = new char [fl];
    f.Read(buf, fl - sizeof(bfh));
    return buf;
}

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage2 property page

CMyPropertyPage2::CMyPropertyPage2() : CPropertyPage(CMyPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage2)
	m_back_bmp = NULL;
	//}}AFX_DATA_INIT
}

CMyPropertyPage2::~CMyPropertyPage2()
{
}

void CMyPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage2)
	DDX_Text(pDX, IDC_SETHOMEPAGE_EDIT, m_strHomePage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage2)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CMyPropertyPage1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAPINFOHEADER *bmp = (BITMAPINFOHEADER *)m_back_bmp;
	StretchDIBits(
		dc.m_hDC,   // hDC
		0,    // DestX
		0,     // DestY
		bmp->biWidth,     // nDestWidth
		bmp->biHeight,     // nDestHeight
		0,     // SrcX
		0,     // SrcY
		bmp->biWidth, // SrcW
		bmp->biHeight,   // SrcH
		m_back_bmp+40+4*bmp->biClrUsed,      // lpBits
		(BITMAPINFO *)m_back_bmp, // lpBitsInfo
		DIB_RGB_COLORS,
		SRCCOPY
        );    
	
	dc.SetBkMode(TRANSPARENT); 
	// Do not call CPropertyPage::OnPaint() for painting messages
}

BOOL CMyPropertyPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_back_bmp = LoadBMP("Alarm.bmp"); 

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

void CMyPropertyPage1::OnSetalarmmusic() 
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

char * CMyPropertyPage2::LoadBMP(char *fn)
{
    CFile f;
    int s = f.Open(fn, CFile::modeRead);
    if(!s) return 0;

    int fl = f.GetLength();
    BITMAPFILEHEADER bfh;

    f.Read(&bfh, sizeof(bfh));
    char *buf = new char [fl];
    f.Read(buf, fl - sizeof(bfh));
    return buf;
}

void CMyPropertyPage2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAPINFOHEADER *bmp = (BITMAPINFOHEADER *)m_back_bmp;
	StretchDIBits(
		dc.m_hDC,   // hDC
		0,    // DestX
		0,     // DestY
		bmp->biWidth,     // nDestWidth
		bmp->biHeight,     // nDestHeight
		0,     // SrcX
		0,     // SrcY
		bmp->biWidth, // SrcW
		bmp->biHeight,   // SrcH
		m_back_bmp+40+4*bmp->biClrUsed,      // lpBits
		(BITMAPINFO *)m_back_bmp, // lpBitsInfo
		DIB_RGB_COLORS,
		SRCCOPY
        );    
	
	dc.SetBkMode(TRANSPARENT); 
	// Do not call CPropertyPage::OnPaint() for painting messages
}

BOOL CMyPropertyPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_back_bmp = LoadBMP("Homepage.bmp");

	// 1. Registry 에서 홈페이지 읽어와서 멤버 변수 설정
	CWinApp *pApp = AfxGetApp();
	CString HomeSection = _T("Explore Option");
	CString HomeEntry = _T("Home Page"), strResult ;
	strResult = pApp ->GetProfileString(HomeSection, HomeEntry, _T("Ab ~ Sulma Fail? KUKU"));
	if(strResult.Compare(_T("Ab ~ Sulma Fail? KUKU")) == 0)
		// 실패시... 기본 다음(daum.net) 을 홈페이지로 설정..
		m_strHomePage = _T("http://www.daum.net");
	else
		// 성공시...
		m_strHomePage = strResult ;
	// 2. 멤버 변수의 값을 Edit Control 에 설정
	SetDlgItemText(IDC_SETHOMEPAGE_EDIT, m_strHomePage);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyPropertyPage2::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	// 1. 컨트롤에 설정된 페이지 주소를 m_strHomePage 에 설정
	GetDlgItemText(IDC_SETHOMEPAGE_EDIT, m_strHomePage);
	// 2. m_strHomePage 의 주소를 Registry 에 저장
	CWinApp *pApp = AfxGetApp();
	CString HomeSection = _T("Explore Option");
	CString HomeEntry = _T("Home Page");
	BOOL bResult = pApp ->WriteProfileString(HomeSection, HomeEntry, m_strHomePage);
	if(!bResult)
		//실패시
		pApp ->WriteProfileString(HomeSection, HomeEntry, _T("http://www.daum.net"));

	//	얻은 m_strHomePage 를 View 의 m_strHome 에다가 저장한다.
	((CMainFrame *)AfxGetMainWnd ()) ->GetView() ->m_strHome = m_strHomePage;

	CPropertyPage::OnOK();
}
