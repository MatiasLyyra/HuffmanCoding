#!/bin/sh

mkdir build/coverage_data
cd build/coverage_data

cmake ../.. -DCMAKE_BUILD_TYPE=coverage
make
make HuffmanCoverage

mv coverage ../../dokumentaatio/coverage

cd ..
rm -r coverage_data
