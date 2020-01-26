#!/bin/bash


# Makefile
#

include ../../pi3/circle-stdlib/Config.mk

CIRCLEHOME = ../../pi3/circle-stdlib/libs/circle
NEWLIBDIR = ../../pi3/circle-stdlib/install/$(NEWLIB_ARCH)

OBJS	= main.o kernel.o

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../../pi3/circle-stdlib/include
LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
	../../pi3/littlevgl/liblvgl.a \
	../../pi3/littlevgl/liblv_examples.a \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/lib/fs/fat/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a
  	
CFLAGS += -Wno-narrowing
