#ifndef INTERFACE_H
#define INTERFACE_H

/* System headers */

#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <time.h>
#include <math.h>

/* Color printing macros*/

#define RED "\033[31m"
#define BRIGHT_RED "\033[91m"
#define GREEN "\033[32m"
#define BRIGHT_GREEN "\033[92m"
#define YELLOW "\033[33m"
#define BRIGHT_YELLOW "\033[93m"
#define BLUE "\033[34m"
#define BRIGHT_BLUE "\033[94m"
#define MAGENTA "\033[35m"
#define BRIGHT_MAGENTA "\033[95m"
#define CYAN "\033[36m"
#define BRIGHT_CYAN "\033[96m"
#define RESET "\033[0m"

/* Linux compatibility macro */

#if !defined(__APPLE__) && !defined(__FreeBSD__)
    #ifndef wcsdup
    static inline wchar_t *wcsdup(const wchar_t *s) 
    {
        size_t len = wcslen(s) + 1;
        wchar_t *new_str = (wchar_t*)calloc(len, sizeof(wchar_t));
        if (new_str == NULL) 
        {
            return NULL;
        }
        return wmemcpy(new_str, s, len);
    }
    #endif
#endif

/* list.c */

typedef struct Wchar_Array_List 
{
    wchar_t **list;
    size_t size;
} Wchar_Array_List;

Wchar_Array_List* init_list(const wchar_t **waa);
void free_list(Wchar_Array_List *wal);
int add_item(Wchar_Array_List *wal, const wchar_t *wa);
int update_item(Wchar_Array_List *wal, const wchar_t *wa, size_t i);
int insert_item(Wchar_Array_List *wal, const wchar_t *wa, size_t n);
int swap_items(Wchar_Array_List *wal, size_t i, size_t j);
int delete_item(Wchar_Array_List *wal, size_t n);
void print_list(Wchar_Array_List *wal);
wchar_t* get_item(Wchar_Array_List *wal, size_t n);

/* array.c */

typedef struct Dynamic_Wchar_Array
{
    wchar_t *data;
    size_t size;
} Dynamic_Wchar_Array;

Dynamic_Wchar_Array* init_dwc_array(const wchar_t *wa);
void free_dwc_array(Dynamic_Wchar_Array *dwa);
void append_to_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa);
void prepend_to_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa);
void replace_dwc_array(Dynamic_Wchar_Array *dwa, const wchar_t *wa);
void substitute_in_dwc_array(Dynamic_Wchar_Array* ds, const wchar_t *old_wa, const wchar_t *new_wa);

/* terminal.c */

void enable_single_character_input();
void restore_normal_input();
void hide_console_cursor();
void show_console_cursor();
void render_menu(const wchar_t *menu[], size_t size, size_t count);
int select_option(const wchar_t *menu[], size_t size);
char* edit_prompt(const char *prompt, const char *buffer, size_t max);

/* files.c */

bool file_exists(const char *name);
wchar_t* read_file_to_wchar(const char *name);
bool write_wchar_to_file(const char *name, const wchar_t *wide_string);
bool append_wchar_to_file(const char *name, const wchar_t *wide_string);

/* strings.c */

bool compare_lengths(const char* str1, const char* str2);
bool compare_first_char(const char* str1, const char* str2);
bool compare_full_strings(const char* str1, const char* str2);
bool compare_optimized(const char* str1, const char* str2);

/* misc.c */

void seed();
int pseudo(const int arg);
int to_int(const wchar_t *arg);
bool is_int(const wchar_t *arg);
bool is_pos_int(const wchar_t *arg);
bool is_neg_int(const wchar_t *arg);
bool is_wchar_digit(const wchar_t arg);
bool is_wchar_hex_digit(const wchar_t arg);
bool is_wchar_alpha_numeric(const wchar_t arg);
bool is_wchar_letter(const wchar_t arg);
bool is_wchar_lower_case(const wchar_t arg);
bool is_wchar_upper_case(const wchar_t arg);
bool is_wchar_punct(const wchar_t arg);
bool is_wchar_white_space(const wchar_t arg);
bool is_wchar_graphical(const wchar_t arg);

#endif
