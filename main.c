
#include <stdint.h>

#include "scheduler.h"
#include "screen.h"
#include "heap.h"



//TODO:
//LUT of all the interrupts possible with proper descriptions

void process_A(void);
void process_B(void);
void process_C(void);
void process_D(void);

process p1, p2, p3, p4;





void kernel_main() {
    
    screen_init();
    heap_init();
    uint32_t *page_directory = kalloc(4 * 1024);
    //process_table_init();
    //scheduler_init();
    
	print( "Welcome to ArsenalKernal!" );
	println();
	print( "We are now in Protected-mode(32-bits)" );
	println();
	printi(42);
	println();
    
//    process_create((uint32_t *)&process_A, &p1);
//    process_create((uint32_t *)&process_B, &p2);
//    process_create((uint32_t *)&process_C, &p3);
//    process_create((uint32_t *)&process_D, &p4);
    
	
	while( 1 );
}




void interrupt_handler(int interrupt_number, int error_code) {
	println();
	print("Interrupt Received ");
	printi(interrupt_number);
    println();
    print("Error Code ");
    printi(error_code);
    
}




void process_A(void) {
    
    print("PROCESS A:");
    
    while(1) {
        __asm__ volatile ("mov $5390, %eax");
    }
}


void process_B(void) {
    
    print("PROCESS B:");
    
    while(1) {
        __asm__ volatile ("mov $5391, %eax");
    }
}


void process_C(void) {
    
    print("PROCESS C:");
    
    while(1) {
        __asm__ volatile ("mov $5392, %eax");
    }
}


void process_D(void) {
    
    print("PROCESS D:");
    
    while(1) {
        __asm__ volatile ("mov $5393, %eax");
    }
}
