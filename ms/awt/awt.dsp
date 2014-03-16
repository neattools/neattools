# Microsoft Developer Studio Project File - Name="awt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=awt - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "awt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "awt.mak" CFG="awt - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "awt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "awt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "awt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\awt___Wi"
# PROP BASE Intermediate_Dir ".\awt___Wi"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "_AWT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\awt.dll"
# SUBTRACT LINK32 /map /debug

!ELSEIF  "$(CFG)" == "awt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "awt___Win32_Debug"
# PROP BASE Intermediate_Dir "awt___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "awt___Win32_Debug"
# PROP Intermediate_Dir "awt___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "_AWT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "_AWT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_WIN32_WCE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\awt.dll"
# SUBTRACT BASE LINK32 /map /debug
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"..\awt.dll"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "awt - Win32 Release"
# Name "awt - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\AWT\JBorderLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JCanvas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JClipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JColorBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JDimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JFileBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JFlowLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JFontMetrics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JGraphics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JGridLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JInputBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JInsets.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JIntegerBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JIntegerListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JModal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JPanel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JPushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JRuler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JScroller.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JTextField.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JThumb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JTriangleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\AWT\JWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\awt\JAWT.hpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JBorderLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JButton.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JCanvas.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JClipboard.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JColor.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JColorBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JDimension.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFileBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFlowLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFont.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFontMetrics.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JGraphics.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JGridLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JImage.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JInputBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JInsets.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JIntegerBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JIntegerListBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JLabel.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JLayoutManager.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JListBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JMessageBox.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JModal.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPushButton.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRect.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRegion.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRuler.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JScroller.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JSeparator.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JTextField.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JThumb.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JToggleButton.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JTriangleButton.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\awt\JWindow.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
