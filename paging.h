
#include <stdint.h>

#define PDE_NUM 3
#define PTE_NUM 1024


extern void load_page_directory();
extern void enable_paging();



void paging_init();
uint32_t create_page_entry(uint32_t base_address, char present, char writable, char privilege_level, char cache_enabled, char write_through_cache, char accessed, char page_size, char dirty);
