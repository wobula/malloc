# Malloc

#### a dynamic memory allocation system

## Summary

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

## Explanation

Why do we use Malloc?  Two reasons: convenience and speed.

### Convenience

The system call for requesting memory, mmap, has the following function prototype:

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

A quick comparison of mmap's prototype with Malloc's, and we can see that malloc is much simpler.  Where mmap takes 6 arguments, malloc takes one.  But beyond this surface level ease in terms of supplying arguments, Malloc is also easier, not just on the programmer, but also *on the computer*.

### Speed

Malloc is easier on the computer because it doesn't task the kernel nearly as much as mmap.  The reason for this is malloc calls mmap once in order to allocate a giant *slab* of memory, which it then parcels out to the user during each subsequent malloc call.  If malloc runs out of memory -- then it calls mmap and asks for more memory, but not until then.  By asking for a big slab and giving the user a small amount of that slab, we can improve performance through a reduction in kernel taskings.  This is the heart of why we use malloc.

## Data Structures

#### Linked Lists Galore

This specific implimentation of malloc uses a multidimensional, embedded linked list data structure.  What this means is that when we first call malloc, we ask the kernel for a large slab of memory.  The struct that contains all the meta-data about this slab is, itself, the first node of a linked list.  Each successive call to mmap for another slab adds another node to this original, head node.  The structure of this system is a simple singularly linked list as shown below:

[head_node]--[next_slab]--[yet_a_third_slab]--NULL

#### Now let's add a little bit of complexity

The memory for each of these slabs is divided into two subsequent sections, TINY and MEDIUM.  Both of these sections are, themselves, a linked list.  The structs for these two linked lists consist of two parts per node: a meta-data struct and the void *ptr to the users memory allocation.  See the image below:

[head_node]--[next_slab]--NULL
 ^  ^ ^       ^  ^  ^
 |  | |       |  |  |---Large section is present in data structure but only used on head node
 |  | |       | MEDIUM
 |  | |       TNY
 |  | |
 |  | |---Large [[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--continues infinity
 | MEDIUM [[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--continues to 100 nodes and then NULL
 TNY [[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--[[meta-ptr](user void*ptr)]--continues to 100 nodes and then NULL

 In other words, we have a head spinal column linked list with three other rib-cage linked lists coming off each node of this list.

 #### So what happens when we call malloc?

 When a user calls malloc the first time, they first allocate a slab of memory -- a spinal column node -- and in the subsequent functions, they also setup the scaffolding for the rib-cage linked lists that radiate off the spine. Once these ribs are setup, malloc returns the first void pointer in the tny or med section, depending on the size the user requested.  Each subsequent call to malloc involves traversing these TNY and MED linked lists and returning void *ptrs to the user until all 100 nodes are used up.  The next call to malloc will add a second spinal column node to the head node.  Malloc then traverses past the head node, to the next, and it begins returning void *ptrs from the tiny and medium sections of this data structure. Realloc and calloc both operate in a similar manner.

 One other side note: you may have noticed that there is a large section.  This large section has it's own linked list, but for my implimentation, all large allocations are located off the head spinal node.

 #### What about free?

When we provide a void *ptr to free, free begins looking for our ptr.  It starts at the head of each spine node and checks to see if our pointer is within the range of the pointers for this section (if not, it goes to the next spinal node).  Once free finds the correct spinal node, it begins checking the lower level, ribcage linked lists with similar pointer range comparisons.  If it finds that our pointer is in the tny section, it starts at the first node of the tny section and does a pointer comparison with each void*ptr until it finds our pointer.

One other thing free does is if we free all the allocations -- both tny and med -- free will also free the spinal node for this section.