## === for src level =================
TOPDIR=./..

EXCLUDE_DIRS= include builds
LIBPATH=$(TOPDIR)/builds/lib
BINPATH=$(TOPDIR)/builds/bin

include $(TOPDIR)/Makefile.env

# set the dependency relationship of TARGET and LIB
test_led: jz2440_led jz2440_clock
test_uart: jz2440_led jz2440_clock jz2440_uart
test_mem: jz2440_clock jz2440_uart jz2440_mem
test_nand: jz2440_clock jz2440_uart jz2440_mem



## === for top module =================
#TOPDIR=./../..

#TARGET=main

#LIBPATH=$(TOPDIR)/builds/lib
#BINPATH=$(TOPDIR)/builds/bin

#CFLAGS= -I$(TOPDIR)/include/xx
#LDFLAGS= -lxx

#include $(TOPDIR)/Makefile.env



## === for sub module =================
#TOPDIR=./../..

#LIB=xx.a
#LIBPATH=$(TOPDIR)/builds/lib

#INCPATH=$(TOPDIR)/include/xx
#CFLAGS= -I$(INCPATH)

#include $(TOPDIR)/Makefile.env


