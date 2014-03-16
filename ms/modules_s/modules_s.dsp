# Microsoft Developer Studio Project File - Name="modules_s" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MODULES_S - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules_s.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules_s.mak" CFG="MODULES_S - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules_s - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules_s - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules_s - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /I "..\..\filter" /D "_MODULES_LIB" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules_s - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "modules_s___Win32_Debug"
# PROP BASE Intermediate_Dir "modules_s___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "modules_s___Win32_Debug"
# PROP Intermediate_Dir "modules_s___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /I "..\..\filter" /D "_MODULES_LIB" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\awt" /I "..\..\util" /I "..\..\io" /I "..\..\neat" /I "..\..\net" /I "..\..\filter" /D "_MODULES_LIB" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
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

# Name "modules_s - Win32 Release"
# Name "modules_s - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\modules\int64.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DMeterObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DSliderObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DViewerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\J2DMeterObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\J2DSliderObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAccumulatorObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAudioCodecObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAvgFilterObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBenchmarkObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBMPFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBytesObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCalibrateObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCHObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JClockDividerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JColorObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCOMObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JComplexObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JControlObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JConvertObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDataBaseObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDateObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDaviconObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDecoderObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDelayObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDelaySustainObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDeMultiplexerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEncoderObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JExclusiveObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEXEFileObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JFocusObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JG723.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JHPCounterObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JIntegerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoWObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JJoyStickObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JKeyboardObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLabelObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLEDObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLPTObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIChannelObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIFileObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIInObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIOutObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMixerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMouseBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMouseObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMousePosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMultiplexerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNBitsObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNodeObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNOTObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNTLFileObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JORObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JOxfordObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPulseObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPushBtnObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRealComplexObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRealObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRecorderObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMIDFileObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSampleObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JServerSocketObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSocketObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStateObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSwitchObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTailObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTimeObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTimerObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNG3Obj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNG4Obj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNGObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveFileObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveInObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveOutObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWtoIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JXORObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=..\..\modules\int64.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DMeterObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DSliderObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\J1DViewerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\J2DMeterObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\J2DSliderObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAccumulatorObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAudioCodecObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JAvgFilterObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBenchmarkObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBMPFile.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JBtnObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCalibrateObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCHObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JClockDividerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JColorObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCOMObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JComplexObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JControlObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JConvertObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDataBaseObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDateObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDaviconObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDecoderObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDelayObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDelaySustainObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDeMultiplexerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEncoderObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JExclusiveObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEXEFileObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JFocusObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JG723.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JHPCounterObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JIntegerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JItoWObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JJoyStickObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JKeyboardObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLabelObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLEDObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JLPTObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIChannelObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIFileObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIInObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMIDIOutObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMixerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMouseBtnObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMouseObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMousePosObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMultiplexerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNBitsObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNodeObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNOTObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNTLFileObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JORObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JOxfordObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPulseObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPushBtnObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRealComplexObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRealObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRecorderObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMIDFileObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSampleObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JServerSocketObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSocketObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JStateObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSwitchObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTailObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTimeObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTimerObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNG3Obj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNG4Obj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JTNGObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveFileObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveInObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWaveOutObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JWtoIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JXORObj.h
# End Source File
# End Group
# End Target
# End Project
