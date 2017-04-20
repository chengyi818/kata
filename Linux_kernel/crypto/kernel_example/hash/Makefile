ifneq ($(KERNELRELEASE),)
	obj-m += sha1.o
else
	SRC_PWD := $(shell pwd)
	EXTRA_CFLAGS += -DDEBUG -D -I$(SRC_PWD)/
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
endif

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf modules.order Module.symvers *.o *~ *.ko *.mod.c .*.cmd .tmp_versions
