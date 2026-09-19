#ifndef FileTools_cpp

#define FileTools_cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys\stat.h>
#include <errno.h>

#include "OneginHelpers.cpp"

int     GetFileSize         (const char* filename);

void    ClearFile           (const char* filename);

int     ReadFromFile        (const char* filename, char destination[], int size);

int     WriteIntoFile       (const char* filename, char* source[], int lines);

void    WriteDelimeter      (const char* filename);



int GetFileSize(const char* filename)  //returns byte size (including '\r' and ' \n')
{   
    assert(filename);

    struct stat FileInfo = {};

    FILE* file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("ERROR: GetFileSize -> fopen()");
        abort();
    }

    stat(filename, &FileInfo);

    fclose(file);

    return FileInfo.st_size;
}

void ClearFile(const char* filename)
{
    assert(filename);

    FILE* file = fopen(filename, "w");
    
    if (file == NULL)
    {
        perror("ERROR: GetFileSize -> fopen()");
        abort();
    }

    fclose(file);
}

int ReadFromFile(const char* filename, char destination[], int size)
{   
    assert(filename);
    assert(destination);

    int read_bytes = 0;

    FILE* file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("ERROR: GetFileSize -> fopen()");
        abort();
    }

    read_bytes = fread(destination, sizeof(char), size, file);
    
    destination[size] = '\0';

    fclose(file);

    return read_bytes;
}

int WriteIntoFile(const char* filename, char* source[], int lines)
{   
    assert(filename);
    assert(source);

    FILE *file = fopen(filename, "ab");

    if (file == NULL)
    {
        perror("ERROR: GetFileSize -> fopen()");
        abort();
    }

    for (int i = 0; i < lines; i++)
        fwrite(source[i], sizeof(char), LFstrlen(source[i]), file);

    fclose(file);

    return 1;
}

void WriteDelimeter(const char* filename)
{   
    assert(filename);

    FILE* file = fopen(filename, "a");

    if (file == NULL)
    {
        perror("ERROR: GetFileSize -> fopen()");
        abort();
    }

    fputc('\n', file);
    fputs("DELIMETER", file);

    for (int i = 0; i < 40; i++)
        fputc('*', file);
    fputc('\n', file);

    fclose(file);    
}

#endif
