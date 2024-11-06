#include <stdio.h>
#include <stdlib.h>

#include "salloc.h"


int main() {
    // Test the custom malloc function
    init_salloc();

    // Initialize and print the allocated memory
    for (int i = 0; i < 20; i++) {
        int *arr = (int*) salloc(5 * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed : %d\n", i);
        
        }
        else
        {
            printf("allocation success : %d => %X\n", i, (uint32_t)arr);
            for (int j = 0; j < 1; j++)
            {
                arr[j] = j * 100 + i;
                printf("arr[%d] = %d\n", i, arr[j]);
            }
            sallfree(arr);
        }
    }

    // Free the allocated memory

    return 0;
}