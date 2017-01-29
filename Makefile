
EXTRA_CFLAGS := -I /usr/xenomai/include/

ifneq (${KERNELRELEASE},)
	obj-m += reactionTime.o

else
	ARCH ?= arm
	CROSS_COMPILE ?= /usr/local/cross/rpi/bin/arm-linux-
	KERNEL_DIR = /usr/src/linux
	MODULE_DIR := $(shell pwd)
	CFLAGS := -Wall -g 

.PHONY: all
all:: modules

.PHONY: modules
modules:
	${MAKE} -C ${KERNEL_DIR} SUBDIRS=${MODULE_DIR}  modules

XENOCONFIG=/usr/xenomai/bin/xeno-config

.PHONY: clean
clean::
	rm -f  *.o  .*.o  .*.o.* *.ko  .*.ko  *.mod.* .*.mod.* .*.cmd *~
	rm -f Module.symvers Module.markers modules.order 
	rm -rf .tmp_versions
endif

