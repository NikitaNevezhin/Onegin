#ifndef FILETOOL_CPP

#define FILETOOLS_CPP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys\stat.h>
#include <errno.h>

#include "OneginHelpers.cpp"

struct LineInfo
{
    char* line;
    int length;
};

struct FileInfo
{
    int lines;
    const char* filename;
    int size;
    char* buffer;
    LineInfo** indexes;
};

int     GetFileSize         (const char* filename);

void    ClearFile           (const char* filename);

int     ReadFromFile        (const char* filename, char destination[], int size);

int     WriteIntoFile       (const char* filename, LineInfo* source[], int lines);

void    WriteDelimeter      (const char* filename);

void    CreateFileInfo      (FileInfo *file_info, const char* filename);

void    PrintFileInfo       (FileInfo *file_info);



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

int WriteIntoFile(const char* filename, LineInfo* source[], int lines)
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
        fwrite(source[i]->line, sizeof(char), source[i]->length, file);

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

void CreateFileInfo(FileInfo *file_info, const char* filename)
{
    file_info->filename = filename;
    file_info->size = GetFileSize(filename); 
    file_info->buffer = (char*)calloc(file_info->size + 1, sizeof(char));  // file_size + 1 was made for adding '\0' at the end of the buffer

    if (file_info->buffer == NULL)
    {
        printf("calloc returned NULL pointer in CreateFileInfo\n");
        abort();
    }
    // printf("CreateFileInfo: trying to read from file...\n");

    ReadFromFile(filename, file_info->buffer, file_info->size);

    // printf("CreateFileInfo: I read from file...\n");

    file_info->lines = StrCount(file_info->buffer, '\n') + 1;  // there is no '\n' for the last line of the file. That's why +1

    // printf("CreateFileInfo: I try to get memory for LineInfo...\n");
    file_info->indexes = (LineInfo**)calloc(file_info->lines, sizeof(LineInfo*));
    // printf("CreateFileInfo: I executed calloc...\n");

    if (file_info->indexes == NULL)
    {
        printf("calloc returned NULL pointer in CreateFileInfo\n");
        abort();
    }

    // printf("CreateFileInfo: indexes is not NULL");
    for (int i = 0; i < file_info->lines; i++) 
    {
        file_info->indexes[i] = (LineInfo*)calloc(1, sizeof(LineInfo));

        if (file_info->indexes[i] == NULL) 
        {
            printf("calloc returned NULL pointer for indexes[%d] in CreateFileInfo\n", i);
            abort();
        }
    }

    file_info->indexes[0]->line = file_info->buffer;
    file_info->indexes[0]->length = LFstrlen(file_info->indexes[0]->line);

    // printf("Starting to fill LineInfo...\n");

    for (int i = 0; i < file_info->lines - 1; i++)
    {
        file_info->indexes[i + 1]->line = strchr(file_info->indexes[i]->line, '\n') + sizeof(char);
        file_info->indexes[i + 1]->length = LFstrlen(file_info->indexes[i + 1]->line);
    }
}

void PrintFileInfo(FileInfo *file_info)
{
    printf("File name: %s\n", file_info->filename);
    printf("File size: %d\n", file_info->size);
    printf("Lines in file: %d\n", file_info->lines);
}

#endif
