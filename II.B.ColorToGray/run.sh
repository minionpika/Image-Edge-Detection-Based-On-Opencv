#!/bin/bash
g++ -std=c++11 gr.cpp `pkg-config --libs --cflags opencv` -o gr
./gr src.jpg
