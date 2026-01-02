#ifndef _MEM_H
#define _MEM_H

#define COUNTER_HEADINGS " size  malloc  free  deref \n====== ====== ====== ======\n"

int mem_alloc( int size );
void mem_free( int addr );
int get_value( int addr );
void set_value( int addr, int val );
int get_next( int addr );
void set_next( int addr, int val );

void reset_counters( void );
void print_counters( int i );
#endif
