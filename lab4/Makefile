obj-m := l4t1.o
obj-m += l4t2.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

CC_FLAGS_FPU := -mhard-float
CFLAGS_l4t2.o += $(CC_FLAGS_FPU)
CFLAGS_REMOVE_l4t2.o += $(CC_FLAGS_NO_FPU)

BUILD_DIR := $(PWD)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
