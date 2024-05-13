#!/bin/bash

valgrind  --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file=cache_outputs/blas.cache ./tema3_blas ../input/input_valgrind
exit 0
