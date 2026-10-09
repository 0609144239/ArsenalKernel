#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "process.h"



uint32_t get_next_sch_pid();
uint32_t get_curr_sch_pid();

void scheduler_init();
process *get_next_process();

void scheduler( uint32_t eip, uint32_t edi,
                uint32_t esi, uint32_t ebp,
                uint32_t esp, uint32_t ebx,
                uint32_t edx, uint32_t ecx,
                uint32_t eax
               );




#endif

