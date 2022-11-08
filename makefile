# Copyright (C) Dalitso Sakala <contact@dalitsosakala.com>
# All Rights Reserved.
# Unauthorized copying of this file, via any medium is strictly
# prohibited proprietary and confidential.

build: clean sources/numbers.c sources/strings.c include/numbers.h include/strings.h
	gcc -fPIC -Wall -I./include -c sources/*.c\
	&& gcc -shared -o libc_utils.so *.o\
	&& rm *.o

clean:
	if [ -f *.so ]; then rm *.o *.out *.so 2> /dev/null;echo; fi
buildn: build examples/numbers.c
	gcc examples/numbers.c -lc_utils -Iinclude -L. -o a.out
buildt: build examples/test.c
	gcc examples/test.c -lc_utils -Iinclude -L. -o a.out

run: export LD_LIBRARY_PATH = $(shell pwd)
run: a.out libc_utils.so
	  ./a.out 
