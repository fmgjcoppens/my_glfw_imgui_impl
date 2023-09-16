#!/usr/bin/env bash

cmake -S . -B build
cd build
make -j
cd ..
ln -svf build/MyApp .

