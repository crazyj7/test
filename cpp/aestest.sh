#!/bin/sh
g++ -c aes.cpp aesw.cpp
g++ -c aestest.cpp
g++ -o a.out aes.o aesw.o aestest.o
./a.out
