#!/bin/bash

valgrind  --tool=memcheck --leak-check=full --log-file=memory_outputs/blas.memory ./tema3_blas ../input/input_valgrind
exit 0
