#include "interface.h"

/* List data type */

List* init_list(const char** str_array) 
{
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) 
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    int size = 0;
    while (str_array[size] != NULL) 
    {
        size++;
    }

    list->list = (char**)malloc((size + 1) * sizeof(char*));
    if (list->list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(list);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        list->list[i] = strdup(str_array[i]);
        if (list->list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(list->list[j]);
            }
            free(list->list);
            free(list);
            return NULL;
        }
    }
    list->list[size] = NULL;
    list->size = size;

    return list;
}

void free_list(List* l)
{
    for (int i = 0; i < l->size; i++) 
    {
        free(l->list[i]);
    }
    free(l->list);
}

int add_item(List* l, const char* s) 
{
    l->size++;
    l->list = realloc(l->list, l->size * sizeof(char*));
    if (l->list == NULL) 
    {
        return -1;
    }
    l->list[l->size - 1] = strdup(s);
    return 0;
}

int update_item(List* l, const char* s, int i) 
{
    if (i < 0 || i >= l->size) 
    {
        return -1;
    }
    free(l->list[i]);
    l->list[i] = strdup(s);
    return 0;
}

int insert_item(List* l, const char* s, int n) 
{
    if (n < 0 || n > l->size) 
    {
        return -1;
    }
    l->size++;
    l->list = realloc(l->list, l->size * sizeof(char*));
    if (l->list == NULL) 
    {
        return -1;
    }
    memmove(&l->list[n + 1], &l->list[n], (l->size - n - 1) * sizeof(char*));
    l->list[n] = strdup(s);
    return 0;
}

int swap_items(List* l, int i, int j) 
{
    if (i < 0 || i >= l->size || j < 0 || j >= l->size) 
    {
        return -1;
    }
    char* temp = l->list[i];
    l->list[i] = l->list[j];
    l->list[j] = temp;
    return 0;
}

int delete_item(List* l, int n) 
{
    if (n < 0 || n >= l->size) 
    {
        return -1;
    }
    free(l->list[n]);
    memmove(&l->list[n], &l->list[n + 1], (l->size - n - 1) * sizeof(char*));
    l->size--;
    l->list = realloc(l->list, l->size * sizeof(char*));
    return 0;
}

void print_list(List* l) 
{
    for (int i = 0; i < l->size; i++) 
    {
        printf("%s\n", l->list[i]);
    }
}

char* get_item(List* l, int n) 
{
    if (n < 0 || n >= l->size) 
    {
        return "\0";
    }
    return l->list[n];
}