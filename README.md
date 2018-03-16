# kernel_data_structures
Linux kernel datastructures implementation  

Problem statement 
Write a kernel module to perform the following operations.

For now, I have implemented them as separate kernel modules.

Linked lists : (A) constructs a linked list containing dstruct_size random integers; (B) prints on the kernel
log the content of the list through the use of list navigation functions; and (C) destructs the list and free its
content. It is asked to write two versions of the linked list exercise: one executing (A), (B) and (C) in the same
function, the second calling (A), (B) and (C) each in a different function.

Queues : creates a queue and enqueue dstruct_size random integers, then dequeue these elements, print them,
then free them if needed.


Maps : creates a map and insert in it dstruct_size random integers. The id value associated with each element
should be constrained into a specific range defined by a low and high bound, clearly indicated in the code.
It is asked to print the content of the map and the id associated with each element before freeing the data
structure.


Red-black trees : creates a rbtree with nodes being random integers, indexed by the integers values. It is asked
to insert into the tree dstruct_size random integers (while being careful not to insert duplicates). Next,
print the tree on the kernel log. Then, a loop should iterate over an integer range of your choice (according
to the tree content) and for each of these indicate (by printing to the kernel log) if it is present in the tree, and
remove the element. Next, print the tree again. Finally all remaining elements should be removed from the
tree and the data structure freed if needed. Note that with the red-black tree implementation of Linux, it is
needed to implement the search and insert functions.

