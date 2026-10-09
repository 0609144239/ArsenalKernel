
#include <stdint.h>
#include "process.h"


static uint32_t process_count;
static uint32_t curr_pid;
process *process_list[12];



void process_table_init(void) {
    
    process_count = 0;
    curr_pid = 0;

    
}




void process_create(uint32_t *base_addr, process *process) {
    
    process->pid = curr_pid++;
    
    process->context.eax = 0;
    process->context.ecx = 0;
    process->context.edx = 0;
    process->context.ebx = 0;
    process->context.esp = 0;
    process->context.ebp = 0;
    process->context.esi = 0;
    process->context.edi = 0;
    process->context.eip = *base_addr;
    
    process->state = READY;
    
    process->base_addr = base_addr;
    
    process_list[process->pid] = process;
    
    process_count++;
    
}




process *get_process(uint32_t pid){
    
    if (pid > 11 || pid < 0) {
        
        println();
        char *errorPID = "INVALID PID";
        print(errorPID);
        return nullptr;
        
    }
    
    return process_list[pid];
    
}


uint32_t get_process_count(void) {
    
    return process_count;
}

uint32_t get_curr_pid(void){
    
    return curr_pid;
}
