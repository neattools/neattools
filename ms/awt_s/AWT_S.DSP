# Microsoft Developer Studio Project File - Name="awt_s" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AWT_S - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "awt_s.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "awt_s.mak" CFG="AWT_S - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "awt_s - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "awt_s - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "awt_s - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /D "_AWT_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "awt_s - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "awt_s___Win32_Debug"
# PROP BASE Intermediate_Dir "awt_s___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "awt_s___Win32_Debug"
# PROP Intermediate_Dir "awt_s___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /D "_AWT_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /ZI /Od /I "..\..\lang" /I "..\..\util" /I "..\..\io" /I "..\..\net" /I "..\..\filter" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_LIB" /D "_AWT_LIB" /YX /FD /c
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

# Name "awt_s - Win32 Release"
# Name "awt_s - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\awt\JBorderLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JCanvas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JClipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JColorBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JDimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFileBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFlowLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JFontMetrics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JGraphics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JGridLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JInputBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JInsets.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JIntegerBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JIntegerListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JModal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPanel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JPushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JRuler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JScroller.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JTextField.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JThumb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JTriangleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\awt\JWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
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
# End Group
# End Target
# End Project
