#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "OneginHelpers.cpp"
// #include "OldFileTools.cpp"
// #include "OldMyqsort.cpp"
// #include "OldComparators.cpp"

#include "FileTools.cpp"
#include "Myqsort.cpp"
#include "Comparators.cpp"

#define NAME_SIZE 100

int main(void)
{   
    // printf("Starting in main()...\n");

    clock_t start = clock();

    const char readfile[NAME_SIZE] = "RawOneginText.txt";
    const char writefile[NAME_SIZE] = "SortedOnegin.txt";

    FileInfo OneginInfo = {};
    // printf("I want to create OneginInfo...\n");
    CreateFileInfo(&OneginInfo, readfile);
    // printf("Created OneginInfo...\n");

    ClearFile(writefile);
    
    qsort(OneginInfo.indexes, OneginInfo.lines, sizeof(OneginInfo.indexes[0]), CompareLines);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);

    WriteDelimeter(writefile);  // different sortings of Onegin are divided by word "DELIMETER"

    Myqsort(OneginInfo.indexes, 0, OneginInfo.lines - 1, sizeof(OneginInfo.indexes[0]), CompareLinesByEnd);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);;

    WriteDelimeter(writefile);

    qsort(OneginInfo.indexes, OneginInfo.lines, sizeof(OneginInfo.indexes[0]), CompareLinesAddress);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);

    clock_t end = clock();

    printf("Execution time: %lg\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);

    return EXIT_SUCCESS;
}
