#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "OneginHelpers.cpp"
#include "FileTools.cpp"
#include "Myqsort.cpp"
#include "Comparators.cpp"

#define NAME_SIZE 100

int main(int argc, char* argv[])
{   
    if (argc != 3)
    {   
        printf("ERROR: two arguments required!\n"
                "Fuck you! I need two file names: the one I read from and the one I write into.\n");
        return EXIT_FAILURE;
    }

    const char* readfile = argv[1];
    const char* writefile = argv[2];

    FileInfo OneginInfo = {};
    CreateFileInfo(&OneginInfo, readfile);

    ClearFile(writefile);
    
    qsort(OneginInfo.indexes, OneginInfo.lines, sizeof(OneginInfo.indexes[0]), CompareLines);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);

    WriteDelimeter(writefile);  // different sortings of Onegin are divided by word "DELIMETER"

    Myqsort(OneginInfo.indexes, 0, OneginInfo.lines - 1, sizeof(OneginInfo.indexes[0]), CompareLinesByEnd);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);;

    WriteDelimeter(writefile);

    qsort(OneginInfo.indexes, OneginInfo.lines, sizeof(OneginInfo.indexes[0]), CompareLinesAddress);
    WriteIntoFile(writefile, OneginInfo.indexes, OneginInfo.lines);

    return EXIT_SUCCESS;
}
