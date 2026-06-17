
#include <stdbool.h>

// LIST-STACK
#define STACK_SUCCESS 0;
#define STACK_ERROR_NULL -1;
#define STACK_ERROR_ALLOC -2;
#define STACK_ERROR_EMPTY -3;
#define STACK_ERROR_FULL -4;


typedef struct _stack* stack;

stack create_stack(int _capacity);

void destroy_stack(stack* _s);

int stack_push(stack _s, void* _value);

int stack_pop(stack _s, void** _value_out);

int stack_top(stack _s, void** _value_out);

bool stack_is_empty(stack _s);

bool stack_is_full(stack _s);
