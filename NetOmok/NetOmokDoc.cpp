// NetOmokDoc.cpp : implementation of the CNetOmokDoc class
//

#include "stdafx.h"
#include "NetOmok.h"

#include "NetOmokDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetOmokDoc

IMPLEMENT_DYNCREATE(CNetOmokDoc, CDocument)

BEGIN_MESSAGE_MAP(CNetOmokDoc, CDocument)
	//{{AFX_MSG_MAP(CNetOmokDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetOmokDoc construction/destruction

CNetOmokDoc::CNetOmokDoc()
{
	// TODO: add one-time construction code here

}

CNetOmokDoc::~CNetOmokDoc()
{
}

BOOL CNetOmokDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNetOmokDoc serialization

void CNetOmokDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNetOmokDoc diagnostics

#ifdef _DEBUG
void CNetOmokDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNetOmokDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetOmokDoc commands
