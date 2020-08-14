## === for top level =================

export G_DEBUG=TRUE
export G_STRIP_FUNC=


TOPDIR=.

EXCLUDE_DIRS= include builds
LIBPATH=$(TOPDIR)/builds/lib
BINPATH=$(TOPDIR)/builds/bin

include $(TOPDIR)/Makefile.env

## === for top module =================
#TOPDIR=./../..

#TARGET=main

#LIBPATH=$(TOPDIR)/builds/lib
#BINPATH=$(TOPDIR)/builds/bin

#CFLAGS= -I$(TOPDIR)/include/
#LDFLAGS= -L$(LIBPATH) -l:xx.a

#include $(TOPDIR)/Makefile.env



## === for sub module =================
#TOPDIR=./../..

#LIB=xx.a
#LIBPATH=$(TOPDIR)/builds/lib

#INCPATH=$(TOPDIR)/include/
#CFLAGS= -I$(INCPATH)

#include $(TOPDIR)/Makefile.env


