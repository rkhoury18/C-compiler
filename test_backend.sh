#!/bin/bash

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    >&2 echo "warning: dos2unix is not installed."
    # This should work on Linux and MacOS, it matches all the carriage returns with sed and removes
    # them.  `tr` is used instead of `sed` because some versions of `sed` don't recognize the
    # carriage return symbol.  Something similar could be implemented with `sed` if necessary or
    # worst case it could be disabled by substituting it with `cat`.  One other thing to note is
    # that there are no quotes around the \r, which is so that it gets converted by bash.
    DOS2UNIX="tr -d \r"
    # DOS2UNIX="sed -e s/\r//g"
    # DOS2UNIX="cat"
fi

echo " Cleaning Directories... "
make clean &> /dev/null # Throw Away

mkdir output # For Output Files
mkdir debug # Error Files

echo ""
echo "========================================"
echo " BUILDING COMPILER"
echo "========================================"
echo ""

make bin/c_compiler -B #&> debug/debugMake.txt # Redirect Make errors 

if [[ "$?" -ne 0 ]]; then
    echo "Build Failed.";
else 
    echo "Build Successful.";
fi
echo ""
echo "========================================="
echo "              Run TestCases              "
echo "========================================="
echo ""

# Iterate through Each Folder

TOTAL_TESTS=0
PASSED_TESTS=0

for fileName in compiler_tests/*/*_driver.c; do

    ((TOTAL_TESTS=TOTAL_TESTS+1))

    IN_DRIVE="${fileName}"
    IN_COMPILE="${fileName%_driver.c}.c"

    # Get File Name

    FILE_TEMP="${fileName%_driver.c}"
    FILE="${FILE_TEMP##*/}"

    echo " Test Case ${TOTAL_TESTS} -- ${FILE} "
    echo ""

    # Create Output Folders

    TMP="${fileName%/*}"
    FOLDER="${TMP#*/}"
    OUT_FOLDER="output/${FOLDER}"
    mkdir $OUT_FOLDER &> /dev/null

    # Create FILEPATHS

    OUT_COMPILE="${OUT_FOLDER}""/""${FILE}_compile.s"
    OUT_PRINT="${OUT_FOLDER}""/""${FILE}_print.txt"
    OUT_ERROR="${OUT_FOLDER}""/""${FILE}_error.txt"
    OUT_ASSEMBLE="${OUT_FOLDER}""/""${FILE}_assemble.o"
    OUT_EXE="${OUT_FOLDER}""/""${FILE}"

    bin/c_compiler -S $IN_COMPILE -o $OUT_COMPILE -P $OUT_PRINT &>> $OUT_ERROR # RUN COMPILER
    mips-linux-gnu-gcc-10 -mfp32 -o $OUT_ASSEMBLE -c $OUT_COMPILE &>> $OUT_ERROR # ASSEMBLE
    mips-linux-gnu-gcc-10 -mfp32 -static -o $OUT_EXE $OUT_ASSEMBLE $IN_DRIVE &>> $OUT_ERROR # LINK
    qemu-mips $OUT_EXE &>> $OUT_ERROR # RUN

    if [[ "$?" -eq 0 ]]; then
        echo " Test Passed ";
        ((PASSED_TESTS=PASSED_TESTS+1))
    else 
        echo " Test Failed ";
    fi
    echo ""
    echo "<><><><><><><><><><>><><><><><><><><><><>"
    echo ""

done

echo ""
echo "========================================="
echo "                 Results                 "
echo "========================================="
echo ""
echo "${PASSED_TESTS} / ${TOTAL_TESTS}"
echo " Tests Passed"
echo ""

