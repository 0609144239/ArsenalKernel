#include <stdint.h>
#include "scheduler.h"


static uint32_t next_sch_pid;
static uint32_t curr_sch_pid;
process *next_process;





void scheduler_init() {
    
    next_sch_pid = 0;
    curr_sch_pid = 0;
    
}


uint32_t get_next_sch_pid() {
    return next_sch_pid;
}


uint32_t get_curr_sch_pid() {
    return curr_sch_pid;
}


process *get_next_process() {
    
    next_process = get_process(next_sch_pid);
    
    curr_sch_pid = next_sch_pid;
    next_sch_pid++;
    next_sch_pid = next_sch_pid % get_process_count();
    
    return next_process;
    
    
}



void scheduler(uint32_t eip, uint32_t edi,
               uint32_t esi, uint32_t ebp,
               uint32_t esp, uint32_t ebx,
               uint32_t edx, uint32_t ecx,
               uint32_t eax) {
    
    process *curr_process;
    
    print(" EAX = ");
    printi(eax);
    
    curr_process = get_process(curr_sch_pid);
    next_process = get_next_process();
    
    
    if (curr_process->state == RUNNING) {
        
        curr_process->context.eax = eax;
        curr_process->context.ecx = ecx;
        curr_process->context.edx = edx;
        curr_process->context.ebx = ebx;
        curr_process->context.esp = esp;
        curr_process->context.ebp = ebp;
        curr_process->context.esi = esi;
        curr_process->context.edi = edi;
        curr_process->context.eip = eip;
        
    }
    
    
    curr_process->state = READY;
    
    
    __asm__ volatile(
          "mov %0, %%eax; \
           mov %0, %%ecx; \
           mov %0, %%edx; \
           mov %0, %%ebx; \
           mov %0, %%esi; \
           mov %0, %%edi;"
          :
          :"r" (next_process->context.eax), "r" (next_process->context.ecx),
           "r" (next_process->context.edx), "r" (next_process->context.ebx),
           "r" (next_process->context.esi), "r" (next_process->context.edi)
        );
        
        
        
    
    
    next_process->state = RUNNING;

}


void run_next_process() {
    __asm__ volatile( " sti; \
           jmp *%0" :
           : "r" (next_process->context.eip)
        );
}


