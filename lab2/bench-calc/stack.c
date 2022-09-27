#include "stack.h"

struct double_stack * double_stack_new(int max_size) {
    struct double_stack *result;
    result = malloc(sizeof(struct double_stack));
    result -> top = 0;
    result -> max_size = max_size;
    result -> items = malloc(sizeof(double) * max_size);
    return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
    assert(this -> top < this -> max_size);
    this -> items[this -> top] = value;
    this -> top++;
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
    assert(this -> top > 0);
    this -> top--;
    return this -> items[this -> top];
}