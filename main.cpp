//!@file

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int StringMaker (char* str, int length, char** pointer);

long ReadFileLength (char* file);

int ReadFile (char* name, char* str, int length);

void Qsort (int left, int right, char** pointer);

int Is_Larger_Str (char *str1, char *str2);

void Swap (char *arr[], int a, int b);

char Down (char c);

int WriteFile (char *file, int num, char** pointer);

int main ()
{
    char* file_read = (char*)calloc (75, 1);
    char* file_write = (char*)calloc (75, 1);

    printf ("Enter which file to read: ");
    scanf ("%s", file_read);
    printf ("Enter where to write: ");
    scanf ("%s", file_write);

    long fsize = ReadFileLength (file_read);
    printf ("Number of symbols in the text = %ld\n", fsize);

    char* my_string = (char*) calloc (fsize + 1, 1);

    ReadFile (file_read, my_string, fsize);

    char** pointer = (char**)calloc (fsize, sizeof (char**));

    int num_lines = StringMaker (my_string, fsize, pointer);

    Qsort(0, num_lines - 1, pointer);

    for (int  i = 0; i < num_lines; i++) printf ("%s\n", *(pointer + i));

    WriteFile(file_write, num_lines, pointer);

    return 0;
}


/*! This function counts the number of symbols in the file.

@param[in] file The pointer to the name of the file

\return The amount of symbols in the file

\warning This function also counts special invisible symbols as:
"\n" and "\r".

*/

long ReadFileLength (char* file)
{
    assert (file);

    FILE* f = fopen (file, "r");
    long pointer1 = ftell (f);

    fseek (f, 0, SEEK_END);
    long pointer2 = ftell (f);

    fseek (f, 0, 0);
    fclose (f);
    return (pointer2 - pointer1);

}

/*! This function reads a text from a file to a string.

@param[in] name The name of the file.
@param[in] str A pointer to the string where the text writes to.
@param[in] length The maximum length of the file.

\return 1 if everything is alright.

*/

int ReadFile (char* name, char* str, int length)
{
    assert (name);
    assert (str);

    FILE* f = fopen (name, "r");
    fread ( (char*)str, 1, length, f);
    fclose (f);
    return 1;
}

/*! This function replaces symbols '\n' to '\0'

@param[in] str The pointer to a string to write it.
@param[in] length The length of the string.
@param[in] pointer The pointer to the pointer to the string.
\return The number of sublines.

*/

int StringMaker (char* str, int length, char** pointer)
{
    assert (str);

    int counter = 0;
    *pointer = str;

    int i;
    for (i = 0; i < length && *str ; i++)
    {
        if (*str == '\n')
        {
            *str = '\0';
            if (*(str + 1))
                *(pointer + ++counter) = str + 1;
        }
        str++;
    }

    if (*str == '\0')
        counter++;

    return counter;
}

/*!
@brief This function sorts quick elements of the array.

@param[in] left The left bound of the part of the array needs sorting.
@param[in] right The right bound of the part of the array needs sorting.
@param[in] *pointer[NLINES] The array which elements need sorting.

*/

void Qsort (int left, int right, char** pointer)
    {
        assert (*pointer);

        if (left >= right)
            return;

        int mid = (left + right) / 2;
        Swap (pointer, left, mid);

        int last = left;
        int i;
        for (i = left; i <= right; i++)
            if (Is_Larger_Str (*(pointer + left), *(pointer + i)) > 0)
               Swap (pointer, i, ++last);

        Swap (pointer, left, last);

        Qsort (left, last -  1, pointer);
        Qsort (last + 1, right, pointer);

    }

/*!
@brief This function compares two strings lexicographically.

@param[in] *str1 The pointer to the first string needs comparing
@param[in] *str2 The pointer to the second string needs comparing

\return The function returns an integer number.
If the first line is longer than the second one it returns a number that is more than 0;
if the second line is longer than the first one it returns a number that is less than 0;
if the lines are equal the function returns 0.

*/

int Is_Larger_Str (char *str1, char *str2)
    {
        assert (str1);
        assert (str2);

        while (Down (*str1) && Down (*str2)&&(Down (*str1) == Down (*str2)) )
        {
            *str1++;
            *str2++;
        }
        return Down (*str1) - Down (*str2);
    }

/*!
@brief This function changes two elements to each other of the array arr[] with indexes a and b.

param[in] *arr[] The array which elements need changing with each other.
param[in] a The first index.
param[in] a The second index.

*/

void Swap (char** arr, int a, int b)
    {
        assert (arr);
        char *temp;
        temp = *(arr + a);
        *(arr + a) = *(arr + b);
        *(arr + b) = temp;
    }

/*!
@brief This function returns a little letter, if the letter was capital,
and else it returns this very symbol.

@param[in] char c The char needs checking if the letter is capital.
@param[out] The function returns the decapitallated symbol.

*/

char Down (char c)
{

    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    else return c;
}

/*!
@brief This function writes lines to a file from an
array of string with a pointer *pointer.

@param[in] *file Is a pointer to a file to write the text to.
@param[in] num Is an amount of the array that is written.
@param[in] *pointer[NLINES] Is a pointer to an array of char with NLINES lines.
The function writes strings from this array to the file.

\return It returns 1 if everything is alright and returns 0 if something went wrong.

*/

int WriteFile (char *file, int num, char** pointer)
{
    assert (file);
    assert (num);
    assert (*pointer);

    FILE* f = fopen (file, "w");
    if (!f)
    {
        printf ("This file - %s - doesn't exist!\n", file);
        return 1;
    }

    int i;
    for (i = 0; i < num; i++)
    {
        fputs (*(pointer + i),f);
        fputc ('\n', f);
    }
    fclose (f);

    return 0;

}
