# Copyright (C) Dalitso Sakala <contact@dalitsosakala.com>
# All Rights Reserved.
# Unauthorized copying of this file, via any medium is strictly
# prohibited proprietary and confidential.

build: clean sources/numbers.c sources/strings.c include/numbers.h include/strings.h
	gcc -fPIC -Wall -I./include -c sources/*.c >>logs 2>&1\
	&& gcc -shared -o libc_utils.so *.o\
	&& rm *.o

clean:
	if [ -f *.so ]; then rm *.o *.so 2> /dev/null;echo; fi