#ifndef SALLOC_H
#define SALLOC_H

#include <stdint.h>



#define SAM_MEMORY_POOL_SIZE        8000  // nbr of byte can be allocated

#define SAM_MAX_ALOCATION_ALLOWED   10  // must be greater than 1

#define SAM_CAST_TYPE uint64_t

#if (SAM_MEMORY_POOL_SIZE > UINT32_MAX)
    #define SAM_SIZETYPE uint64_t
#elif (SAM_MEMORY_POOL_SIZE > UINT16_MAX)
    #define SAM_SIZETYPE uint32_t
#elif (SAM_MEMORY_POOL_SIZE > UINT8_MAX)
    #define SAM_SIZETYPE uint16_t
#else
    #define SAM_SIZETYPE uint8_t
#endif


typedef struct allocatedMemory_s{
    SAM_SIZETYPE size;
    SAM_SIZETYPE mem;
    struct allocatedMemory_s *next;
} sam_t;



void* salloc(SAM_SIZETYPE size);

void sallfree(void* sam);


void init_salloc();



#endif // SALLOC_H

