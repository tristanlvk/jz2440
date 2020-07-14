## === for top level =================
#TOPDIR=./..

#EXCLUDE_DIRS= include builds
#LIBPATH=$(TOPDIR)/builds/lib
#BINPATH=$(TOPDIR)/builds/bin

#include $(TOPDIR)/Makefile.env


## === for top module =================
TOPDIR=./../..

GCCLIBPATH=/usr/local/arm


TARGET=test_led

LIBPATH=$(TOPDIR)/builds/lib
BINPATH=$(TOPDIR)/builds/bin

CFLAGS= -I$(TOPDIR)/include/
LDFLAGS= -nostdlib -L$(LIBPATH) -l:jz2440_led.a -l:jz2440_clock.a

include $(TOPDIR)/Makefile.env

# for toplevel
$(TARGET):$(OBJS_C) $(OBJS_S)
	$(CC) -o $@.elf -Ttext 0 $(OBJS_S) $(OBJS_C) $(LDFLAGS)
	$(OBJCOPY) -O binary -S $@.elf $@.bin
	$(OBJDUMP) -D $@.elf > $@.dis
	cp $@.bin $(BINPATH)


## === for sub module =================
#TOPDIR=./../..

#LIB=jz2440_led
#LIBPATH=$(TOPDIR)/builds/lib

#INCPATH=$(TOPDIR)/include/
#CFLAGS= -I$(INCPATH)

#include $(TOPDIR)/Makefile.env


