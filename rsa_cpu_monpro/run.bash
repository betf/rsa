#!/bin/bash

gcc mul32x32.c dbg.c restoringDiv.c modInverse.c modInverse_Table.c monPro.c main.c test_vectors.c -lm -o main
./main


