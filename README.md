# Malloc

### a dynamic memory allocation and recycling system

#### Summary

Malloc is a memory management system consisting of the following five functions:

##### void *malloc(size_t size);
Returns a void ptr to a memory address of the specified size.  If no memory is available, returns NULL.

##### void free(void *this);
Frees the provided void ptr.  This memory becomes usable again during subsequent calls to malloc, realloc, and calloc.

##### void *realloc(void *this, size_t size);
Reallocates the provided pointer to the specified size.  If the size is smaller than the current size, realloc copies as much of the original memory as can fit into the new, smaller size.  If the new size is larger, realloc copies everything from the original memory into the new space.  If the provided pointer is null, realloc calls malloc with the provided size.  If size is 0, then realloc calls free on the provided pointer.  Phew!

##### void *calloc(size_t nitems, size_t size);
Calloc allocates sets of data by multiplying nitems by size and returning a pointer to this space.  Unlike Malloc and realloc, Calloc zeroes out all of its provided memory.

##### void show_alloc_mem(void);
Show alloc mem is a debugging function that prints out statistics on a programs memory usage.

#### Explanation

Why do we use Malloc?  Two reasons: convenience and speed.

##### Convenience

The system call for requesting memory, mmap, has the following function prototype:

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

A quick comparison of mmap's prototype with Malloc's, and we can see that malloc is much simpler.  Where mmap takes 6 arguments, malloc takes one.  But beyond this surface level ease in terms of supplying arguments, Malloc is also easier, not just on the programmer, but also *on the computer*.  Read the next section to find out why.

##### Speed

Malloc is easier on the computer because it doesn't task the kernel nearly as much as mmap.  The reason for this is that malloc calls mmap once in order to allocate a giant *slab* of memory, which it then parcels out to the user during each subsequent malloc call.  If malloc runs out of memory -- then it calls mmap and asks for more memory, but not until then.  By asking for a big slab and giving the user a small amount of that slab, we can improve performance through a reduction in kernel taskings.  This is the heart of why we use malloc.