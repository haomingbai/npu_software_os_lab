obj-m := l2t1.o
obj-m += l2t2.o
obj-m += l2t3.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

BUILD_DIR := $(PWD)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
