#include "interface.h"

/* File I/O operations */

bool file_exists(const char *name) 
{
    FILE* file = fopen(name, "r");
    if (file) 
    {
        fclose(file);
        return true;
    }
    return false;
}

wchar_t* read_file_to_wchar(const char *name) 
{
    setlocale(LC_ALL, "");
    FILE* file = fopen(name, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char* utf8_string = (char*)malloc(file_size + 1);
    if (utf8_string == NULL) 
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }
    size_t bytes_read = fread(utf8_string, 1, file_size, file);
    fclose(file);
    if (bytes_read != (size_t)file_size) 
    {
        perror("Error reading file");
        free(utf8_string);
        return NULL;
    }
    utf8_string[bytes_read] = '\0';
    size_t wide_size = mbstowcs(NULL, utf8_string, 0) + 1;
    wchar_t *wide_string = (wchar_t*)malloc(wide_size * sizeof(wchar_t));
    if (wide_string == NULL) 
    {
        perror("Memory allocation failed");
        free(utf8_string);
        return NULL;
    }
    if (mbstowcs(wide_string, utf8_string, wide_size) == (size_t)-1) 
    {
        perror("Conversion error");
        free(utf8_string);
        free(wide_string);
        return NULL;
    }
    free(utf8_string);
    return wide_string;
}

bool write_wchar_to_file(const char *name, const wchar_t *wide_string) 
{
    setlocale(LC_ALL, "");
    FILE *file = fopen(name, "w");
    if (file == NULL) 
    {
        perror("Error opening file");
        return false;
    }
    size_t utf8_size = wcstombs(NULL, wide_string, 0) + 1;
    char *utf8_string = (char*)malloc(utf8_size);
    if (utf8_string == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return false;
    }
    if (wcstombs(utf8_string, wide_string, utf8_size) == (size_t)-1) 
    {
        perror("Conversion error");
        free(utf8_string);
        fclose(file);
        return false;
    }
    fprintf(file, "%s", utf8_string);  // Write the UTF-8 string to the file
    free(utf8_string);
    fclose(file);
    return true;
}

bool append_wchar_to_file(const char *name, const wchar_t *wide_string) 
{
    setlocale(LC_ALL, "");
    FILE *file = fopen(name, "a");
    if (file == NULL) 
    {
        perror("Error opening file");
        return false;
    }
    size_t utf8_size = wcstombs(NULL, wide_string, 0) + 1;
    char* utf8_string = (char*)malloc(utf8_size);
    if (utf8_string == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return false;
    }
    if (wcstombs(utf8_string, wide_string, utf8_size) == (size_t)-1) 
    {
        perror("Conversion error");
        free(utf8_string);
        fclose(file);
        return false;
    }
    fprintf(file, "%s", utf8_string);  // Write the UTF-8 string to the file
    free(utf8_string);
    fclose(file);
    return true;
}