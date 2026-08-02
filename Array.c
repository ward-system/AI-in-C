#include "Array.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Array arr_alloc(size_t ItemSize)
{
    Array b;
    b.ItemSize = ItemSize;
    b.capacity = 5; // defualt capacity
    b.size = 0;

    b.data = malloc(ItemSize * b.capacity);
    assert(b.data);
    memset(b.data, 0, ItemSize * b.capacity);

    return b;
}

void arr_copy(Array* dest, Array src)
{
    dest->size = src.size;
    dest->capacity = src.capacity;
    dest->ItemSize = src.ItemSize;

    if (!dest->data){
        dest->data = malloc(dest->ItemSize * dest->capacity);
    }

    memcpy(dest->data, src.data, dest->ItemSize * src.size);
}


void arr_push_back(Array *arr, void* Item)
{
    size_t newSize = arr->size + 1;
    size_t newSizeInBytes = newSize * arr->ItemSize;
    if(newSize >= arr->capacity){ // We need to copy data
        arr->capacity += 5;
        void *temp = malloc(arr->capacity * arr->ItemSize);
        memset(temp, 0, arr->capacity * arr->ItemSize);
        memcpy(temp, arr->data, newSizeInBytes);
        free(arr->data);
        arr->data = malloc(newSizeInBytes);
        memset(temp, 0, arr->capacity * arr->ItemSize);
        memcpy(arr->data, temp, newSizeInBytes);
        free(temp);
    }


    // pushing the Item to the back
    void *target = (unsigned char*)arr->data + (arr->size * arr->ItemSize);

    memcpy(target, Item, arr->ItemSize);

    arr->size = newSize;
}

void* arr_index_item(Array *arr, size_t index)
{
    void *target = (unsigned char*)arr->data + (index * arr->ItemSize);

    return target;
}

void arr_remove_back(Array *arr)
{
    // Setting the back of the array to 0
    void *target = (unsigned char*)arr->data + (arr->size * arr->ItemSize);
    memset(target, 0, arr->ItemSize);

    --arr->size;
}


void arr_clear(Array *arr){
    arr->capacity = 5;
    arr->size = 0;
}

void arr_unalloc(Array* arr){
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
    arr->ItemSize = 0;
}