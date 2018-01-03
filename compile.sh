#!/bin/bash
${CXX} -isystem ${GTEST_DIR}/include -pthread test/BigInt.cpp ${GTEST_DIR}/libgtest.a -o travis_test -lgmp
