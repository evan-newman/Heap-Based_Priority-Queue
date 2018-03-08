/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Evan Newman
 * Email: newmanev@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {

	struct dynarray* dy_val;
	struct dynarray* dy_prio;

};

void node_swap(struct dynarray* da, int idx1, int idx2) {
	
	assert(da);

	void* temp1 = dynarray_get(da, idx1);
	void* temp2 = dynarray_get(da, idx2);

	dynarray_set(da, idx1, temp2);
	dynarray_set(da, idx2, temp1);
	
}

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {

	struct pq* prio_que = malloc(sizeof(struct pq));
	assert(prio_que);

	prio_que->dy_val = dynarray_create();
	prio_que->dy_prio = dynarray_create();
	assert(prio_que->dy_val);
	assert(prio_que->dy_prio);

	return prio_que;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {

	dynarray_free(pq->dy_val);
	dynarray_free(pq->dy_prio);
	free(pq);

}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {

	int size = dynarray_size(pq->dy_prio);
	if(size == 0)
		return 1;
	else
		return 0;

}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {

	assert(pq);
	assert(value);

	int curr = dynarray_size(pq->dy_prio);

	/*
	 * Allocate memory on heap for priority integer and
	 * insert new values at first open spot (end of array)
	 */
	int* x = malloc(sizeof(int));
	*x = priority;

	dynarray_insert(pq->dy_prio, curr, x);
	dynarray_insert(pq->dy_val, curr, value);
	
	/*
	 * Loop until impossible for inserted value to have a parent
	 */
	while((curr - 1) / 2 >= 0){
		int parent = *((int*)(dynarray_get(pq->dy_prio, (curr - 1) / 2)));

		/*
		 * swap idx of inserted value and it's parent value in array if smaller, 
		 * else (if bigger or equal) value is where it needs to be and return
		 */
		if(priority < parent) {
			node_swap(pq->dy_val, curr, (curr - 1) / 2);
			node_swap(pq->dy_prio, curr, (curr - 1) / 2);

			curr = ((curr - 1) / 2);
		}
		else {
			return;
		}
	}

}

/* * This function should return the value of the first item in a priority * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	assert(pq);
	return dynarray_get(pq->dy_val, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	assert(pq);
	return *((int*)dynarray_get(pq->dy_prio, 0));
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {

	assert(pq);
	int size = dynarray_size(pq->dy_prio) - 1;

	void* last_val = dynarray_get(pq->dy_val, 0);

	node_swap(pq->dy_prio, 0, size); 
	node_swap(pq->dy_val, 0, size);

	int last_in = *((int*)dynarray_get(pq->dy_prio, 0));

	free(dynarray_get(pq->dy_prio, size));
	dynarray_remove(pq->dy_prio, size);
	dynarray_remove(pq->dy_val, size);

	size = size - 1;
	int curr = 0;
	
	/*
	 * Loop until impossible for last in value to have a child
	 * (not right child because will always have at least one left child).
	 */
	while(2 * curr + 1 <= size){

		int left = *((int*)(dynarray_get(pq->dy_prio, 2 * curr + 1)));

		/*
		 * If right child isn't out of scope compare
		 * left and right child priority values
		 * if last in priority value is larger than smallest child
		 * swap idx in array
		 * else return the last value inserted because
		 * the last in value is where it needs to be in array
		 */
		if(2 * curr + 2 <= size) {
			
			int right = *((int*)(dynarray_get(pq->dy_prio, 2 * curr + 2)));

			if(left <= right && last_in > left) {
				node_swap(pq->dy_val, curr, 2 * curr + 1);
				node_swap(pq->dy_prio, curr, 2 * curr + 1);
				curr = 2 * curr + 1;
			}
			else if(last_in > right){
				node_swap(pq->dy_val, curr, 2 * curr + 2);
				node_swap(pq->dy_prio, curr, 2 * curr + 2);
				curr = 2 * curr + 2;
			}
			else {
				return last_val;
			}
		}
		else if(last_in > left) {
			node_swap(pq->dy_val, curr, 2 * curr + 1);
			node_swap(pq->dy_prio, curr, 2 * curr + 1);
			curr = 2 * curr + 1;
		}
		else {
			return last_val;
		}

	}
	return last_val;

}
