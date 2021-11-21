
#ifndef WHY_LIB_H
#define WHY_LIB_H

#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#define FALSE               0
#define TRUE                1
#define NOT_FOUND           -1
#define SUCCESS             1
#define FAILURE             0
#define WHY_INT_MAX         LLONG_MAX
#define OVERFLOW_CHECK      FALSE
#define A_CAPACITY_DEFAULT  (1 << 10)
#define A_CAPACITY_MIN      (1 << 2)
#define H_CAPACITY_DEFAULT  (1 << 5)

enum WHY_ERROR_TYPE
{
    WHY_ERROR_DEFAULT,
    WHY_ERROR_GENERIC,
    WHY_ERROR_TOTAL_BRICK,
    WHY_ERROR_MEMORY,
    WHY_ERROR_INDEX,
    WHY_ERROR_PARSE,
    WHY_ERROR_SYNTAX,
    WHY_ERROR_MATH,
    WHY_ERROR_NAME,
    WHY_ERROR_SYMBOL,
    WHY_ERROR_EVAL,
    WHY_ERROR_CONV,
    WHY_ERROR_FILE,
};

typedef unsigned long long  int_unsigned;
typedef long long           int_signed;
typedef unsigned char       byte;
typedef long double         real;
typedef unsigned char       boolean;
typedef struct Array        Array;
typedef struct Buffer       Buffer;
typedef struct HashTable    HashTable;
typedef struct Tree         Set;
typedef struct Array        Heap;
typedef struct List         List;
typedef struct Polynomial   Polynomial;
typedef struct String       String;
typedef struct StringView   StringView;
typedef struct Tree         Tree;
typedef struct Rational     Rational;
typedef struct Complex      Complex;
typedef struct Matrix       Matrix;
typedef enum WHY_ERROR_TYPE WHY_ERROR_TYPE;

extern int_unsigned         WHY_ERROR;
extern char*                error_string;

#define WHY_RAND_MAX        (((int_unsigned)1 << 31) - 2)
#define EPSILON             (((real)1) / (1 << 12))
#define PI                  (real)3.1415926535
#define E                   (real)2.7182818284

//macros
#define         ABS(x) ((((x) < 0)) ? -(x) : (x))
#define         MAX(x, y) (((x) > (y)) ? (x) : (y))
#define         MIN(x, y) (((x) < (y)) ? (x) : (y))
#define         SWAP(a , b, type) {type swap = a; a = b; b = swap;}

//memory
void*           memory_init(void* restrict destination, const void* restrict source, int_unsigned size);
void*           memory_init_backwards(void* restrict destination, const void* restrict source_end, int_unsigned size);
void*           allocate(int_unsigned size);
void*           memory_set(void* object, byte value, int_unsigned size);
void*           memory_copy(const void* source, int_unsigned size);
void*           reallocate(const void* item, int_unsigned current_size, int_unsigned extra_size);
void*           memory_zero(int_unsigned size);
void            memory_destroy(void* item);
void            destroy_shallow(void* item);

//array
Array*          array_create(void* (*copy)(), void (*destroy_)());
Array*          array_create_with_capacity(void* (copy)(), void (*destroy)(), int_signed capacity);
Array*          array_copy(const Array* array);
Array*          array_copy_with(const Array* array, void* (*copy_function)());
Array*          array_concat(Array* lhs, const Array* rhs);
Array*          array_concatG(Array* lhs, const Array* rhs, void* (copy)());
bool            array_push(Array* array, const void* item);
bool            array_pushG(Array* array, const void* item, void* (*copy)());
bool            array_push_frontG(Array* array, const void* item, void* (*copy)());
bool            array_push_front(Array* array, const void* item);
int_signed      array_size(const Array* array);
int_signed      array_get_capacity(const Array* array);
void*           array_at(const Array* array, int_signed index);
void*           array_set(Array* array, void* item, int_signed index);
void*           array_pop(Array* array);
void*           array_pop_front(Array* array);
void            array_map(Array* array, void (*function)());
void            array_swap(Array* array, int_signed m, int_signed n);
void            array_destroy(Array* array);
void            array_destroy_no_content(Array* array);
void            array_sortI(Array* array, int_signed (*compare)());
void            array_sortM(Array* array, int_signed (*compare)());
void            array_sortH(Array* array, int_signed (*compare)());
void            array_sortQ(Array* array, int_signed (*comapre)());
void*           array_findCMP(const Array* array, const void* item, int_signed (*comapre)());
void*           array_find(const Array* array, const void* item);
void*           array_first(const Array* array);
void*           array_last(const Array* array);
void            array_set_compare(Array* array, int_signed (*compare)());
int_signed      array_compare_elements(const Array* array, int_signed left, int_signed right);
void            _bubble_sort_slice(Array* array, int_signed left, int_signed right);
void            _insert_sort_slice(Array* array, int_signed left, int_signed right);

//list
List*           list_create(void* (*copy)(), void (*destroy)());
void            list_destroy(List* list);
int_signed      list_length(const List* list);
List*           list_push_back(List* list, const void* data);
List*           list_push_front(List* list, const void* data);
void*           list_pop_back(List* list);
void*           list_pop_front(List* list);
List*           list_reverse(List* list);
void            list_map(List* list, void (*function)());
void*           list_find(const List* list, const void* item, int_signed (*compare)());
void*           list_remove(List* list, const void* item, int_signed (*compare)());

//heap
Heap*           heap_create_with_capacity(void* (*copy)(), void (*destroy)(), int_signed (*compare)(), int_signed capacity);
Heap*           heap_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void            heap_destroy(Heap* heap);
int_signed      heap_size(const Heap* heap);
bool            heap_push(Heap* heap, const void* item);
void*           heap_pop_root(Heap* heap);
void            heap_map(Heap* heap, void (*function)());
void            heap_sort(Heap* heap);
void*           heap_find(const Heap* heap, const void* item);

//tree
Tree*           tree_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
Tree*           tree_create_avl(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void            tree_destroy(Tree* tree);
void*           tree_get_root(const Tree* tree);
int_signed      tree_get_size(const Tree* tree);
bool            tree_insert(Tree* tree, const void* item);
void*           tree_remove(Tree* tree, const void* item);
void*           tree_find(const Tree* tree, const void* item);
void            tree_map_inorder(Tree* tree, void (*function)());
int_signed      tree_fold(const Tree* tree, int_signed (*function)());
void*           tree_max(Tree* tree);
void*           tree_min(Tree* tree);
void*           tree_pop_min(Tree* tree);
int_signed      tree_compute_height(const Tree* tree);

//hash table
HashTable*      hash_table_create(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity);
HashTable*      _hash_table_create_force_capacity(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity);
void            hash_table_destroy(HashTable* table);
int_unsigned    hash_table_capacity(const HashTable* table);
int_signed      hash_table_number_of_items(const HashTable* table);
void*           hash_table_at(const HashTable* table, int_unsigned n);
bool            hash_table_is_in(const HashTable* table, const void* item, int_signed (*compare)());
bool            hash_table_is_in_at_index(const HashTable* table, const void* item, int_signed (*compare)(), int_unsigned index);
bool            hash_table_is_in_hashed(const HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value);
bool            hash_table_insert(HashTable* table, const void* item, int_signed (*compare)());
bool            hash_table_insert_at_index(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned index);
bool            hash_table_insert_hashed(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value);
void*           hash_table_remove(HashTable* table, const void* item, int_signed (*compare)());
void*           hash_table_remove_hashed(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value);
void*           hash_table_remove(HashTable* table, const void* item, int_signed (*compare)());

//set
Set*            set_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void            set_destroy(Set* set);
int_signed      set_get_size(const Set* set);
bool            set_insert(Set* set, const void* item);
void*           set_find(const Set* set, const void* item);
void*           set_remove(Set* set, const void* item);
void*           set_pop_min(Set* set);

//c_string
int_signed      cstr_length(const char* string);
int_signed      cstr_compare(const char* lhs, const char* rhs);
int_signed      cstr_compare_length(const char* lhs, const char* rhs, int_signed length);
int_signed      cstr_index_of(const char* string, char c);
int_signed      cstr_index_of_any(const char* string, const char* set);
int_signed      cstr_index_of_substring(const char* haystack, const char* needle);
char*           cstr_substring(const char* string, int_unsigned length);
char*           cstr_copy(const char* string);
char*           cstr_concat_length(const char* lhs, int_signed lhs_len, const char* rhs, int_signed rhs_len);
char*           cstr_concat(const char* lhs, const char* rhs);
void            cstr_destroy(char* string);
void            cstr_to_lower(char* string);
char            cstr_char_to_lower(char c);
char*           cstr_trim(const char* string);
boolean         cstr_starts_with(const char*  restrict string, const char*  restrict start);
int_unsigned    id_digit(const char* string);
int_unsigned    id_lower(const char* string);
int_unsigned    id_upper(const char* string);
int_unsigned    id_alpha(const char* string);
int_unsigned    id_alphanum(const char* string);
int_unsigned    id_unsigned(const char* string);
int_unsigned    id_whitespace(const char* string);
int_unsigned    id_digit_string(const char* string);
int_unsigned    id_int(const char* string);
int_unsigned    id_float(const char* string);
int_unsigned    id_imaginary(const char* string);
int_unsigned    id_int_or_float(const char* string);

//string
String*         string_createFL(const char* literal, int_signed length);
String*         string_createFL_backwards(const char* literal_end, int_signed length);
String*         string_create(const char* literal);
int_signed      string_length(const String* string);
char            string_at(const String* string, int_signed n);
void            string_set(String* string, char value, int_signed index);
char*           string_get_characters(const String* string);
void            string_destroy(String* string);
String*         string_copy(const String* string);
String*         string_appendC(String* string, const char* rhs);
String*         string_appendS(String* string, const String* rhs);
String*         string_copy_shallow(const String* string);
int_signed      string_compare(const String* lhs, const String* rhs);
int_signed      string_compare_length(const String* lhs, const String* rhs, int_signed length);
String*         string_substring(const String* string, int_signed left_index, int_signed length);
String*         string_substring_end(const String* string, int_signed left_index);
String*         string_substitute_chars(String* string, const char* set, char replacement);
String*         string_to_lower(String* string);
bool            string_starts_with(const String* string, const char* start);
char*           string_slice_index(const String* string, int_signed left_index, int_signed length);
char*           string_slice(const String* string, int_signed length);
String*         string_trim(const String* string);
String*         string_trimD(String* string);

//string: search    
int_signed      string_index_of_predicate(const String* string, int_signed start, char c, bool (*predicate)(char, char));
int_signed      string_index_of_from(const String* string, int_signed start, char c);
int_signed      string_index_of(const String* string, char c);
int_signed      string_index_of_compliment_from(const String* string, int_signed start, char c);
int_signed      string_index_of_any(const String* string, char* characters);
int_signed      string_find(const String* haystack, const String* needle);
int_signed      string_find_literal(const String* haystack, const char* needle);

//string view
void            string_view_init(StringView* view, const String* string);
void            string_view_initB(StringView* view, const char* buffer, int_signed length);
void            string_view_shift(StringView* view, int_signed shift);
void            string_view_shrink(StringView* view, int_signed amount);
void            string_view_rewind(StringView* view);
int_signed      string_view_length(const StringView* view);
int_signed      string_view_index_of(const StringView* view, char c);
bool            string_view_starts_with(const StringView* view, char c);
bool            string_view_starts_with_any(const StringView* view, const char* set);
bool            string_view_ends_with_any(const StringView* view, const char* set);
bool            string_view_ends_with(const StringView* view, char c);
String*         string_view_substring(StringView* view, int_signed length);
String*         string_view_substringE(StringView* view);
String*         string_view_substring_shift(StringView* view, int_signed length);
String*         string_view_substring_shiftE(StringView* view);
char*           string_view_substringCSTR(StringView *view, int_signed length);
char*           string_view_substringCSTRE(StringView* view);
char*           string_view_substring_shiftCSTR(StringView* view, int_signed length);
char*           string_view_substring_shiftCSTRE(StringView* view);

//buffer
Buffer*         buffer_create();
void            buffer_destroy(Buffer* buffer);
int_signed      buffer_search(Buffer* buffer, char c);
int_signed      buffer_search_string(Buffer* buffer, const char* literal);
int_signed      buffer_write_into(Buffer* buffer, int_signed n_bytes, int f_descriptor);
int_signed      buffer_write_all_bytes_into(Buffer* buffer, int f_descriptor);
int_signed      buffer_count_unread_bytes(Buffer* buffer);
String*         buffer_read_from(Buffer* buffer, int_signed n_bytes);
String*         buffer_flush_all(Buffer* buffer);
String*         buffer_flush_sequence(Buffer* buffer, char terminator);

//split and get lines
Array*          string_split(const String* string, char delimiter);
Array*          string_splitCSTR(const char* c_string, char delimiter);
Array*          cstr_split(const char* string, char delimiter);
Array*          get_all_linesA(int file_descriptor);
Array*          get_all_linesAFN(const char* file_name);
String*         get_line(int file_descriptor);
String*         get_all_lines(int file_descriptor);

//hash functions
int_unsigned    hash_bytesFL(const byte* bytes, int_signed length);
int_unsigned    hash_cstringFL(const char* string, int_signed length);
int_unsigned    hash_cstring(const char* string);
int_unsigned    hash_string(const String* string);

//algebra
int_signed      int_add(int_signed n, int_signed m);
int_signed      int_mult(int_signed n, int_signed m);
int_signed      int_subtract(int_signed n, int_signed m);
int_signed      int_divide(int_signed n, int_signed m);
int_signed      int_mod(int_signed n, int_signed m);
real            real_add(real x, real y);
real            real_mult(real x, real y);
real            real_subtract(real x, real y);
real            real_divide(real x, real y);
bool            real_is_zeroP(const real* x);
void*           real_addP(const real* x, const real* y);
void*           real_multP(const real* x, const real* y);
bool            complex_is_zeroP(const Complex* z);
void*           complex_addP(const Complex* z, const Complex* w);
void*           complex_multP(const Complex* z, const Complex* w);

//rational
Rational        rational(int_signed top, int_signed bot);
Rational        rational_one();
Rational        rational_zero();
Rational        rational_scale(Rational p, int_signed factor);
Rational        rational_add(Rational lhs, Rational rhs);

//complex
Complex         complex(real re, real im);
Complex*        complex_create(real re, real im);
Complex*        complex_copy(Complex* z);
Complex         complex_zero();
Complex         complex_one();
Complex         complex_add(Complex lhs, Complex rhs);
Complex         complex_mult(Complex lhs, Complex rhs);
Complex         complex_div(Complex lhs, Complex rhs);
Complex         complex_subtract(Complex lhs, Complex rhs);
Complex         complex_inv(Complex z);
bool            complex_is_real(Complex z);
bool            complex_is_zero(Complex z);
bool            complex_is_imaginary(Complex z);
Complex         complex_scale(Complex z, real a);
Complex         complex_conjugate(Complex z);
Complex         complex_power(Complex z, int_unsigned n);
real            complex_mod_squared(Complex z);

//polynomial
Polynomial*     polynomial_create(char* variable);
Polynomial*     polynomial_create_from_complex(Complex z);
Polynomial*     polynomial_create_from_complexG(Complex z, int_signed degree, char* variable);
Polynomial*     polynomial_create_from_coefficients(real coefficients[], int_signed size);
Polynomial*     polynomial_copy(const Polynomial* p);
void            polynomial_destroy(Polynomial* p);
int_signed      polynomial_get_degree(const Polynomial* p);
char*           polynomial_get_variable(const Polynomial* p);
Complex         polynomial_at(const Polynomial* p, int_signed degree);
Complex         polynomial_get_leading_coefficient(const Polynomial* p);
bool            polynomial_set(Polynomial* p, Complex value, int_signed degree);
Polynomial*     polynomial_increment(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_add(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_addLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_subtract(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_subtractLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_multiply(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_multiplyLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_scale(Polynomial* p, Complex factor);
Polynomial*     polynomial_exponentiate(Polynomial* p, int_signed power);
Polynomial*     polynomial_factor(const Polynomial* p,const Polynomial* q);
Polynomial*     polynomial_differentiate(const Polynomial* p);
Complex         polynomial_evaluate(const Polynomial* p, Complex value);
bool            polynomial_is_constant(const Polynomial* p);
Complex         polynomial_get_constant_coefficient(const Polynomial* p);
bool            polynomial_is_real(const Polynomial* p);
bool            polynomial_is_zero(const Polynomial* p);
Array*          polynomial_roots(const Polynomial* p);
real            polynomial_newtons(const Polynomial* p);

//matrix
Matrix*         matrix_create(int_signed n_rows, int_signed n_cols);
void            matrix_destroy(Matrix* matrix);
Matrix*         matrix_copy(const Matrix* matrix);
int_signed      matrix_get_n_rows(const Matrix* matrix);
int_signed      matrix_get_n_cols(const Matrix* matrix);
int_signed      matrix_get_total_size(const Matrix* matrix);
Complex         matrix_at(const Matrix* A, int_signed j, int_signed k);
bool            matrix_set(Matrix* A, Complex z, int_signed j, int_signed k);
Matrix*         matrix_eye(int_signed size);
void            matrix_add_to_left(Matrix* lhs, const Matrix* rhs);
void            matrix_mult_lhs(Matrix* lhs, const Matrix* rhs);
Matrix*         matrix_add(const Matrix* A, const Matrix* B);
Matrix*         matrix_mult(const Matrix* A, const Matrix* B);

//math
bool            within_delta(real x, real y, real delta);
bool            real_is_int(real x);
real            math_mod(real x, real mod);
real            power(real base, int_unsigned n);
real            absolute_value(real x);
int_signed      power_int(int_signed base, int_unsigned n);
int_unsigned    factorial(int_unsigned n);
int_unsigned    round_to_int(real x);
int_unsigned    fib(int_unsigned n);
int_unsigned    math_is_perfect_square(int_unsigned x);
int_signed      math_gcd(int_signed a, int_signed b);

//math: R -> R
real            math_sqrt(real a);
real            math_exp(real x);
real            math_ln(real x);
real            math_log2(real x);
real            math_log10(real x);
real            math_log(real x, real base);
real            math_id(real x);
real            math_sin(real x);
real            math_cos(real x);
real            math_tan(real x);

//math: primes
bool            is_prime(int_unsigned n);
int_unsigned    get_next_prime(int_unsigned n);

//random
int_unsigned    random_get();
int_unsigned    random_in_range(int_unsigned left, int_unsigned right);
void            random_seed(int_unsigned seed);
real            random_chi_squared(int_unsigned seed, int_unsigned max_value, int_unsigned sample_size);
bool            random_chi_squared_test(int_unsigned seed, int_unsigned max, int_unsigned sample_size);

//conversion
int_signed      convert_to_int(const char* string);
int_signed      convert_to_intS(const String* string);
real            convert_to_real(const char* string);
Complex         convert_to_complex(const char* string);
String*         convert_to_string_uintB(int_unsigned n, byte base);
String*         convert_to_string_uint(int_unsigned n);

//copy
void*           copy_shallow(const void* item);
void*           copy_int_signed(int_signed* n);
void*           copy_real(real* x);
void*           copy_complex(Complex* z);
void*           copy_cstring(const char* string);

//print
void            print_int(int_signed n);
void            print_uint(int_unsigned n);
void            print_intN(int_signed n);
void            print_int_pointer(int_signed* n);
void            print_int_pointerN(int_signed* n);
void            print_real(real x);
void            print_complex(Complex z);
void            print_cstring(const char* string);
void            print_cstringN(const char* string);
void            print_string(const String* string);
void            print_stringN(const String* string);
void            print_cstringS(const char* string);
void            print_stringL(const String* string);
void            print_polynomial(const Polynomial* p);
void            print_polynomial_with_rhs(const Polynomial* p);
void            _print_polynomialDBG(const Polynomial* p);
void            print_array(const Array* array, void (*print)(), const char* separator);
void            print_arrayN(const Array* array, void (*print)(), const char* separator);
void            print_list(const List* list, void (*function)());
void            print_distribution(const Array* distribution);
void            print_hash_table(const HashTable* table, void (*print)());
void            print_hash_table_cell(const HashTable* table, void (*print)(), int_signed n);
void            print_heap(const Heap* heap, void (*print)());
void            print_tree(const Tree* tree, void (*print)());
void            print_treeN(const Tree* tree, void (*print)());
void            print_set(const Set* set, void (*print)());
void            print_setN(const Set* set, void (*print)());
void            print_time_diff(clock_t start, clock_t end);

//error
void*           error_set(int_unsigned type, const char* _error_message);
void            error_display();
void*           error_display_return();
void            error_reset();
void            error_display_message(const char* message);
void*           error_display_message_return(const char* message);
void            error_display_custom(const char* message);
void*           error_display_custom_return(const char* message);

#endif
