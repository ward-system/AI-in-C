#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
// #include <cstddef>

// Memory
typedef struct{
    void* data;
    size_t ItemSize;
    size_t size;
    size_t capacity;
}Array;

Array arr_alloc(size_t size);

void arr_copy(Array* dest, Array src);

void arr_push_back(Array *arr, void* Item);

void* arr_index_item(Array *arr, size_t index);

void arr_remove_back(Array *arr);

void arr_clear(Array *arr);

void arr_unalloc(Array* arr);


#endif // ARRAY_H