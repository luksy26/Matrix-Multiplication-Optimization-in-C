#!/bin/bash

valgrind  --tool=memcheck --leak-check=full --log-file=memory_outputs/opt_m.memory ./tema3_opt_m ../input/input_valgrind
exit 0
