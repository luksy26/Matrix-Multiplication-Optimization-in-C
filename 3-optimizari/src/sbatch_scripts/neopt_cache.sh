#!/bin/bash

valgrind  --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file=cache_outputs/neopt.cache ./tema3_neopt ../input/input_valgrind
