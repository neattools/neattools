# Microsoft Developer Studio Project File - Name="msdebug" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=msdebug - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "msdebug.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "msdebug.mak" CFG="msdebug - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "msdebug - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "msdebug - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "msdebug - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /I "..\lang" /I "..\util" /I "..\io" /I "..\net" /I "..\awt" /I "..\neat" /I "..\modules" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 user32.lib winmm.lib gdi32.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"oopw.exe"

!ELSEIF  "$(CFG)" == "msdebug - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msdebug___Win32_Debug"
# PROP BASE Intermediate_Dir "msdebug___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msdebug___Win32_Debug"
# PROP Intermediate_Dir "msdebug___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /I "..\lang" /I "..\util" /I "..\io" /I "..\net" /I "..\awt" /I "..\neat" /I "..\modules" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\lang" /I "..\util" /I "..\io" /I "..\net" /I "..\awt" /I "..\neat" /I "..\modules" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_LIB" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib winmm.lib gdi32.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"oopw.exe"
# ADD LINK32 user32.lib winmm.lib gdi32.lib wsock32.lib /nologo /subsystem:windows /incremental:yes /debug /machine:I386 /out:"oopw.exe"

!ENDIF 

# Begin Target

# Name "msdebug - Win32 Release"
# Name "msdebug - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;rc"
# Begin Source File

SOURCE=..\mainw\JNeatTool.cpp
# End Source File
# Begin Source File

SOURCE=..\mainw\JView.cpp
# End Source File
# Begin Source File

SOURCE=..\mainw\JView2.cpp
# End Source File
# Begin Source File

SOURCE=..\oopw.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=..\mainw\JNeatTool.h
# End Source File
# Begin Source File

SOURCE=..\mainw\JView.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\cursor1.cur
# End Source File
# Begin Source File

SOURCE=..\oopw.ico
# End Source File
# End Target
# End Project
