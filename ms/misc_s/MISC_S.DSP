# Microsoft Developer Studio Project File - Name="misc_s" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=misc_s - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "misc_s.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "misc_s.mak" CFG="misc_s - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "misc_s - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "misc_s - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "misc_s - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "misc_s - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "misc_s___Win32_Debug"
# PROP BASE Intermediate_Dir "misc_s___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "misc_s___Win32_Debug"
# PROP Intermediate_Dir "misc_s___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "misc_s - Win32 Release"
# Name "misc_s - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\modules\JBAddObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBDelObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBInsObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBLenObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBPosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBSubObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtoIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtoSObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDGreaterEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDGreaterThanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDtoRObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoBObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoRObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoSObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoDObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSAddObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSDelObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSGreaterEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSGreaterThanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSInsObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSKeyboardObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSLenObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSLowerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSPosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSSubObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStoBObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStoIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSUpperObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=..\..\modules\JBSubObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtoIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtoSObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDGreaterEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDGreaterThanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDNotEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDtoRObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoBObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoRObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoSObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoDObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSAddObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSDelObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSGreaterEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSGreaterThanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSKeyboardObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSLowerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSNotEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSSubObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStoBObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStoIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSubtractObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSUpperObj.h
# End Source File
# End Group
# End Target
# End Project
