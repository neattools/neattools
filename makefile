export

arch=$(shell arch)
MAKE=make

ARCH = unknown

ifeq ($(arch),sun4)
 ARCH = solaris_sun4
 EXTS =-lnsl -lsocket
 EXTW =$(EXTS) -L/usr/X11R6/lib -lX11
endif

ifeq ($(arch),i86pc)
 ARCH = solaris_i86pc
 EXTS =-lnsl -lsocket
 EXTW =$(EXTS) -L/usr/X11R6/lib -lX11
 MAKE=gmake
endif

ifeq ($(arch),i686)
 ARCH = linux_i686
 EXTS =
 EXTW = -L/usr/X11R6/lib -lX11
endif

LIB_DIR = lib/$(ARCH)
BIN_DIR = bin/$(ARCH)
OOP_BIN = $(BIN_DIR)/oop
OOPW_BIN = $(BIN_DIR)/oopw
SUB_DIRS = lang io net util main awt neat modules mainw
SUB_MF = ../makefile.sub
OOP_DIRS = main net util io lang util
OOPW_DIRS = mainw modules neat awt net util io lang util
OOP_DEST = $(OOP_DIRS:%=$(LIB_DIR)/lib%.a)
OOPW_DEST = $(OOPW_DIRS:%=$(LIB_DIR)/lib%.a)
INCLUDES = $(OOPW_DIRS:%=-I../%) -I/usr/X11R6/include

CFLAGS=-O2 -fPIC -DBSD_COMP -D$(ARCH)
LIBS=-lm -lpthread $(EXTS)
LIBW=-lm -lpthread $(EXTW)
RM=rm -f
AR=ar
AR_FLAGS = rv
CP=cp
CC=gcc

all ::
	@if [ -d lib ]; then true; else mkdir -p lib; fi
	@if [ -d bin ]; then true; else mkdir -p bin; fi
	@if [ -d $(LIB_DIR) ]; then true; else mkdir -p $(LIB_DIR); fi
	@if [ -d $(BIN_DIR) ]; then true; else mkdir -p $(BIN_DIR); fi
	@for d in $(SUB_DIRS); do ($(MAKE) -C $$d -f $(SUB_MF)); done

all:: $(OOP_BIN) $(OOPW_BIN)

$(OOP_BIN): $(OOP_DEST)
	$(CC) -o $@ $(LIBS) $(OOP_DEST)

$(OOPW_BIN): $(OOPW_DEST)
	$(CC) -o $@ $< $(LIBW) $(OOPW_DEST)

tgz :
	tar cvf oop.tar $(OOP_DIRS) main makefile.sub makefile.oop
	tar cvf oopw.tar $(OOPW_DIRS) main mainw\
 makefile.oop makefile.sub makefile run
	$(RM) oop.tar.gz oopw.tar.gz
	gzip oop.tar
	gzip oopw.tar

tar :
	tar cvf $(ARCH).tar $(BIN_DIR)/oopw $(LIB_DIR)/* *.ntl
	gzip $(ARCH).tar

depend :
	@for d in $(SUB_DIRS); do ($(MAKE) -C $$d -f $(SUB_MF) depend); done

.PHONY : clean
clean :
	@for d in $(SUB_DIRS); do ($(MAKE) -C $$d -f $(SUB_MF) clean); done
	$(RM) $(OOP_BIN) $(OOPW_BIN)
