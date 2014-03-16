# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=oop - Win32 Release
!MESSAGE No configuration specified.  Defaulting to oop - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "oop - Win32 Release" && "$(CFG)" != "oopw - Win32 Release" &&\
 "$(CFG)" != "blackjack - Win32 Release" && "$(CFG)" != "html - Win32 Release"\
 && "$(CFG)" != "count - Win32 Release" && "$(CFG)" != "backup - Win32 Release"\
 && "$(CFG)" != "base - Win32 Release" && "$(CFG)" != "awt - Win32 Release" &&\
 "$(CFG)" != "filter - Win32 Release" && "$(CFG)" != "neat - Win32 Release" &&\
 "$(CFG)" != "modules - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "oop.mak" CFG="oop - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oop - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "oopw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "blackjack - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "html - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "count - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "backup - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "base - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "awt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "filter - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "neat - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "modules - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "modules - Win32 Release"

!IF  "$(CFG)" == "oop - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "base - Win32 Release" "$(OUTDIR)\oop.exe"

CLEAN : 
	-@erase ".\oop.exe"
	-@erase ".\Release\Oop.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /I "..\scsi" /I "scsi" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX"oop" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /I "..\scsi" /I\
 "scsi" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/oop.pch" /YX"oop"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x404 /d "NDEBUG"
# ADD RSC /l 0x404 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/oop.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"oop.exe"
# SUBTRACT LINK32 /pdb:none /map /debug
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/oop.pdb" /machine:I386 /out:"oop.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Oop.obj" \
	".\base\Release\base.lib"

"$(OUTDIR)\oop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "oopw - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "oopw\Release"
# PROP BASE Intermediate_Dir "oopw\Release"
# PROP BASE Target_Dir "oopw"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "oopw\Release"
# PROP Intermediate_Dir "oopw\Release"
# PROP Target_Dir "oopw"
OUTDIR=.\oopw\Release
INTDIR=.\oopw\Release

ALL : "base - Win32 Release" "modules - Win32 Release" "awt - Win32 Release"\
 "neat - Win32 Release" "$(OUTDIR)\oopw.exe"

CLEAN : 
	-@erase ".\oopw.exe"
	-@erase ".\oopw\Release\Oopw.obj"
	-@erase ".\oopw\Release\JView2.obj"
	-@erase ".\oopw\Release\JNeatTool.obj"
	-@erase ".\oopw\Release\JView.obj"
	-@erase ".\oopw\Release\oopw.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /I "..\neat" /I "neat" /I "..\modules" /I "modules" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"oop" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /I "..\neat" /I\
 "neat" /I "..\modules" /I "modules" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/oopw.pch" /YX"oop" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\oopw\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/oopw.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"oopw.bsc"
BSC32_FLAGS=/nologo /o"oopw.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /machine:I386 /out:"oopw.exe"
# SUBTRACT LINK32 /pdb:none /map /debug
LINK32_FLAGS=user32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/oopw.pdb" /machine:I386 /out:"oopw.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Oopw.obj" \
	"$(INTDIR)/JView2.obj" \
	"$(INTDIR)/JNeatTool.obj" \
	"$(INTDIR)/JView.obj" \
	"$(INTDIR)/oopw.res" \
	".\neat\Release\neat.lib" \
	".\awt\Release\awt.lib" \
	".\modules\Release\modules.lib" \
	".\base\Release\base.lib"

"$(OUTDIR)\oopw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "blackjack - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "blackjack\Release"
# PROP BASE Intermediate_Dir "blackjack\Release"
# PROP BASE Target_Dir "blackjack"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "blackjack\Release"
# PROP Intermediate_Dir "blackjack\Release"
# PROP Target_Dir "blackjack"
OUTDIR=.\blackjack\Release
INTDIR=.\blackjack\Release

ALL : "$(OUTDIR)\blackjack.exe"

CLEAN : 
	-@erase ".\blackjack.exe"
	-@erase ".\blackjack\Release\blackjack.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /I "..\net" /I "net" /I "..\awt" /I "awt" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/blackjack.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\blackjack\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/blackjack.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"blackjack.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/blackjack.pdb" /machine:I386 /out:"blackjack.exe" 
LINK32_OBJS= \
	"$(INTDIR)/blackjack.obj"

"$(OUTDIR)\blackjack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "html - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "html\Release"
# PROP BASE Intermediate_Dir "html\Release"
# PROP BASE Target_Dir "html"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "html\Release"
# PROP Intermediate_Dir "html\Release"
# PROP Target_Dir "html"
OUTDIR=.\html\Release
INTDIR=.\html\Release

ALL : "$(OUTDIR)\html.exe"

CLEAN : 
	-@erase ".\html\Release\html.exe"
	-@erase ".\html\Release\html.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/html.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\html\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/html.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/html.pdb" /machine:I386 /out:"$(OUTDIR)/html.exe" 
LINK32_OBJS= \
	"$(INTDIR)/html.obj"

"$(OUTDIR)\html.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "count - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "count\Release"
# PROP BASE Intermediate_Dir "count\Release"
# PROP BASE Target_Dir "count"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "count\Release"
# PROP Intermediate_Dir "count\Release"
# PROP Target_Dir "count"
OUTDIR=.\count\Release
INTDIR=.\count\Release

ALL : "$(OUTDIR)\count.exe"

CLEAN : 
	-@erase ".\count\Release\count.exe"
	-@erase ".\count\Release\count.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/count.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\count\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/count.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/count.pdb" /machine:I386 /out:"$(OUTDIR)/count.exe" 
LINK32_OBJS= \
	"$(INTDIR)/count.obj"

"$(OUTDIR)\count.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "backup - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "backup\Release"
# PROP BASE Intermediate_Dir "backup\Release"
# PROP BASE Target_Dir "backup"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "backup\Release"
# PROP Intermediate_Dir "backup\Release"
# PROP Target_Dir "backup"
OUTDIR=.\backup\Release
INTDIR=.\backup\Release

ALL : "$(OUTDIR)\backup.exe"

CLEAN : 
	-@erase ".\backup\Release\backup.exe"
	-@erase ".\backup\Release\backup.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util" /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "lang" /I "..\util" /I "util"\
 /I "..\io" /I "io" /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/backup.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\backup\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/backup.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/backup.pdb" /machine:I386 /out:"$(OUTDIR)/backup.exe" 
LINK32_OBJS= \
	"$(INTDIR)/backup.obj"

"$(OUTDIR)\backup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "base - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "base\Release"
# PROP BASE Intermediate_Dir "base\Release"
# PROP BASE Target_Dir "base"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "base\Release"
# PROP Intermediate_Dir "base\Release"
# PROP Target_Dir "base"
OUTDIR=.\base\Release
INTDIR=.\base\Release

ALL : "$(OUTDIR)\base.dll"

CLEAN : 
	-@erase ".\base.dll"
	-@erase ".\base\Release\JEOFException.obj"
	-@erase ".\base\Release\JFloat.obj"
	-@erase ".\base\Release\JThread.obj"
	-@erase ".\base\Release\JOutputStream.obj"
	-@erase ".\base\Release\JSocketInputStream.obj"
	-@erase ".\base\Release\JString.obj"
	-@erase ".\base\Release\JFilterOutputStream.obj"
	-@erase ".\base\Release\JDList.obj"
	-@erase ".\base\Release\JProcess.obj"
	-@erase ".\base\Release\JBlock.obj"
	-@erase ".\base\Release\JProcessCreateException.obj"
	-@erase ".\base\Release\JBlockOutputStream.obj"
	-@erase ".\base\Release\JServerSocket.obj"
	-@erase ".\base\Release\JRandom.obj"
	-@erase ".\base\Release\JBlockInputStream.obj"
	-@erase ".\base\Release\JSocketException.obj"
	-@erase ".\base\Release\JPObject.obj"
	-@erase ".\base\Release\JException.obj"
	-@erase ".\base\Release\JObjectPtr.obj"
	-@erase ".\base\Release\JSocket.obj"
	-@erase ".\base\Release\JInputStream.obj"
	-@erase ".\base\Release\JIllegalArgumentException.obj"
	-@erase ".\base\Release\JArray.obj"
	-@erase ".\base\Release\JHashTable.obj"
	-@erase ".\base\Release\JThreadCreateException.obj"
	-@erase ".\base\Release\JThrowable.obj"
	-@erase ".\base\Release\JFile.obj"
	-@erase ".\base\Release\JRuntimeException.obj"
	-@erase ".\base\Release\JBufferedOutputStream.obj"
	-@erase ".\base\Release\JClassReferenceException.obj"
	-@erase ".\base\Release\JDictionary.obj"
	-@erase ".\base\Release\JObject.obj"
	-@erase ".\base\Release\JPipedStream.obj"
	-@erase ".\base\Release\JFileOutputStream.obj"
	-@erase ".\base\Release\JArithmeticException.obj"
	-@erase ".\base\Release\JSystem.obj"
	-@erase ".\base\Release\JDouble.obj"
	-@erase ".\base\Release\JInteger.obj"
	-@erase ".\base\Release\JFileInputStream.obj"
	-@erase ".\base\Release\JAssociation.obj"
	-@erase ".\base\Release\JDescriptor.obj"
	-@erase ".\base\Release\JUnknownHostException.obj"
	-@erase ".\base\Release\JLong.obj"
	-@erase ".\base\Release\JInterruptedIOException.obj"
	-@erase ".\base\Release\JBoolean.obj"
	-@erase ".\base\Release\JNullPointerException.obj"
	-@erase ".\base\Release\JCharacter.obj"
	-@erase ".\base\Release\JCriticalSection.obj"
	-@erase ".\base\Release\JInetAddress.obj"
	-@erase ".\base\Release\JBufferedInputStream.obj"
	-@erase ".\base\Release\JFilterInputStream.obj"
	-@erase ".\base\Release\JIOException.obj"
	-@erase ".\base\Release\JMath.obj"
	-@erase ".\base\Release\JList.obj"
	-@erase ".\base\Release\JReference.obj"
	-@erase ".\base\Release\JSocketOutputStream.obj"
	-@erase ".\base\Release\base.lib"
	-@erase ".\base\Release\base.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\util" /I "..\io" /I "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_DLL" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\util" /I "..\io" /I\
 "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_BASE_DLL"\
 /Fp"$(INTDIR)/base.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\base\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/base.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"base.dll"
LINK32_FLAGS=user32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/base.pdb" /machine:I386 /out:"base.dll"\
 /implib:"$(OUTDIR)/base.lib" 
LINK32_OBJS= \
	"$(INTDIR)/JEOFException.obj" \
	"$(INTDIR)/JFloat.obj" \
	"$(INTDIR)/JThread.obj" \
	"$(INTDIR)/JOutputStream.obj" \
	"$(INTDIR)/JSocketInputStream.obj" \
	"$(INTDIR)/JString.obj" \
	"$(INTDIR)/JFilterOutputStream.obj" \
	"$(INTDIR)/JDList.obj" \
	"$(INTDIR)/JProcess.obj" \
	"$(INTDIR)/JBlock.obj" \
	"$(INTDIR)/JProcessCreateException.obj" \
	"$(INTDIR)/JBlockOutputStream.obj" \
	"$(INTDIR)/JServerSocket.obj" \
	"$(INTDIR)/JRandom.obj" \
	"$(INTDIR)/JBlockInputStream.obj" \
	"$(INTDIR)/JSocketException.obj" \
	"$(INTDIR)/JPObject.obj" \
	"$(INTDIR)/JException.obj" \
	"$(INTDIR)/JObjectPtr.obj" \
	"$(INTDIR)/JSocket.obj" \
	"$(INTDIR)/JInputStream.obj" \
	"$(INTDIR)/JIllegalArgumentException.obj" \
	"$(INTDIR)/JArray.obj" \
	"$(INTDIR)/JHashTable.obj" \
	"$(INTDIR)/JThreadCreateException.obj" \
	"$(INTDIR)/JThrowable.obj" \
	"$(INTDIR)/JFile.obj" \
	"$(INTDIR)/JRuntimeException.obj" \
	"$(INTDIR)/JBufferedOutputStream.obj" \
	"$(INTDIR)/JClassReferenceException.obj" \
	"$(INTDIR)/JDictionary.obj" \
	"$(INTDIR)/JObject.obj" \
	"$(INTDIR)/JPipedStream.obj" \
	"$(INTDIR)/JFileOutputStream.obj" \
	"$(INTDIR)/JArithmeticException.obj" \
	"$(INTDIR)/JSystem.obj" \
	"$(INTDIR)/JDouble.obj" \
	"$(INTDIR)/JInteger.obj" \
	"$(INTDIR)/JFileInputStream.obj" \
	"$(INTDIR)/JAssociation.obj" \
	"$(INTDIR)/JDescriptor.obj" \
	"$(INTDIR)/JUnknownHostException.obj" \
	"$(INTDIR)/JLong.obj" \
	"$(INTDIR)/JInterruptedIOException.obj" \
	"$(INTDIR)/JBoolean.obj" \
	"$(INTDIR)/JNullPointerException.obj" \
	"$(INTDIR)/JCharacter.obj" \
	"$(INTDIR)/JCriticalSection.obj" \
	"$(INTDIR)/JInetAddress.obj" \
	"$(INTDIR)/JBufferedInputStream.obj" \
	"$(INTDIR)/JFilterInputStream.obj" \
	"$(INTDIR)/JIOException.obj" \
	"$(INTDIR)/JMath.obj" \
	"$(INTDIR)/JList.obj" \
	"$(INTDIR)/JReference.obj" \
	"$(INTDIR)/JSocketOutputStream.obj"

"$(OUTDIR)\base.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "awt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "awt\awt___Wi"
# PROP BASE Intermediate_Dir "awt\awt___Wi"
# PROP BASE Target_Dir "awt"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "awt\Release"
# PROP Intermediate_Dir "awt\Release"
# PROP Target_Dir "awt"
OUTDIR=.\awt\Release
INTDIR=.\awt\Release

ALL : "base - Win32 Release" "filter - Win32 Release" "$(OUTDIR)\awt.dll"

CLEAN : 
	-@erase ".\awt.dll"
	-@erase ".\awt\Release\JIntegerBox.obj"
	-@erase ".\awt\Release\JRegion.obj"
	-@erase ".\awt\Release\JFileBox.obj"
	-@erase ".\awt\Release\JInputBox.obj"
	-@erase ".\awt\Release\JToggleButton.obj"
	-@erase ".\awt\Release\JInsets.obj"
	-@erase ".\awt\Release\JTriangleButton.obj"
	-@erase ".\awt\Release\JGridLayout.obj"
	-@erase ".\awt\Release\JDimension.obj"
	-@erase ".\awt\Release\JComponent.obj"
	-@erase ".\awt\Release\JFlowLayout.obj"
	-@erase ".\awt\Release\JDialog.obj"
	-@erase ".\awt\Release\JFont.obj"
	-@erase ".\awt\Release\JLabel.obj"
	-@erase ".\awt\Release\JPoint.obj"
	-@erase ".\awt\Release\JModal.obj"
	-@erase ".\awt\Release\JClipboard.obj"
	-@erase ".\awt\Release\JFontMetrics.obj"
	-@erase ".\awt\Release\JPushButton.obj"
	-@erase ".\awt\Release\JRect.obj"
	-@erase ".\awt\Release\JImage.obj"
	-@erase ".\awt\Release\JIntegerListBox.obj"
	-@erase ".\awt\Release\JThumb.obj"
	-@erase ".\awt\Release\JScroller.obj"
	-@erase ".\awt\Release\JWindow.obj"
	-@erase ".\awt\Release\JSeparator.obj"
	-@erase ".\awt\Release\JMessageBox.obj"
	-@erase ".\awt\Release\JGraphics.obj"
	-@erase ".\awt\Release\JPanel.obj"
	-@erase ".\awt\Release\JCanvas.obj"
	-@erase ".\awt\Release\JLayoutManager.obj"
	-@erase ".\awt\Release\JButton.obj"
	-@erase ".\awt\Release\JRuler.obj"
	-@erase ".\awt\Release\JTextField.obj"
	-@erase ".\awt\Release\JColorBox.obj"
	-@erase ".\awt\Release\JEvent.obj"
	-@erase ".\awt\Release\JBorderLayout.obj"
	-@erase ".\awt\Release\JListBox.obj"
	-@erase ".\awt\Release\JColor.obj"
	-@erase ".\awt\Release\awt.lib"
	-@erase ".\awt\Release\awt.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\util" /I "..\io" /I "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AWT_DLL" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\util" /I "..\io" /I\
 "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AWT_DLL"\
 /Fp"$(INTDIR)/awt.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\awt\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/awt.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"awt.dll"
# SUBTRACT LINK32 /map /debug
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib wsock32.lib\
 winmm.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/awt.pdb" /machine:I386 /out:"awt.dll"\
 /implib:"$(OUTDIR)/awt.lib" 
LINK32_OBJS= \
	"$(INTDIR)/JIntegerBox.obj" \
	"$(INTDIR)/JRegion.obj" \
	"$(INTDIR)/JFileBox.obj" \
	"$(INTDIR)/JInputBox.obj" \
	"$(INTDIR)/JToggleButton.obj" \
	"$(INTDIR)/JInsets.obj" \
	"$(INTDIR)/JTriangleButton.obj" \
	"$(INTDIR)/JGridLayout.obj" \
	"$(INTDIR)/JDimension.obj" \
	"$(INTDIR)/JComponent.obj" \
	"$(INTDIR)/JFlowLayout.obj" \
	"$(INTDIR)/JDialog.obj" \
	"$(INTDIR)/JFont.obj" \
	"$(INTDIR)/JLabel.obj" \
	"$(INTDIR)/JPoint.obj" \
	"$(INTDIR)/JModal.obj" \
	"$(INTDIR)/JClipboard.obj" \
	"$(INTDIR)/JFontMetrics.obj" \
	"$(INTDIR)/JPushButton.obj" \
	"$(INTDIR)/JRect.obj" \
	"$(INTDIR)/JImage.obj" \
	"$(INTDIR)/JIntegerListBox.obj" \
	"$(INTDIR)/JThumb.obj" \
	"$(INTDIR)/JScroller.obj" \
	"$(INTDIR)/JWindow.obj" \
	"$(INTDIR)/JSeparator.obj" \
	"$(INTDIR)/JMessageBox.obj" \
	"$(INTDIR)/JGraphics.obj" \
	"$(INTDIR)/JPanel.obj" \
	"$(INTDIR)/JCanvas.obj" \
	"$(INTDIR)/JLayoutManager.obj" \
	"$(INTDIR)/JButton.obj" \
	"$(INTDIR)/JRuler.obj" \
	"$(INTDIR)/JTextField.obj" \
	"$(INTDIR)/JColorBox.obj" \
	"$(INTDIR)/JEvent.obj" \
	"$(INTDIR)/JBorderLayout.obj" \
	"$(INTDIR)/JListBox.obj" \
	"$(INTDIR)/JColor.obj" \
	".\filter\Release\filter.lib" \
	".\base\Release\base.lib"

"$(OUTDIR)\awt.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "filter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "filter\Release"
# PROP BASE Intermediate_Dir "filter\Release"
# PROP BASE Target_Dir "filter"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "filter\Release"
# PROP Intermediate_Dir "filter\Release"
# PROP Target_Dir "filter"
OUTDIR=.\filter\Release
INTDIR=.\filter\Release

ALL : "$(OUTDIR)\filter.dll"

CLEAN : 
	-@erase ".\filter.dll"
	-@erase ".\filter\Release\Filter.obj"
	-@erase ".\filter\Release\filter.lib"
	-@erase ".\filter\Release\filter.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/filter.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\filter\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/filter.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"filter.dll"
# SUBTRACT LINK32 /map /debug
LINK32_FLAGS=user32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/filter.pdb" /machine:I386 /out:"filter.dll"\
 /implib:"$(OUTDIR)/filter.lib" 
LINK32_OBJS= \
	"$(INTDIR)/Filter.obj"

"$(OUTDIR)\filter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "neat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "neat\Release"
# PROP BASE Intermediate_Dir "neat\Release"
# PROP BASE Target_Dir "neat"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "neat\Release"
# PROP Intermediate_Dir "neat\Release"
# PROP Target_Dir "neat"
OUTDIR=.\neat\Release
INTDIR=.\neat\Release

ALL : "base - Win32 Release" "awt - Win32 Release" "$(OUTDIR)\neat.dll"

CLEAN : 
	-@erase ".\neat.dll"
	-@erase ".\neat\Release\JModuleButton.obj"
	-@erase ".\neat\Release\JProperty.obj"
	-@erase ".\neat\Release\JIntegerListProperty.obj"
	-@erase ".\neat\Release\JGuideObj.obj"
	-@erase ".\neat\Release\JFocusSet.obj"
	-@erase ".\neat\Release\JPropertyBox.obj"
	-@erase ".\neat\Release\JIntegerProperty.obj"
	-@erase ".\neat\Release\JFRect.obj"
	-@erase ".\neat\Release\JANDObj.obj"
	-@erase ".\neat\Release\JFileProperty.obj"
	-@erase ".\neat\Release\JModuleObj.obj"
	-@erase ".\neat\Release\JViewObj.obj"
	-@erase ".\neat\Release\JLineObj.obj"
	-@erase ".\neat\Release\JStringProperty.obj"
	-@erase ".\neat\Release\JFDimension.obj"
	-@erase ".\neat\Release\JAbout.obj"
	-@erase ".\neat\Release\JModuleCanvas.obj"
	-@erase ".\neat\Release\JFPoint.obj"
	-@erase ".\neat\Release\JLinkObj.obj"
	-@erase ".\neat\Release\JViewSet.obj"
	-@erase ".\neat\Release\JColorProperty.obj"
	-@erase ".\neat\Release\neat.lib"
	-@erase ".\neat\Release\neat.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\awt" /I "..\util" /I "..\io" /I "..\neat" /I "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_NEAT_DLL" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\awt" /I "..\util" /I\
 "..\io" /I "..\neat" /I "..\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_NEAT_DLL" /Fp"$(INTDIR)/neat.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\neat\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/neat.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"neat.dll"
LINK32_FLAGS=user32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/neat.pdb" /machine:I386 /out:"neat.dll"\
 /implib:"$(OUTDIR)/neat.lib" 
LINK32_OBJS= \
	"$(INTDIR)/JModuleButton.obj" \
	"$(INTDIR)/JProperty.obj" \
	"$(INTDIR)/JIntegerListProperty.obj" \
	"$(INTDIR)/JGuideObj.obj" \
	"$(INTDIR)/JFocusSet.obj" \
	"$(INTDIR)/JPropertyBox.obj" \
	"$(INTDIR)/JIntegerProperty.obj" \
	"$(INTDIR)/JFRect.obj" \
	"$(INTDIR)/JANDObj.obj" \
	"$(INTDIR)/JFileProperty.obj" \
	"$(INTDIR)/JModuleObj.obj" \
	"$(INTDIR)/JViewObj.obj" \
	"$(INTDIR)/JLineObj.obj" \
	"$(INTDIR)/JStringProperty.obj" \
	"$(INTDIR)/JFDimension.obj" \
	"$(INTDIR)/JAbout.obj" \
	"$(INTDIR)/JModuleCanvas.obj" \
	"$(INTDIR)/JFPoint.obj" \
	"$(INTDIR)/JLinkObj.obj" \
	"$(INTDIR)/JViewSet.obj" \
	"$(INTDIR)/JColorProperty.obj" \
	".\awt\Release\awt.lib" \
	".\base\Release\base.lib"

"$(OUTDIR)\neat.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "modules - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "modules\Release"
# PROP BASE Intermediate_Dir "modules\Release"
# PROP BASE Target_Dir "modules"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "modules\Release"
# PROP Intermediate_Dir "modules\Release"
# PROP Target_Dir "modules"
OUTDIR=.\modules\Release
INTDIR=.\modules\Release

ALL : "base - Win32 Release" "neat - Win32 Release" "awt - Win32 Release"\
 "$(OUTDIR)\modules.dll"

CLEAN : 
	-@erase ".\modules.dll"
	-@erase ".\modules\Release\JDelayObj.obj"
	-@erase ".\modules\Release\JGreaterThanObj.obj"
	-@erase ".\modules\Release\JDecoderObj.obj"
	-@erase ".\modules\Release\JAccumulatorObj.obj"
	-@erase ".\modules\Release\JExclusiveObj.obj"
	-@erase ".\modules\Release\JBtnObj.obj"
	-@erase ".\modules\Release\JJoyStickObj.obj"
	-@erase ".\modules\Release\JDeMultiplexerObj.obj"
	-@erase ".\modules\Release\JORObj.obj"
	-@erase ".\modules\Release\JTimeObj.obj"
	-@erase ".\modules\Release\JMultiplyObj.obj"
	-@erase ".\modules\Release\JCOMObj.obj"
	-@erase ".\modules\Release\JMIDIInObj.obj"
	-@erase ".\modules\Release\JMousePosObj.obj"
	-@erase ".\modules\Release\JAvgFilterObj.obj"
	-@erase ".\modules\Release\JWaveOutObj.obj"
	-@erase ".\modules\Release\JGreaterEqualObj.obj"
	-@erase ".\modules\Release\JEncoderObj.obj"
	-@erase ".\modules\Release\J2DSliderObj.obj"
	-@erase ".\modules\Release\JSubtractObj.obj"
	-@erase ".\modules\Release\J2DMeterObj.obj"
	-@erase ".\modules\Release\JOxfordObj.obj"
	-@erase ".\modules\Release\JRMIDFileObj.obj"
	-@erase ".\modules\Release\JEqualObj.obj"
	-@erase ".\modules\Release\JDivideObj.obj"
	-@erase ".\modules\Release\JSocketObj.obj"
	-@erase ".\modules\Release\JMIDIObj.obj"
	-@erase ".\modules\Release\JPushBtnObj.obj"
	-@erase ".\modules\Release\JCHObj.obj"
	-@erase ".\modules\Release\JTimerObj.obj"
	-@erase ".\modules\Release\JConvertObj.obj"
	-@erase ".\modules\Release\JKeyboardObj.obj"
	-@erase ".\modules\Release\JRemainObj.obj"
	-@erase ".\modules\Release\JNOTObj.obj"
	-@erase ".\modules\Release\JMultiplexerObj.obj"
	-@erase ".\modules\Release\J1DMeterObj.obj"
	-@erase ".\modules\Release\JCalibrateObj.obj"
	-@erase ".\modules\Release\JLEDObj.obj"
	-@erase ".\modules\Release\JIntegerObj.obj"
	-@erase ".\modules\Release\JXORObj.obj"
	-@erase ".\modules\Release\JControlObj.obj"
	-@erase ".\modules\Release\JRecorderObj.obj"
	-@erase ".\modules\Release\JSwitchObj.obj"
	-@erase ".\modules\Release\JClockDividerObj.obj"
	-@erase ".\modules\Release\JMinObj.obj"
	-@erase ".\modules\Release\JServerSocketObj.obj"
	-@erase ".\modules\Release\JMixerObj.obj"
	-@erase ".\modules\Release\JColorObj.obj"
	-@erase ".\modules\Release\JLPTObj.obj"
	-@erase ".\modules\Release\JLabelObj.obj"
	-@erase ".\modules\Release\J1DViewerObj.obj"
	-@erase ".\modules\Release\JMIDIFileObj.obj"
	-@erase ".\modules\Release\JSampleObj.obj"
	-@erase ".\modules\Release\JAddObj.obj"
	-@erase ".\modules\Release\JMIDIChannelObj.obj"
	-@erase ".\modules\Release\J1DSliderObj.obj"
	-@erase ".\modules\Release\JTNGObj.obj"
	-@erase ".\modules\Release\JMouseBtnObj.obj"
	-@erase ".\modules\Release\JMaxObj.obj"
	-@erase ".\modules\Release\JNotEqualObj.obj"
	-@erase ".\modules\Release\JTNG3Obj.obj"
	-@erase ".\modules\Release\JPulseObj.obj"
	-@erase ".\modules\Release\JFocusObj.obj"
	-@erase ".\modules\Release\JWaveFileObj.obj"
	-@erase ".\modules\Release\JMIDIOutObj.obj"
	-@erase ".\modules\Release\JWaveInObj.obj"
	-@erase ".\modules\Release\modules.lib"
	-@erase ".\modules\Release\modules.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\awt" /I "..\util" /I "..\io" /I "..\neat" /I "..\net" /I "..\scsi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MODULES_DLL" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lang" /I "..\awt" /I "..\util" /I\
 "..\io" /I "..\neat" /I "..\net" /I "..\scsi" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_MODULES_DLL" /Fp"$(INTDIR)/modules.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\modules\Release/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/modules.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"modules.dll"
LINK32_FLAGS=user32.lib winmm.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/modules.pdb" /machine:I386 /out:"modules.dll"\
 /implib:"$(OUTDIR)/modules.lib" 
LINK32_OBJS= \
	"$(INTDIR)/JDelayObj.obj" \
	"$(INTDIR)/JGreaterThanObj.obj" \
	"$(INTDIR)/JDecoderObj.obj" \
	"$(INTDIR)/JAccumulatorObj.obj" \
	"$(INTDIR)/JExclusiveObj.obj" \
	"$(INTDIR)/JBtnObj.obj" \
	"$(INTDIR)/JJoyStickObj.obj" \
	"$(INTDIR)/JDeMultiplexerObj.obj" \
	"$(INTDIR)/JORObj.obj" \
	"$(INTDIR)/JTimeObj.obj" \
	"$(INTDIR)/JMultiplyObj.obj" \
	"$(INTDIR)/JCOMObj.obj" \
	"$(INTDIR)/JMIDIInObj.obj" \
	"$(INTDIR)/JMousePosObj.obj" \
	"$(INTDIR)/JAvgFilterObj.obj" \
	"$(INTDIR)/JWaveOutObj.obj" \
	"$(INTDIR)/JGreaterEqualObj.obj" \
	"$(INTDIR)/JEncoderObj.obj" \
	"$(INTDIR)/J2DSliderObj.obj" \
	"$(INTDIR)/JSubtractObj.obj" \
	"$(INTDIR)/J2DMeterObj.obj" \
	"$(INTDIR)/JOxfordObj.obj" \
	"$(INTDIR)/JRMIDFileObj.obj" \
	"$(INTDIR)/JEqualObj.obj" \
	"$(INTDIR)/JDivideObj.obj" \
	"$(INTDIR)/JSocketObj.obj" \
	"$(INTDIR)/JMIDIObj.obj" \
	"$(INTDIR)/JPushBtnObj.obj" \
	"$(INTDIR)/JCHObj.obj" \
	"$(INTDIR)/JTimerObj.obj" \
	"$(INTDIR)/JConvertObj.obj" \
	"$(INTDIR)/JKeyboardObj.obj" \
	"$(INTDIR)/JRemainObj.obj" \
	"$(INTDIR)/JNOTObj.obj" \
	"$(INTDIR)/JMultiplexerObj.obj" \
	"$(INTDIR)/J1DMeterObj.obj" \
	"$(INTDIR)/JCalibrateObj.obj" \
	"$(INTDIR)/JLEDObj.obj" \
	"$(INTDIR)/JIntegerObj.obj" \
	"$(INTDIR)/JXORObj.obj" \
	"$(INTDIR)/JControlObj.obj" \
	"$(INTDIR)/JRecorderObj.obj" \
	"$(INTDIR)/JSwitchObj.obj" \
	"$(INTDIR)/JClockDividerObj.obj" \
	"$(INTDIR)/JMinObj.obj" \
	"$(INTDIR)/JServerSocketObj.obj" \
	"$(INTDIR)/JMixerObj.obj" \
	"$(INTDIR)/JColorObj.obj" \
	"$(INTDIR)/JLPTObj.obj" \
	"$(INTDIR)/JLabelObj.obj" \
	"$(INTDIR)/J1DViewerObj.obj" \
	"$(INTDIR)/JMIDIFileObj.obj" \
	"$(INTDIR)/JSampleObj.obj" \
	"$(INTDIR)/JAddObj.obj" \
	"$(INTDIR)/JMIDIChannelObj.obj" \
	"$(INTDIR)/J1DSliderObj.obj" \
	"$(INTDIR)/JTNGObj.obj" \
	"$(INTDIR)/JMouseBtnObj.obj" \
	"$(INTDIR)/JMaxObj.obj" \
	"$(INTDIR)/JNotEqualObj.obj" \
	"$(INTDIR)/JTNG3Obj.obj" \
	"$(INTDIR)/JPulseObj.obj" \
	"$(INTDIR)/JFocusObj.obj" \
	"$(INTDIR)/JWaveFileObj.obj" \
	"$(INTDIR)/JMIDIOutObj.obj" \
	"$(INTDIR)/JWaveInObj.obj" \
	".\awt\Release\awt.lib" \
	".\neat\Release\neat.lib" \
	".\base\Release\base.lib"

"$(OUTDIR)\modules.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "oop - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Main\Oop.cpp
DEP_CPP_OOP_C=\
	".\..\lang\JObject.h"\
	".\..\lang\JPObject.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	".\..\util\JDList.h"\
	".\..\util\JAssociation.h"\
	".\..\util\JDictionary.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JMath.h"\
	".\..\util\JRandom.h"\
	".\..\lang\JBoolean.h"\
	".\..\lang\JCharacter.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JLong.h"\
	".\..\lang\JFloat.h"\
	".\..\lang\JDouble.h"\
	".\..\lang\JProcess.h"\
	".\..\io\JPipedStream.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JEOFException.h"\
	".\..\net\JSocketException.h"\
	".\..\net\JInetAddress.h"\
	".\..\net\JSocket.h"\
	".\..\net\JServerSocket.h"\
	".\..\net\JSocketInputStream.h"\
	".\..\net\JSocketOutputStream.h"\
	".\..\io\JFile.h"\
	".\..\util\JFileArray.h"\
	".\..\lang\JNullPointerException.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\io\JFileIOStream.h"\
	".\..\lang\JRuntimeException.h"\
	

"$(INTDIR)\Oop.obj" : $(SOURCE) $(DEP_CPP_OOP_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "base"

!IF  "$(CFG)" == "oop - Win32 Release"

"base - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="base - Win32 Release" 

!ENDIF 

# End Project Dependency
# End Target
################################################################################
# Begin Target

# Name "oopw - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\bc5\oop\oopw.rc
DEP_RSC_OOPW_=\
	".\..\oopw.ico"\
	

!IF  "$(CFG)" == "oopw - Win32 Release"


"$(INTDIR)\oopw.res" : $(SOURCE) $(DEP_RSC_OOPW_) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/oopw.res" /i "\bc5\oop" /d "NDEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Mainw\Oopw.cpp
DEP_CPP_OOPW_C=\
	".\..\awt\JWindow.hpp"\
	".\..\util\JDictionary.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JNullPointerException.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	

"$(INTDIR)\Oopw.obj" : $(SOURCE) $(DEP_CPP_OOPW_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "neat"

!IF  "$(CFG)" == "oopw - Win32 Release"

"neat - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="neat - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "awt"

!IF  "$(CFG)" == "oopw - Win32 Release"

"awt - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="awt - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "modules"

!IF  "$(CFG)" == "oopw - Win32 Release"

"modules - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="modules - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\mainw\JNeatTool.cpp
DEP_CPP_JNEAT=\
	".\..\mainw\JNeatTool.h"\
	".\..\neat\JAbout.h"\
	".\..\awt\JWindow.h"\
	".\..\mainw\JView.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JRuler.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JLabel.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JFocusSet.h"\
	".\..\io\JFile.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JImage.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JBlock.h"\
	

"$(INTDIR)\JNeatTool.obj" : $(SOURCE) $(DEP_CPP_JNEAT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\mainw\JView.cpp
DEP_CPP_JVIEW=\
	".\..\mainw\JView.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JAbout.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JBlockInputStream.h"\
	".\..\io\JBlockOutputStream.h"\
	".\..\io\JBufferedInputStream.h"\
	".\..\io\JBufferedOutputStream.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JClassReferenceException.h"\
	".\..\awt\JToggleButton.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JDouble.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JGuideObj.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JGridLayout.h"\
	".\..\awt\JFlowLayout.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JSeparator.h"\
	".\..\neat\JModuleButton.h"\
	".\..\modules\JMixerObj.h"\
	".\..\awt\JFileBox.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JClipboard.h"\
	".\..\lang\JPObject.h"\
	".\..\io\JFile.h"\
	".\..\awt\JRuler.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JLabel.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JImage.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\awt\JButton.h"\
	".\..\neat\JANDObj.h"\
	".\..\awt\JInputBox.h"\
	".\..\awt\JListBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	

"$(INTDIR)\JView.obj" : $(SOURCE) $(DEP_CPP_JVIEW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "base"

!IF  "$(CFG)" == "oopw - Win32 Release"

"base - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="base - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\mainw\JView2.cpp
DEP_CPP_JVIEW2=\
	".\..\mainw\JView.h"\
	".\..\awt\JDialog.h"\
	".\..\awt\JPanel.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JFlowLayout.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JPropertyBox.h"\
	".\..\awt\JRuler.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JLabel.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JFocusSet.h"\
	".\..\io\JFile.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JImage.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\neat\JModuleCanvas.h"\
	".\..\awt\JModal.h"\
	

"$(INTDIR)\JView2.obj" : $(SOURCE) $(DEP_CPP_JVIEW2) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "blackjack - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Main\blackjack.cpp
DEP_CPP_BLACK=\
	".\..\awt\JWindow.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JNullPointerException.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\blackjack.obj" : $(SOURCE) $(DEP_CPP_BLACK) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "html - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Main\html.cpp
DEP_CPP_HTML_=\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\util\JArray.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\html.obj" : $(SOURCE) $(DEP_CPP_HTML_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "count - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Main\count.cpp
DEP_CPP_COUNT=\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\util\JArray.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\count.obj" : $(SOURCE) $(DEP_CPP_COUNT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "backup - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Main\backup.cpp
DEP_CPP_BACKU=\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\util\JArray.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\backup.obj" : $(SOURCE) $(DEP_CPP_BACKU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "base - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JCriticalSection.cpp
DEP_CPP_JCRIT=\
	".\..\lang\JCriticalSection.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JCriticalSection.obj" : $(SOURCE) $(DEP_CPP_JCRIT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JObject.cpp
DEP_CPP_JOBJE=\
	".\..\lang\JObject.h"\
	".\..\lang\JBlock.h"\
	".\..\util\JDictionary.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JLong.h"\
	".\..\lang\JDouble.h"\
	".\..\lang\JFloat.h"\
	".\..\lang\JClassReferenceException.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	".\..\lang\JString.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JObject.obj" : $(SOURCE) $(DEP_CPP_JOBJE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JBlock.cpp
DEP_CPP_JBLOC=\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JCharacter.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JBlock.obj" : $(SOURCE) $(DEP_CPP_JBLOC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JArray.cpp
DEP_CPP_JARRA=\
	".\..\util\JArray.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JArray.obj" : $(SOURCE) $(DEP_CPP_JARRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JAssociation.cpp
DEP_CPP_JASSO=\
	".\..\util\JAssociation.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JAssociation.obj" : $(SOURCE) $(DEP_CPP_JASSO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JDictionary.cpp
DEP_CPP_JDICT=\
	".\..\util\JDictionary.h"\
	".\..\util\JAssociation.h"\
	".\..\lang\JString.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDictionary.obj" : $(SOURCE) $(DEP_CPP_JDICT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JDList.cpp
DEP_CPP_JDLIS=\
	".\..\util\JDList.h"\
	".\..\util\JList.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDList.obj" : $(SOURCE) $(DEP_CPP_JDLIS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JHashTable.cpp
DEP_CPP_JHASH=\
	".\..\util\JHashTable.h"\
	".\..\util\JList.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JHashTable.obj" : $(SOURCE) $(DEP_CPP_JHASH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JReference.cpp
DEP_CPP_JREFE=\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JReference.obj" : $(SOURCE) $(DEP_CPP_JREFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JString.cpp
DEP_CPP_JSTRI=\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JString.obj" : $(SOURCE) $(DEP_CPP_JSTRI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JInputStream.cpp
DEP_CPP_JINPU=\
	".\..\io\JInputStream.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JInputStream.obj" : $(SOURCE) $(DEP_CPP_JINPU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JOutputStream.cpp
DEP_CPP_JOUTP=\
	".\..\io\JOutputStream.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JOutputStream.obj" : $(SOURCE) $(DEP_CPP_JOUTP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JObjectPtr.cpp
DEP_CPP_JOBJEC=\
	".\..\lang\JObjectPtr.h"\
	".\..\lang\JPObject.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JObjectPtr.obj" : $(SOURCE) $(DEP_CPP_JOBJEC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JPObject.cpp
DEP_CPP_JPOBJ=\
	".\..\lang\JPObject.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JPObject.obj" : $(SOURCE) $(DEP_CPP_JPOBJ) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JBlockInputStream.cpp
DEP_CPP_JBLOCK=\
	".\..\io\JBlockInputStream.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JBlockInputStream.obj" : $(SOURCE) $(DEP_CPP_JBLOCK) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JBlockOutputStream.cpp
DEP_CPP_JBLOCKO=\
	".\..\io\JBlockOutputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JBlockOutputStream.obj" : $(SOURCE) $(DEP_CPP_JBLOCKO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JBoolean.cpp
DEP_CPP_JBOOL=\
	".\..\lang\JBoolean.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JBoolean.obj" : $(SOURCE) $(DEP_CPP_JBOOL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JBufferedInputStream.cpp
DEP_CPP_JBUFF=\
	".\..\io\JBufferedInputStream.h"\
	".\..\lang\JString.h"\
	".\..\io\JInterruptedIOException.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JBufferedInputStream.obj" : $(SOURCE) $(DEP_CPP_JBUFF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JBufferedOutputStream.cpp
DEP_CPP_JBUFFE=\
	".\..\io\JBufferedOutputStream.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	

"$(INTDIR)\JBufferedOutputStream.obj" : $(SOURCE) $(DEP_CPP_JBUFFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JCharacter.cpp
DEP_CPP_JCHAR=\
	".\..\lang\JCharacter.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JCharacter.obj" : $(SOURCE) $(DEP_CPP_JCHAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JDescriptor.cpp
DEP_CPP_JDESC=\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDescriptor.obj" : $(SOURCE) $(DEP_CPP_JDESC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JDouble.cpp
DEP_CPP_JDOUB=\
	".\..\lang\JDouble.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDouble.obj" : $(SOURCE) $(DEP_CPP_JDOUB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JFile.cpp
DEP_CPP_JFILE=\
	".\..\io\JFile.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.hpp"\
	".\..\lang\JObject.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\JFile.obj" : $(SOURCE) $(DEP_CPP_JFILE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JFileInputStream.cpp
DEP_CPP_JFILEI=\
	".\..\io\JFileInputStream.h"\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JEOFException.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.hpp"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\JFileInputStream.obj" : $(SOURCE) $(DEP_CPP_JFILEI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JFileOutputStream.cpp
DEP_CPP_JFILEO=\
	".\..\io\JFileOutputStream.h"\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JIOException.h"\
	".\..\io\JFile.hpp"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\JFileOutputStream.obj" : $(SOURCE) $(DEP_CPP_JFILEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JFilterInputStream.cpp
DEP_CPP_JFILT=\
	".\..\io\JFilterInputStream.h"\
	".\..\lang\JString.h"\
	".\..\lang\JBlock.h"\
	".\..\io\JInputStream.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JFilterInputStream.obj" : $(SOURCE) $(DEP_CPP_JFILT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JFilterOutputStream.cpp
DEP_CPP_JFILTE=\
	".\..\io\JFilterOutputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	

"$(INTDIR)\JFilterOutputStream.obj" : $(SOURCE) $(DEP_CPP_JFILTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JFloat.cpp

!IF  "$(CFG)" == "base - Win32 Release"

DEP_CPP_JFLOA=\
	".\..\lang\JFloat.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JFloat.obj" : $(SOURCE) $(DEP_CPP_JFLOA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JInetAddress.cpp
DEP_CPP_JINET=\
	".\..\net\JInetAddress.h"\
	".\..\net\JSocket.hpp"\
	".\..\net\JUnknownHostException.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JAssociation.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\util\JHashTable.h"\
	

"$(INTDIR)\JInetAddress.obj" : $(SOURCE) $(DEP_CPP_JINET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JInteger.cpp
DEP_CPP_JINTE=\
	".\..\lang\JInteger.h"\
	".\..\lang\JCharacter.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JInteger.obj" : $(SOURCE) $(DEP_CPP_JINTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JList.cpp
DEP_CPP_JLIST=\
	".\..\util\JList.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JString.h"\
	

"$(INTDIR)\JList.obj" : $(SOURCE) $(DEP_CPP_JLIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JLong.cpp
DEP_CPP_JLONG=\
	".\..\lang\JLong.h"\
	".\..\lang\JCharacter.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JLong.obj" : $(SOURCE) $(DEP_CPP_JLONG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JMath.cpp
DEP_CPP_JMATH=\
	".\..\lang\JMath.h"\
	".\..\util\JRandom.h"\
	".\..\lang\JArithmeticException.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	

"$(INTDIR)\JMath.obj" : $(SOURCE) $(DEP_CPP_JMATH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JPipedStream.cpp
DEP_CPP_JPIPE=\
	".\..\io\JPipedStream.h"\
	".\..\io\JIOException.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JObject.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	

"$(INTDIR)\JPipedStream.obj" : $(SOURCE) $(DEP_CPP_JPIPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JProcess.cpp
DEP_CPP_JPROC=\
	".\..\lang\JProcess.h"\
	".\..\lang\JProcessCreateException.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JProcess.obj" : $(SOURCE) $(DEP_CPP_JPROC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\util\JRandom.cpp
DEP_CPP_JRAND=\
	".\..\util\JRandom.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JRandom.obj" : $(SOURCE) $(DEP_CPP_JRAND) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JServerSocket.cpp
DEP_CPP_JSERV=\
	".\..\net\JServerSocket.h"\
	".\..\net\JSocket.hpp"\
	".\..\net\JSocketException.h"\
	".\..\net\JSocket.h"\
	".\..\net\JInetAddress.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JServerSocket.obj" : $(SOURCE) $(DEP_CPP_JSERV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JSocket.cpp
DEP_CPP_JSOCK=\
	".\..\net\JSocket.h"\
	".\..\net\JSocket.hpp"\
	".\..\net\JSocketException.h"\
	".\..\net\JInetAddress.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JSocket.obj" : $(SOURCE) $(DEP_CPP_JSOCK) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JSocketInputStream.cpp
DEP_CPP_JSOCKE=\
	".\..\net\JSocketInputStream.h"\
	".\..\net\JSocket.hpp"\
	".\..\net\JSocketException.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\net\JSocket.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JOutputStream.h"\
	".\..\net\JInetAddress.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	
NODEP_CPP_JSOCKE=\
	".\..\net\JString.h"\
	

"$(INTDIR)\JSocketInputStream.obj" : $(SOURCE) $(DEP_CPP_JSOCKE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JSocketOutputStream.cpp
DEP_CPP_JSOCKET=\
	".\..\net\JSocketOutputStream.h"\
	".\..\net\JSocket.hpp"\
	".\..\io\JIOException.h"\
	".\..\io\JOutputStream.h"\
	".\..\net\JSocket.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\net\JInetAddress.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JString.h"\
	".\..\util\JArray.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JSocketOutputStream.obj" : $(SOURCE) $(DEP_CPP_JSOCKET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JSystem.cpp
DEP_CPP_JSYST=\
	".\..\lang\JSystem.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JSystem.obj" : $(SOURCE) $(DEP_CPP_JSYST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JThread.cpp
DEP_CPP_JTHRE=\
	".\..\lang\JThread.h"\
	".\..\lang\JThreadCreateException.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	

"$(INTDIR)\JThread.obj" : $(SOURCE) $(DEP_CPP_JTHRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JThrowable.cpp
DEP_CPP_JTHRO=\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JThrowable.obj" : $(SOURCE) $(DEP_CPP_JTHRO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JClassReferenceException.cpp
DEP_CPP_JCLAS=\
	".\..\lang\JClassReferenceException.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JClassReferenceException.obj" : $(SOURCE) $(DEP_CPP_JCLAS)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JException.cpp
DEP_CPP_JEXCE=\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JException.obj" : $(SOURCE) $(DEP_CPP_JEXCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JIllegalArgumentException.cpp
DEP_CPP_JILLE=\
	".\..\lang\JIllegalArgumentException.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JIllegalArgumentException.obj" : $(SOURCE) $(DEP_CPP_JILLE)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JNullPointerException.cpp
DEP_CPP_JNULL=\
	".\..\lang\JNullPointerException.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JNullPointerException.obj" : $(SOURCE) $(DEP_CPP_JNULL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JProcessCreateException.cpp
DEP_CPP_JPROCE=\
	".\..\lang\JProcessCreateException.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JProcessCreateException.obj" : $(SOURCE) $(DEP_CPP_JPROCE)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JRuntimeException.cpp
DEP_CPP_JRUNT=\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JRuntimeException.obj" : $(SOURCE) $(DEP_CPP_JRUNT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JThreadCreateException.cpp
DEP_CPP_JTHREA=\
	".\..\lang\JThreadCreateException.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JThreadCreateException.obj" : $(SOURCE) $(DEP_CPP_JTHREA)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\lang\JArithmeticException.cpp
DEP_CPP_JARIT=\
	".\..\lang\JArithmeticException.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JArithmeticException.obj" : $(SOURCE) $(DEP_CPP_JARIT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JEOFException.cpp
DEP_CPP_JEOFE=\
	".\..\io\JEOFException.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JEOFException.obj" : $(SOURCE) $(DEP_CPP_JEOFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JInterruptedIOException.cpp
DEP_CPP_JINTER=\
	".\..\io\JInterruptedIOException.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JInterruptedIOException.obj" : $(SOURCE) $(DEP_CPP_JINTER)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\io\JIOException.cpp
DEP_CPP_JIOEX=\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JIOException.obj" : $(SOURCE) $(DEP_CPP_JIOEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JUnknownHostException.cpp
DEP_CPP_JUNKN=\
	".\..\net\JUnknownHostException.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JUnknownHostException.obj" : $(SOURCE) $(DEP_CPP_JUNKN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\net\JSocketException.cpp
DEP_CPP_JSOCKETE=\
	".\..\net\JSocketException.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JSocketException.obj" : $(SOURCE) $(DEP_CPP_JSOCKETE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "awt - Win32 Release"
################################################################################
# Begin Project Dependency

# Project_Dep_Name "filter"

!IF  "$(CFG)" == "awt - Win32 Release"

"filter - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="filter - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JBorderLayout.cpp
DEP_CPP_JBORD=\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JString.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JPoint.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JBorderLayout.obj" : $(SOURCE) $(DEP_CPP_JBORD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JButton.cpp
DEP_CPP_JBUTT=\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JButton.obj" : $(SOURCE) $(DEP_CPP_JBUTT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JCanvas.cpp
DEP_CPP_JCANV=\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JCanvas.obj" : $(SOURCE) $(DEP_CPP_JCANV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JClipboard.cpp
DEP_CPP_JCLIP=\
	".\..\awt\JClipboard.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JBlock.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JClipboard.obj" : $(SOURCE) $(DEP_CPP_JCLIP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JColor.cpp
DEP_CPP_JCOLO=\
	".\..\awt\JColor.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JNullPointerException.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	".\..\lang\JString.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JColor.obj" : $(SOURCE) $(DEP_CPP_JCOLO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JColorBox.cpp
DEP_CPP_JCOLOR=\
	".\..\awt\JColorBox.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JGridLayout.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JCanvas.h"\
	

"$(INTDIR)\JColorBox.obj" : $(SOURCE) $(DEP_CPP_JCOLOR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JComponent.cpp
DEP_CPP_JCOMP=\
	".\..\awt\JComponent.h"\
	".\..\awt\JImage.h"\
	".\..\lang\JString.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JAssociation.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JThread.h"\
	".\..\awt\JWindow.hpp"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JIllegalArgumentException.h"\
	".\..\lang\JPObject.h"\
	".\..\util\JDList.h"\
	".\..\lang\JInteger.h"\
	".\..\net\JInetAddress.h"\
	".\..\io\JFile.h"\
	".\..\io\JFile.hpp"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JRuntimeException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\JComponent.obj" : $(SOURCE) $(DEP_CPP_JCOMP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JDialog.cpp
DEP_CPP_JDIAL=\
	".\..\awt\JDialog.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JDialog.obj" : $(SOURCE) $(DEP_CPP_JDIAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JDimension.cpp
DEP_CPP_JDIME=\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDimension.obj" : $(SOURCE) $(DEP_CPP_JDIME) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JEvent.cpp
DEP_CPP_JEVEN=\
	".\..\awt\JEvent.h"\
	".\..\lang\JSystem.h"\
	".\..\lang\JString.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JEvent.obj" : $(SOURCE) $(DEP_CPP_JEVEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JFileBox.cpp
DEP_CPP_JFILEB=\
	".\..\awt\JFileBox.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JGridLayout.h"\
	".\..\util\JAssociation.h"\
	".\..\io\JFile.h"\
	".\..\io\JFile.hpp"\
	".\..\awt\JInputBox.h"\
	".\..\awt\JListBox.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\JFileBox.obj" : $(SOURCE) $(DEP_CPP_JFILEB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JFlowLayout.cpp
DEP_CPP_JFLOW=\
	".\..\awt\JFlowLayout.h"\
	".\..\lang\JPObject.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JArray.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JFlowLayout.obj" : $(SOURCE) $(DEP_CPP_JFLOW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JFont.cpp
DEP_CPP_JFONT=\
	".\..\awt\JFont.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JFont.obj" : $(SOURCE) $(DEP_CPP_JFONT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JFontMetrics.cpp
DEP_CPP_JFONTM=\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JWindow.hpp"\
	".\..\awt\JFont.h"\
	".\..\awt\JGraphics.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JRegion.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JFontMetrics.obj" : $(SOURCE) $(DEP_CPP_JFONTM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JGraphics.cpp
DEP_CPP_JGRAP=\
	".\..\lang\JMath.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JImage.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JRegion.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\util\JHashTable.h"\
	

"$(INTDIR)\JGraphics.obj" : $(SOURCE) $(DEP_CPP_JGRAP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JGridLayout.cpp
DEP_CPP_JGRID=\
	".\..\awt\JGridLayout.h"\
	".\..\lang\JPObject.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JString.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JPoint.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JGridLayout.obj" : $(SOURCE) $(DEP_CPP_JGRID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JImage.cpp
DEP_CPP_JIMAG=\
	".\..\awt\JImage.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JReference.h"\
	".\..\awt\JGraphics.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JRegion.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\util\JHashTable.h"\
	

"$(INTDIR)\JImage.obj" : $(SOURCE) $(DEP_CPP_JIMAG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JInputBox.cpp
DEP_CPP_JINPUT=\
	".\..\awt\JInputBox.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	

"$(INTDIR)\JInputBox.obj" : $(SOURCE) $(DEP_CPP_JINPUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JInsets.cpp
DEP_CPP_JINSE=\
	".\..\awt\JInsets.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JInsets.obj" : $(SOURCE) $(DEP_CPP_JINSE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JIntegerBox.cpp
DEP_CPP_JINTEG=\
	".\..\awt\JIntegerBox.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JInputBox.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	

"$(INTDIR)\JIntegerBox.obj" : $(SOURCE) $(DEP_CPP_JINTEG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JIntegerListBox.cpp
DEP_CPP_JINTEGE=\
	".\..\awt\JIntegerListBox.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\util\JArray.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JIntegerListBox.obj" : $(SOURCE) $(DEP_CPP_JINTEGE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JLabel.cpp
DEP_CPP_JLABE=\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JLabel.obj" : $(SOURCE) $(DEP_CPP_JLABE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JLayoutManager.cpp
DEP_CPP_JLAYO=\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JString.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JPoint.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JLayoutManager.obj" : $(SOURCE) $(DEP_CPP_JLAYO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JListBox.cpp
DEP_CPP_JLISTB=\
	".\..\awt\JListBox.h"\
	".\..\util\JAssociation.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JArray.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JListBox.obj" : $(SOURCE) $(DEP_CPP_JLISTB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JMessageBox.cpp
DEP_CPP_JMESS=\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JSeparator.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JFlowLayout.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JMessageBox.obj" : $(SOURCE) $(DEP_CPP_JMESS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JModal.cpp
DEP_CPP_JMODA=\
	".\..\awt\JModal.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JSeparator.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JFlowLayout.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	

"$(INTDIR)\JModal.obj" : $(SOURCE) $(DEP_CPP_JMODA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JPoint.cpp
DEP_CPP_JPOIN=\
	".\..\awt\JPoint.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JPoint.obj" : $(SOURCE) $(DEP_CPP_JPOIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JPushButton.cpp
DEP_CPP_JPUSH=\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JPushButton.obj" : $(SOURCE) $(DEP_CPP_JPUSH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JRect.cpp
DEP_CPP_JRECT=\
	".\..\awt\JRect.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JRect.obj" : $(SOURCE) $(DEP_CPP_JRECT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JRegion.cpp
DEP_CPP_JREGI=\
	".\..\awt\JRegion.h"\
	".\..\awt\JWindow.hpp"\
	".\..\lang\JReference.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JRegion.obj" : $(SOURCE) $(DEP_CPP_JREGI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JRuler.cpp
DEP_CPP_JRULE=\
	".\..\awt\JRuler.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JDouble.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JImage.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JRuler.obj" : $(SOURCE) $(DEP_CPP_JRULE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JScroller.cpp
DEP_CPP_JSCRO=\
	".\..\awt\JScroller.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JScroller.obj" : $(SOURCE) $(DEP_CPP_JSCRO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JSeparator.cpp
DEP_CPP_JSEPA=\
	".\..\awt\JSeparator.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JSeparator.obj" : $(SOURCE) $(DEP_CPP_JSEPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JTextField.cpp
DEP_CPP_JTEXT=\
	".\..\awt\JTextField.h"\
	".\..\lang\JSystem.h"\
	".\..\awt\JLabel.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JTextField.obj" : $(SOURCE) $(DEP_CPP_JTEXT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JThumb.cpp
DEP_CPP_JTHUM=\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JThumb.obj" : $(SOURCE) $(DEP_CPP_JTHUM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JToggleButton.cpp
DEP_CPP_JTOGG=\
	".\..\awt\JToggleButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JToggleButton.obj" : $(SOURCE) $(DEP_CPP_JTOGG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JTriangleButton.cpp
DEP_CPP_JTRIA=\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JTriangleButton.obj" : $(SOURCE) $(DEP_CPP_JTRIA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JWindow.cpp
DEP_CPP_JWIND=\
	".\..\awt\JWindow.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JWindow.obj" : $(SOURCE) $(DEP_CPP_JWIND) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "base"

!IF  "$(CFG)" == "awt - Win32 Release"

"base - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="base - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\awt\JPanel.cpp
DEP_CPP_JPANE=\
	".\..\awt\JPanel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	

"$(INTDIR)\JPanel.obj" : $(SOURCE) $(DEP_CPP_JPANE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "filter - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\Filter\Filter.cpp

"$(INTDIR)\Filter.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "neat - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JAbout.cpp
DEP_CPP_JABOU=\
	".\..\neat\JAbout.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	

"$(INTDIR)\JAbout.obj" : $(SOURCE) $(DEP_CPP_JABOU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JColorProperty.cpp
DEP_CPP_JCOLORP=\
	".\..\neat\JColorProperty.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JColorBox.h"\
	".\..\neat\JProperty.h"\
	".\..\awt\JColor.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	

"$(INTDIR)\JColorProperty.obj" : $(SOURCE) $(DEP_CPP_JCOLORP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JFDimension.cpp
DEP_CPP_JFDIM=\
	".\..\neat\JFDimension.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JFDimension.obj" : $(SOURCE) $(DEP_CPP_JFDIM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JFileProperty.cpp
DEP_CPP_JFILEP=\
	".\..\neat\JFileProperty.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JFileBox.h"\
	".\..\neat\JStringProperty.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JInputBox.h"\
	".\..\awt\JListBox.h"\
	".\..\io\JFile.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	

"$(INTDIR)\JFileProperty.obj" : $(SOURCE) $(DEP_CPP_JFILEP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JFocusSet.cpp
DEP_CPP_JFOCU=\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObjectPtr.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JPObject.h"\
	

"$(INTDIR)\JFocusSet.obj" : $(SOURCE) $(DEP_CPP_JFOCU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JFPoint.cpp
DEP_CPP_JFPOI=\
	".\..\neat\JFPoint.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JFPoint.obj" : $(SOURCE) $(DEP_CPP_JFPOI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JFRect.cpp
DEP_CPP_JFREC=\
	".\..\neat\JFRect.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JFRect.obj" : $(SOURCE) $(DEP_CPP_JFREC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JGuideObj.cpp
DEP_CPP_JGUID=\
	".\..\neat\JGuideObj.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JDouble.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JList.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	

"$(INTDIR)\JGuideObj.obj" : $(SOURCE) $(DEP_CPP_JGUID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JIntegerListProperty.cpp
DEP_CPP_JINTEGER=\
	".\..\neat\JIntegerListProperty.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JIntegerListBox.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\util\JList.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	

"$(INTDIR)\JIntegerListProperty.obj" : $(SOURCE) $(DEP_CPP_JINTEGER)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JIntegerProperty.cpp
DEP_CPP_JINTEGERP=\
	".\..\neat\JIntegerProperty.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JIntegerBox.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JInputBox.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JLabel.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	

"$(INTDIR)\JIntegerProperty.obj" : $(SOURCE) $(DEP_CPP_JINTEGERP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JLineObj.cpp
DEP_CPP_JLINE=\
	".\..\neat\JLineObj.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JList.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JLineObj.obj" : $(SOURCE) $(DEP_CPP_JLINE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JLinkObj.cpp
DEP_CPP_JLINK=\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JLineObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JPObject.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JBlock.h"\
	

"$(INTDIR)\JLinkObj.obj" : $(SOURCE) $(DEP_CPP_JLINK) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JModuleButton.cpp
DEP_CPP_JMODU=\
	".\..\neat\JModuleButton.h"\
	".\..\awt\JButton.h"\
	".\..\neat\JModuleObj.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\neat\JViewObj.h"\
	".\..\lang\JBlock.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JModuleButton.obj" : $(SOURCE) $(DEP_CPP_JMODU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JModuleCanvas.cpp
DEP_CPP_JMODUL=\
	".\..\neat\JModuleCanvas.h"\
	".\..\awt\JCanvas.h"\
	".\..\neat\JModuleObj.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\util\JList.h"\
	".\..\neat\JViewObj.h"\
	".\..\lang\JBlock.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JModuleCanvas.obj" : $(SOURCE) $(DEP_CPP_JMODUL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JModuleObj.cpp
DEP_CPP_JMODULE=\
	".\..\lang\JPObject.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JModuleButton.h"\
	".\..\neat\JLinkObj.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JPropertyBox.h"\
	".\..\neat\JColorProperty.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\neat\JModuleCanvas.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	

"$(INTDIR)\JModuleObj.obj" : $(SOURCE) $(DEP_CPP_JMODULE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JProperty.cpp
DEP_CPP_JPROP=\
	".\..\neat\JProperty.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JProperty.obj" : $(SOURCE) $(DEP_CPP_JPROP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JPropertyBox.cpp
DEP_CPP_JPROPE=\
	".\..\neat\JPropertyBox.h"\
	".\..\awt\JCanvas.h"\
	".\..\awt\JBorderLayout.h"\
	".\..\awt\JGridLayout.h"\
	".\..\util\JAssociation.h"\
	".\..\io\JFile.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JModuleCanvas.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JScroller.h"\
	".\..\util\JArray.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JString.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JPropertyBox.obj" : $(SOURCE) $(DEP_CPP_JPROPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\neat\JStringProperty.cpp
DEP_CPP_JSTRIN=\
	".\..\neat\JStringProperty.h"\
	".\..\lang\JInteger.h"\
	".\..\awt\JInputBox.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JTextField.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\util\JList.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	

"$(INTDIR)\JStringProperty.obj" : $(SOURCE) $(DEP_CPP_JSTRIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JViewObj.cpp
DEP_CPP_JVIEWO=\
	".\..\lang\JPObject.h"\
	".\..\neat\JViewSet.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JDouble.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JPropertyBox.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JArray.h"\
	".\..\util\JList.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\awt\JMessageBox.h"\
	".\..\awt\JListBox.h"\
	".\..\neat\JModuleCanvas.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JScroller.h"\
	".\..\awt\JTriangleButton.h"\
	".\..\awt\JThumb.h"\
	".\..\awt\JPushButton.h"\
	".\..\awt\JButton.h"\
	".\..\awt\JLabel.h"\
	".\..\awt\JCanvas.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JBlock.h"\
	

"$(INTDIR)\JViewObj.obj" : $(SOURCE) $(DEP_CPP_JVIEWO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\neat\JViewSet.cpp
DEP_CPP_JVIEWS=\
	".\..\neat\JViewSet.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JLineObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JDouble.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JList.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\util\JArray.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JHashTable.h"\
	

"$(INTDIR)\JViewSet.obj" : $(SOURCE) $(DEP_CPP_JVIEWS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "awt"

!IF  "$(CFG)" == "neat - Win32 Release"

"awt - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="awt - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "base"

!IF  "$(CFG)" == "neat - Win32 Release"

"base - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="base - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\neat\JANDObj.cpp
DEP_CPP_JANDO=\
	".\..\neat\JANDObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JANDObj.obj" : $(SOURCE) $(DEP_CPP_JANDO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "modules - Win32 Release"
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\J1DMeterObj.cpp
DEP_CPP_J1DME=\
	".\..\modules\J1DMeterObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JIntegerObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\J1DMeterObj.obj" : $(SOURCE) $(DEP_CPP_J1DME) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\J1DSliderObj.cpp
DEP_CPP_J1DSL=\
	".\..\modules\J1DSliderObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\modules\JBtnObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\J1DSliderObj.obj" : $(SOURCE) $(DEP_CPP_J1DSL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\J1DViewerObj.cpp
DEP_CPP_J1DVI=\
	".\..\modules\J1DViewerObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\modules\J1DMeterObj.h"\
	".\..\awt\JImage.h"\
	".\..\modules\JIntegerObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\J1DViewerObj.obj" : $(SOURCE) $(DEP_CPP_J1DVI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\J2DMeterObj.cpp
DEP_CPP_J2DME=\
	".\..\modules\J2DMeterObj.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JIntegerObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\J2DMeterObj.obj" : $(SOURCE) $(DEP_CPP_J2DME) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\J2DSliderObj.cpp
DEP_CPP_J2DSL=\
	".\..\modules\J2DSliderObj.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\modules\JBtnObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\J2DSliderObj.obj" : $(SOURCE) $(DEP_CPP_J2DSL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JAccumulatorObj.cpp
DEP_CPP_JACCU=\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JAccumulatorObj.obj" : $(SOURCE) $(DEP_CPP_JACCU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JAddObj.cpp
DEP_CPP_JADDO=\
	".\..\modules\JAddObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JAddObj.obj" : $(SOURCE) $(DEP_CPP_JADDO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JAvgFilterObj.cpp
DEP_CPP_JAVGF=\
	".\..\modules\JAvgFilterObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JString.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JAvgFilterObj.obj" : $(SOURCE) $(DEP_CPP_JAVGF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JBtnObj.cpp
DEP_CPP_JBTNO=\
	".\..\modules\JBtnObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JStringProperty.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JBtnObj.obj" : $(SOURCE) $(DEP_CPP_JBTNO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JCalibrateObj.cpp
DEP_CPP_JCALI=\
	".\..\modules\JCalibrateObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JCalibrateObj.obj" : $(SOURCE) $(DEP_CPP_JCALI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JCHObj.cpp
DEP_CPP_JCHOB=\
	".\..\modules\JCHObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JCHObj.obj" : $(SOURCE) $(DEP_CPP_JCHOB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JClockDividerObj.cpp
DEP_CPP_JCLOC=\
	".\..\modules\JClockDividerObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JClockDividerObj.obj" : $(SOURCE) $(DEP_CPP_JCLOC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JColorObj.cpp
DEP_CPP_JCOLORO=\
	".\..\modules\JColorObj.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JColorObj.obj" : $(SOURCE) $(DEP_CPP_JCOLORO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JCOMObj.cpp
DEP_CPP_JCOMO=\
	".\..\modules\JCOMObj.h"\
	".\..\lang\JThread.h"\
	".\..\neat\JLinkObj.h"\
	".\..\awt\JMessageBox.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\awt\JModal.h"\
	".\..\awt\JButton.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\awt\JLabel.h"\
	".\..\util\JList.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\awt\JCanvas.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JCOMObj.obj" : $(SOURCE) $(DEP_CPP_JCOMO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JControlObj.cpp
DEP_CPP_JCONT=\
	".\..\modules\JControlObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\modules\JSampleObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\util\JArray.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JControlObj.obj" : $(SOURCE) $(DEP_CPP_JCONT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JConvertObj.cpp
DEP_CPP_JCONV=\
	".\..\modules\JConvertObj.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\lang\JDouble.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JConvertObj.obj" : $(SOURCE) $(DEP_CPP_JCONV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JDecoderObj.cpp
DEP_CPP_JDECO=\
	".\..\modules\JDecoderObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDecoderObj.obj" : $(SOURCE) $(DEP_CPP_JDECO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JDelayObj.cpp
DEP_CPP_JDELA=\
	".\..\modules\JDelayObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JDelayObj.obj" : $(SOURCE) $(DEP_CPP_JDELA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JDeMultiplexerObj.cpp
DEP_CPP_JDEMU=\
	".\..\modules\JDeMultiplexerObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JDeMultiplexerObj.obj" : $(SOURCE) $(DEP_CPP_JDEMU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JDivideObj.cpp
DEP_CPP_JDIVI=\
	".\..\modules\JDivideObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JDivideObj.obj" : $(SOURCE) $(DEP_CPP_JDIVI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JEncoderObj.cpp
DEP_CPP_JENCO=\
	".\..\modules\JEncoderObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JEncoderObj.obj" : $(SOURCE) $(DEP_CPP_JENCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JEqualObj.cpp
DEP_CPP_JEQUA=\
	".\..\modules\JEqualObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JEqualObj.obj" : $(SOURCE) $(DEP_CPP_JEQUA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JExclusiveObj.cpp
DEP_CPP_JEXCL=\
	".\..\modules\JExclusiveObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JExclusiveObj.obj" : $(SOURCE) $(DEP_CPP_JEXCL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JFocusObj.cpp
DEP_CPP_JFOCUS=\
	".\..\modules\JFocusObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\awt\JComponent.h"\
	".\..\modules\JBtnObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	

"$(INTDIR)\JFocusObj.obj" : $(SOURCE) $(DEP_CPP_JFOCUS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JGreaterEqualObj.cpp
DEP_CPP_JGREA=\
	".\..\modules\JGreaterEqualObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JGreaterEqualObj.obj" : $(SOURCE) $(DEP_CPP_JGREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JGreaterThanObj.cpp
DEP_CPP_JGREAT=\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JGreaterThanObj.obj" : $(SOURCE) $(DEP_CPP_JGREAT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JIntegerObj.cpp
DEP_CPP_JINTEGERO=\
	".\..\modules\JIntegerObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JIntegerObj.obj" : $(SOURCE) $(DEP_CPP_JINTEGERO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JJoyStickObj.cpp
DEP_CPP_JJOYS=\
	".\..\modules\JJoyStickObj.h"\
	".\..\lang\JThread.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JJoyStickObj.obj" : $(SOURCE) $(DEP_CPP_JJOYS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JKeyboardObj.cpp
DEP_CPP_JKEYB=\
	".\..\modules\JKeyboardObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JCharacter.h"\
	".\..\lang\JInteger.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JKeyboardObj.obj" : $(SOURCE) $(DEP_CPP_JKEYB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JLabelObj.cpp
DEP_CPP_JLABEL=\
	".\..\modules\JLabelObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JStringProperty.h"\
	".\..\neat\JColorProperty.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JLabelObj.obj" : $(SOURCE) $(DEP_CPP_JLABEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JLEDObj.cpp
DEP_CPP_JLEDO=\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JColorProperty.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JLEDObj.obj" : $(SOURCE) $(DEP_CPP_JLEDO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JLPTObj.cpp
DEP_CPP_JLPTO=\
	".\..\modules\JLPTObj.h"\
	".\..\lang\JThread.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\awt\JWindow.hpp"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JHashTable.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JLPTObj.obj" : $(SOURCE) $(DEP_CPP_JLPTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMaxObj.cpp
DEP_CPP_JMAXO=\
	".\..\modules\JMaxObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JMaxObj.obj" : $(SOURCE) $(DEP_CPP_JMAXO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIChannelObj.cpp
DEP_CPP_JMIDI=\
	".\..\modules\JMIDIChannelObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JMIDIChannelObj.obj" : $(SOURCE) $(DEP_CPP_JMIDI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIFileObj.cpp
DEP_CPP_JMIDIF=\
	".\..\modules\JMIDIFileObj.h"\
	".\..\modules\JWaveOutObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JSystem.h"\
	".\..\neat\JStringProperty.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\io\JIOException.h"\
	".\..\io\JEOFException.h"\
	".\..\lang\JMath.h"\
	".\..\modules\JRecorderObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JBufferedInputStream.h"\
	".\..\io\JBufferedOutputStream.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JMIDIFileObj.obj" : $(SOURCE) $(DEP_CPP_JMIDIF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIInObj.cpp
DEP_CPP_JMIDII=\
	".\..\modules\JMIDIInObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JWindow.hpp"\
	".\..\modules\JMIDIOutObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\lang\JBlock.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	

"$(INTDIR)\JMIDIInObj.obj" : $(SOURCE) $(DEP_CPP_JMIDII) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JMIDIObj.cpp
DEP_CPP_JMIDIO=\
	".\..\modules\JMIDIObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JMIDIObj.obj" : $(SOURCE) $(DEP_CPP_JMIDIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JMIDIOutObj.cpp
DEP_CPP_JMIDIOU=\
	".\..\modules\JMIDIOutObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\awt\JWindow.hpp"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\util\JList.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JMIDIOutObj.obj" : $(SOURCE) $(DEP_CPP_JMIDIOU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMinObj.cpp
DEP_CPP_JMINO=\
	".\..\modules\JMinObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JMinObj.obj" : $(SOURCE) $(DEP_CPP_JMINO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMouseBtnObj.cpp
DEP_CPP_JMOUS=\
	".\..\modules\JMouseBtnObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JCharacter.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JMouseBtnObj.obj" : $(SOURCE) $(DEP_CPP_JMOUS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMousePosObj.cpp
DEP_CPP_JMOUSE=\
	".\..\modules\JMousePosObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JCharacter.h"\
	".\..\modules\JMouseBtnObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JMousePosObj.obj" : $(SOURCE) $(DEP_CPP_JMOUSE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMultiplexerObj.cpp
DEP_CPP_JMULT=\
	".\..\modules\JMultiplexerObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JReference.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JMultiplexerObj.obj" : $(SOURCE) $(DEP_CPP_JMULT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JMultiplyObj.cpp
DEP_CPP_JMULTI=\
	".\..\modules\JMultiplyObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JMultiplyObj.obj" : $(SOURCE) $(DEP_CPP_JMULTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JNotEqualObj.cpp
DEP_CPP_JNOTE=\
	".\..\modules\JNotEqualObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JNotEqualObj.obj" : $(SOURCE) $(DEP_CPP_JNOTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JNOTObj.cpp
DEP_CPP_JNOTO=\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JNOTObj.obj" : $(SOURCE) $(DEP_CPP_JNOTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JORObj.cpp
DEP_CPP_JOROB=\
	".\..\modules\JORObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JORObj.obj" : $(SOURCE) $(DEP_CPP_JOROB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JOxfordObj.cpp
DEP_CPP_JOXFO=\
	".\..\modules\JOxfordObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JOxfordObj.obj" : $(SOURCE) $(DEP_CPP_JOXFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JPulseObj.cpp
DEP_CPP_JPULS=\
	".\..\modules\JPulseObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JPulseObj.obj" : $(SOURCE) $(DEP_CPP_JPULS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JPushBtnObj.cpp
DEP_CPP_JPUSHB=\
	".\..\modules\JPushBtnObj.h"\
	".\..\modules\JBtnObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JPushBtnObj.obj" : $(SOURCE) $(DEP_CPP_JPUSHB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JRecorderObj.cpp
DEP_CPP_JRECO=\
	".\..\modules\JRecorderObj.h"\
	".\..\modules\JConvertObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JSystem.h"\
	".\..\io\JFile.h"\
	".\..\neat\JFileProperty.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\io\JIOException.h"\
	".\..\io\JEOFException.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JBufferedInputStream.h"\
	".\..\io\JBufferedOutputStream.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\neat\JStringProperty.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JRecorderObj.obj" : $(SOURCE) $(DEP_CPP_JRECO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JRemainObj.cpp
DEP_CPP_JREMA=\
	".\..\modules\JRemainObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JObject.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JRemainObj.obj" : $(SOURCE) $(DEP_CPP_JREMA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JRMIDFileObj.cpp
DEP_CPP_JRMID=\
	".\..\modules\JRMIDFileObj.h"\
	".\..\modules\JWaveOutObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JSystem.h"\
	".\..\neat\JFileProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\io\JIOException.h"\
	".\..\io\JEOFException.h"\
	".\..\lang\JMath.h"\
	".\..\awt\JWindow.hpp"\
	".\..\modules\JMIDIFileObj.h"\
	".\..\modules\JRecorderObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JBufferedInputStream.h"\
	".\..\io\JBufferedOutputStream.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\neat\JStringProperty.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JRMIDFileObj.obj" : $(SOURCE) $(DEP_CPP_JRMID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JSampleObj.cpp
DEP_CPP_JSAMP=\
	".\..\modules\JSampleObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JANDObj.h"\
	".\..\util\JArray.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JSampleObj.obj" : $(SOURCE) $(DEP_CPP_JSAMP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JServerSocketObj.cpp
DEP_CPP_JSERVE=\
	".\..\modules\JServerSocketObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\net\JSocketException.h"\
	".\..\modules\JSocketObj.h"\
	".\..\net\JServerSocket.h"\
	".\..\neat\JANDObj.h"\
	".\..\net\JSocket.h"\
	".\..\net\JSocketInputStream.h"\
	".\..\net\JSocketOutputStream.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\net\JInetAddress.h"\
	".\..\io\JIOException.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JServerSocketObj.obj" : $(SOURCE) $(DEP_CPP_JSERVE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JSocketObj.cpp
DEP_CPP_JSOCKETO=\
	".\..\modules\JSocketObj.h"\
	".\..\modules\JConvertObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JCharacter.h"\
	".\..\neat\JStringProperty.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\net\JSocketException.h"\
	".\..\net\JUnknownHostException.h"\
	".\..\neat\JANDObj.h"\
	".\..\net\JSocket.h"\
	".\..\net\JSocketInputStream.h"\
	".\..\net\JSocketOutputStream.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\io\JIOException.h"\
	".\..\net\JInetAddress.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JException.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JThrowable.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JSocketObj.obj" : $(SOURCE) $(DEP_CPP_JSOCKETO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JSubtractObj.cpp
DEP_CPP_JSUBT=\
	".\..\modules\JSubtractObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JGreaterThanObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\modules\JAccumulatorObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	

"$(INTDIR)\JSubtractObj.obj" : $(SOURCE) $(DEP_CPP_JSUBT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JSwitchObj.cpp
DEP_CPP_JSWIT=\
	".\..\modules\JSwitchObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JBtnObj.h"\
	".\..\modules\JLEDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JSwitchObj.obj" : $(SOURCE) $(DEP_CPP_JSWIT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTimeObj.cpp
DEP_CPP_JTIME=\
	".\..\modules\JTimeObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\lang\JString.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JDList.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JTimeObj.obj" : $(SOURCE) $(DEP_CPP_JTIME) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTimerObj.cpp
DEP_CPP_JTIMER=\
	".\..\modules\JTimerObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JSystem.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JObject.h"\
	".\..\lang\JReference.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JTimerObj.obj" : $(SOURCE) $(DEP_CPP_JTIMER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JTNGObj.cpp
DEP_CPP_JTNGO=\
	".\..\modules\JTNGObj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JReference.h"\
	".\..\util\JList.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JDescriptor.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JTNGObj.obj" : $(SOURCE) $(DEP_CPP_JTNGO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\Oop\modules\JWaveFileObj.cpp
DEP_CPP_JWAVE=\
	".\..\modules\JWaveFileObj.h"\
	".\..\modules\JWaveOutObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JInteger.h"\
	".\..\lang\JSystem.h"\
	".\..\neat\JFileProperty.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\io\JIOException.h"\
	".\..\io\JEOFException.h"\
	".\..\awt\JWindow.hpp"\
	".\..\modules\JRecorderObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\io\JFileInputStream.h"\
	".\..\io\JFileOutputStream.h"\
	".\..\io\JBufferedInputStream.h"\
	".\..\io\JBufferedOutputStream.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	".\..\io\JFilterInputStream.h"\
	".\..\io\JFilterOutputStream.h"\
	".\..\neat\JStringProperty.h"\
	".\..\lang\JException.h"\
	".\..\lang\JThrowable.h"\
	

"$(INTDIR)\JWaveFileObj.obj" : $(SOURCE) $(DEP_CPP_JWAVE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JWaveInObj.cpp
DEP_CPP_JWAVEI=\
	".\..\modules\JWaveInObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JWindow.hpp"\
	".\..\modules\JWaveOutObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\util\JList.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	

"$(INTDIR)\JWaveInObj.obj" : $(SOURCE) $(DEP_CPP_JWAVEI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JWaveOutObj.cpp
DEP_CPP_JWAVEO=\
	".\..\modules\JWaveOutObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JBlock.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JIntegerListProperty.h"\
	".\..\awt\JComponent.h"\
	".\..\awt\JWindow.hpp"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JThread.h"\
	".\..\lang\JCriticalSection.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JString.h"\
	".\..\neat\JProperty.h"\
	".\..\util\JArray.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JColor.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRegion.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JHashTable.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\neat\JFocusSet.h"\
	".\..\lang\JObject.h"\
	".\..\util\JList.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JFRect.h"\
	".\..\util\JDictionary.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	

"$(INTDIR)\JWaveOutObj.obj" : $(SOURCE) $(DEP_CPP_JWAVEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\bc5\oop\modules\JXORObj.cpp
DEP_CPP_JXORO=\
	".\..\modules\JXORObj.h"\
	".\..\neat\JLinkObj.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JXORObj.obj" : $(SOURCE) $(DEP_CPP_JXORO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "awt"

!IF  "$(CFG)" == "modules - Win32 Release"

"awt - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="awt - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "neat"

!IF  "$(CFG)" == "modules - Win32 Release"

"neat - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="neat - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JMixerObj.cpp
DEP_CPP_JMIXE=\
	".\..\modules\JMixerObj.h"\
	".\..\lang\JMath.h"\
	".\..\neat\JLinkObj.h"\
	".\..\awt\JWindow.hpp"\
	".\..\neat\JANDObj.h"\
	".\..\lang\JObject.h"\
	".\..\neat\JViewSet.h"\
	".\..\neat\JModuleObj.h"\
	".\..\util\JHashTable.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JDList.h"\
	".\..\awt\JComponent.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\util\JList.h"\
	".\..\awt\JRect.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\lang\JReference.h"\
	".\..\lang\JDescriptor.h"\
	".\..\lang\JString.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	

"$(INTDIR)\JMixerObj.obj" : $(SOURCE) $(DEP_CPP_JMIXE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "base"

!IF  "$(CFG)" == "modules - Win32 Release"

"base - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\oop.mak CFG="base - Win32 Release" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\Bc5\oop\modules\JTNG3Obj.cpp
DEP_CPP_JTNG3=\
	".\..\modules\JTNG3Obj.h"\
	".\..\lang\JInteger.h"\
	".\..\neat\JIntegerProperty.h"\
	".\..\neat\JLinkObj.h"\
	".\..\modules\JTNGObj.h"\
	".\..\modules\JNOTObj.h"\
	".\..\neat\JANDObj.h"\
	".\..\neat\JModuleObj.h"\
	".\..\neat\JViewObj.h"\
	".\..\util\JArray.h"\
	".\..\lang\JBlock.h"\
	".\..\awt\JColor.h"\
	".\..\neat\JFocusSet.h"\
	".\..\neat\JProperty.h"\
	".\..\neat\JFRect.h"\
	".\..\awt\JGraphics.h"\
	".\..\awt\JEvent.h"\
	".\..\awt\JRegion.h"\
	".\..\util\JDictionary.h"\
	".\..\awt\JComponent.h"\
	".\..\neat\JFPoint.h"\
	".\..\neat\JFDimension.h"\
	".\..\lang\JObject.h"\
	".\..\io\JInputStream.h"\
	".\..\io\JOutputStream.h"\
	".\..\lang\JReference.h"\
	".\..\awt\JFont.h"\
	".\..\awt\JRect.h"\
	".\..\lang\JString.h"\
	".\..\awt\JPoint.h"\
	".\..\awt\JDimension.h"\
	".\..\util\JHashTable.h"\
	".\..\awt\JInsets.h"\
	".\..\awt\JFontMetrics.h"\
	".\..\awt\JLayoutManager.h"\
	".\..\util\JList.h"\
	".\..\lang\JDescriptor.h"\
	".\..\neat\JViewSet.h"\
	".\..\util\JDList.h"\
	

"$(INTDIR)\JTNG3Obj.obj" : $(SOURCE) $(DEP_CPP_JTNG3) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
