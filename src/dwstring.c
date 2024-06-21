#include "interface.h"

/* Dynamic string data type */

Dynamic_Wide_String* init_dwstring(const wchar_t* ws)
{
    Dynamic_Wide_String* dws = malloc(sizeof(Dynamic_Wide_String));
    if (dws == NULL) return NULL;
    dws->size = wcslen(ws);
    dws->data = malloc((dws->size + 1) * sizeof(wchar_t));
    if (dws->data == NULL) 
    {
        free(dws);
        return NULL;
    }
    wcscpy(dws->data, ws);
    return dws;
}

void free_dwstring(Dynamic_Wide_String* dws)
{
    if (dws) 
    {
        free(dws->data);
        free(dws);
    }
}

void append_to_dwstring(Dynamic_Wide_String* dws, const wchar_t* ws)
{
    int new_size = dws->size + wcslen(ws);
    wchar_t* new_data = realloc(dws->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    dws->data = new_data;
    wcscat(dws->data, ws);
    dws->size = new_size;
}

void prepend_to_dwstring(Dynamic_Wide_String* dws, const wchar_t* ws)
{
    int prepend_len = wcslen(ws);
    int new_size = dws->size + prepend_len;
    wchar_t* new_data = malloc((new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    wcscpy(new_data, ws);
    wcscat(new_data, dws->data);
    free(dws->data);
    dws->data = new_data;
    dws->size = new_size;
}

void replace_dwstring(Dynamic_Wide_String* dws, const wchar_t* ws)
{
    int new_size = wcslen(ws);
    wchar_t* new_data = realloc(dws->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    dws->data = new_data;
    wcscpy(dws->data, ws);
    dws->size = new_size;
}

void substitute_in_dwstring(Dynamic_Wide_String* dws, const wchar_t* old_ws, const wchar_t* new_ws)
{
    wchar_t* pos = wcsstr(dws->data, old_ws);
    if (pos == NULL) return;
    int old_len = wcslen(old_ws);
    int new_len = wcslen(new_ws);
    int diff = new_len - old_len;
    if (diff > 0) 
    {
        int new_size = dws->size + diff;
        wchar_t* new_data = realloc(dws->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        dws->data = new_data;
        dws->size = new_size;
        pos = wcsstr(dws->data, old_ws);
    }
    memmove(pos + new_len, pos + old_len, (wcslen(pos + old_len) + 1) * sizeof(wchar_t));
    wmemcpy(pos, new_ws, new_len);
    if (diff < 0) 
    {
        int new_size = dws->size + diff;
        wchar_t* new_data = realloc(dws->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        dws->data = new_data;
        dws->size = new_size;
    }
}