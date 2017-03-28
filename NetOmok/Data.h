// Data.h: interface for the CData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__8D93E9A1_11A7_11D6_9871_004854839105__INCLUDED_)
#define AFX_DATA_H__8D93E9A1_11A7_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetOmokDoc.h"
class CData : public CObject  
{
public:
	CData();
	CData(CNetOmokDoc* pDoc);
	virtual ~CData();
public:

	void Serialize(CArchive& ar);
	CNetOmokDoc* m_pDoc;
	int m_nGubun; 
	int m_x; 
	int m_y;
	CString m_strChat; 
protected:
	DECLARE_SERIAL(CData);
};

#endif // !defined(AFX_DATA_H__8D93E9A1_11A7_11D6_9871_004854839105__INCLUDED_)
