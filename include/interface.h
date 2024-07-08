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

/* Linux compatibility macros */

#if !defined(__APPLE__) && !defined(__FreeBSD__)
    #if !defined(wcsdup) && !defined(_WCHAR_H)
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

/* Sqlite3 macros */

#define COMMAND_FORMAT "echo \"%s\" | sqlite3 %s.db"
#define INSERT_QUERY "INSERT INTO %s (key, value) VALUES ('%s', '%s');"
#define SELECT_ALL_KEYS_QUERY "SELECT key FROM %s;"
#define SELECT_ALL_VALUES_QUERY "SELECT value FROM %s;"
#define DELETE_QUERY "DELETE FROM %s WHERE key = '%s';"
#define SELECT_ALL_QUERY "SELECT * FROM %s;"
#define SELECT_ROW_QUERY "SELECT * FROM %s WHERE key = '%s';"
#define SELECT_VALUE_QUERY "SELECT value FROM %s WHERE key = '%s';"

/* dynamic.c */

typedef struct Dynamic_String
{
    wchar_t *data;
    size_t size;
} Dynamic_String;

Dynamic_String* init_dynamic_string(const wchar_t *wa);
void free_dynamic_string(Dynamic_String *ds);
void append_to_dynamic_string(Dynamic_String *ds, const wchar_t *wa);
void prepend_to_dynamic_string(Dynamic_String *ds, const wchar_t *wa);
void replace_dynamic_string(Dynamic_String *ds, const wchar_t *wa);
void substitute_in_dynamic_string(Dynamic_String* ds, const wchar_t *old_wa, const wchar_t *new_wa);
bool dynamic_strings_equal(const Dynamic_String *str1, const Dynamic_String *str2);

/* list.c */

typedef struct Dynamic_String_List 
{
    Dynamic_String **strings;
    size_t count;
    size_t capacity;
} Dynamic_String_List;

Dynamic_String_List* init_dynamic_string_list(size_t initial_capacity);
void free_dynamic_string_list(Dynamic_String_List *list);
bool add_to_dynamic_string_list(Dynamic_String_List *list, Dynamic_String *str);
bool remove_from_dynamic_string_list(Dynamic_String_List *list, size_t index);
Dynamic_String* get_from_dynamic_string_list(Dynamic_String_List *list, size_t index);
int find_in_dynamic_string_list(Dynamic_String_List *list, const Dynamic_String *str);
void sort_dynamic_string_list(Dynamic_String_List *list);
Dynamic_String_List* dynamic_string_to_list(Dynamic_String* ds, const wchar_t delimiter);
Dynamic_String* list_to_dynamic_string(Dynamic_String_List* list, const wchar_t delimiter);

/* rational.c */

typedef struct Rational
{
    int numerator;
    int denominator;
} Rational;

int gcd(int a, int b);
void print_rational(Rational r);
bool create_rational(int numerator, int denominator, Rational *result);
bool add_rationals(Rational a, Rational b, Rational *result);
bool subtract_rationals(Rational a, Rational b, Rational *result);
bool multiply_rationals(Rational a, Rational b, Rational *result);
bool divide_rationals(Rational a, Rational b, Rational *result);
bool simplify_rational(Rational *r);

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

bool compare_optimized(const char *str1, const char *str2);
char* join_strings_by_char(char **arg, char c, size_t size);
char** split_string_by_char(const char *s, char c);

/* kvstore.c */

bool is_sqlite_installed();
char* create_key_value_table(const char *t);
bool table_contains_key(const char *t, const char *k);
char* execute_sqlite_command(const char *query, const char *table);
char* insert_key_value_pair(const char *t, const char *k, const char *v);
char* select_all_keys(const char *t);
char* select_all_values(const char *t);
char* delete_key_value_pair(const char *t, const char *k);
char* select_all_pairs(const char *t);
char* select_row_from_key(const char *t, const char *k);
char* select_value_from_key(const char *t, const char *k);

/* misc.c */

void seed();
size_t pseudo(size_t arg);
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
