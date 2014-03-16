# Microsoft Developer Studio Project File - Name="math_s" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=math_s - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "math_s.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "math_s.mak" CFG="math_s - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "math_s - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "math_s - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "math_s - Win32 Release"

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

!ELSEIF  "$(CFG)" == "math_s - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "math_s___Win32_Debug"
# PROP BASE Intermediate_Dir "math_s___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "math_s___Win32_Debug"
# PROP Intermediate_Dir "math_s___Win32_Debug"
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

# Name "math_s - Win32 Release"
# Name "math_s - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\modules\JAbsObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCAddObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCConjObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCCoshObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCCosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCDivideObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCExpObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCMultiplyObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCPolrObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSinhObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSinObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSubtractObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCTanhObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCTanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCtoRObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDivideObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JGreaterEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JGreaterThanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMaxObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMinObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMultiplyObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPolrCObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPowObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAbsObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRACosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAddObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRandomObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRASinObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAtan2Obj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRATanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCalibrateObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCeilObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRDelayObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRDivideObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRemainObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JREObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JREqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRExpObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRFloorObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRGreaterEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRGreaterThanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRLogObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMaxObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMinObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRModObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMultiplyObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRNotEqualObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRPIObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRPowObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRRandomObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRRoundObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRSinObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRSqrtObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRSubtractObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRTanObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoCObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSubtractObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=..\..\modules\JAbsObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCAddObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCConjObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCCoshObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCCosObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCDivideObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCExpObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCMultiplyObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCNotEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCPolrObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSinhObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSinObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCSubtractObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCTanhObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCTanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JCtoRObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JDivideObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JGreaterEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JGreaterThanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMaxObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMinObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JMultiplyObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JNotEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPolrCObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JPowObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAbsObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRACosObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAddObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRandomObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRASinObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRAtan2Obj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRATanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCalibrateObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCeilObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRCosObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRDelayObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRDivideObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRemainObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JREObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JREqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRExpObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRFloorObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRGreaterEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRGreaterThanObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRLogObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMaxObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMinObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRMultiplyObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRNotEqualObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRPIObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRPowObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRRandomObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRSubtractObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JRtoCObj.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\JSubtractObj.h
# End Source File
# End Group
# End Target
# End Project
