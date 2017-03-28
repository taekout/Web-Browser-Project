; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NetOmok.h"
LastPage=0

ClassCount=8
Class1=CNetOmokApp
Class2=CNetOmokDoc
Class3=CNetOmokView
Class4=CMainFrame

ResourceCount=5
Resource1=CG_IDD_CHATDLG
Resource2=CG_IDD_INFOBAR
Class5=CAboutDlg
Resource3=IDD_CONNECT_DIALOG
Resource4=IDD_ABOUTBOX
Class6=CConnectDlg
Class7=CListenSocket
Class8=CClientSocket
Resource5=IDR_MAINFRAME

[CLS:CNetOmokApp]
Type=0
HeaderFile=NetOmok.h
ImplementationFile=NetOmok.cpp
Filter=N

[CLS:CNetOmokDoc]
Type=0
HeaderFile=NetOmokDoc.h
ImplementationFile=NetOmokDoc.cpp
Filter=N

[CLS:CNetOmokView]
Type=0
HeaderFile=NetOmokView.h
ImplementationFile=NetOmokView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CNetOmokView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=NetOmok.cpp
ImplementationFile=NetOmok.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONNECT_IP
Command2=ID_CONNECT_DISCONNECT
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONNECT_IP
Command2=ID_APP_EXIT
Command3=ID_CONNECT_DISCONNECT
CommandCount=3

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:CG_IDD_CHATDLG]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT_SEND_MSG,edit,1350631552
Control2=IDC_EDIT_RECEIVE_MSG,edit,1350631552
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865

[DLG:CG_IDD_INFOBAR]
Type=1
Class=?
ControlCount=2
Control1=IDC_STATIC_SU,static,1342308352
Control2=IDC_STATIC,static,1342308865

[DLG:IDD_CONNECT_DIALOG]
Type=1
Class=CConnectDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO_SERVERCLIENT,button,1342308361
Control5=IDC_RADIO_SERVERCLIENT2,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_COMBO_IP,combobox,1344340034

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO_SERVERCLIENT

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CListenSocket

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CClientSocket
VirtualFilter=uq

