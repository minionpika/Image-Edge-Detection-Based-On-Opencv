#!/bin/bash
g++ -std=c++11 th.cpp `pkg-config --libs --cflags opencv` -o th
./th src.jpg
