#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "OneginHelpers.cpp"
#include "FileTools.cpp"
#include "Myqsort.cpp"
#include "Comparators.cpp"

#define NAME_SIZE 100

struct FileInfo
{
    int lines;
    char* filename;
    int size;
    char* buffer;
    char** indexes;
};


int main(void)
{   
    const char readfile[NAME_SIZE] = "RawOneginText.txt";
    const char writefile[NAME_SIZE] = "SortedOnegin.txt";

    FileInfo OneginInfo = {};

    ClearFile(writefile);

    OneginInfo.size = GetFileSize(readfile);

    OneginInfo.buffer = (char*)calloc(OneginInfo.size + 1, sizeof(char));  // file_size + 1 was made for adding '\0' at the end of the buffer

    ReadFromFile(readfile, OneginInfo.buffer, OneginInfo.size);

    OneginInfo.lines = StrCount(OneginInfo.buffer, '\n') + 1;  // there is no '\n' for the last line of the file. That's why +1

    OneginInfo.indexes = (char**)calloc(OneginInfo.lines, sizeof(char*));

    OneginInfo.indexes[0] = OneginInfo.buffer;

    for (int i = 0; i < OneginInfo.lines - 1; i++)
        OneginInfo.indexes[i + 1] = strchr(OneginInfo.indexes[i], '\n') + sizeof(char);
    
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


