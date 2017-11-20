# Malloc

### a dynamic memory allocation and recycling system

Malloc is a memory management system consisting of the following five functions:

#### void *malloc(size_t size);

#### void free(void *this);

#### void *realloc(void *this, size_t size);

#### void *calloc(size_t nitems, size_t size);

#### void show_alloc_mem(void);