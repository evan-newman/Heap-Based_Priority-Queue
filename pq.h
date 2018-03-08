/*
 * This file contains the definition of the interface for a priority queue.
 * You will implement the structures and functiond declared here in pq.c.
 */

#ifndef __PQ_H
#define __PQ_H
#include "dynarray.h"

struct pq;

void node_swap(struct dynarray*, int, int);

struct pq* pq_create();
void pq_free(struct pq* pq);
int pq_isempty(struct pq* pq);
void pq_insert(struct pq* pq, void* value, int priority);
void* pq_first(struct pq* pq);
int pq_first_priority(struct pq* pq);
void* pq_remove_first(struct pq* pq);

#endif
