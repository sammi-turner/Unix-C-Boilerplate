#include "interface.h"

/* Dynamic string data type */

Dstring* init_dstring(const char* str) 
{
    Dstring* ds = (Dstring*)malloc(sizeof(Dstring));
    ds->size = strlen(str);
    ds->data = (char*)malloc((ds->size + 1) * sizeof(char));
    strcpy(ds->data, str);
    return ds;
}

void free_dstring(Dstring* ds) 
{
    free(ds->data);
    free(ds);
}

void append_to_dstring(Dstring* ds, const char* str) 
{
    int new_size = ds->size + strlen(str);
    ds->data = (char*)realloc(ds->data, (new_size + 1) * sizeof(char));
    strcat(ds->data, str);
    ds->size = new_size;
}

void prepend_to_dstring(Dstring* ds, const char* str) 
{
    int new_size = ds->size + strlen(str);
    char* new_data = (char*)malloc((new_size + 1) * sizeof(char));
    strcpy(new_data, str);
    strcat(new_data, ds->data);
    free(ds->data);
    ds->data = new_data;
    ds->size = new_size;
}

void replace_dstring(Dstring* ds, const char* new_data) 
{
    if (ds == NULL || new_data == NULL)
        return;

    int new_size = strlen(new_data);

    free(ds->data);
    ds->data = (char*)malloc((new_size + 1) * sizeof(char));
    strcpy(ds->data, new_data);
    ds->size = new_size;
}

void substitute_in_dstring(Dstring* ds, const char* old_substr, const char* new_substr) 
{
    int old_len = strlen(old_substr);
    int new_len = strlen(new_substr);
    int dsLen = ds->size;

    // Count the number of occurrences of old_substr in the Dstring
    int count = 0;
    char* pos = ds->data;
    while ((pos = strstr(pos, old_substr)) != NULL) 
    {
        count++;
        pos += old_len;
    }

    // Calculate the new size of the Dstring after replacing the substrings
    int new_size = dsLen + count * (new_len - old_len);

    // Allocate memory for the new Dstring data
    char* new_data = (char*)malloc((new_size + 1) * sizeof(char));

    // Replace the substrings
    char* src_pos = ds->data;
    char* dest_pos = new_data;
    while ((pos = strstr(src_pos, old_substr)) != NULL) 
    {
        int len = pos - src_pos;
        strncpy(dest_pos, src_pos, len);
        dest_pos += len;
        strcpy(dest_pos, new_substr);
        dest_pos += new_len;
        src_pos = pos + old_len;
    }
    strcpy(dest_pos, src_pos);

    // Free the old Dstring data and update the Dstring
    free(ds->data);
    ds->data = new_data;
    ds->size = new_size;
}