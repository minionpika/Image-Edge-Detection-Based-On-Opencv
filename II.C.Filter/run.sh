#!/bin/bash
g++ -std=c++11 fil.cpp `pkg-config --libs --cflags opencv` -o fil
./fil src.jpg
