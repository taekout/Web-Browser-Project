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

	에러날 경우 mciGetErrorString 를 이용하여 에러 메세지를 얻어본다
	UNIX 의 perror 시스템 콜과 같은 역할
	
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
	//avi 형태의 화일로 mci를 오픈한다.
	mciSendCommand(0,
			MCI_OPEN,
			MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_DGV_OPEN_WS,
			(DWORD)(LPVOID) &mciOpenParms);					
	//open 된 mci를 받는다.
	wDeviceID = mciOpenParms.wDeviceID;
	mciRect.rc.top = rect.top;
	mciRect.rc.left= rect.left;
	mciRect.rc.right=rect.right;					
	mciRect.rc.bottom =rect.bottom;
	//위치를 설정한다.	
	mciSendCommand(wDeviceID,MCI_PUT,MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT,
				(DWORD) (LPVOID) &mciRect);

	mciSendCommand(wDeviceID,MCI_WINDOW,MCI_DGV_WINDOW_HWND,
						(DWORD)(LPVOID) &mciWindow);
	return TRUE;
}

CMyVideo::~CMyVideo()
{
	//mci 를 닫는다.
	if(m_strFileName!="")
		mciSendCommand(wDeviceID,MCI_CLOSE,0,NULL);	// Error --> Library 를 잘 포함시켜라..!
}

BOOL CMyVideo::Play()
{
	//화면을 플레이 한다.
	DWORD	nErr  = 0;
	TCHAR pszErrText[101];
	nErr = mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY,
						(DWORD)(LPVOID) &mciPlayParms);
	if(nErr)
	{
		mciGetErrorString(nErr, pszErrText, 100);
		AfxMessageBox(pszErrText);
	}

	//avi이기 때문에 팔레트를 다시 활성화 시켜준다.
	mciSendCommand(wDeviceID,MCI_REALIZE,MCI_DGV_REALIZE_NORM,NULL);
	return TRUE;
}

void CMyVideo::MoveWindow(int x,int y,int cx,int cy)
{
	mciRect.rc.top = x;
	mciRect.rc.left= y;
	mciRect.rc.right=cx;
	mciRect.rc.bottom = cy;
	//윈도우의 위치를 바꾼다.
	mciSendCommand(wDeviceID,MCI_PUT,MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT,
				(DWORD) (LPVOID) &mciRect);
} 

void CMyVideo::MoveCursor(DWORD Position,HWND hWnd)
{
	mciPlayParms.dwCallback =(DWORD)(LPVOID)hWnd;
	mciPlayParms.dwFrom = Position;
	mciPlayParms.dwTo = GetTotalLength();		// 보류 ! 임의로 첨가!
	//Avi의 위치를 바꾸어 준다.
	mciSendCommand(wDeviceID,MCI_SEEK,/*SEEK_TO_START*/ MCI_NOTIFY,
					(DWORD)(LPVOID) &mciPlayParms);
}

void CMyVideo::Pause()
{
	//일시 정지
	mciSendCommand(wDeviceID,MCI_PAUSE,MCI_NOTIFY,
					(DWORD)(LPVOID) &mciPlayParms);

}


BOOL CMyVideo::Rewind (void)
{
	//처음으로 간다.
	mciSendCommand (wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD) (LPVOID) NULL);
	return TRUE;
}

BOOL CMyVideo::Foward (void)
{
	//나중으로 간다.
	mciSendCommand (wDeviceID, MCI_SEEK, MCI_SEEK_TO_END, (DWORD) (LPVOID) NULL);
	return TRUE;
}
//point로 정의된 만큼 포인터 이전
BOOL CMyVideo::FrameNext (long point)
{
	DWORD RetCode;
    MCI_DGV_STEP_PARMS StepParms;
	MCI_STATUS_PARMS StatusParms;
	DWORD Length, Position;

	//전체위치를 받는다.
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
		
	Length = StatusParms.dwReturn;

	// 현재의 위치를 알라낸다.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;

	// 현재위위치가 화일 끝이면
	if (Length == Position)
		return TRUE;

	// point 프레임 만큼 동한다.
   StepParms.dwFrames = point;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STEP, MCI_DGV_STEP_FRAMES, (DWORD) (LPVOID) &StepParms)){
		return FALSE;
		}

	return TRUE;
}
//point 프레임 만큼 이전으로 간다.
BOOL CMyVideo::FramePrev (long point)
{
	DWORD RetCode;
	MCI_STATUS_PARMS StatusParms;
	DWORD Length, Position;

	//전체 프레임을 얻는다.
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
		
	Length = StatusParms.dwReturn;

	// 현재의 포지션을 얻는다.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;

	// 현재의 포지션이 0이면 처음이므로 리턴
	if (Position == 0)
		return TRUE;

	MCI_SEEK_PARMS mciSeekParms;
	mciSeekParms.dwTo = Position-point;
	//point 프레임 만큼 이전으로 이동한다.
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

	//전체 프레임을 얻는다.
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

	// 현재의 포지션을 얻는다.
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if (RetCode = mciSendCommand (wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, 
		(DWORD) (LPVOID) &StatusParms)){
		return FALSE;
		}
	Position = StatusParms.dwReturn;
	return Position;

}

#endif