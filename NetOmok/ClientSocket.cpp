// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "NetOmok.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
	m_pSocketFile=NULL;
}

CClientSocket::~CClientSocket()
{
	//해제 작업 
	if(m_pSocketFile)
	{
//	m_pSocketFile->Abort();//sd//지원되지 않는 작동..
//	m_pSocketFile->Close();//sd
	delete m_pSocketFile;
	m_pSocketFile=NULL;
	}

	if(m_pArchiveIn)
	{
	
		//	m_pArchiveIn->Flush();
		m_pArchiveIn->Abort();
	//	m_pArchiveIn->Close();
	delete m_pArchiveIn;
	m_pArchiveIn=NULL;
	}
	if(m_pArchiveOut)
	{
	m_pArchiveOut->Abort();
		delete m_pArchiveOut;
	m_pArchiveOut=NULL;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

CClientSocket::CClientSocket(CNetOmokView *pView)
{
m_pView = pView;
}

void CClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pView->CloseClient();
	CSocket::OnClose(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pView->ReceiveData();
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::Init()
{
m_pSocketFile = new CSocketFile(this);//소켓객체를 이용해서 소켓파일객체를 만들고..
m_pArchiveIn = new CArchive(m_pSocketFile,CArchive::load);
m_pArchiveOut = new CArchive(m_pSocketFile,CArchive::store);

}
