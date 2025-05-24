obj-m := l3t2.o
obj-m += l3t3.o
obj-m += l3t4.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

BUILD_DIR := $(PWD)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
