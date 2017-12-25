#!/bin/bash
g++ -isystem ${GTEST_DIR}/include -pthread main.cpp ${GTEST_DIR}/libgtest.a -o travis_test
