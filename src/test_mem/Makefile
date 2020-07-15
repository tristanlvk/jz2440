## === for top level =================
#TOPDIR=./..

#EXCLUDE_DIRS= include builds
#LIBPATH=$(TOPDIR)/builds/lib
#BINPATH=$(TOPDIR)/builds/bin

#include $(TOPDIR)/Makefile.env


## === for top module =================
TOPDIR=./../..

GCCLIBPATH=/usr/local/arm


TARGET=test_mem

LIBPATH=$(TOPDIR)/builds/lib
BINPATH=$(TOPDIR)/builds/bin

CFLAGS= -I$(TOPDIR)/include/
LDFLAGS= -nostdlib -T sdram.lds -L$(LIBPATH) -l:jz2440_led.a -l:jz2440_clock.a -l:jz2440_mem.a

include $(TOPDIR)/Makefile.env

# for toplevel
$(TARGET):$(OBJS_C) $(OBJS_S)
	$(CC) -o $@.elf $(OBJS_S) $(OBJS_C) $(LDFLAGS)
	$(OBJCOPY) -O binary -S $@.elf $@.bin
	$(OBJDUMP) -d $@.elf > $@.dis
	cp $@.bin $(BINPATH)


## === for sub module =================
#TOPDIR=./../..

#LIB=jz2440_led
#LIBPATH=$(TOPDIR)/builds/lib

#INCPATH=$(TOPDIR)/include/
#CFLAGS= -I$(INCPATH)

#include $(TOPDIR)/Makefile.env


