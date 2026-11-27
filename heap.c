
#include <stdint.h>

#include "heap.h"


uint32_t heap_base;

void heap_init(void) {
    
    //heap_base = 0x100000;
    heap_base = 0x400000;
    
}

uint32_t* kalloc(uint32_t bytes) {
    
    uint32_t *new_object_address = (uint32_t*) heap_base;
    
    heap_base += bytes;
    
    return new_object_address;
    
}


