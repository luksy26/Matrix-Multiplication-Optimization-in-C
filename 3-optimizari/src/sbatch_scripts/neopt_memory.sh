#!/bin/bash

valgrind  --tool=memcheck --leak-check=full --log-file=memory_outputs/neopt.memory ./tema3_neopt ../input/input_valgrind
exit 0
