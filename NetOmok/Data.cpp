// Data.cpp: implementation of the CData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetOmok.h"
#include "Data.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CData,CObject,0)
CData::CData()
{
m_nGubun=0;
m_strChat=_T("");
m_x=m_y=30;
}

CData::CData(CNetOmokDoc *pDoc)
{
m_pDoc = pDoc;
}
CData::~CData()
{

}


void CData::Serialize(CArchive &ar)
{
if(ar.IsStoring())
{
ar<<m_nGubun<<m_x<<m_y<<m_strChat;
}
else
{
ar>>m_nGubun>>m_x>>m_y>>m_strChat;
}
}
