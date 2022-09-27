#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "stack.h"
#include "postfix.h"


double evaluate_infix_expression(char ** infix, int size);

int precedence(char * args);

bool tos_is_greater_op(struct double_stack * stack, char * op, char ** infix);

#endif
