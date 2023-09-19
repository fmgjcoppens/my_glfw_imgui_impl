#!/usr/bin/env bash

COMPILER=clang++
CXXFLAGS='-Wall -Wextra -g -Ofast'
BUILD_DIR=_build_linux

cmake \
    -DCMAKE_CXX_COMPILER=${COMPILER} \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
    -S . -B ${BUILD_DIR}

(cd ${BUILD_DIR} && make -j)

ln -svf ${BUILD_DIR}/MyApp .
