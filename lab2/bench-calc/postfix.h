#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stack.h"
#include <stdbool.h>


double evaluate_postfix_expression(char ** expr, int nterms);

bool is_operator(char* token);

#endif
