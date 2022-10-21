#ifndef PQUEUE_H
#define PQUEUE_H 1

struct PQUEUE;
typedef struct PQUEUE PQueue;

/* constructor */
extern PQueue* pq_new(void);
/* add data with priority, less number of priority goes first */
extern void pq_push(PQueue* pq, void* data, int priority);
/* add copy of data with priority */
extern void pq_push_copy(PQueue* pq, const void* data, int priority, void* (*data_copy_func)(const void*));
/* return pointer to first elements data */
extern void* pq_front_data(PQueue* pq);
/* return first elements priority */
extern int pq_front_priority(PQueue* pq);
/* remove first element from queue */
extern void pq_shift(PQueue* pq);
/* remove first element destructing data */
extern void pq_shift_data(PQueue* pq, void (*data_destructor_func)(void*));
/* tests if queue is empty */
extern int pq_is_empty(PQueue* pq);
/* return size of queue */
extern unsigned pq_size(PQueue* pq);
/* destructor */
extern void pq_free(PQueue* pq);
/* destructor with data destructor function */
extern void pq_free_data(PQueue* pq, void (*data_destructor_func)(void*));

#endif /* PQUEUE_H */