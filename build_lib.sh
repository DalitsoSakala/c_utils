# Copyright (C) Dalitso Sakala <contact@dalitsosakala.com>
# All Rights Reserved.
# Unauthorized copying of this file, via any medium is strictly
# prohibited proprietary and confidential.

NAME=lib$(pwd)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
rm *.o *.so 2> /dev/null
gcc -fPIC -Wall -I./include -c sources/*.c >>logs 2>&1\
&& gcc -shared -o libc_utils.so *.o\
&& rm *.o 2>/dev/null
