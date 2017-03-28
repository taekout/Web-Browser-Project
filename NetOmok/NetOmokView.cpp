// NetOmokView.cpp : implementation of the CNetOmokView class
//

#include "stdafx.h"
#include "NetOmok.h"

#include "NetOmokDoc.h"
#include "NetOmokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView

IMPLEMENT_DYNCREATE(CNetOmokView, CView)

BEGIN_MESSAGE_MAP(CNetOmokView, CView)
	//{{AFX_MSG_MAP(CNetOmokView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CONNECT_IP, OnConnectIp)
	ON_COMMAND(ID_CONNECT_DISCONNECT, OnConnectDisconnect)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView construction/destruction

CNetOmokView::CNetOmokView()
{
	// TODO: add construction code here
	m_nBoardSize = 15;
	m_nBoardUnit = 24;
	m_nStartX = 30;
	m_nStartY = 30;
	m_nCurCol = -1;
	m_nCurRow = -1;
	m_colorWinner = EMPTY;
    m_nMyStone = WHITE;

	for(int i=0;i<15;i++)for(int j=0;j<15;j++)	colorState[i][j]=EMPTY;

	m_suCount=0;
	m_pListenSocket=NULL;
    m_pClientSocket=NULL;
	takeTurn=0;
	m_IsGameOver=0;
  
}

CNetOmokView::~CNetOmokView()
{
}

BOOL CNetOmokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView drawing
#include "Data.h"
void CNetOmokView::OnDraw(CDC* pDC)
{
	CNetOmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
		int row, col;
		int sx = m_nStartX;
		int sy = m_nStartY;

		CRect rect(sx-m_nBoardUnit,sy-m_nBoardUnit,sx+m_nBoardUnit*m_nBoardSize,sy+m_nBoardUnit*m_nBoardSize);//전체 판때기 
		CBrush* pOldBrush;
		CBrush br(RGB(230,140,0));
		pOldBrush = (CBrush*)pDC->SelectObject(&br);
		pDC->Rectangle(rect);
		pDC->SelectObject(pOldBrush);
		for(row=0; row<m_nBoardSize; row++){
			pDC->MoveTo(sx, sy+row*m_nBoardUnit);
			pDC->LineTo(sx+m_nBoardUnit*(m_nBoardSize-1), sy+row*m_nBoardUnit);
		}
		for(col=0; col<m_nBoardSize; col++){
			pDC->MoveTo(sx+col*m_nBoardUnit, sy);
			pDC->LineTo(sx+col*m_nBoardUnit, sy+m_nBoardUnit*(m_nBoardSize-1));
		}
		
		POSITION pos = pDoc->m_listData.GetHeadPosition();
		CData* pData = new CData;
			while(pos)
			{
			pData = (CData*)pDoc->m_listData.GetNext(pos);
			for(row=0; row<m_nBoardSize;row++)
			{
		    for(col=0; col<m_nBoardSize; col++)
			{
			DrawStone(pDC, row, col ,colorState[col][row]);
			}
			}
			}
	
			
			
			
		


}

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView printing

BOOL CNetOmokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNetOmokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNetOmokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView diagnostics

#ifdef _DEBUG
void CNetOmokView::AssertValid() const
{
	CView::AssertValid();
}

void CNetOmokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNetOmokDoc* CNetOmokView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetOmokDoc)));
	return (CNetOmokDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetOmokView message handlers

void CNetOmokView::DrawStone(CDC *pDC, int row, int col, int color)
{
	if(color==EMPTY) return;

	int x,y,r;

	x = m_nStartX + col*m_nBoardUnit;
	y = m_nStartY + row*m_nBoardUnit;
	r = m_nBoardUnit*6/13;

	if(color==BLACK){
		pDC->SelectStockObject(BLACK_BRUSH);
		pDC->Ellipse(x-r,y-r,x+r,y+r);
	}
	else if(color==WHITE){
		pDC->SelectStockObject(WHITE_BRUSH);
		pDC->Ellipse(x-r,y-r,x+r,y+r);
	}
	if(row==m_lastStone.y && col==m_lastStone.x){
		pDC->SelectStockObject(GRAY_BRUSH);
		pDC->Rectangle(x-r/2,y-r/2,x+r/2,y+r/2);
	}
}


#include "Data.h"
#include "ClientSocket.h"

#include "MainFrm.h"
void CNetOmokView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(threeMthress(m_nCurCol,m_nCurRow))
	{AfxMessageBox("3*3입니다.");return;}
	CClientDC dc(this);
	if(m_pClientSocket!=NULL && takeTurn==2){AfxMessageBox("두실 차례가 아닙니다.");return;}
	if(m_pClientSocket!=NULL && isThereStone(m_nCurCol,m_nCurRow)){AfxMessageBox("그곳에는 둘 수 없습니다.");return;}
    colorState[m_nCurCol][m_nCurRow] = m_nMyStone;
    if(!threeMthress(m_nCurCol,m_nCurRow))
	DrawStone(&dc, m_nCurRow, m_nCurCol, m_nMyStone);
	DrawCross(&dc, m_nCurRow, m_nCurCol);
	if(m_pClientSocket!=NULL&&isGameOver(m_nCurCol,m_nCurRow))
	{
	displayGameOver();
	POSITION pos = GetDocument()->m_listData.GetHeadPosition();
	CData* pData = new CData;
	while(pos)
	{
	pData = (CData*)GetDocument()->m_listData.GetNext(pos);
	delete pData;
	}
	GetDocument()->m_listData.RemoveAll();

	}
	if(m_pClientSocket!= NULL)
	{
	CData* pData = new CData;
	
	pData->m_nGubun=1;
	pData->m_x = point.x;
	pData->m_y = point.y;
	CNetOmokDoc* pDoc = GetDocument();
	if(!threeMthress(m_nCurCol,m_nCurRow))
	{pDoc->m_listData.AddTail(pData);
	 pData->Serialize(*m_pClientSocket->m_pArchiveOut);
	m_pClientSocket->m_pArchiveOut->Flush();
	whatSuIsItNow();
    takeTurn=2;
	}
	}
	
	
	
	CView::OnLButtonDown(nFlags, point);
}

void CNetOmokView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int sx = m_nStartX - m_nBoardUnit/2;
	int sy = m_nStartY - m_nBoardUnit/2;
	int ex = m_nStartX + m_nBoardUnit*m_nBoardSize - m_nBoardUnit/2;
	int ey = m_nStartY + m_nBoardUnit*m_nBoardSize - m_nBoardUnit/2;

	int row, col;




	CClientDC dc(this);
	if(point.x>=sx && point.x<ex && point.y>=sy && point.y<ey){

		row = (point.y - sy)/m_nBoardUnit;
		col = (point.x - sx)/m_nBoardUnit;
		if(row!=m_nCurRow || col!=m_nCurCol){
			if(m_nCurRow!=-1 && m_nCurCol!=-1)
				DrawCross(&dc, m_nCurRow, m_nCurCol);
			DrawCross(&dc, row, col);
			m_nCurRow = row;
			m_nCurCol = col;
		}
	}
	else if(m_nCurRow!=-1 && m_nCurCol!=-1){
		DrawCross(&dc, m_nCurRow, m_nCurCol);
		m_nCurRow = -1;
		m_nCurCol = -1;
	}
	CView::OnMouseMove(nFlags, point);
}

void CNetOmokView::DrawCross(CDC *pDC, int row, int col)
{
    int r = m_nBoardUnit*3/8;
	int nOldMode = pDC->SetROP2(R2_NOT);

	pDC->MoveTo(m_nStartX+col*m_nBoardUnit-r,m_nStartY+row*m_nBoardUnit);
	pDC->LineTo(m_nStartX+col*m_nBoardUnit+r,m_nStartY+row*m_nBoardUnit);
	pDC->MoveTo(m_nStartX+col*m_nBoardUnit,m_nStartY+row*m_nBoardUnit-r);
	pDC->LineTo(m_nStartX+col*m_nBoardUnit,m_nStartY+row*m_nBoardUnit+r);
	pDC->SetROP2(nOldMode);
}
#include "ConnectDlg.h"
#include "ListenSocket.h"
#include "ClientSocket.h"
void CNetOmokView::OnConnectIp() 
{
	// TODO: Add your command handler code here

	CConnectDlg dlg;
	if(dlg.DoModal()!=IDOK)return;
	
	
	if(dlg.m_radioSC==0)
	{
		
		if(m_pListenSocket!=NULL)
			return;
		m_pListenSocket = new CListenSocket(this); 
		
		if(!m_pListenSocket->Create(2000) || !m_pListenSocket->Listen() )
		{
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		MessageBeep(MB_ICONEXCLAMATION);
		MessageBox("서버에 필요한 소켓을 구성할 수 없습니다!","Listen오류",MB_ICONSTOP);
		return;
		}
		else
		{
		AfxMessageBox("오목판 초기화");
		for(int i=0;i<15;i++)for(int j=0;j<15;j++)colorState[i][j]=EMPTY;
		Invalidate();
		MessageBox("서버모드로 접속요청을 기다리고 있습니다.","확인",MB_OK);
		}
	}
		else if(dlg.m_radioSC==1)
	{
		if(m_pClientSocket!=NULL)return;
        m_pClientSocket = new CClientSocket(this);
		if(!m_pClientSocket->Create() || 
			!m_pClientSocket->Connect(dlg.m_strComboIP,2000))
		{
		m_pClientSocket=NULL;
		MessageBeep(MB_ICONEXCLAMATION);
		MessageBox("서버 접속에 필요한 소켓을 구성할 수 없습니다.\nIP주소를 다시 확인해 주세요.","FAIL",MB_ICONSTOP);
		}
		else
		{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CEdit* pEdit = (CEdit*) pFrame->m_wndInfoBar.GetDlgItem(IDC_STATIC_SU);
		pEdit->SetWindowText("서버에 접속하였습니다. 즐거운 게임이 되기를...");
		for(int i=0;i<15;i++)for(int j=0;j<15;j++)colorState[i][j]=EMPTY;
		Invalidate();
		m_pClientSocket->Init();
		}
	}

}

void CNetOmokView::AcceptClient()
{
    if( m_pListenSocket == NULL) return; 
	if( m_pClientSocket != NULL) return;
    m_pClientSocket=new CClientSocket(this);
	if( !m_pListenSocket->Accept(*m_pClientSocket))
	{
	delete m_pClientSocket;
	m_pClientSocket=NULL;
	MessageBox("접속요청을 받아들일 수 없습니다.","Accept오류",MB_ICONSTOP);
	}
	else
	{
		m_pClientSocket->Init();
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CEdit* pEdit = (CEdit*) pFrame->m_wndInfoBar.GetDlgItem(IDC_STATIC_SU);
		pEdit->SetWindowText("접속요청을 받아 들였습니다.");
		for(int i=0;i<15;i++)for(int j=0;j<15;j++)colorState[i][j]=EMPTY;
	}
}

void CNetOmokView::CloseClient()
{
	if(m_pClientSocket)
	{
		
		m_pClientSocket->ShutDown(2);
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket=NULL;
	POSITION pos = GetDocument()->m_listData.GetHeadPosition();
	CData* pData = new CData;
	while(pos)
	{
	pData = (CData*)GetDocument()->m_listData.GetNext(pos);
	delete pData;
	}
	GetDocument()->m_listData.RemoveAll();
	}	
	takeTurn=0;
	MessageBox("상대방이 접속을 끊었습니다.","접속해제",MB_ICONSTOP);

}
#include "MainFrm.h"
void CNetOmokView::ReceiveData()
{
do
	{
		CData* pData = new CData;
		pData->Serialize(*m_pClientSocket->m_pArchiveIn);
		
		if(pData->m_nGubun==0)
		{
		delete pData;
		CloseClient();
		MessageBox("접속이 끊어졌습니다.","접속해제",MB_ICONSTOP);
		break;
		}
		else if(pData->m_nGubun==2)
		{
	
	   	if(m_pClientSocket==NULL){AfxMessageBox("메세지를 보낼 수 없습니다.\n먼저 접속하세요.");return;}
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CEdit *pEdit = (CEdit*)pFrame->m_wndChatDlg.GetDlgItem(IDC_EDIT_RECEIVE_MSG);
		pEdit->SetWindowText(pData->m_strChat);
		UpdateData(0);
		}
		else if(pData->m_nGubun==1)
		{
		GetDocument()->m_listData.AddTail(pData);
		
		int col;
		int row;
		int sx = m_nStartX - m_nBoardUnit/2;
	    int sy = m_nStartY - m_nBoardUnit/2;
		row = (pData->m_y - sy)/m_nBoardUnit;
		col = (pData->m_x - sx)/m_nBoardUnit;
		CDC* pDC = GetDC();

		int imsiColor;
		if(m_nMyStone==0)imsiColor=1;
		else if(m_nMyStone==1)imsiColor=0;
		takeTurn=1;
		whatSuIsItNow();
		colorState[col][row]=imsiColor;
		DrawStone(pDC,row,col,imsiColor);
	
	
		ReleaseDC(pDC);
		}

	else if(pData->m_nGubun==3)
	{
	AfxMessageBox("당신이 졌습니다.");
	for(int i=0;i<15;i++)for(int j=0;j<15;j++)	colorState[i][j]=EMPTY;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CEdit* pEdit = (CEdit*) pFrame->m_wndInfoBar.GetDlgItem(IDC_STATIC_SU);
	pEdit->SetWindowText("당신이 선수입니다.");
    POSITION pos = GetDocument()->m_listData.GetHeadPosition();
	CData* pData = new CData;
	while(pos)
	{
	pData = (CData*)GetDocument()->m_listData.GetNext(pos);
	delete pData;
	}
	GetDocument()->m_listData.RemoveAll();
	pEdit->SetWindowText("오목판 초기화");
	Invalidate();
	}
	}while(!m_pClientSocket->m_pArchiveIn->IsBufferEmpty());


}

void CNetOmokView::OnConnectDisconnect() 
{
	// TODO: Add your command handler code here
	if(m_pClientSocket==NULL && m_pListenSocket==NULL){AfxMessageBox("접속이 이미 끊어져 있습니다.");return;}
	if(m_pClientSocket==NULL)
	{
		delete m_pListenSocket;
		m_pListenSocket = NULL; 
		return;
	}
	takeTurn=0;
		
	if(m_pListenSocket)
	{
		m_pListenSocket->ShutDown(2);
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket=NULL;
		}

	if(m_pClientSocket)
	{
	    
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket=NULL;
	}

	CNetOmokDoc* pDoc = GetDocument();
	POSITION pos = pDoc->m_listData.GetHeadPosition();
	while(pos)
	{
	CData* pData =  ( CData*) pDoc->m_listData.GetNext(pos);
	delete pData;
	}
	pDoc->m_listData.RemoveAll();
	MessageBox("접속이 끊겼습니다.","접속해제",MB_ICONSTOP);

}

BOOL CNetOmokView::isThereStone(int m_nCurCol, int m_nCurRow)
{
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
		if(colorState[m_nCurCol][m_nCurRow]==WHITE || colorState[m_nCurCol][m_nCurRow]==BLACK)
			return 1;
		
		}
 return 0;
}





BOOL CNetOmokView::isGameOver(int m_nCurCol, int m_nCurRow)
{
	int i,x1,y1,check=0,check1=0,check2=0,check3=0;
    x1= m_nCurCol;
    y1= m_nCurRow;
        for(i=-4;i<5;i++)      
		{
			if(colorState[x1+i][y1+i]==WHITE) check++;
			else check=0;
			if(colorState[x1+i][y1]==WHITE) check1++;
			else check1=0;
			if(colorState[x1][y1+i]==WHITE) check2++;
			else check2=0;
			if(colorState[x1-i][y1+i]==WHITE) check3++;
			else check3=0;
			if(check==5 || check1==5 || check2==5 || check3==5)
			{
			
			return 1; 
			}
		}
	return 0;
}

void CNetOmokView::displayGameOver()
{
	MessageBox("당신이 이겼습니다.","WINNER",MB_OK);
	if(m_pClientSocket!=NULL)
	{
	CData* pData = new CData;
	
	pData->m_nGubun=3;
	CNetOmokDoc* pDoc = GetDocument();
	pDoc->m_listData.AddTail(pData);
	pData->Serialize(*m_pClientSocket->m_pArchiveOut);
	m_pClientSocket->m_pArchiveOut->Flush();
	}

	for(int i=0;i<15;i++)for(int j=0;j<15;j++)colorState[i][j]=EMPTY;
	Invalidate();
	
	
    POSITION pos = GetDocument()->m_listData.GetHeadPosition();
	CData* pData = new CData;
	while(pos)
	{
	pData = (CData*)GetDocument()->m_listData.GetNext(pos);
	delete pData;
	}
	GetDocument()->m_listData.RemoveAll();
	m_IsGameOver=1;
}





void CNetOmokView::whatSuIsItNow()
{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CEdit* pEdit = (CEdit*)pFrame->m_wndInfoBar.GetDlgItem(IDC_STATIC_SU);
		CString su;
	
CData* pData = new CData;
 if(m_IsGameOver)
 {
 GetDocument()->m_listData.RemoveAll();
 }
 
int x=0;

POSITION pos = GetDocument()->m_listData.GetHeadPosition();
while(pos)
{
	pData = (CData*)GetDocument()->m_listData.GetNext(pos);
    if(m_IsGameOver)x--;
	if(pData->m_x)x++;
	
}
su.Format("현재 %d수 진행중 입니다.",x);
pEdit->SetWindowText(su);
m_IsGameOver=0;
}

BOOL CNetOmokView::threeMthress(int m_nCurCol, int m_nCurRow)
{
  
//공사중
/*  int i,x1,y1,check=0,check1=0,check2=0,check3=0;
    x1= m_nCurCol;
    y1= m_nCurRow;
        for(i=-1;i<2;i++)      
		{
			if(colorState[x1+i][y1+i]==WHITE)check++;
			else check=0;
			if(colorState[x1+i][y1]==WHITE)check1++;
			else check1=0;
			if(colorState[x1][y1+i]==WHITE)check2++;
			else check2=0;
			if(colorState[x1-i][y1+i]==WHITE)check3++;
			else check3=0;
			if(colorState[x1+2][y1]==BLACK || colorState[x1-2][y1]==BLACK || 
				colorState[x1][y1+2]==BLACK || colorState[x1][y1-2]==BLACK||
				colorState[x1+2][y1+2]==BLACK || colorState[x1-2][y1-2]==BLACK)
				return 0;
		}
			
			if( (check==3 && check1==3) || (check==3 && check2==3) || (check==3 && check3==3))
			return 1; 
			if( (check1==3 && check2==3) || (check1==3 && check3==3)  )
			return 1;
			if( check2==3 && check3==3)
			return 1;
			
			
		
		




*/
	return 0;
}








