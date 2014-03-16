# Microsoft Developer Studio Project File - Name="base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=base - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "base.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "base.mak" CFG="base - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "base - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "base - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "base - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "_BASE_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\base.dll"

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "base___Win32_Debug"
# PROP BASE Intermediate_Dir "base___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "base___Win32_Debug"
# PROP Intermediate_Dir "base___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "_BASE_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "_BASE_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\base.dll"
# ADD LINK32 user32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"..\base.dll"

!ENDIF 

# Begin Target

# Name "base - Win32 Release"
# Name "base - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\lang\bcomplex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JArithmeticException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JAssociation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JBlockInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JBlockOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JBoolean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JBufferedInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JBufferedOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JCharacter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JClassReferenceException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JComplex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JCriticalSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JDataBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JDictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JDList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JDouble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JEOFException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JFileArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFileInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFileIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFileOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFilterInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JFilterOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JFloat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JHashTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JIllegalArgumentException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JInetAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JInterruptedIOException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JIOException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JLong.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JMath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JNullPointerException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JObjectPtr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\IO\JPipedStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JPObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JProcessCreateException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\UTIL\JRandom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JReference.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JRuntimeException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JSocketException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JSocketInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JSocketOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JThreadCreateException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JThrowable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NET\JUnknownHostException.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\lang\bcomplex.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JArithmeticException.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JArray.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JAssociation.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JBase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JBlock.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JBlockInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JBlockOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JBoolean.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JBufferedInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JBufferedOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JCharacter.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JClassReferenceException.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JComplex.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JCriticalSection.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDataBase.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDate.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JDescriptor.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDictionary.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDList.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JDouble.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JEOFException.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JError.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JException.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFile.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFile.hpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JFileArray.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileIOStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFilterInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JFilterOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JFloat.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JHashTable.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JIllegalArgumentException.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JInetAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JInteger.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JInterruptedIOException.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JIOException.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JList.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JLong.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JMath.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JNullPointerException.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JObject.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JObjectPtr.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\io\JPipedStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JPObject.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JProcessCreateException.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JRandom.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JReference.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JRunable.hpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JRuntimeException.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocket.hpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketException.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JString.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JSystem.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThread.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThreadCreateException.h
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThrowable.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JUnknownHostException.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
