
#include <stdbool.h>

#define QUEUE_SUCCESS 0;
#define QUEUE_ERROR_NULL -1;
#define QUEUE_ERROR_ALLOC -2;
#define QUEUE_ERROR_EMPTY -3;
#define QUEUE_ERROR_FULL -4;

// LIST-QUEUE
typedef struct _queue* queue;

queue create_queue(int _capacity);

void queue_destroy(queue* _q);

int enqueue(queue _q, void* _value);

int dequeue(queue _q, void** _value_out);

int queue_peek(queue _q, void** _value_out);

bool queue_is_empty(queue _q);

bool queue_is_full(queue _q);

