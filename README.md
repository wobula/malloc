# Malloc

### a dynamic memory allocation and recycling system

Malloc is a memory management system consisting of the following five functions:

#### void *malloc(size_t size);
Returns a void ptr to a memory address of the specified size.  If no memory is available, returns NULL.

#### void free(void *this);
Frees the provided void ptr.  This memory becomes usable again during subsequent calls to malloc, realloc, and calloc.

#### void *realloc(void *this, size_t size);
Reallocates the provided pointer to the specified size.  If the size is smaller than the current size, realloc copies as much of the original memory as can fit into the new, smaller size.  If the new size is larger, realloc copies everything from the original memory into the new space.  If the provided pointer is null, realloc calls malloc with the provided size.  If size is 0, then realloc calls free on the provided pointer.  Phew!

#### void *calloc(size_t nitems, size_t size);
Calloc allocates sets of data by multiplying nitems by size and returning a pointer to this space.  Unlike Malloc and realloc, Calloc zeroes out all of its provided memory.

#### void show_alloc_mem(void);
Show alloc mem is a debugging function that prints out statistics on a programs memory usage.