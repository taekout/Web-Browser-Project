# Microsoft Developer Studio Project File - Name="Browser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Browser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Browser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Browser.mak" CFG="Browser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Browser - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Browser - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Browser - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /compile_only /include:"Release/" /nologo /warn:nofileopt /winapp
# ADD F90 /compile_only /include:"Release/" /nologo /warn:nofileopt /winapp
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Browser - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /check:bounds /compile_only /debug:full /include:"Debug/" /nologo /traceback /warn:argument_checking /warn:nofileopt /winapp
# ADD F90 /browser /check:bounds /compile_only /debug:full /include:"Debug/" /nologo /traceback /warn:argument_checking /warn:nofileopt /winapp
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Browser - Win32 Release"
# Name "Browser - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Group "AVI_CPP"

# PROP Default_Filter "Media Player"
# Begin Source File

SOURCE=.\Avi.cpp
# End Source File
# End Group
# Begin Group "Picture_CPP"

# PROP Default_Filter "Graphics File Info Class"
# Begin Source File

SOURCE=.\BaseBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseImage.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseJPG.cpp
# End Source File
# Begin Source File

SOURCE=.\Gif.cpp
# End Source File
# Begin Source File

SOURCE=.\Jpeg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AlarmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Browser.cpp
# End Source File
# Begin Source File

SOURCE=.\Browser.rc
# End Source File
# Begin Source File

SOURCE=.\BrowserDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserView.cpp
# End Source File
# Begin Source File

SOURCE=.\FTPDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPropertyPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UrlDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "AVI_H"

# PROP Default_Filter "Media Player"
# Begin Source File

SOURCE=.\Avi.h
# End Source File
# End Group
# Begin Group "Picture_H"

# PROP Default_Filter "Graphics File Info Class"
# Begin Source File

SOURCE=.\BaseBitmap.h
# End Source File
# Begin Source File

SOURCE=.\BaseImage.h
# End Source File
# Begin Source File

SOURCE=.\BaseJPG.h
# End Source File
# Begin Source File

SOURCE=.\Gif.h
# End Source File
# Begin Source File

SOURCE=.\Jpeg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AlarmDlg.h
# End Source File
# Begin Source File

SOURCE=.\Browser.h
# End Source File
# Begin Source File

SOURCE=.\BrowserDoc.h
# End Source File
# Begin Source File

SOURCE=.\BrowserView.h
# End Source File
# Begin Source File

SOURCE=.\FTPDlg.h
# End Source File
# Begin Source File

SOURCE=.\InputDialog.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MoveDialog.h
# End Source File
# Begin Source File

SOURCE=.\mylistbox.h
# End Source File
# Begin Source File

SOURCE=.\MyPropertyPage1.h
# End Source File
# Begin Source File

SOURCE=.\MyPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UrlDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\_Splash1.bmp
# End Source File
# Begin Source File

SOURCE=.\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Browser.ico
# End Source File
# Begin Source File

SOURCE=.\res\Browser.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BrowserDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\linkbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splash1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splash2.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar16bit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=".\Project ����.doc"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\res\�ֱ���.wav"
# End Source File
# End Target
# End Project
# Section Browser : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
