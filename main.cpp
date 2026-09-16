#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "Myqsort.cpp"

#define MAX_LINES 4540
#define LINE_LENGTH 256
#define BUFFER_SIZE 1000

int     ReadFromFile    (const char* filename, char* destination[]);

int     WriteIntoFile   (const char* filename, char* source[], int lines);

void    PrintStrings    (char* strings[], int n);

int     CompareLines    (const void* s1_value, const void* s2_value);

int main(void)
{   
    // printf("Main executing...\n");
    char* original_indexes[MAX_LINES] = {};
    char* working_indexes[MAX_LINES] = {};

    const char readfile[LINE_LENGTH] = "RawOneginText.txt";
    const char writefile[LINE_LENGTH] = "SortedOnegin.txt";

    int informative_lines = ReadFromFile(readfile, original_indexes);
    // PrintStrings(original_indexes, MAX_LINES);
    Myqsort(original_indexes, 0, informative_lines - 1, sizeof(original_indexes[0]), CompareLines);
    WriteIntoFile(writefile, original_indexes, informative_lines);

    return 0;
}

int ReadFromFile(const char* filename, char* destination[])
{
    char buffer[BUFFER_SIZE] = {};

    FILE *file = fopen(filename, "r");
    int nLines = 0;

    if (file)
    {   
        while (fgets(buffer, LINE_LENGTH, file))
        {
            destination[nLines] = strdup(buffer);
            nLines++;    
        }
    }
    fclose(file);

    return nLines;
}

int WriteIntoFile(const char* filename, char* source[], int lines)
{
    FILE *file = fopen(filename, "w");

    if (file)
    {
        for (int i = 0; i < lines; i++)
            fputs(source[i], file);
    }
}

void PrintStrings(char* strings[], int n)
{
    for (int i = 0; i < n; i++)
    {   
        if (strings[i])
            printf("%s", strings[i]);
    }
}

int CompareLines(const void* s1_value, const void* s2_value)
{   
    char* s1 = *(char**)s1_value;
    char* s2 = *(char**)s2_value;
    // printf("s1 = %s", s1);
    // printf("s2 = %s", s2);

    int i = 0, j = 0;

    while(s1[i] != '\0' && s2[j] != '\0')
    {
        while (!(isalpha(s1[i])) && s1[i] != '\0')
            i++;

        while (!(isalpha(s2[j])) && s2[j] != '\0')
            j++;
        
        if (s1[i] == '\0' || s2[i] == '\0')
            break;

        char curr_s1_symb = tolower(s1[i]);
        char curr_s2_symb = tolower(s2[j]);

        if (curr_s1_symb == curr_s2_symb)
        {   
            i++;
            j++;
            continue;
        }
        
        return (int)(curr_s1_symb) - (int)(curr_s2_symb);
    }

    return (int)(s1[i]) - (int)(s2[j]);
}