EXTRA_CFLAGS = -Wall
obj-m = exam.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean