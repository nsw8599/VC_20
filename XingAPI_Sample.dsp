# Microsoft Developer Studio Project File - Name="XingAPI_Sample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XingAPI_Sample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XingAPI_Sample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XingAPI_Sample.mak" CFG="XingAPI_Sample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XingAPI_Sample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XingAPI_Sample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XingAPI_Sample - Win32 Release"

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
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XingAPI_Sample - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XingAPI_Sample - Win32 Release"
# Name "XingAPI_Sample - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExcludeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TRBar.cpp
# End Source File
# Begin Source File

SOURCE=.\XingAPI_Sample.cpp
# End Source File
# Begin Source File

SOURCE=.\XingAPI_Sample.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\DlgExcludeItem.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRBar.h
# End Source File
# Begin Source File

SOURCE=.\IXingAPI.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRBar.h
# End Source File
# Begin Source File

SOURCE=.\XingAPI_Sample.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\XingAPI_Sample.ico
# End Source File
# Begin Source File

SOURCE=.\res\XingAPI_Sample.rc2
# End Source File
# End Group
# Begin Group "Login"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.h
# End Source File
# End Group
# Begin Group "TR"

# PROP Default_Filter ""
# Begin Group "주식"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_CSPAQ02200.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAQ02200.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAQ02300.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAQ02300.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAQ03700.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAQ03700.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00600.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00600.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00700.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00700.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00800.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPAT00800.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPBQ00200.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CSPBQ00200.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_H1_.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_H1_.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_H2_.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_H2_.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_h2_ELW.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_h2_ELW.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_h3_ELW.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_h3_ELW.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC0.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC0.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC1.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC1.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC2.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC3.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC4.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SC4.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1101.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1101.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1301.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1301.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1305.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1305.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1452.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1452.h
# End Source File
# End Group
# Begin Group "선물옵션"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_CFOAQ00600.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAQ00600.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00100.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00100.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00200.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00200.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00300.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOAT00300.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOFQ02400.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CFOFQ02400.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_FC0.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_FC0.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_JC0.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_JC0.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1601.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t1601.h
# End Source File
# End Group
# Begin Group "업종"

# PROP Default_Filter ""
# End Group
# Begin Group "투자자"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_BM_.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_BM_.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_BMT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_BMT.h
# End Source File
# End Group
# Begin Group "프로그램"

# PROP Default_Filter ""
# End Group
# Begin Group "투자정보"

# PROP Default_Filter ""
# End Group
# Begin Group "차트"

# PROP Default_Filter ""
# End Group
# Begin Group "기타"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_t9942.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t9942.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t9943.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t9943.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_t9944.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_t9944.h
# End Source File
# End Group
# Begin Group "선물 CME"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_CCEAT00100.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CCEAT00100.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CCEAT00200.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CCEAT00200.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CCEAT00300.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CCEAT00300.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
