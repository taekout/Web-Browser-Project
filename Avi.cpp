// Avi.cpp: implementation of the CMyVideo class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Browser.h"
#include "Avi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#ifndef AVI_CPP__
#define	AVI_CPP__


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*

	������ ��� mciGetErrorString �� �̿��Ͽ� ���� �޼����� ����
	UNIX �� perror �ý��� �ݰ� ���� ����
	
  */

#include "avi.h"

CMyVideo::CMyVideo(int x,int y,int cx,int cy,LPSTR filename,HWND wnd)
{
	m_strFileName=filename;
	Open(CRect(x,y,cx,cy),wnd);
	
}                  
CMyVideo::CMyVideo()
{
	m_strFileName="";
}
BOOL CMyVideo::Open(CRect rect, HWND hwnd)
{
	mciWindow.hWnd = hwnd ;
	mciOpenParms.lpstrDeviceType = "AVIVideo";
    mciOpenParms.lpstrElementName = (LPSTR)(LPCSTR)m_strFileName;
	//avi ������ ȭ�Ϸ� mci�� �����Ѵ�.
	mciSendCommand(0,
			MCI_OPEN,
			MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_DGV_OPEN_WS,
			(DWORD)(LPVOID) &mciOpenParms);					
	//open �� mci�� �޴´�.
	wDeviceID = mciOpenParms.wDeviceID;
	mciRect.rc.top = rect.top;
	mciRect.rc.left= rect.left;
	mciRect.rc.right=rect.right;					
	mciRect.rc.bottom =rect.bottom;
	//��ġ�� �����Ѵ�.	
	mciSendCommand(wDeviceID,MCI_PUT,MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT,
				(DWORD) (LPVOID) &mciRect);

	mciSendCommand(wDeviceID,MCI_WINDOW,MCI_DGV_WINDOW_HWND,
						(DWORD)(LPVOID) &mciWindow);
	return TRUE;
}

CMyVideo::~CMyVideo()
{
	//mci �� �ݴ´�.
	if(m_strFileName!="")
		mciSendCommand(wDeviceID,MCI_CLOSE,0,NULL);	// Error --> Library �� �� ���Խ��Ѷ�..!
}

BOOL CMyVideo::Play()
{
	//ȭ���� �÷��� �Ѵ�.
	DWORD	nErr  = 0;
	TCHAR pszErrText[101];
	nErr = mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY,
						(DWORD)(LPVOID) &mciPlayParms);
	if(nErr)
	{
		mciGetErrorString(nErr, pszErrText, 100);
		AfxMessageBox(pszErrText);
	}

	//avi�̱� ������ �ȷ�Ʈ�� �ٽ� Ȱ��ȭ �����ش�.
	mciSendCommand(wDeviceID,MCI_REALIZE,MCI_DGV_REALIZE_NORM,NULL);
	return TRUE;
}

void CMyVideo::MoveWindow(int x,int y,int cx,int cy)
{
	mciRect.rc.top = x;
	mciRect.rc.left= y;
	mciRect.rc.right=cx;
	mciRect.rc.bottom = cy;
	//�������� ��ġ�� �ٲ۴�.
	mciSendCommand(wDeviceID,MCI_PUT,MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT,
				(DWORD) (LPVOID) &mciRect);
} 

void CMyVideo::MoveCursor(DWORD Position,HWND hWnd)
{
	mciPlayParms.dwCallback =(DWORD)(LPVOID)hWnd;
	mciPlayParms.dwFrom = Position;
	mciPlayParms.dwTo = GetTotalLength();		// ���� ! ���Ƿ� ÷��!
	//Avi�� ��ġ�� �ٲپ� �ش�.
	mciSendCommand(wDeviceID,MCI_SEEK,/*SEEK_TO_START*/ MCI_NOTIFY,
					(DWORD)(LPVOID) &mciPlayParms);
}

void CMyVideo::Pause()
{
	//�Ͻ� ����
	mciSendCommand(wDeviceID,MCI_PAUSE,MCI_NOTIFY,
					(DWORD)(LPVOID) &mciPlayParms);

}


BOOL CMyVideo::Rewind (void)
{
	//ó������ ����.
	mciSendCommand (wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD) (LPVOID) NULL);
	return TRUE;
}

BOOL CMyVideo::Foward (void)
{
	//�������� ����.
	mciSendCommand (wDeviceID, MCI_SEEK, MCI_SEEK_TO_END, (DWORD) (LPVOID) NULL);
	return TRUE;
}
//point�� ���ǵ� ��ŭ ������ ����
BOOL CMyVideo::FrameNext (long point)
{
	DWORD RetCode;
    MCI_DGV_STEP_PARMS StepParms;
	MCI_STATUS_PARMS StatusParms;
	DWORD Length, Position;

	//��ü��ġ�� �޴´�.
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
		
	Length = StatusParms.dwReturn;

	// ������ ��ġ�� �˶󳽴�.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;

	// ��������ġ�� ȭ�� ���̸�
	if (Length == Position)
		return TRUE;

	// point ������ ��ŭ ���Ѵ�.
   StepParms.dwFrames = point;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STEP, MCI_DGV_STEP_FRAMES, (DWORD) (LPVOID) &StepParms)){
		return FALSE;
		}

	return TRUE;
}
//point ������ ��ŭ �������� ����.
BOOL CMyVideo::FramePrev (long point)
{
	DWORD RetCode;
	MCI_STATUS_PARMS StatusParms;
	DWORD Length, Position;

	//��ü �������� ��´�.
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
		
	Length = StatusParms.dwReturn;

	// ������ �������� ��´�.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;

	// ������ �������� 0�̸� ó���̹Ƿ� ����
	if (Position == 0)
		return TRUE;

	MCI_SEEK_PARMS mciSeekParms;
	mciSeekParms.dwTo = Position-point;
	//point ������ ��ŭ �������� �̵��Ѵ�.
	mciSendCommand(wDeviceID,MCI_SEEK,MCI_TO|MCI_WAIT,
					(DWORD)(LPVOID) &mciSeekParms);

	return TRUE;
}

BOOL CMyVideo::Close()
{
	if(m_strFileName!="")
	mciSendCommand(wDeviceID,MCI_CLOSE,0,NULL);
	return TRUE;
}

DWORD CMyVideo::GetTotalLength()
{

	DWORD RetCode;
	MCI_STATUS_PARMS StatusParms;
	DWORD Length;

	//��ü �������� ��´�.
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, 
		(DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
		
	Length = StatusParms.dwReturn;
	return Length;

}

DWORD CMyVideo::GetCurPosition()
{
	DWORD RetCode;
	MCI_STATUS_PARMS StatusParms;
	DWORD Position;

	// ������ �������� ��´�.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, 
		(DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;
	return Position;

}

#endif