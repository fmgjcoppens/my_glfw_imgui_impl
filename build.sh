#!/usr/bin/env bash

make clean && CXXFLAGS="-I../HazelPVR/include/vendor/glfw/include -L../HazelPVR/_build/include/vendor/glfw/src -lglfw3" make -j

