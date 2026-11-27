
#include <stdint.h>
#include "paging.h"
#include "heap.h"



uint32_t *page_directory;




uint32_t create_page_entry(uint32_t base_address, char present, char writable, char privilege_level, char cache_enabled, char write_through_cache, char accessed, char page_size, char dirty)
{
    uint32_t entry = 0;
    
    entry |= present;
    entry |= writable << 1;
    entry |= privilege_level << 2;
    entry |= write_through_cache << 3;
    entry |= cache_enabled << 4;
    entry |= accessed << 5;
    entry |= dirty << 6;
    entry |= page_size << 7;
    
    return base_address | entry;
}

void paging_init()
{
    // PART 1:
    
    uint32_t curr_page_frame = 0;
    
    page_directory = kalloc( 4 * 1024 );
        
    for ( uint32_t currPDE = 0; currPDE < PDE_NUM; currPDE++ )
    {
        uint32_t *pagetable = kalloc(4 * PTE_NUM);
        
        for ( uint32_t currPTE = 0; currPTE < PTE_NUM; currPTE++, curr_page_frame++ )
            pagetable[ currPTE ] = create_page_entry(curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0 );
        
        page_directory[ currPDE ] = create_page_entry((uint32_t)pagetable, 1, 0, 0, 1, 1, 0, 0, 0 );
    }
    
    // ... //
    
    // PART 2
    
    load_page_directory();
    enable_paging();
}
