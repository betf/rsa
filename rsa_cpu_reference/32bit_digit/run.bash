#!/bin/bash

gcc mul32x32.c dbg.c restoringDiv.c modInverse.c modInverse_Table.c monPro.c main.c input.c -lm -o main
./main;


