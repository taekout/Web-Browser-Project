  // FTPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Browser.h"
#include "FTPDlg.h"
#include "MainFrm.h"
#include "BrowserView.h"
#include "BrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg dialog


CFTPDlg::CFTPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFTPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTPDlg)
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
	m_pDoc = ((CMainFrame *)AfxGetMainWnd()) ->GetView() ->GetDocument();
	m_pFileFind = NULL;	// FTP ���� �˻� �뵵 Ŭ����
	m_pConnect  = NULL;		// FTP ��� ���� ��Ʈ�� Ŭ����
	GetDocument() ->m_bConnected = FALSE;
}

CFTPDlg::~CFTPDlg()
{
	if(m_pConnect)
	{
		m_pConnect ->Close();	// FTP Connection Ŭ���� ����
		delete m_pConnect;		// ��ü �Ҹ�
	}
	m_pConnect = NULL;		// �ʱ�ȭ
	if(m_pFileFind)
		delete	m_pFileFind;	// FTP ���� �˻� �뵵 Ŭ���� ��ü �Ҹ�
	m_pFileFind = NULL;		// �ʱ�ȭ
	m_Session.Close();	// ���� Ŭ���� ����
	GetDocument() ->m_bConnected = FALSE;
}

void CFTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTPDlg)
	DDX_Control(pDX, IDC_NAME_COMBOBOX, m_comboName);
	DDX_Control(pDX, IDC_MANAGEADDRESS_LIST, m_listManageAddress);
	DDX_Control(pDX, IDC_LOCALLIST_LISTBOX, m_listLocal);
	DDX_Control(pDX, IDC_FILELIST_LISTBOX, m_listServer);
	DDX_Control(pDX, IDC_ADDRESS_COMBOBOX, m_comboAddress);
	DDX_Text(pDX, IDC_PASSWORD_EDIT, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFTPDlg, CDialog)
	//{{AFX_MSG_MAP(CFTPDlg)
	ON_BN_CLICKED(IDC_DOWNLOAD_BUTTON, OnDownloadButton)
	ON_BN_CLICKED(IDC_UPLOAD_BUTTON, OnUploadButton)
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, OnConnectButton)
	ON_LBN_DBLCLK(IDC_FILELIST_LISTBOX, OnDblclkFilelistListbox)
	ON_LBN_DBLCLK(IDC_LOCALLIST_LISTBOX, OnDblclkLocallistListbox)
	ON_LBN_DBLCLK(IDC_MANAGEADDRESS_LIST, OnDblclkManageaddressList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONHELP, OnButtonhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg message handlers

void CFTPDlg::OnDownloadButton() 
{
	// TODO: Add your control notification handler code here
	CBrowserDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc ->m_bConnected)
	{
		MessageBox(_T("������ ���� ���ּ���"), _T("Error"));
		return;
	}
	UpdateData( FALSE );
	int	num = m_listServer.GetCurSel ();
	if(num == CB_ERR)
	{
		MessageBox(_T("������ ����� ���� �������ּ���"), _T("ERROR"));
		return;
	}
	LPTSTR	temp = (LPTSTR) malloc( 512 );
	m_listServer.GetText( num, temp );

	if( temp[ _tcslen(temp) - 1] == '/' )
	{
		AfxMessageBox( "���丮�� ���縦 �� �� �����Ǵϴ�... ^^��");
		return;
	}
	CString	downData;
	downData += temp;	// error ���� �ʳ�? Ȯ��..

//	CFileDialog	dlg( TRUE, NULL, temp, OFN_HIDEREADONLY
//		, _T("��� ���� (*.*) |*.*|"), this );
	CFile	*pFile = new CFile( downData, CFile::modeCreate );
	pDoc ->m_strLocalPath = pFile ->GetFilePath ();
	delete	pFile;
	CFile::Remove( pDoc ->m_strLocalPath );
	SetCursor( LoadCursor( NULL, IDC_WAIT ) );
	if( m_pConnect ->GetFile( downData, pDoc ->m_strLocalPath ) == NULL )
	{
		TRACE1( _T("%d"), GetLastError() );
		return;
	}
	SetCursor( LoadCursor( NULL, IDC_CROSS ) );

	//	Free Memory
	free( temp );

	//  Local List Initialization
	//	Enumerate Now Loading Folder
	m_listLocal.EnumerateList();
	//  End ENUMERATING FOLDER.
}

void CFTPDlg::OnUploadButton() 
{
	// TODO: Add your control notification handler code here
	CBrowserDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc ->m_bConnected)
	{
		MessageBox(_T("������ ���� ���ּ���"), _T("Error"));
		return;
	}

	CString		strFileName;
	SetCursor( LoadCursor( NULL, IDC_WAIT ));
	INT		nIndex = m_listLocal.GetCurSel();
	if( nIndex == LB_ERR )
	{
		MessageBox("Local ��� ������ �׸��� �����Ͽ��ֽʽÿ�.");
		return;
	}
	m_listLocal.GetText( nIndex, strFileName );
//	strFileName = dlg.GetFileName();
	if( strFileName[ strFileName.GetLength()-1 ] == '/' )
	{
		MessageBox("���丮�� ���ε��ų �� �����ϴ�.");
		return;
	}
	CFile	*pFile = new CFile( strFileName, CFile::modeRead );
	pDoc ->m_strLocalPath = pFile ->GetFilePath ();
	delete	pFile;
	if( m_pConnect ->PutFile( pDoc ->m_strLocalPath, strFileName ) == NULL ) // Error!
	{
		TRACE1( _T("%d"), GetLastError() );
		MessageBox("��Ʈ��ŷ ����. ������ Ŭ���̾�Ʈ�� ��� �̻� �Ǵ� ���� ���� �ҷ��Դϴ�.");
	}

/*
	m_listServer.ResetContent();
	CString		data;
	m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
	m_pFileFind ->FindFile( pDoc ->m_strServerPath );
	BOOL	bContinue = TRUE;
	while( bContinue )
	{
		bContinue = m_pFileFind ->FindNextFile();
		data = m_pFileFind ->GetFileName();
		if( m_pFileFind ->IsDirectory() )
			data += "/";
		m_listServer.AddString( data );
	}
	m_listServer.AddString( "./" );
	m_listServer.AddString( "../" );
	*/
	m_listServer.EnumerateList();
	SetCursor( LoadCursor( NULL, IDC_CROSS ));
}

void CFTPDlg::OnConnectButton() 
{
	// TODO: Add your control notification handler code here
	CBrowserDoc *pDoc = (CBrowserDoc *) GetDocument();
	if( pDoc ->m_bConnected )
	{
		MessageBox("�̹� ���ӵǾ� �ִ� �����Դϴ�.");
		return;
	}

	UpdateData( TRUE );
	try
	{
		SetCursor( LoadCursor( NULL, IDC_WAIT ) );
	}
	catch( CInternetException	*pEx )
	{
		pEx ->Delete();
		pEx ->ReportError();
		AfxMessageBox("����!");
	}

	CString	strAddress, strName ;
	INT		nIndex;
	if( (nIndex = m_comboAddress.GetCurSel()) == CB_ERR )	// �ּҸ� ���� ��Ʈ�ѿ� ���� �Է½�
	{
		m_comboAddress.GetWindowText( strAddress );
		LPTSTR	lpszToken = (LPTSTR) malloc( 500 );
		_tcscpy( lpszToken , strAddress.GetBuffer(7));
		for( INT i = 0 ; i < 10 && *(lpszToken + i) ; i++ )
		{
			if( *(lpszToken + i) >= 'a' && *(lpszToken + i) <= 'z' )
			{
				*(lpszToken + i) -= 0x20;
			}
		}
		*(lpszToken + 7) = '\0';

		if( _tcscmp( lpszToken , "HTTP://" ) == NULL )
			strAddress.Delete( 0 , 7 );
		if( m_comboAddress.FindString( -1 , strAddress ) == CB_ERR )
			m_comboAddress.AddString( strAddress );
		if( m_listManageAddress.FindString( -1 , strAddress ) == LB_ERR )
			m_listManageAddress.AddString( strAddress );
		free(lpszToken);
	}
	else
	{
		TCHAR	lpszAdd[300];
		m_comboAddress.GetLBText( nIndex, lpszAdd );
		strAddress = lpszAdd;
	}
	if( (nIndex = m_comboName.GetCurSel()) == CB_ERR )		// user ���� ���� ��Ʈ�ѿ� ���� �Է½�
	{
		m_comboName.GetWindowText( strName );
		if( m_comboName.FindString( -1 , strName ) == CB_ERR )
			m_comboName.AddString( strName );
	}
	else
	{
		TCHAR	lpszName[300];
		m_comboName.GetLBText( nIndex, lpszName );
		strName = lpszName;
	}
	SetWindowText( strAddress );
	if( strName.GetLength() == 0 )
		m_pConnect = m_Session.GetFtpConnection( strAddress );
	else
		m_pConnect = m_Session.GetFtpConnection( strAddress, strName, m_strPassword );
	m_listServer.m_pConnection = m_pConnect;	// CFtpConnection �� �ּҸ� ListBox ����� ����
	m_listServer.m_pSession = &m_Session;
	m_listServer.m_pFileFind = m_pFileFind;
	m_listServer.m_pDoc = GetDocument();
	m_listLocal.m_pConnection = m_pConnect;
	m_listLocal.m_pSession = &m_Session;
	m_listLocal.m_pFileFind = m_pFileFind;
	m_listLocal.m_pDoc = GetDocument();
	if( m_pConnect )
	{
		// ����! szDir �� ��ü�� ����� �˾ƺ� ��!
		m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
		pDoc ->m_strServerPath += "/";
		if( m_pFileFind )
			delete	m_pFileFind;
		m_pFileFind = new CFtpFileFind( m_pConnect );
		m_listServer.m_pFileFind = m_pFileFind;
		//  ���Ⱑ ������ �ٸ�
		/*
		m_listServer.ResetContent();
		CString	data;
		m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
		m_pFileFind ->FindFile( pDoc ->m_strServerPath );
		BOOL	bContinue = TRUE;
		while( bContinue )
		{
			// ���ϸ��� ����
			bContinue = m_pFileFind ->FindNextFile ();
			data = m_pFileFind ->GetFileName ();
			if( m_pFileFind ->IsDirectory() )
				data += "/";
			//	����Ʈ ���ڿ� ÷��... ������ �ٸ�
			m_listServer.AddString( data );
		}
		m_listServer.AddString( "./" );
		m_listServer.AddString( "../" );
		*/
		m_listServer.EnumerateList();
	}
	else
	{
		AfxMessageBox( "�����Դϴ�... �ּ� �̻�.");
	}
	SetCursor( LoadCursor( NULL, IDC_CROSS ) );

	//  ������� ���� ��ũ�� ������ ǥ��...
	m_listLocal.EnumerateList();
/*
	m_listLocal.ResetContent();
	WIN32_FIND_DATA		fd;
	HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

	if( hFind != INVALID_HANDLE_VALUE )
	{
		do {
			if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			{
				m_listLocal.AddString( fd.cFileName );
			}
			else
			{
				CString		strDirectoryName = fd.cFileName ;
				strDirectoryName += "/";
				m_listLocal.AddString( strDirectoryName );
			}
		}  while( ::FindNextFile( hFind, &fd ) );
		::FindClose( hFind );
	}
	*/
	//  Connecting �������� ��� ������ ǥ��
	pDoc ->m_bConnected = 1;
	m_listServer.m_pConnection = m_pConnect;	// CFtpConnection �� �ּҸ� ListBox ����� ����
	m_listServer.m_pSession = &m_Session;
	m_listServer.m_pFileFind = m_pFileFind;
	m_listServer.m_pDoc = GetDocument();
	m_listLocal.m_pConnection = m_pConnect;
	m_listLocal.m_pSession = &m_Session;
	m_listLocal.m_pFileFind = m_pFileFind;
	m_listLocal.m_pDoc = GetDocument();
}

void CFTPDlg::OnDblclkFilelistListbox() 
{
	// TODO: Add your control notification handler code here
	UpdateData( FALSE );
	CBrowserDoc *pDoc = GetDocument ();

	int	num = m_listServer.GetCurSel();
	if( num == LB_ERR )		//  �̷� ��Ȳ�� �Ƹ� �� �� ���̳� Ȥ�� ������ ���...
		return;
	CString	strDir;
	m_listServer.GetText( num , strDir );
	if( strDir == "./" )
		return;
	if( strDir == "../" )		// ���� ���丮�� �̵��� ���
	{
		m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
		if( pDoc ->m_strServerPath == "/" )
		{
			MessageBox("���� �� ���丮�� ���� ���� ���丮�Դϴ�.");
			return;
		}
		LPTSTR	temp = (LPTSTR) malloc( 100 );
		_tcscpy( temp , pDoc ->m_strServerPath );
		if( temp[ _tcslen(temp) -1 ] == '/' )
			temp[ _tcslen(temp) -1 ] = NULL;
		int nLen = _tcslen( temp ) -1;
		for( INT i = nLen ; i >= 0 ; i-- )
		{
			if( temp[i] == '/' )
			{
				temp[i + 1] = NULL;
				break;
			}
		}
		pDoc ->m_strServerPath = temp;
//		pDoc ->m_strServerPath += "/";
		free( temp );
		if( !m_pConnect ->SetCurrentDirectory( pDoc ->m_strServerPath ) )
		{
			MessageBox( "���丮 �̵� ����! ���� ��ΰ� ���� �ֻ� ����� ���� �ֽ��ϴ�.");
			return;
		}

		// Server List Initialization
		/*
		CString	data;
		data.Empty();
		m_listServer.ResetContent();
		m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
		m_pFileFind ->FindFile( pDoc ->m_strServerPath );

		BOOL	bContinue;
		while( bContinue )
		{
			bContinue = m_pFileFind ->FindNextFile ();
			data = m_pFileFind ->GetFileName ();
			if( m_pFileFind ->IsDirectory() )
				data += "/";
			m_listServer.AddString( data );
		}
		m_listServer.AddString( "./" );
		m_listServer.AddString( "../" );
		*/
		m_listServer.EnumerateList();
		SetCursor( LoadCursor( NULL, IDC_CROSS ) );
		return;
	}
	else
	{
		pDoc ->m_strServerPath += strDir;
	}
	if( pDoc ->m_strServerPath[pDoc ->m_strServerPath.GetLength()-1] != '/' )
	{
		UpdateData( FALSE );
		int	num = m_listServer.GetCurSel ();
		LPTSTR	temp = (LPTSTR) malloc( 512 );
		m_listServer.GetText( num, temp );

		CString	downData;
		downData += temp;	// error ���� �ʳ�? Ȯ��..

//		CFileDialog	dlg( TRUE, NULL, temp, OFN_HIDEREADONLY
//			, _T("��� ���� (*.*) |*.*|"), this );
		free( temp );
//		dlg.DoModal();
		SetCursor( LoadCursor( NULL, IDC_WAIT ) );
//		CString		str = dlg.GetPathName();
		CFile	*pFile = new CFile( downData, CFile::modeCreate );
		pDoc ->m_strLocalPath = pFile ->GetFilePath();
		delete	pFile;
		CFile::Remove( pDoc ->m_strLocalPath );
		if( m_pConnect ->GetFile( downData, pDoc ->m_strLocalPath ) == NULL )
		{
			TRACE1( _T("%d"), GetLastError() );
			MessageBox("�ٿ�ε� ����!");
		}
		SetCursor( LoadCursor( NULL, IDC_CROSS ) );

		//  Local �ʱ�ȭ
		/*
		m_listLocal.ResetContent();
		WIN32_FIND_DATA		fd;
		HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );
		if( hFind != INVALID_HANDLE_VALUE ) {
			do {
				if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
					m_listLocal.AddString( fd.cFileName );
				else
				{
					CString		strDirectory;
					strDirectory = fd.cFileName;
					strDirectory += "/";
					m_listLocal.AddString( strDirectory );
				}
			} while( ::FindNextFile( hFind, &fd ) );
		}
		*/
		m_listLocal.EnumerateList();
		//  End ENUMERATING FOLDER.

		return;
	}

	if( !m_pConnect ->SetCurrentDirectory( pDoc ->m_strServerPath ) )
	{
		pDoc ->m_strServerPath += "/";
		AfxMessageBox("���丮 �̵� �Ұ�");
		return;
	}
	SetCursor( LoadCursor( NULL, IDC_WAIT ) );

//	BOOL	bContinue = TRUE;
//	m_listServer.ResetContent();
//	CString	data;
//	m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
//	bContinue = m_pFileFind ->FindFile( pDoc ->m_strServerPath );
//	if( bContinue == NULL )	// ���� �߻���
//		if( GetLastError() == ERROR_NO_MORE_FILES )		// ������ ���� ���� ����
//		{
//			SetCursor( LoadCursor( NULL, IDC_CROSS ) );
//			m_listServer.EnumerateList();
//			return;
//		}
//	while( bContinue )
//	{
//		bContinue = m_pFileFind ->FindNextFile ();
//		data = m_pFileFind ->GetFileName ();
//		if( m_pFileFind ->IsDirectory() )
//			data += "/";
//		m_listServer.AddString( data );
//	}
//	m_listServer.AddString( "./" );
//	m_listServer.AddString( "../" );
	m_listServer.EnumerateList();
	SetCursor( LoadCursor( NULL, IDC_CROSS ) );
}

void CFTPDlg::OnDblclkLocallistListbox() 
{
	// TODO: Add your control notification handler code here
	CBrowserDoc *pDoc = GetDocument();
	CString		strFileName;
	SetCursor( LoadCursor( NULL, IDC_WAIT ));

	m_listLocal.GetText( m_listLocal.GetCurSel(), strFileName );
	if( strFileName[ strFileName.GetLength()-1 ] == '/' )	// Is Directory...?
	{
		strFileName.Delete( strFileName.GetLength()-1 );
		::SetCurrentDirectory( strFileName );
		// Enumerate Folders.
		/*
		m_listLocal.ResetContent();
		WIN32_FIND_DATA		fd;
		HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

		if( hFind != INVALID_HANDLE_VALUE ) {
			do {
				if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
					m_listLocal.AddString( fd.cFileName );
				else
				{
					CString		strDirectory;
					strDirectory = fd.cFileName;
					strDirectory += "/";
					m_listLocal.AddString( strDirectory );
				}
			} while( ::FindNextFile( hFind, &fd ) );
		}
		*/
		m_listLocal.EnumerateList();
		strFileName += "/" ;
		//  End ENUMERATING FOLDER.
		return;
	}
	if( strFileName == "../" )	// ���� ���丮�� �̵��϶�
	{
		::SetCurrentDirectory( _T("..") );
//		LPTSTR	strTemp = (LPTSTR) malloc( 30 );
//		::GetCurrentDirectory( 30 , strTemp );
//		pDoc ->m_strLocalPath = strTemp;
//		free(strTemp);
		//  ENUMERATE FOLDER   CFileDialog
		/*
		m_listLocal.ResetContent();
		WIN32_FIND_DATA		fd;
		HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

		if( hFind != INVALID_HANDLE_VALUE )
		{
			do {
				if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )	// Is Directory..
				{
					CString		strDirectory;
					strDirectory = fd.cFileName;
					strDirectory += "/";
					m_listLocal.AddString( fd.cFileName );
				}
				else		// Is Files..
					m_listLocal.AddString( fd.cFileName );
			} while( ::FindNextFile( hFind, &fd ) );
		}
		*/
		m_listLocal.EnumerateList();
		return;
	}
	strFileName.Empty ();		//  ���� ����
	m_listLocal.GetText( m_listLocal.GetCurSel(), strFileName );	// ���� ����
	CFile		*pFile = new CFile( strFileName, CFile::modeRead );
	pDoc ->m_strLocalPath = pFile ->GetFilePath();
	delete	pFile;
//	pDoc ->m_strLocalPath.Replace( "\\", "\\\\" );
//	pDoc ->m_strServerPath.Replace( "//", "/" );
//	if( pDoc ->m_strServerPath[0] == '/' )
//		pDoc ->m_strServerPath.Delete( 0 );
	if( m_pConnect ->PutFile( pDoc ->m_strLocalPath , strFileName ) == NULL ) // Error!
	{
		TRACE1( _T("%d"), GetLastError() );
		MessageBox("��Ʈ��ŷ ����. ������ Ŭ���̾�Ʈ�� ��� �̻� �Ǵ� ���� ���� �ҷ��Դϴ�.");
		return;
		// Error Code ==> (53)ERROR_BAD_NETPATH : The network path was not found.
		// ==> (32)The process cannot access the file because it is being used by another process.  ERROR_SHARING_VIOLATION
	}
//	if( pDoc ->m_strServerPath[ nLeng - 1 ] != '/' )
//		pDoc ->m_strServerPath += "/";
	/*
	m_listServer.ResetContent();
	CString		data;
	m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
	m_pFileFind ->FindFile( pDoc ->m_strServerPath );
	BOOL	bContinue = TRUE;
	while( bContinue )
	{
		bContinue = m_pFileFind ->FindNextFile();
		data = m_pFileFind ->GetFileName();
		if( m_pFileFind ->IsDirectory() )
			data += "/";
		m_listServer.AddString( data );
	}
	m_listServer.AddString( "./" );
	m_listServer.AddString( "../" );
	*/
	m_listServer.EnumerateList();
	SetCursor( LoadCursor( NULL, IDC_CROSS ));
}

void CFTPDlg::OnDblclkManageaddressList() 
{
	// TODO: Add your control notification handler code here
	INT		nIndex;
	if( (nIndex = m_listManageAddress.GetCurSel()) == LB_ERR )
		return;
	CString		strAddress;
	m_listManageAddress.GetText( nIndex , strAddress );
	m_comboAddress.SetWindowText( strAddress );
	UpdateData( FALSE );
}

CBrowserDoc* CFTPDlg::GetDocument()
{
	return	m_pDoc;
}

void	CFTPDlg::EnumerateFolder()
{
}

HRESULT	CFTPDlg::DownloadFile( CString  dwnFile )
{
	CBrowserDoc *pDoc = GetDocument();
//	UpdateData( FALSE );
//	int	num = m_listServer.GetCurSel ();
	LPTSTR	temp = (LPTSTR) malloc( 512 );
	_tcscpy( temp, dwnFile );
//	m_listServer.GetText( num, temp );

	if( temp[ _tcslen(temp) - 1] == '/' )
	{
		AfxMessageBox( "���丮�� ���縦 �� �� �����Ǵϴ�... ^^��");
		return	E_FAIL;
	}
	CString	downData;
	downData += temp;	// error ���� �ʳ�? Ȯ��..

//	CFileDialog	dlg( TRUE, NULL, temp, OFN_HIDEREADONLY
//		, _T("��� ���� (*.*) |*.*|"), this );
	CFile	*pFile = new CFile( downData, CFile::modeCreate );
	pDoc ->m_strLocalPath = pFile ->GetFilePath ();
	delete	pFile;
	CFile::Remove( pDoc ->m_strLocalPath );
	SetCursor( LoadCursor( NULL, IDC_WAIT ) );
	if( m_pConnect ->GetFile( downData, pDoc ->m_strLocalPath ) == NULL )
	{
		TRACE1( _T("%d"), GetLastError() );
		return	E_FAIL;
	}
	SetCursor( LoadCursor( NULL, IDC_CROSS ) );

	//	Free Memory
	free( temp );

	//  Local List Initialization
	//	Enumerate Now Loading Folder
/*	m_listLocal.ResetContent();
	WIN32_FIND_DATA		fd;
	HANDLE	hFind = ::FindFirstFile( _T("*.*"), &fd );

	if( hFind != INVALID_HANDLE_VALUE ) {
		do {
			if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
				m_listLocal.AddString( fd.cFileName );
			else
			{
				CString		strDirectory;
				strDirectory = fd.cFileName;
				strDirectory += "/";
				m_listLocal.AddString( strDirectory );
			}
		} while( ::FindNextFile( hFind, &fd ) );
	}*/
	m_listLocal.EnumerateList();
	//  End ENUMERATING FOLDER.
	return	S_OK;
}

HRESULT	CFTPDlg::UploadFile( CString upFile )
{
	CBrowserDoc *pDoc = GetDocument();
	CString		strFileName;
	SetCursor( LoadCursor( NULL, IDC_WAIT ));
//	INT		nIndex = m_listLocal.GetCurSel();
/*	if( nIndex == LB_ERR )
	{
		MessageBox("Local ��� ������ �׸��� �����Ͽ��ֽʽÿ�.");
		return	E_FAIL;
	}*/
//	m_listLocal.GetText( nIndex, strFileName );
//	strFileName = dlg.GetFileName();
	strFileName = upFile;
	if( strFileName[ strFileName.GetLength()-1 ] == '/' )
	{
		MessageBox("���丮�� ���ε��ų �� �����ϴ�.");
		return	E_FAIL;
	}
	CFile	*pFile = new CFile( strFileName, CFile::modeRead );
	pDoc ->m_strLocalPath = pFile ->GetFilePath ();
	delete	pFile;
	if( m_pConnect ->PutFile( pDoc ->m_strLocalPath, strFileName ) == NULL ) // Error!
	{
		TRACE1( _T("%d"), GetLastError() );
		MessageBox("��Ʈ��ŷ ����. ������ Ŭ���̾�Ʈ�� ��� �̻� �Ǵ� ���� ���� �ҷ��Դϴ�.");
	}

/*	m_listServer.ResetContent();
	CString		data;
	m_pConnect ->GetCurrentDirectory( pDoc ->m_strServerPath );
	m_pFileFind ->FindFile( pDoc ->m_strServerPath );
	BOOL	bContinue = TRUE;
	while( bContinue )
	{
		bContinue = m_pFileFind ->FindNextFile();
		data = m_pFileFind ->GetFileName();
		if( m_pFileFind ->IsDirectory() )
			data += "/";
		m_listServer.AddString( data );
	}
	m_listServer.AddString( "./" );
	m_listServer.AddString( "../" );
	*/
	m_listServer.EnumerateList();
	SetCursor( LoadCursor( NULL, IDC_CROSS ));
	return	S_OK;
}

BOOL CFTPDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_uploadButton.SubclassDlgItem(IDC_UPLOAD_BUTTON, this);
	m_uploadButton.LoadBitmaps(IDB_UPLOAD);
	m_uploadButton.SizeToContent();
	m_downloadButton.SubclassDlgItem(IDC_DOWNLOAD_BUTTON, this);
	m_downloadButton.LoadBitmaps(IDB_DOWNLOAD);
	m_downloadButton.SizeToContent();

	// TODO: Add extra initialization here
	m_listManageAddress.AddString(_T("www.interface.or.kr"));
	m_listManageAddress.AddString(_T("www.daum.net"));
	m_listManageAddress.AddString(_T("www.sejong.ac.kr"));
	m_listManageAddress.AddString(_T("ce.sejong.ac.kr"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFTPDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete	this;
	CDialog::PostNcDestroy();
}

void CFTPDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	PostNcDestroy();
}

void CFTPDlg::OnButtonhelp() 
{
	// TODO: Add your control notification handler code here
	CString		helpStr;

	helpStr = _T("�ȳ��Ͻʴϱ�? All FTP �� ����� ���� ���� ȯ���մϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("��ɵ��� ������ �����ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("1. Upload ��ư�� Ŭ���ϸ� ���� Local List Box �� ���õ� �������� Upload �˴ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("2. Download ��ư�� Ŭ���ϸ� ���� Server List Box �� ���õ� �������� Download �˴ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("3. Server List Box ���� Local List �� �������� �巡���ϸ� �ڵ� �ٿ�ε�˴ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("4. Local List Box ���� Server List �� �������� �巡���ϸ� �ڵ� ���ε�˴ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("5. URL �� �� �� ���ӽ� ������ ����� URL ����Ʈ �ڽ��� URL �Է¹ٿ� ���ο� URL �� �߰��˴ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("6. ������ Ŭ���̾�Ʈ�� ����� ���� ������ Ŭ���ϰ� Del Ű�� �Է��ϸ� ���� ������ �� �ֽ��ϴ�.\n");
	helpStr += _T("\n");
	helpStr += _T("7. ������ Ŭ���̾�Ʈ�� ������ Ŭ���ϰ� Ctrl + R �� �Է½� ������ �̸��� �ٲ� �� �ֽ��ϴ�.\n");
	helpStr += _T("\n\n% ��Ÿ �������̽� : ������ �ڽ��� Ȩ���丮 ���� ���丮�δ� �̵��� �� ���� �Ǿ� �ֽ��ϴ�.(���Ȼ�)");
	helpStr += _T("\n\n                    ���丮�� �̸� �ڿ� '/'�� �ٽ��ϴ�.   EX> DirName/");
	helpStr += _T("\n\n                    ������ �̸� �ڿ� �ƹ� ǥ���� �����ϴ�. EX> FileName");

	MessageBox(helpStr, _T("����"));
}