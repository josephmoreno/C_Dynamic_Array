#include "dynamic_array.h"

int main() {

    printf("\n");

    struct DynamicArray dyn_arr;
    DynArr_init(&dyn_arr);
    
    // User Menu
    unsigned char c = '\0';
    int x0, x1;

    while(1) {
        DynArr_print(&dyn_arr);
        printf("\n");

        printf("Choose an operation:\n");
        printf("1: Resize array\n2: Write value to indexed position\n3: Insert element\n4: Erase element by index\n");
        printf("Q: Quit / End program\n\n");
        printf("> ");

        scanf("%c", &c);

        printf("\n");
        switch(c) {
            case '1':
                printf("Enter desired size for array: ");
                scanf("%d", &x0);

                DynArr_resize(&dyn_arr, x0);
                break;

            case '2':
                printf("Enter desired value to write into array: ");
                scanf("%d", &x0);

                printf("Enter the index at which the value will be written to (-1 for last index): ");
                scanf("%d", &x1);

                DynArr_write(&dyn_arr, x1, x0);
                break;

            case '3':
                printf("Enter desired value to write into array: ");
                scanf("%d", &x0);

                printf("Enter the index at which the value will be inserted at (-1 for last index): ");
                scanf("%d", &x1);

                DynArr_insert(&dyn_arr, x1, x0);
                break;

            case '4':
                printf("Enter index of element to erase (-1 for last index): ");
                scanf("%d", &x0);

                DynArr_erase(&dyn_arr, x0);
                break;

            case 'Q':
            case 'q':
                return(0);

            default:
                break;
        }

        // Clear out input buffer.
        while ((c = getchar()) != '\n' && c != EOF) { }

        printf("\n");
    }

    DynArr_free(&dyn_arr);

    return(0);

}

void DynArr_init(struct DynamicArray *dyn_arr) {
    dyn_arr->array0 = NULL;
    dyn_arr->array1 = NULL;
    dyn_arr->cur = 0;
    dyn_arr->size = 0;

    return;
}

void DynArr_resize(struct DynamicArray *dyn_arr, int size) {
    unsigned int i;

    // If the size passed <= 0, initialize the array.
    if (size <= 0) {
        DynArr_init(dyn_arr);
        
        return;
    }
    
    // If it's an empty array...
    if (dyn_arr->size == 0) {
        // Set the active array to array0.
        dyn_arr->cur = 0;

        // Size array0.
        dyn_arr->array0 = (int *)calloc(size, sizeof(int));

        // Record the array's current size.
        dyn_arr->size = size;
    }

    // If active array is array0...
    else if (dyn_arr->cur == 0) {
        // Set the active array to array1.
        dyn_arr->cur = 1;

        // Size array1.
        dyn_arr->array1 = (int *)calloc(size, sizeof(int));

        // Copy contents of array0 to array1.
        if (size <= dyn_arr->size) {
            for(i = 0; i < size; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];
        }else {
            for(i = 0; i < dyn_arr->size; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];
        }

        // Free array0.
        free(dyn_arr->array0);
        dyn_arr->array0 = NULL;

        // Record the array's current size.
        dyn_arr->size = size;
    }

    // If active array is array1...
    else if (dyn_arr->cur == 1) {
        // Set the active array to array0.
        dyn_arr->cur = 0;

        // Size array0.
        dyn_arr->array0 = (int *)calloc(size, sizeof(int));

        // Copy contents of array1 to array0.
        if (size <= dyn_arr->size) {
            for(i = 0; i < size; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];
        }else {
            for(i = 0; i < dyn_arr->size; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];
        }

        // Free array1.
        free(dyn_arr->array1);
        dyn_arr->array1 = NULL;

        // Record the array's current size.
        dyn_arr->size = size;
    }

    return;
}

void DynArr_insert(struct DynamicArray *dyn_arr, int index, int value) {
    unsigned int i;

    // Return if index passed is < -1.
    if (index < -1)
        return;

    // Return if index is > the array's size (can push an element at the end of the array).
    if (index > dyn_arr->size)
        return;

    // If index == -1, push value to the end of the array.
    if (index == -1) {
        
        // If active array is array0...
        if (dyn_arr->cur == 0) {
            // Set the active array to array1.
            dyn_arr->cur = 1;

            // Size array1 and record dynamic array's size.
            dyn_arr->array1 = (int *)calloc(++dyn_arr->size, sizeof(int));

            // Copy contents of array0 to array1 and push value at the end of array1.
            for(i = 0; i < dyn_arr->size - 1; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];

            dyn_arr->array1[dyn_arr->size - 1] = value;
            
            // Free array0.
            free(dyn_arr->array0);
            dyn_arr->array0 = NULL;

        // If active array is array1...
        }else if (dyn_arr->cur == 1) {
            // Set the active array to array0.
            dyn_arr->cur = 0;

            // Size array0 and record dynamic array's size.
            dyn_arr->array0 = (int *)calloc(++dyn_arr->size, sizeof(int));

            // Copy contents of array0 to array1 and push value at the end of array1.
            for(i = 0; i < dyn_arr->size - 1; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];

            dyn_arr->array0[dyn_arr->size - 1] = value;

            // Free array1.
            free(dyn_arr->array1);
            dyn_arr->array1 = NULL;
        }

    // If 0 <= index <= dyn_arr->size, then...
    }else {

        // If active array is array0...
        if (dyn_arr->cur == 0) {
            // Set the active array to array1.
            dyn_arr->cur = 1;

            // Size array1 and record dynamic array's size.
            dyn_arr->array1 = (int *)calloc(++dyn_arr->size, sizeof(int));

            // Copy contents of array0 to array1 and write value at array1[index].
            for(i = 0; i < index; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];

            dyn_arr->array1[index] = value;

            for(i = (index + 1); i < dyn_arr->size; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i - 1];
            
            // Free array0.
            free(dyn_arr->array0);
            dyn_arr->array0 = NULL;

        // If active array is array1...
        }else if (dyn_arr->cur == 1) {
            // Set the active array to array0.
            dyn_arr->cur = 0;

            // Size array0 and record dynamic array's size.
            dyn_arr->array0 = (int *)calloc(++dyn_arr->size, sizeof(int));

            // Copy contents of array1 to array0 and write value at array0[index].
            for(i = 0; i < index; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];

            dyn_arr->array0[index] = value;

            for(i = (index + 1); i < dyn_arr->size; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i - 1];

            // Free array1.
            free(dyn_arr->array1);
            dyn_arr->array1 = NULL;
        }
    }

    return;
}

void DynArr_write(struct DynamicArray *dyn_arr, int index, int value) {
    // Return if index passed is < -1.
    if (index < -1)
        return;

    // Return if index passed is >= dyn_arr->size.
    if (index >= dyn_arr->size)
        return;

    if (index == -1) {
        if (dyn_arr->cur == 0) 
            dyn_arr->array0[dyn_arr->size - 1] = value;
        else if (dyn_arr->cur == 1)
            dyn_arr->array1[dyn_arr->size - 1] = value;
    }else {
        if (dyn_arr->cur == 0) 
            dyn_arr->array0[index] = value;
        else if (dyn_arr->cur == 1)
            dyn_arr->array1[index] = value;
    }

    return;
}

void DynArr_erase(struct DynamicArray *dyn_arr, int index) {
    unsigned int i;

    // Return if index passed is < -1.
    if (index < -1)
        return;

    // Return if index passed is >= dyn_arr->size.
    if (index >= dyn_arr->size)
        return;

    // If index == -1, erase element at the end of the array.
    if (index == -1) {

        // If active array is array0...
        if (dyn_arr->cur == 0) {
            // Set the active array to array1.
            dyn_arr->cur = 1;

            // Size array1 and record dynamic array's size.
            dyn_arr->array1 = (int *)calloc(--dyn_arr->size, sizeof(int));

            // Copy contents from array0 to array1, except for array0[dyn_arr->size - 1].
            for(i = 0; i < dyn_arr->size; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];

            // Free array0.
            free(dyn_arr->array0);
            dyn_arr->array0 = NULL;

        // If active array is array1...
        }else if (dyn_arr->cur == 1) {
            // Set the active array to array0.
            dyn_arr->cur = 0;

            // Size array0 and record dynamic array's size.
            dyn_arr->array0 = (int *)calloc(--dyn_arr->size, sizeof(int));

            // Copy contents from array1 to array0, except for array1[dyn_arr->size - 1].
            for(i = 0; i < dyn_arr->size; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];

            // Free array1.
            free(dyn_arr->array1);
            dyn_arr->array1 = NULL;
        }

    // If 0 <= index < dyn_arr->size...
    }else {
        // If active array is array0...
        if (dyn_arr->cur == 0) {
            // Set the active array to array1.
            dyn_arr->cur = 1;

            // Size array1 and record dynamic array's size.
            dyn_arr->array1 = (int *)calloc(--dyn_arr->size, sizeof(int));

            // Copy contents from array0 to array1, except for array0[index].
            for(i = 0; i < index; ++i)
                dyn_arr->array1[i] = dyn_arr->array0[i];

            for(i = (index + 1); i < (dyn_arr->size + 1); ++i)
                dyn_arr->array1[i - 1] = dyn_arr->array0[i];

            // Free array0.
            free(dyn_arr->array0);
            dyn_arr->array0 = NULL;

        // If active array is array1...
        }else if (dyn_arr->cur == 1) {
            // Set the active array to array0.
            dyn_arr->cur = 0;

            // Size array0 and record dynamic array's size.
            dyn_arr->array0 = (int *)calloc(--dyn_arr->size, sizeof(int));

            // Copy contents from array1 to array0, except for array1[index].
            for(i = 0; i < index; ++i)
                dyn_arr->array0[i] = dyn_arr->array1[i];

            for(i = (index + 1); i < (dyn_arr->size + 1); ++i)
                dyn_arr->array0[i - 1] = dyn_arr->array1[i];

            // Free array1.
            free(dyn_arr->array1);
            dyn_arr->array1 = NULL;
        }
    }

    return;
}

void DynArr_print(struct DynamicArray *dyn_arr) {
    unsigned int i;

    if (dyn_arr->size == 0) {
        printf("{}\n");
    }else {
        printf("{");
        if (dyn_arr->cur == 0) {
            for(i = 0; i < (dyn_arr->size - 1); ++i) 
                printf("%d, ", dyn_arr->array0[i]);

            printf("%d}\n", dyn_arr->array0[dyn_arr->size - 1]);
        }else if (dyn_arr->cur == 1) {
            for(i = 0; i < (dyn_arr->size - 1); ++i)
                printf("%d, ", dyn_arr->array1[i]);

            printf("%d}\n", dyn_arr->array1[dyn_arr->size - 1]);
        }
    }

    printf("Array Size: %d; Active Array: %d\n", dyn_arr->size, dyn_arr->cur);

    return;
}

void DynArr_free(struct DynamicArray *dyn_arr) {
    free(dyn_arr->array0);
    free(dyn_arr->array1);

    dyn_arr->array0 = NULL;
    dyn_arr->array1 = NULL;

    return;
}