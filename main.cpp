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

int     ReadFromFile        (const char* filename, char* destination[]);

int     WriteIntoFile       (const char* filename, char* source[], int lines);

void    ClearFile           (const char* filename);

void    WriteDelimeter      (const char* filename);

void    PrintStrings        (char* strings[], int n);

int     CompareLines        (const void* s1_value, const void* s2_value);

int     CompareLinesByEnd   (const void* s1_value, const void* s2_value);


int main(void)
{   
    // printf("Main executing...\n");
    char* original_indexes[MAX_LINES] = {};
    char* working_indexes[MAX_LINES] = {};

    const char readfile[LINE_LENGTH] = "RawOneginText.txt";
    const char writefile[LINE_LENGTH] = "SortedOnegin.txt";

    ClearFile(writefile);

    int informative_lines = ReadFromFile(readfile, original_indexes);

    for (int i = 0; i < MAX_LINES; i++)
        working_indexes[i] = original_indexes[i];
    // PrintStrings(original_indexes, MAX_LINES);
    
    qsort(working_indexes, MAX_LINES - 1, sizeof(working_indexes[0]), CompareLines);
    WriteIntoFile(writefile, working_indexes, informative_lines);

    WriteDelimeter(writefile); // different sortings of Onegin are divided by word "DELIMETER"

    Myqsort(working_indexes, 0, informative_lines - 1, sizeof(working_indexes[0]), CompareLinesByEnd);
    WriteIntoFile(writefile, working_indexes, informative_lines);
    // PrintStrings(working_indexes, informative_lines);

    WriteDelimeter(writefile);

    WriteIntoFile(writefile, original_indexes, informative_lines);

    return 0;
}

int ReadFromFile(const char* filename, char* destination[])
{   
    assert(filename);
    assert(destination);

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
    assert(filename);
    assert(source);

    FILE *file = fopen(filename, "a");

    if (file)
    {
        for (int i = 0; i < lines; i++)
            fputs(source[i], file);
    }
    fclose(file);
}

void PrintStrings(char* strings[], int n)
{   
    assert(strings);

    for (int i = 0; i < n; i++)
    {   
        if (strings[i])
        {   
            int length = strlen(strings[i]);
            printf("[address: %p] ", strings[i]);
            putchar('<');
            int j = 0;
            for ( ; j < length - 1; j++)
                putchar(strings[i][j]);
            if (strings[i][j] != '\n')
                putchar(strings[i][j]);
            putchar('>');
            printf("%*s %d\n", 50 - length, "Length:", length);
        }
    }
}

int CompareLines(const void* s1_value, const void* s2_value)
{   
    assert(s1_value);
    assert(s2_value);

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

int CompareLinesByEnd(const void* s1_value, const void* s2_value)
{   
    assert(s1_value);
    assert(s2_value);

    char* s1 = *(char**)s1_value;
    char* s2 = *(char**)s2_value;
    
    int length1 = strlen(s1);
    int length2 = strlen(s2);

    int i = 0, j = 0;

    while((length1 - i - 1) >= 0 && (length2 - j - 1) >= 0)
    {
        while (!(isalpha(s1[length1 - i - 1])) && (length1 - i - 1) >= 0)
            i++;

        while (!(isalpha(s2[length2 - j - 1])) && (length2 - j - 1) >= 0)
            j++;
        
        if ((length1 - i - 1) < 0 || (length2 - j - 1) < 0)
            break;

        char curr_s1_symb = tolower(s1[length1 - i - 1]);
        char curr_s2_symb = tolower(s2[length2 - j - 1]);

        if (curr_s1_symb == curr_s2_symb)
        {   
            i++;
            j++;
            continue;
        }
        
        return (int)(curr_s1_symb) - (int)(curr_s2_symb);
    }

    if ((length1 - i - 1) < 0 && (length2 - j - 1) >= 0)
        return -1;
    else if ((length2 - j - 1) < 0 && (length1 - i - 1) >= 0)
        return 1;
    return 0;   
}

void ClearFile(const char* filename)
{
    assert(filename);

    FILE* file = fopen(filename, "w");
    assert(file);
    fclose(file);
}

void WriteDelimeter(const char* filename)
{   
    assert(filename);

    FILE* file = fopen(filename, "a");
    fputc('\n', file);
    fputs("DELIMETER", file);
    for (int i = 0; i < 40; i++)
        fputc('*', file);
    fputc('\n', file);
    fclose(file);    
}