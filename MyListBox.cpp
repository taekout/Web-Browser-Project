// ServerListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MyListBox.h"
#include "InputDialog.h"
#include "BrowserDoc.h"
#include "BrowserView.h"
#include "FTPDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerListBox

CServerListBox::CServerListBox()
{
	m_pConnection = NULL;
	m_pSession = NULL;
	m_pFileFind = NULL;
	m_bDragStartPointInServer = FALSE;
//	m_bDragEndPointInServer = FALSE;
}

CServerListBox::~CServerListBox()
{
}

CString  &CServerListBox::GetSelString()
{
	INT	nIndex ;
	CString	*strSel = new CString();
	if( (nIndex = this ->GetCurSel()) == LB_ERR )
	{
		return	*strSel;
	}
	this ->GetText( nIndex , *strSel );
	return	*strSel;
}

void  CServerListBox::EnumerateList()
{
	BOOL	bContinue;
	CString	data;
	m_pConnection ->GetCurrentDirectory( m_pDoc ->m_strServerPath );
	bContinue = m_pFileFind ->FindFile( m_pDoc ->m_strServerPath );
	ResetContent();
	AddString("./");
	AddString("../");
	if( bContinue == NULL )	// 에러 발생시
		if( GetLastError() == ERROR_NO_MORE_FILES )		// 파일이 없을 경우는 예외
		{
			SetCursor( LoadCursor( NULL, IDC_CROSS ) );
			return;
		}

	while( bContinue )
	{
		bContinue = m_pFileFind ->FindNextFile ();
		data = m_pFileFind ->GetFileName ();
		if( m_pFileFind ->IsDirectory() )
			data += "/";
		AddString( data );
	}
}


BEGIN_MESSAGE_MAP(CServerListBox, CListBox)
	//{{AFX_MSG_MAP(CServerListBox)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerListBox message handlers

void CServerListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString	strFileName = GetSelString();
	if( strFileName.GetLength() == 0 )
		return;
	if( nChar == VK_DELETE )
	{
		if( strFileName == "./"  ||  strFileName == "../" )
			return;
		if( MessageBox("정말로 지우시겠습니까?", NULL, MB_OKCANCEL ) == IDCANCEL )
			return;
		if( m_pConnection ->Remove( strFileName ) == NULL )
		{
#if	defined(_DEBUG)
			INT		nErrorCode;
			TRACE1( _T("%d"), nErrorCode = GetLastError() );
#endif	//	#if	defined(_DEBUG)
			return;
		}
		EnumerateList();
	}
	if( (nChar == 'r' || nChar == 'R') && GetKeyState(VK_CONTROL) < 0)
	{
		CInputDialog	dlg;
		dlg.m_strNewName = GetSelString();
		dlg.DoModal();
		if( m_pConnection ->Rename( strFileName, dlg.m_strNewName ) == NULL )
			TRACE1( _T("%d"), GetLastError() );
		EnumerateList();
	}
	CListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CServerListBox::BeginDrag( CPoint pt )
{
	m_bDragStartPointInServer = TRUE;
	return	CDragListBox::BeginDrag( pt );
}

void CServerListBox::Dropped( int nSrcIndex, CPoint pt )
{
	ScreenToClient( &pt );
	CRect	rt( 0, 168, 428, 278 );	// Local 영역 사각형
	CFTPDlg *pDlg;
	pDlg = (CFTPDlg *)this ->GetOwner();


	if( m_bDragStartPointInServer == TRUE &&
		pDlg ->m_listLocal.m_bDragStartPointInLocal == FALSE &&
		rt.PtInRect( pt ) != NULL )		// Drop 이 로컬로 떨어졌을 시에
	{
		MessageBox("Download");
		CString strDropFile;
		GetText( nSrcIndex, strDropFile );
		pDlg ->DownloadFile( strDropFile );
	}
	CDragListBox::Dropped( nSrcIndex, pt );
	m_bDragStartPointInServer = FALSE;
}

BOOL CLocalListBox::BeginDrag( CPoint pt )
{
	m_bDragStartPointInLocal = TRUE;
	return	CDragListBox::BeginDrag( pt );
}

void CLocalListBox::Dropped( int nSrcIndex, CPoint pt )
{
	ScreenToClient( &pt );
	CRect	rt( 0, -168, 428, -46 );	// Server 영역 사각형
	POSITION	pos = m_pDoc ->GetFirstViewPosition();
	CFTPDlg	*pDlg;
	pDlg = (CFTPDlg *)this ->GetOwner();

	if( m_bDragStartPointInLocal == TRUE &&
		pDlg ->m_listServer.m_bDragStartPointInServer == FALSE &&
		rt.PtInRect( pt ) != NULL )		// Drop 이 서버로 떨어졌을 시에
	{
		MessageBox("Upload");
		CString	strDropFile;
		GetText( nSrcIndex, strDropFile );
		pDlg ->UploadFile( strDropFile );
	}
	CDragListBox::Dropped( nSrcIndex, pt );
	m_bDragStartPointInLocal = FALSE;
}
/*
void CServerListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDragStartPointInServer = TRUE;
	m_bDragEndPointInServer = FALSE;
	m_strSel = GetSelString();

	CListBox::OnLButtonDown(nFlags, point);
}

void CServerListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDragStartPointInServer = FALSE;
	m_bDragEndPointInServer = TRUE;
	POSITION	pos = m_pDoc ->GetFirstViewPosition();
	CFTPView	*pView = NULL;
	if( pos != NULL )
	{
		pView = (CFTPView *)m_pDoc ->GetNextView( pos );
	}
	if( pView ->m_listLocal.m_bDragStartPointInLocal == TRUE )
	{
		pView ->UploadFile( pView ->m_listLocal.m_strSel );
	}
//	if( 1//스타트가 로컬이 되어있을 경우 )
//		MessageBox("이 때 Upload..");
//	SendMessage(

	CListBox::OnLButtonUp(nFlags, point);
}
*/



// LocalListBox.cpp : implementation file
//


/////////////////////////////////////////////////////////////////////////////
// CLocalListBox

CLocalListBox::CLocalListBox()
{
//	m_pRect = new CRect( 15, 195, 263, 272 );
	m_bDragStartPointInLocal = FALSE;
//	m_bDragEndPointInLocal = FALSE;
	m_pConnection = NULL;
	m_pSession = NULL;
	m_pFileFind = NULL;
}

CLocalListBox::~CLocalListBox()
{
}

CString  &CLocalListBox::GetSelString()
{
	INT	nIndex ;
	CString	*strSel = new CString();
	if( (nIndex = this ->GetCurSel()) == LB_ERR )
	{
		return	*strSel;
	}
	this ->GetText( nIndex , *strSel );
	return	*strSel;
}

void  CLocalListBox::EnumerateList()
{
	ResetContent();
	WIN32_FIND_DATA		fd;
	HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

	if( hFind != INVALID_HANDLE_VALUE ) {
		do {
			if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
				AddString( fd.cFileName );
			else
			{
				CString		strDirectory;
				strDirectory = fd.cFileName;
				strDirectory += "/";
				AddString( strDirectory );
			}
		} while( ::FindNextFile( hFind, &fd ) );
	}
}

BEGIN_MESSAGE_MAP(CLocalListBox, CListBox)
	//{{AFX_MSG_MAP(CLocalListBox)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalListBox message handlers

void CLocalListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString	strFileName = GetSelString();
	if( strFileName.GetLength() == 0 )
		return;
	if( nChar == VK_DELETE )
	{
		if( strFileName == "./"  ||  strFileName == "../" )
			return;
		else
		{
			if( MessageBox("정말로 지우시겠습니까?", NULL, MB_OKCANCEL ) == IDCANCEL )
				return;
			CFile::Remove( strFileName );
			EnumerateList();
		}
	}
	if( (nChar == 'r' || nChar == 'R') && GetKeyState(VK_CONTROL) < 0 )
	{
		CInputDialog	dlg;
		dlg.m_strNewName = GetSelString();
		dlg.DoModal();
		CFile::Rename( strFileName, dlg.m_strNewName );
		EnumerateList();
	}
	CListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

/*
void CLocalListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDragStartPointInLocal = TRUE;
	m_bDragEndPointInLocal = FALSE;
	m_strSel = GetSelString();

	CListBox::OnLButtonDown(nFlags, point);
}

void CLocalListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDragStartPointInLocal = FALSE;
	m_bDragEndPointInLocal = TRUE;
//	SendMessage(
	POSITION	pos = m_pDoc ->GetFirstViewPosition();
	CFTPView	*pView = NULL;
	if( pos != NULL )
		pView = (CFTPView *)m_pDoc ->GetNextView( pos );
	if( pView ->m_listServer.m_bDragStartPointInServer == TRUE )
	{
		pView ->DownloadFile( pView ->m_listServer.m_strSel );
	}

	CListBox::OnLButtonUp(nFlags, point);
}

void CFTPView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( m_listServer.m_pRect ->PtInRect( point ) == TRUE )
	{
		m_bInServer = TRUE;
		m_bInLocal = FALSE;
	}
	else
	{
		if( m_listLocal.m_pRect ->PtInRect( point ) == TRUE )
		{
			m_bInLocal = TRUE;
			m_bInServer = FALSE;
		}
		else
		{
			m_bInLocal = m_bInServer = FALSE;
		}
	}

	CFormView::OnLButtonDown(nFlags, point);
}

void CFTPView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( m_bInServer == TRUE && m_bInLocal == FALSE )
	{
		if( m_listLocal.m_pRect ->PtInRect( point ) == TRUE )
		{
			MessageBox("이 때 다운로드하면 됩니다.");
		}
	}
	if( m_bInLocal == TRUE && m_bInServer == FALSE )
	{
		if( m_listServer.m_pRect ->PtInRect( point ) == TRUE )
		{
			MessageBox("이 때 Upload하면 됩니다.");
		}
	}

	CFormView::OnLButtonUp(nFlags, point);
}
*/
/*
BOOL CServerListBox::BeginDrag( CPoint pt )
{
	m_bDragStartPointInServer = TRUE;
	return	CDragListBox::BeginDrag( pt );
}*/
/*
void CServerListBox::Dropped( int nSrcIndex, CPoint pt )
{
	ScreenToClient( &pt );
	CRect	rt( 0, 168, 428, 278 );	// Local 영역 사각형
	POSITION	pos = m_pDoc ->GetFirstViewPosition();
	CFTPView  *pView = NULL;
	if( pos != NULL )
		pView = (CFTPView *)m_pDoc ->GetNextView( pos );
	if( m_bDragStartPointInServer == TRUE &&
		pView ->m_listLocal.m_bDragStartPointInLocal == FALSE &&
		rt.PtInRect( pt ) != NULL )		// Drop 이 로컬로 떨어졌을 시에
	{
		MessageBox("Download");
		CString strDropFile;
		GetText( nSrcIndex, strDropFile );
		POSITION	pos = m_pDoc ->GetFirstViewPosition();
		CFTPView	*pView;
		if ( pos != NULL )
		{
			pView = (CFTPView *)m_pDoc ->GetNextView( pos );
		}
		pView ->DownloadFile( strDropFile );
	}
	CDragListBox::Dropped( nSrcIndex, pt );
	m_bDragStartPointInServer = FALSE;
}
*//*
BOOL CLocalListBox::BeginDrag( CPoint pt )
{
	m_bDragStartPointInLocal = TRUE;
	return	CDragListBox::BeginDrag( pt );
}

void CLocalListBox::Dropped( int nSrcIndex, CPoint pt )
{
	ScreenToClient( &pt );
	CRect	rt( 0, -168, 428, -46 );	// Server 영역 사각형
	POSITION	pos = m_pDoc ->GetFirstViewPosition();
	CFTPView  *pView;
	if( pos != NULL )
		pView = (CFTPView *)m_pDoc ->GetNextView( pos );
	if( m_bDragStartPointInLocal == TRUE &&
		pView ->m_listServer.m_bDragStartPointInServer == FALSE &&
		rt.PtInRect( pt ) != NULL )		// Drop 이 서버로 떨어졌을 시에
	{
		MessageBox("Upload");
		CString	strDropFile;
		GetText( nSrcIndex, strDropFile );
		POSITION	pos = m_pDoc ->GetFirstViewPosition();
		CFTPView	*pView = NULL;
		if( pos != NULL )
			pView = (CFTPView *)m_pDoc ->GetNextView( pos );
		pView ->UploadFile( strDropFile );
	}
	CDragListBox::Dropped( nSrcIndex, pt );
	m_bDragStartPointInLocal = FALSE;
}
*/
/*
Server
  (106,286)--------(535, 286)
  (106,380) ---------(511,379)
*/

/*
Local 
 (143,473) _------(571,472)
 (143,583)--------(574,584)
*/


