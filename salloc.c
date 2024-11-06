#include "salloc.h"
#include <unistd.h>
#include <string.h>


uint8_t sam_memory_pool[SAM_MEMORY_POOL_SIZE + 1];
sam_t sam[SAM_MAX_ALOCATION_ALLOWED];
SAM_CAST_TYPE samAddr = 0;
SAM_CAST_TYPE allocationCount = 0;

struct allocatedMemory_s *first = NULL;
struct allocatedMemory_s *last = NULL;

void* salloc(SAM_SIZETYPE size)
{
    SAM_SIZETYPE i = 0;
    
    struct allocatedMemory_s *samP = first;
    if (samP->mem == 0)
    {
        if (size < SAM_MEMORY_POOL_SIZE)
        {
            samP->mem = 1;
            samP->size = size;
            allocationCount ++;
        }
        else
            return NULL;
        return (void*)&sam_memory_pool[1];
    }

    while (samP) {    // search for not allocated memory slot
        if (samP->next == NULL)
        {            // error to check
            return NULL;
        }
        if (samP->next->mem == 0)
        {
            SAM_SIZETYPE nextUsableAdr = ((SAM_SIZETYPE)samP->mem) + samP->size;
            if (nextUsableAdr + size > SAM_MEMORY_POOL_SIZE)
            {
                return NULL;
            }
            samP->next->mem = nextUsableAdr;
            samP->next->size = size;
            allocationCount ++;
            return (void*)&sam_memory_pool[nextUsableAdr];
        }
        else
        {
            samP = samP->next;
        }
    }

    return NULL;
}

void sam_setFirst()
{
    struct allocatedMemory_s *temp = first;

    while (temp->next != NULL)
    {
        
    }

}

struct allocatedMemory_s * sam_getFirstAvailableAllocation()
{

}

void sallfree(void* ptr)
{
    if (!ptr)
        return;
    if (first->mem == ((SAM_CAST_TYPE)ptr - samAddr))
    {
        first->mem = 0;
        first->size = 0;
        allocationCount--;
        if (allocationCount)
        {
            while (first->mem == 0)
            {
                last->next = first;
                last = last->next;
                first->next = first->next->next;
                first = first->next;
            }
        }
    }

}

void init_salloc()
{
    int i = 0;
    samAddr = (SAM_CAST_TYPE)sam;
    allocationCount = 0;
    while (i < SAM_MAX_ALOCATION_ALLOWED)
    {
        sam[i].size = 0;
        sam[i].mem = 0;
        sam[i].next = NULL;
        if (i < SAM_MAX_ALOCATION_ALLOWED -1)
        {
            sam[i].next = &sam[i+1];
        }
        i++;
    }
    first = &sam[0];
    last = &sam[SAM_MAX_ALOCATION_ALLOWED -1];
}

