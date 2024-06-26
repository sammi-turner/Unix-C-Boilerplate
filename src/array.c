#include "interface.h"

/* dynamic wide char array data type */

Dynamic_Wchar_Array* init_dwc_array(const wchar_t *wa)
{
    Dynamic_Wchar_Array *dwa = (Dynamic_Wchar_Array*)calloc(1, sizeof(Dynamic_Wchar_Array));
    if (dwa == NULL) return NULL;
    dwa->size = wcslen(wa);
    dwa->data = (wchar_t*)calloc((dwa->size + 1), sizeof(wchar_t));
    if (dwa->data == NULL) 
    {
        free(dwa);
        return NULL;
    }
    wcscpy(dwa->data, wa);
    return dwa;
}

void free_dwc_array(Dynamic_Wchar_Array *dwa)
{
    if (dwa) 
    {
        free(dwa->data);
        free(dwa);
    }
}

void append_to_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa)
{
    int new_size = dwa->size + wcslen(wa);
    wchar_t* new_data = realloc(dwa->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    dwa->data = new_data;
    wcscat(dwa->data, wa);
    dwa->size = new_size;
}

void prepend_to_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa)
{
    int prepend_len = wcslen(wa);
    int new_size = dwa->size + prepend_len;
    wchar_t *new_data = (wchar_t*)calloc((new_size + 1), sizeof(wchar_t));
    if (new_data == NULL) return;
    wcscpy(new_data, wa);
    wcscat(new_data, dwa->data);
    free(dwa->data);
    dwa->data = new_data;
    dwa->size = new_size;
}

void replace_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa)
{
    int new_size = wcslen(wa);
    wchar_t *new_data = realloc(dwa->data, (new_size + 1) * sizeof(wchar_t));
    if (new_data == NULL) return;
    dwa->data = new_data;
    wcscpy(dwa->data, wa);
    dwa->size = new_size;
}

void substitute_in_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *old_wa, const wchar_t *new_wa)
{
    wchar_t* pos = wcsstr(dwa->data, old_wa);
    if (pos == NULL) return;
    int old_len = wcslen(old_wa);
    int new_len = wcslen(new_wa);
    int diff = new_len - old_len;
    if (diff > 0) 
    {
        int new_size = dwa->size + diff;
        wchar_t* new_data = realloc(dwa->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        dwa->data = new_data;
        dwa->size = new_size;
        pos = wcsstr(dwa->data, old_wa);
    }
    memmove(pos + new_len, pos + old_len, (wcslen(pos + old_len) + 1) * sizeof(wchar_t));
    wmemcpy(pos, new_wa, new_len);
    if (diff < 0) 
    {
        int new_size = dwa->size + diff;
        wchar_t* new_data = realloc(dwa->data, (new_size + 1) * sizeof(wchar_t));
        if (new_data == NULL) return;
        dwa->data = new_data;
        dwa->size = new_size;
    }
}