all:
	cp temp/Makefile ../../../../src/linux-5.15.4/
	cp syscall_64.tbl ../../../../src/linux-5.15.4/arch/x86/entry/syscalls/syscall_64.tbl
	cp syscalls.h ../../../../src/linux-5.15.4/include/linux/syscalls.h
	mkdir ../../../../src/linux-5.15.4/prime_syscall
	cp ../user-space_test/prime_syscall/* ../../../../src/linux-5.15.4/prime_syscall
