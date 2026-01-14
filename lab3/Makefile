# Makefile (kernel module + user program)

obj-m += virtchar7_time.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all: module user

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

user:
	$(CC) -O2 -Wall -Wextra -o user_read_time user_read_time.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) user_read_time
