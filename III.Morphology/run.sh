#!/bin/bash
g++ -std=c++11 mor.cpp `pkg-config --libs --cflags opencv` -o mor
./mor src.jpg
