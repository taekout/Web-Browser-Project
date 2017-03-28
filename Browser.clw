; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Browser.h"
LastPage=0

ClassCount=17
Class1=CBrowserApp
Class2=CBrowserDoc
Class3=CBrowserView
Class4=CMainFrame

ResourceCount=13
Resource1=IDR_GAMEMENU
Class5=CLeftView
Class6=CAboutDlg
Class7=CUrlDlg
Resource2=IDD_ABOUTBOX
Resource3=IDD_SETALARM_PROPERTY
Class8=CMoveDialog
Resource4=IDR_MAINFRAME
Resource5=IDD_SETHOMEPAGE_PROPERTY
Resource6=IDR_CONTEXTGRAPHIC
Resource7=IDD_FTP
Class9=CInputDialog
Class10=CLocalListBox
Class11=CServerListBox
Resource8=IDR_LINKMENU
Class12=CFTPDlg
Class13=CMyPropertyPage2
Resource9=IDD_INPUT
Class14=CAlarmDlg
Class15=CSplashWnd
Resource10=IDD_ALARMOPTION
Resource11=IDR_FUTURE
Class16=CMyPropertySheet
Class17=CMyPropertyPage1
Resource12=IDD_MOVIEPLAY
Resource13=IDR_LINKBAR

[CLS:CBrowserApp]
Type=0
HeaderFile=Browser.h
ImplementationFile=Browser.cpp
Filter=N
LastObject=CBrowserApp

[CLS:CBrowserDoc]
Type=0
HeaderFile=BrowserDoc.h
ImplementationFile=BrowserDoc.cpp
Filter=N
LastObject=IDD_OMOK_ABOUTBOX
BaseClass=CDocument
VirtualFilter=DC

[CLS:CBrowserView]
Type=0
HeaderFile=BrowserView.h
ImplementationFile=BrowserView.cpp
Filter=C
LastObject=CBrowserView
BaseClass=CHtmlView
VirtualFilter=7VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_STRETCHIMAGE



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
LastObject=CLeftView
BaseClass=CTreeView
VirtualFilter=VWC

[CLS:CAboutDlg]
Type=0
HeaderFile=Browser.cpp
ImplementationFile=Browser.cpp
Filter=D
LastObject=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_BACK
Command6=ID_NEXT
Command7=ID_HOME
Command8=ID_STOP
Command9=ID_FRESH
Command10=ID_MENU_VIEWER
Command11=ID_CLEARLEFTVIEW
Command12=ID_AVI
Command13=ID_ALLFTP
Command14=ID_FULLSCREEN
Command15=ID_TRAY_ICON
Command16=ID_GAMEMENU
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_ADDFAVORITE
Command20=ID_SEJONGSITE
Command21=ID_INTERFACESITE
Command22=ID_DAUMSITE
Command23=ID_OPTION
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_FULLSCREEN
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDR_MAINFRAME]
Type=1
Class=CUrlDlg
ControlCount=1
Control1=IDC_COMBOURL,combobox,1344340290

[CLS:CUrlDlg]
Type=0
HeaderFile=UrlDlg.h
ImplementationFile=UrlDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUrlDlg

[MNU:IDR_CONTEXTGRAPHIC]
Type=1
Class=?
Command1=ID_MENU_VIEWER_INSPLIT
Command2=ID_CLEAR
Command3=ID_WINDOW_SPLIT
Command4=ID_STRETCHIMAGE
Command5=ID_MENU_VIEWER_INSPLIT
Command6=ID_WINDOW_SPLIT
CommandCount=6

[DLG:IDD_MOVIEPLAY]
Type=1
Class=CMoveDialog
ControlCount=7
Control1=IDC_ENDDIALOG,button,1342242816
Control2=IDC_PLAY,button,1342242817
Control3=IDC_END,button,1342242816
Control4=IDC_PAUSE,button,1342242816
Control5=IDC_VIDEO,static,1342177287
Control6=IDFILELOAD,button,1342242817
Control7=IDC_PLAYSLIDER,msctls_trackbar32,1342242825

[CLS:CMoveDialog]
Type=0
HeaderFile=MoveDialog.h
ImplementationFile=MoveDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMoveDialog
VirtualFilter=dWC

[MNU:IDR_FUTURE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
Command16=ID_BACK
Command17=ID_NEXT
Command18=ID_HOME
Command19=ID_STOP
Command20=ID_FRESH
Command21=ID_MENU_VIEWER
Command22=ID_CLEARLEFTVIEW
Command23=ID_AVI
Command24=ID_FULLSCREEN
CommandCount=24

[TB:IDR_LINKBAR]
Type=1
Class=?
Command1=ID_SEARCHSITE
Command2=ID_FAVORITESITE
Command3=ID_INTERFACESITE
CommandCount=3

[MNU:IDR_LINKMENU]
Type=1
Class=CMainFrame
Command1=ID_SEARCH_DAUM
Command2=ID_SEARCH_NAVER
Command3=ID_SEARCH_EMPAS
Command4=ID_SEARCH_GOOGLE
Command5=ID_SEARCH_ALTAVISTA
Command6=ID_SEARCH_LYCOS
Command7=ID_SEARCH_MSN
Command8=ID_SEARCH_YAHOO
Command9=ID_SEARCH_CHOL
Command10=ID_SEARCH_DREAMWIZ
Command11=ID_SEARCH_HANMIR
Command12=ID_SEJONGSITE
Command13=ID_INTERFACESITE
Command14=ID_DAUMSITE
CommandCount=14

[DLG:IDD_FTP]
Type=1
Class=CFTPDlg
ControlCount=15
Control1=IDC_ADDRESS_STATIC,static,1342312448
Control2=IDC_ADDRESS_COMBOBOX,combobox,1344340226
Control3=IDC_USER_STATIC,static,1342312448
Control4=IDC_NAME_COMBOBOX,combobox,1344340226
Control5=IDC_STATIC,static,1342312448
Control6=IDC_PASSWORD_EDIT,edit,1350631584
Control7=IDC_CONNECT_BUTTON,button,1342242817
Control8=IDC_FILE_LIST_STATIC,static,1342312448
Control9=IDC_FILELIST_LISTBOX,listbox,1352729857
Control10=IDC_UPLOAD_BUTTON,button,1342242827
Control11=IDC_LOCALLIST_STATIC,static,1342312448
Control12=IDC_LOCALLIST_LISTBOX,listbox,1352729857
Control13=IDC_DOWNLOAD_BUTTON,button,1342242827
Control14=IDC_MANAGEADDRESS_LIST,listbox,1352728835
Control15=IDC_BUTTONHELP,button,1342251008

[CLS:CLocalListBox]
Type=0
HeaderFile=mylistbox.h
ImplementationFile=mylistbox.cpp
BaseClass=CListBox
LastObject=CLocalListBox

[CLS:CServerListBox]
Type=0
HeaderFile=mylistbox.h
ImplementationFile=mylistbox.cpp
BaseClass=CListBox
LastObject=CServerListBox
Filter=W
VirtualFilter=bWC

[DLG:IDD_INPUT]
Type=1
Class=CInputDialog
ControlCount=4
Control1=IDC_INPUTNAME_STATIC,static,1342308352
Control2=IDC_INPUTNAME_EDIT,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CInputDialog]
Type=0
HeaderFile=InputDialog.h
ImplementationFile=InputDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputDialog
VirtualFilter=dWC

[CLS:CFTPDlg]
Type=0
HeaderFile=FTPDlg.h
ImplementationFile=FTPDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTONHELP
VirtualFilter=dWC

[DLG:IDD_ALARMOPTION]
Type=1
Class=CAlarmDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HOUR,static,1342308352
Control5=IDC_MINUTE,static,1342308352
Control6=IDC_HOUREDIT,edit,1350633600
Control7=IDC_SPINHOUR,msctls_updown32,1342177331
Control8=IDC_MINUTEEDIT,edit,1350633600
Control9=IDC_SPINMINUTE,msctls_updown32,1342177331
Control10=IDC_ALARMCHECK,button,1342242819
Control11=IDC_SETALARMMUSIC,button,1342242816

[CLS:CAlarmDlg]
Type=0
HeaderFile=AlarmDlg.h
ImplementationFile=AlarmDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SETALARMMUSIC
VirtualFilter=dWC

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
LastObject=CSplashWnd

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATICHELP3,static,1342308352
Control6=IDC_STATICHELP,static,1342308352
Control7=IDC_STATICHELP2,static,1342308352
Control8=IDC_STATICHELP4,static,1342308352
Control9=IDC_STATICHELP5,static,1342308352
Control10=IDC_STATICHELP6,static,1342308352
Control11=IDC_STATICHELP7,static,1342308352
Control12=IDC_STATICHELP8,static,1342308352

[CLS:CMyPropertySheet]
Type=0
HeaderFile=MyPropertySheet.h
ImplementationFile=MyPropertySheet.cpp
BaseClass=CPropertySheet

[CLS:CMyPropertyPage1]
Type=0
HeaderFile=MyPropertyPage1.h
ImplementationFile=MyPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CMyPropertyPage1

[CLS:CMyPropertyPage2]
Type=0
HeaderFile=MyPropertyPage1.h
ImplementationFile=MyPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=ID_WINDOW_SPLIT

[MNU:IDR_GAMEMENU]
Type=1
Class=?
Command1=ID_GAME_OMOK
CommandCount=1

[DLG:IDD_SETHOMEPAGE_PROPERTY]
Type=1
Class=CMyPropertyPage2
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SETHOMEPAGE_EDIT,edit,1350631552

[DLG:IDD_SETALARM_PROPERTY]
Type=1
Class=CMyPropertyPage1
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_HOUR,static,1342308352
Control3=IDC_MINUTE,static,1342308352
Control4=IDC_HOUREDIT,edit,1350641792
Control5=IDC_SPINHOUR,msctls_updown32,1342177339
Control6=IDC_MINUTEEDIT,edit,1350641792
Control7=IDC_SPINMINUTE,msctls_updown32,1342177339
Control8=IDC_ALARMCHECK,button,1342242819
Control9=IDC_SETALARMMUSIC,button,1342242816

