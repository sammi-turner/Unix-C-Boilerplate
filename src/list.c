#include "interface.h"

/* List data type */

Wide_String_List* init_list(const wchar_t** ws_array) 
{
    Wide_String_List* wl = (Wide_String_List*)malloc(sizeof(Wide_String_List));
    wl->size = 0;
    wl->list = NULL;
    if (ws_array != NULL) 
    {
        int count = 0;
        while (ws_array[count] != NULL)
        {
            count++;
        }
        wl->list = (wchar_t**)malloc(count * sizeof(wchar_t*));
        for (int i = 0; i < count; i++) 
        {
            wl->list[i] = wcsdup(ws_array[i]);
        }
        wl->size = count;
    }
    return wl;
}

void free_list(Wide_String_List* wl) 
{
    if (wl == NULL)
    {
        return;
    }
    for (int i = 0; i < wl->size; i++) 
    {
        free(wl->list[i]);
    }
    free(wl->list);
    free(wl);
}

int add_item(Wide_String_List* wl, const wchar_t* ws) 
{
    if (wl == NULL || ws == NULL)
    {
        return -1;
    }
    wl->list = (wchar_t**)realloc(wl->list, (wl->size + 1) * sizeof(wchar_t*));
    wl->list[wl->size] = wcsdup(ws);
    wl->size++;
    return wl->size - 1;
}

int update_item(Wide_String_List* wl, const wchar_t* ws, int i) 
{
    if (wl == NULL || ws == NULL || i < 0 || i >= wl->size)
    {
        return -1;
    }
    free(wl->list[i]);
    wl->list[i] = wcsdup(ws);
    return i;
}

int insert_item(Wide_String_List* wl, const wchar_t* ws, int n) 
{
    if (wl == NULL || ws == NULL || n < 0 || n > wl->size)
    {
        return -1;
    }
    wl->list = (wchar_t**)realloc(wl->list, (wl->size + 1) * sizeof(wchar_t*));
    memmove(&wl->list[n + 1], &wl->list[n], (wl->size - n) * sizeof(wchar_t*));
    wl->list[n] = wcsdup(ws);
    wl->size++;
    return n;
}

int swap_items(Wide_String_List* wl, int i, int j) 
{
    if (wl == NULL || i < 0 || i >= wl->size || j < 0 || j >= wl->size)
    {
        return -1;
    }
    wchar_t* temp = wl->list[i];
    wl->list[i] = wl->list[j];
    wl->list[j] = temp;
    return 0;
}

int delete_item(Wide_String_List* wl, int n) 
{
    if (wl == NULL || n < 0 || n >= wl->size)
    {
        return -1;
    }
    free(wl->list[n]);
    memmove(&wl->list[n], &wl->list[n + 1], (wl->size - n - 1) * sizeof(wchar_t*));
    wl->size--;
    return 0;
}

void print_list(Wide_String_List* wl) 
{
    setlocale(LC_ALL, "");
    if (wl == NULL)
    {
        return;
    }
    for (int i = 0; i < wl->size; i++) 
    {
        wprintf(L"%ls\n", wl->list[i]);
    }
}

char* get_item(Wide_String_List* wl, int n) 
{
    if (wl == NULL || n < 0 || n >= wl->size)
    {
        return NULL;
    }
    int size = wcstombs(NULL, wl->list[n], 0);
    char* result = (char*)malloc((size + 1) * sizeof(char));
    wcstombs(result, wl->list[n], size + 1);
    return result;
}