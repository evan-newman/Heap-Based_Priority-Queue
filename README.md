# CS 261 Heap-Based Priority Queue

Program impliments a complete heap-based priority queue. File pq.c is given and my program was limited to just that file. Had to define `struct pq` and implement the following function:

  * `pq_create()` - allocates and initializes a heap-based priority queue
  * `pq_free()` - frees all memory allocated to a priority queue
  * `pq_isempty()` - should tell the user whether a priority queue is empty
  * `pq_insert()` - should insert an element with a specified priority value into a priority queue
  * `pq_first()` - should return the value of the first element in a priority queue
  * `pq_first_priority()` - should return the *priority value* associated with the first element in a priority queue
  * `pq_remove_first()` - should remove the first element from a priority queue and return its value

# Notes about my criteria:
  * In the priority queue, *lower* priority values should correspond to elements with *higher* priority.  In other words, the first element in the priority queue should be the one with the *lowest* priority value among all elements in the collection.  For example, the priority queue should return an element with priority value 0 before it returns one with priority value 10.

  * Your `pq_insert()` and `pq_remove_first()` functions should both be *O(log n)*, and your `pq_first()` and `pq_first_priority()` functions should both be *O(1)*.

  * Your priority queue should not have any memory leaks.

# Testing
The file `test` gives an example to work with in my program. I did not code this part, Rob Hess provided this.

# Works Cited 
Credit to Rob Hess for most of the README.md provided and testing function
