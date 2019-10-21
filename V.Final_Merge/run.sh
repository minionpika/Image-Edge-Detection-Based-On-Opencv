#!/bin/bash
g++ -std=c++11 final.cpp `pkg-config --libs --cflags opencv` -o final
./final src.jpg
