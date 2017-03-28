// NetOmokDoc.h : interface of the CNetOmokDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETOMOKDOC_H__EFD62BAB_1198_11D6_9871_004854839105__INCLUDED_)
#define AFX_NETOMOKDOC_H__EFD62BAB_1198_11D6_9871_004854839105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CData;
class CNetOmokDoc : public CDocument
{
protected: // create from serialization only
	CNetOmokDoc();
	DECLARE_DYNCREATE(CNetOmokDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetOmokDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPtrList m_listData;
	virtual ~CNetOmokDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNetOmokDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETOMOKDOC_H__EFD62BAB_1198_11D6_9871_004854839105__INCLUDED_)
