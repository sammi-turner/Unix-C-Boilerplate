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