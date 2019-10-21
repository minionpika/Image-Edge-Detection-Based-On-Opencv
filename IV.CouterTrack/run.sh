#!/bin/bash
g++ -std=c++11 can.cpp `pkg-config --libs --cflags opencv` -o can
./can src.jpg
