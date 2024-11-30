#ifndef VECTOR_H
#define VECTOR_H

typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG,
    TYPE_SHORT,
    TYPE_UNSIGNED_INT,
    TYPE_BOOL,
    TYPE_POINTER,
    TYPE_CHAR_ARRAY,
    TYPE_VOID_POINTER
} VectorType;

#define GET_TYPE(x) _Generic((x), \
    int:          TYPE_INT, \
    char:         TYPE_CHAR, \
    float:        TYPE_FLOAT, \
    double:       TYPE_DOUBLE, \
    long:         TYPE_LONG, \
    long long:    TYPE_LONG, \
    short:        TYPE_SHORT, \
    unsigned int: TYPE_UNSIGNED_INT, \
    char*:        TYPE_CHAR_ARRAY, \
    void*:        TYPE_VOID_POINTER, \
    default:      TYPE_UNKNOWN)


/* API FIRST */

#define Vector(T) struct { \
    T* items;              \
    size_t capacity;       \
    size_t size;           \
    size_t item_size;      \
    t_coliseu allocator;   \
    VectorType type;       \
}


/*
Vector(int) vec;
// vec_push(&vec, 5)
// Se transforma em:
 &(int){5}  // Cria um int temporário com valor 5 e pega seu endereço
*/
#define vector_push(vec, item) \
        _Generic((item), \
            char*:    _vector_push_pointer, \
            void*:    _vector_push_pointer, \
            int*:     _vector_push_pointer, \
            double*:  _vector_push_pointer, \
            float*:   _vector_push_pointer, \
            default: _vector_push \
        )((vec), &(typeof(*(vec)->items)){item})

#define vector_init(vec) _vector_init(vec, GET_TYPE(*(vec)->items), sizeof(*(vec)->items))


void        _vector_push(void* vector, void* item);

void        _vector_push_pointer(void* vector, void* item);

void        _vector_init(void* vector, VectorType type, size_t size_item);

void        _vector_destroy(void* vector);

void        _vector_print(void* vector);

#endif