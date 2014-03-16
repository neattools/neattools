# Microsoft Developer Studio Project File - Name="magic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MAGIC - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "magic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "magic.mak" CFG="MAGIC - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "magic - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
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
# ADD CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\magic" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AWT_LIB" /D "_BASE_LIB" /YX /FD /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 inv252.lib kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"../magic.exe"
# Begin Target

# Name "magic - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;rc;c"
# Begin Source File

SOURCE=..\..\magic\JAbout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JCharacter3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JMagic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JMaterials.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JRenderArea.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JShapes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JStatus2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JText2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\magic\JText3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\oopw.rc
# End Source File
# Begin Source File

SOURCE=..\..\magic\print.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=..\..\magic\JAbout.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JCamera.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JCharacter3.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JMagic.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JMaterials.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JRenderArea.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JShapes.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JStatus2.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JText2.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\JText3.h
# End Source File
# Begin Source File

SOURCE=..\..\magic\print.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\magic\cursor1.cur
# End Source File
# Begin Source File

SOURCE=..\..\magic\magic.ico
# End Source File
# Begin Source File

SOURCE=..\..\oopw.ico
# End Source File
# End Target
# End Project
