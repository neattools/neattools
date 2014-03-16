# Microsoft Developer Studio Project File - Name="base_s" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BASE_S - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "base_s.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "base_s.mak" CFG="BASE_S - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "base_s - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "base_s - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "base_s - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "base_s - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "base_s___Win32_Debug"
# PROP BASE Intermediate_Dir "base_s___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "base_s___Win32_Debug"
# PROP Intermediate_Dir "base_s___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /YX /FD /c
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

# Name "base_s - Win32 Release"
# Name "base_s - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\lang\bcomplex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JArithmeticException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JAssociation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JBlockInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JBlockOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JBoolean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JBufferedInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JBufferedOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JCharacter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JClassReferenceException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\LANG\JComplex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JCriticalSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JDataBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JDictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JDList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JDouble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JEOFException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JFileArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFileOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFilterInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JFilterOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JFloat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JHashTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JIllegalArgumentException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JInetAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JInterruptedIOException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JIOException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JLong.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JMath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JNullPointerException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JObjectPtr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\io\JPipedStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JPObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JProcessCreateException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\JRandom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JReference.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JRuntimeException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocketOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThreadCreateException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\lang\JThrowable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\net\JUnknownHostException.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
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

SOURCE=..\..\lang\JCriticalSection.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDataBase.h
# End Source File
# Begin Source File

SOURCE=..\..\util\JDate.h
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

SOURCE=..\..\lang\JRuntimeException.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\net\JSocket.h
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
# End Target
# End Project
