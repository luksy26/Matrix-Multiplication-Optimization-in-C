#!/bin/bash

valgrind  --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file=cache_outputs/opt_m.cache ./tema3_opt_m ../input/input_valgrind
exit 0
