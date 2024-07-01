#include "interface.h"

/* dynamic string list type */

Dynamic_String_List* init_dynamic_string_list(size_t initial_capacity) 
{
    Dynamic_String_List *list = (Dynamic_String_List*)calloc(1, sizeof(Dynamic_String_List));
    if (list == NULL) return NULL;
    list->strings = (Dynamic_String**)calloc(initial_capacity, sizeof(Dynamic_String*));
    if (list->strings == NULL) 
    {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

void free_dynamic_string_list(Dynamic_String_List *list) 
{
    for (size_t i = 0; i < list->count; i++) 
    {
        free_dynamic_string(list->strings[i]);
    }
    free(list->strings);
    free(list);
}

bool add_to_dynamic_string_list(Dynamic_String_List *list, Dynamic_String *str) 
{
    if (list->count == list->capacity) 
    {
        size_t new_capacity = list->capacity * 2;
        Dynamic_String **new_strings = (Dynamic_String**)realloc(list->strings, new_capacity * sizeof(Dynamic_String*));
        if (new_strings == NULL) return false;
        list->strings = new_strings;
        list->capacity = new_capacity;
    }
    list->strings[list->count++] = str;
    return true;
}

bool remove_from_dynamic_string_list(Dynamic_String_List *list, size_t index) 
{
    if (index >= list->count) return false;
    free_dynamic_string(list->strings[index]);
    for (size_t i = index; i < list->count - 1; i++) 
    {
        list->strings[i] = list->strings[i + 1];
    }
    list->count--;
    return true;
}

Dynamic_String* get_from_dynamic_string_list(Dynamic_String_List *list, size_t index) 
{
    if (index >= list->count) return NULL;
    return list->strings[index];
}

int find_in_dynamic_string_list(Dynamic_String_List *list, const Dynamic_String *str) 
{
    for (size_t i = 0; i < list->count; i++) 
    {
        if (dynamic_strings_equal(list->strings[i], str)) 
        {
            return (int)i;
        }
    }
    return -1;
}

void sort_dynamic_string_list(Dynamic_String_List *list) 
{
    for (size_t i = 0; i < list->count - 1; i++) 
    {
        for (size_t j = 0; j < list->count - i - 1; j++) 
        {
            if (wcscmp(list->strings[j]->data, list->strings[j+1]->data) > 0) 
            {
                Dynamic_String *temp = list->strings[j];
                list->strings[j] = list->strings[j+1];
                list->strings[j+1] = temp;
            }
        }
    }
}

Dynamic_String_List* dynamic_string_to_list(Dynamic_String* ds, const wchar_t delimiter) 
{
    if (ds == NULL || ds->data == NULL) return NULL;
    Dynamic_String_List* list = init_dynamic_string_list(10);
    if (list == NULL) return NULL;
    wchar_t* start = ds->data;
    wchar_t* end = ds->data;
    while (*end != L'\0') 
    {
        if (*end == delimiter) 
        {
            size_t len = end - start;
            wchar_t* temp = calloc((len + 1), sizeof(wchar_t));
            if (temp == NULL) 
            {
                free_dynamic_string_list(list);
                return NULL;
            }
            wcsncpy(temp, start, len);
            temp[len] = L'\0';
            Dynamic_String* new_ds = init_dynamic_string(temp);
            free(temp);
            if (new_ds == NULL) 
            {
                free_dynamic_string_list(list);
                return NULL;
            }
            if (!add_to_dynamic_string_list(list, new_ds)) 
            {
                free_dynamic_string(new_ds);
                free_dynamic_string_list(list);
                return NULL;
            }
            start = end + 1;
        }
        end++;
    }
    if (start != end) 
    {
        Dynamic_String* new_ds = init_dynamic_string(start);
        if (new_ds == NULL || !add_to_dynamic_string_list(list, new_ds)) 
        {
            if (new_ds) free_dynamic_string(new_ds);
            free_dynamic_string_list(list);
            return NULL;
        }
    }
    return list;
}

Dynamic_String* list_to_dynamic_string(Dynamic_String_List* list, const wchar_t delimiter)
{
    if (list == NULL || list->count == 0) return NULL;
    size_t total_size = 0;
    for (size_t i = 0; i < list->count; i++) 
    {
        total_size += wcslen(list->strings[i]->data);
    }
    total_size += list->count - 1;
    Dynamic_String* result = calloc(1, sizeof(Dynamic_String));
    if (result == NULL) return NULL;
    result->data = malloc((total_size + 1) * sizeof(wchar_t));
    if (result->data == NULL) 
    {
        free(result);
        return NULL;
    }
    wchar_t* current = result->data;
    for (size_t i = 0; i < list->count; i++) 
    {
        if (i > 0) 
        {
            *current = delimiter;
            current++;
        }
        size_t len = wcslen(list->strings[i]->data);
        wmemcpy(current, list->strings[i]->data, len);
        current += len;
    }
    *current = L'\0';
    result->size = total_size + 1;
    return result;
}