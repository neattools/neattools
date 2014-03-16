# Microsoft Developer Studio Project File - Name="neat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=neat - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "neat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "neat.mak" CFG="neat - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "neat - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "neat - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "neat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "_NEAT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\neat.dll"

!ELSEIF  "$(CFG)" == "neat - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "neat___Win32_Debug"
# PROP BASE Intermediate_Dir "neat___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "neat___Win32_Debug"
# PROP Intermediate_Dir "neat___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "_NEAT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /D "_NEAT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\neat.dll"
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"..\neat.dll"

!ENDIF 

# Begin Target

# Name "neat - Win32 Release"
# Name "neat - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\NEAT\JAbout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JAddObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JANDObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JBlockData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JBytesData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JColorData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JColorProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JComplexData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JCVideoData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JCWaveData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JDataType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JDateData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JDoubleProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JFDimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JFileProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JFocusSet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JFPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JFRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JGuideObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JIntegerData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JIntegerListProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JIntegerProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JLineObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JLinkObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JMIDIData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JModuleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JModuleCanvas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JModuleObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JPropertyBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JRealData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JRealProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Neat\JScrambledStringProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JStringData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JStringProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JVideoData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JViewObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JViewSet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NEAT\JWaveData.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\neat\JAbout.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JAddObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JANDObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JBlockData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JBytesData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JColorData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JColorProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JComplexData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JCVideoData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JCWaveData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JDateData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JDoubleProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JFDimension.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JFileProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JFocusSet.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JFPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JFRect.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JGuideObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JIntegerData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JIntegerListProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JIntegerProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JLineObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JLinkObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JMIDIData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JModuleButton.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JModuleCanvas.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JModuleObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JNEAT.hpp
# End Source File
# Begin Source File

SOURCE=..\..\neat\JProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JPropertyBox.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JRealData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JRealProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JScrambledStringProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JStringData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JStringProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JVideoData.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JViewObj.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JViewSet.h
# End Source File
# Begin Source File

SOURCE=..\..\neat\JWaveData.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
