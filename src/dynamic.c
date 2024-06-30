#include "interface.h"

/* dynamic string type */

Dynamic_String* init_dynamic_string(const wchar_t *wa)
{
    Dynamic_String *ds = (Dynamic_String*)calloc(1, sizeof(Dynamic_String));
    if (ds == NULL) return NULL;
    ds->size = wcslen(wa);
    ds->data = (wchar_t*)calloc((ds->size + 1), sizeof(wchar_t));
    if (ds->data == NULL) 
    {
        free(ds);
        return NULL;
    }
    wcscpy(ds->data, wa);
    return ds;
}

void free_dynamic_string(Dynamic_String *ds)
{
    free(ds->data);
    free(ds);
}

void append_to_dynamic_string(Dynamic_String *ds, const wchar_t *wa)
{
    int new_size = ds->size + wcslen(wa);
    wchar_t* new_data = realloc(ds->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    ds->data = new_data;
    wcscat(ds->data, wa);
    ds->size = new_size;
}

void prepend_to_dynamic_string(Dynamic_String *ds, const wchar_t *wa)
{
    int prepend_len = wcslen(wa);
    int new_size = ds->size + prepend_len;
    wchar_t *new_data = (wchar_t*)calloc((new_size + 1), sizeof(wchar_t));
    if (new_data == NULL) return;
    wcscpy(new_data, wa);
    wcscat(new_data, ds->data);
    free(ds->data);
    ds->data = new_data;
    ds->size = new_size;
}

void replace_dynamic_string(Dynamic_String *ds, const wchar_t *wa)
{
    int new_size = wcslen(wa);
    wchar_t *new_data = realloc(ds->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    ds->data = new_data;
    wcscpy(ds->data, wa);
    ds->size = new_size;
}

void substitute_in_dynamic_string(Dynamic_String *ds, const wchar_t *old_wa, const wchar_t *new_wa)
{
    wchar_t* pos = wcsstr(ds->data, old_wa);
    if (pos == NULL) return;
    int old_len = wcslen(old_wa);
    int new_len = wcslen(new_wa);
    int diff = new_len - old_len;
    if (diff > 0) 
    {
        int new_size = ds->size + diff;
        wchar_t* new_data = realloc(ds->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        ds->data = new_data;
        ds->size = new_size;
        pos = wcsstr(ds->data, old_wa);
    }
    memmove(pos + new_len, pos + old_len, (wcslen(pos + old_len) + 1) * sizeof(wchar_t));
    wmemcpy(pos, new_wa, new_len);
    if (diff < 0) 
    {
        int new_size = ds->size + diff;
        wchar_t* new_data = realloc(ds->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        ds->data = new_data;
        ds->size = new_size;
    }
}

bool dynamic_strings_equal(const Dynamic_String *str1, const Dynamic_String *str2)
{
    if (str1->size != str2->size)
    {
        return false;
    }
    return (wcscmp(str1->data, str2->data) == 0);
}