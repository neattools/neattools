# Microsoft Developer Studio Project File - Name="modules" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=modules - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules.mak" CFG="modules - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP BASE Output_Dir ".\modules\Release"
# PROP BASE Intermediate_Dir ".\modules\Release"
# PROP BASE Target_Dir ".\modules"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\modules\Release"
# PROP Intermediate_Dir ".\modules\Release"
# PROP Target_Dir ".\modules"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\awt" /I "..\util" /I "..\io" /I "..\neat" /I "..\net" /I "..\scsi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"modules.dll"
# Begin Target

# Name "modules - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\bc5\oop\modules\J1DMeterObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\J1DSliderObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\J1DViewerObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\J2DMeterObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\J2DSliderObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JAccumulatorObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JAddObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JAvgFilterObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JCalibrateObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JCHObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JClockDividerObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JColorObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JCOMObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JControlObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JConvertObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JDecoderObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JDelayObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JDeMultiplexerObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JDivideObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JEncoderObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JExclusiveObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JFocusObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JGreaterEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JGreaterThanObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JIntegerObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JJoyStickObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JKeyboardObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JLabelObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JLEDObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JLPTObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMaxObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIChannelObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIFileObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIInObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JMIDIOutObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMinObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JMixerObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMouseBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMousePosObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMultiplexerObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JMultiplyObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JNOTObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JORObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JOxfordObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JPulseObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JPushBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JRecorderObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JRemainObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JRMIDFileObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JSampleObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JServerSocketObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JSocketObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JSubtractObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JSwitchObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTimeObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTimerObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JTNG3Obj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTNGObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\Oop\modules\JWaveFileObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JWaveInObj.cpp
# End Source File
# Begin Source File

SOURCE=\Bc5\oop\modules\JWaveOutObj.cpp
# End Source File
# Begin Source File

SOURCE=\bc5\oop\modules\JXORObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
