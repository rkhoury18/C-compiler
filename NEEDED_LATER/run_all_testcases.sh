#!/bin/bash

# TO BE WORKED ON

# COMPILING STEP

# bin/c_compiler -S test_program.c -o test_program.s

# ASSEMBLY

# mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s

# LINK W DRIVER FILE

# mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o test_program_driver.c

# SIMULATE MIPS

# qemu-mips test_program

# Check exit code of 0