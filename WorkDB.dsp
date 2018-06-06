# Microsoft Developer Studio Project File - Name="WorkDB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WorkDB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WorkDB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WorkDB.mak" CFG="WorkDB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WorkDB - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WorkDB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WorkDB - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WorkDB - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "WorkDB - Win32 Release"
# Name "WorkDB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Attribute.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeType.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BinDBCreator.cpp
# End Source File
# Begin Source File

SOURCE=.\BinDBQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDatumDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDatumIntervallumDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDictAppendDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDictStrongDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataNamesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=.\DictionarySet.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FontCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsVerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintOptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultOptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelDbToBinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SrcDBDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SrcDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StaffDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TXTImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VerifyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkDB.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkDB.rc
# End Source File
# Begin Source File

SOURCE=.\WorkDBDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Attribute.h
# End Source File
# Begin Source File

SOURCE=.\AttributeNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\AttributesSet.h
# End Source File
# Begin Source File

SOURCE=.\AttributeType.h
# End Source File
# Begin Source File

SOURCE=.\AttributeTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\BinDBCreator.h
# End Source File
# Begin Source File

SOURCE=.\BinDBQuery.h
# End Source File
# Begin Source File

SOURCE=.\DataDatumDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataDatumIntervallumDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataDictAppendDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataDictStrongDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataNamesDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataSelDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\Dictionary.h
# End Source File
# Begin Source File

SOURCE=.\DictionarySet.h
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.h
# End Source File
# Begin Source File

SOURCE=.\FontCombo.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsVerDlg.h
# End Source File
# Begin Source File

SOURCE=.\PersonSet.h
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.h
# End Source File
# Begin Source File

SOURCE=.\PrintOptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrintStatus.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\QueryDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResultOptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelDbToBinDlg.h
# End Source File
# Begin Source File

SOURCE=.\SrcDBDlg.h
# End Source File
# Begin Source File

SOURCE=.\SrcDBSet.h
# End Source File
# Begin Source File

SOURCE=.\StaffDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TXTImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\VerifyDlg.h
# End Source File
# Begin Source File

SOURCE=.\WorkDB.h
# End Source File
# Begin Source File

SOURCE=.\WorkDBDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\WorkDB.ico
# End Source File
# Begin Source File

SOURCE=.\res\WorkDB.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\file_dbl.avi
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
