ifneq ($(KERNELRELEASE),)
	obj-m := ptp_fake.o

else

	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

clean:
	rm -f modules.order Module.symvers ptp_fake.mod.c *.ko *.o
