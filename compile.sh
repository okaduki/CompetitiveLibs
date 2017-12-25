#!/bin/bash
g++ -isystem ${GTEST_DIR}/include -pthread main.cpp libgtest.a -o travis_test
