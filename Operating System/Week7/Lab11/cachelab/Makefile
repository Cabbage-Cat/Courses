# Microsoft Developer Studio Generated NMAKE File, Based on exercise5.dsp
!IF "$(CFG)" == ""
CFG=exercise5 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to exercise5 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "exercise5 - Win32 Release" && "$(CFG)" != "exercise5 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "exercise5.mak" CFG="exercise5 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "exercise5 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "exercise5 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "exercise5 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\exercise5.exe"


CLEAN :
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\driver.obj"
	-@erase "$(INTDIR)\rotate.obj"
	-@erase "$(INTDIR)\smooth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\exercise5.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\exercise5.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\exercise5.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\exercise5.pdb" /machine:I386 /out:"$(OUTDIR)\exercise5.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\driver.obj" \
	"$(INTDIR)\rotate.obj" \
	"$(INTDIR)\smooth.obj"

"$(OUTDIR)\exercise5.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "exercise5 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\exercise5.exe"


CLEAN :
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\driver.obj"
	-@erase "$(INTDIR)\rotate.obj"
	-@erase "$(INTDIR)\smooth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\exercise5.exe"
	-@erase "$(OUTDIR)\exercise5.ilk"
	-@erase "$(OUTDIR)\exercise5.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\exercise5.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\exercise5.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\exercise5.pdb" /debug /machine:I386 /out:"$(OUTDIR)\exercise5.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\driver.obj" \
	"$(INTDIR)\rotate.obj" \
	"$(INTDIR)\smooth.obj"

"$(OUTDIR)\exercise5.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("exercise5.dep")
!INCLUDE "exercise5.dep"
!ELSE 
!MESSAGE Warning: cannot find "exercise5.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "exercise5 - Win32 Release" || "$(CFG)" == "exercise5 - Win32 Debug"
SOURCE=.\cache.c

"$(INTDIR)\cache.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\driver.c

"$(INTDIR)\driver.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rotate.c

"$(INTDIR)\rotate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\smooth.c

"$(INTDIR)\smooth.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

