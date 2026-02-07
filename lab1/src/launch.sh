#!/usr/bin/bash
if g++ -fsanitize=address lab1.cpp rect.cpp barrel.cpp matrix.cpp mystring.cpp textwrapper.cpp -o lab1; then 
    ./lab1;
fi