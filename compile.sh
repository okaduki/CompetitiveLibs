#!/bin/bash
${CXX} -isystem ${GTEST_DIR}/include -pthread -lgmp test/BigInt.cpp ${GTEST_DIR}/libgtest.a -o travis_test
