#include <stdio.h>
#include <ctype.h>

struct DynamicArray {
    int *array0;
    int *array1;
    int size;
    unsigned int cur;   // 0 = array0 is the active array; 1 = array1 is active.
};

void DynArr_init(struct DynamicArray *dyn_arr);
void DynArr_resize(struct DynamicArray *dyn_arr, int size);
void DynArr_insert(struct DynamicArray *dyn_arr, int index, int value);
void DynArr_write(struct DynamicArray *dyn_arr, int index, int value);
void DynArr_erase(struct DynamicArray *dyn_arr, int index);
void DynArr_print(struct DynamicArray *dyn_arr);
void DynArr_free(struct DynamicArray *dyn_arr);