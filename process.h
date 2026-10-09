#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "screen.h"



typedef enum  {RUNNING, READY, WAITING} process_state;

typedef struct process_context { uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi, eip; } process_context;

typedef struct process {
    
    uint32_t pid;
    uint32_t *base_addr;
    uint32_t size;
    process_state state;
    process_context context;

} process;


void process_table_init(void);
void process_create(uint32_t *base_addr, process *process);


process *get_process(uint32_t pid);
uint32_t get_process_count(void);
uint32_t get_curr_pid(void);

    


#endif
