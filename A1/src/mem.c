#include <stdio.h>
#include "mem.h"

#define MAX_BLOCKS 256
struct block
{
  int value;
  int next;
};

struct counters
{
  int mem_alloc;
  int mem_free;
  int deref;
} _COUNTERS;

struct block _MEMORY[MAX_BLOCKS];	// global memory used by program
					
int _USED[MAX_BLOCKS] = {0};		// variable to tell if blocks are 
					// allocated initialized to all zero
					// e.g. if _USED[7]=4, then blocks
					// 7, 8, 9, and 10 are allocated
				
int _available( int start )
{
  // return the number of blocks available from start
  // this is no so efficient
  int cnt = 0;
  for (int i=start;((!_USED[i])&&(i<MAX_BLOCKS));i++,cnt++);
  return cnt;
}

void _allocate( int start, int size )
{
  _USED[start] = size;
}

int mem_alloc( int size )
{
  int available;

  // save address 0 for NULL, so start at 1
  for ( int start=1;start<MAX_BLOCKS;start+=available+_USED[start+available] )
  {
    available = _available( start );

    if ( available >= size )
    {
      _allocate( start, size );
      _COUNTERS.mem_alloc++;
      return start;
    }

  }
  return 0;
}

int get_value( int addr )
{
  _COUNTERS.deref++;
  return _MEMORY[addr].value;
}

void set_value( int addr, int val )
{
  _COUNTERS.deref++;
  _MEMORY[addr].value = val;
}

int get_next( int addr )
{
  _COUNTERS.deref++;
  return _MEMORY[addr].next;
}

void set_next( int addr, int next )
{
  _COUNTERS.deref++;
  _MEMORY[addr].next = next;
}

void mem_free( int addr )
{
  _USED[addr] = 0;
  _COUNTERS.mem_free++;
}

void reset_counters( void )
{
  _COUNTERS.mem_alloc = 0;
  _COUNTERS.mem_free = 0;
  _COUNTERS.deref = 0;
}

void print_counters( int i )
{
  printf( "%6d %6d %6d %6d\n",
          i,
          _COUNTERS.mem_alloc, 
          _COUNTERS.mem_free,
          _COUNTERS.deref );
}
