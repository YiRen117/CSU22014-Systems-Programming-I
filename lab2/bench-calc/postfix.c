#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** expr, int size) {
    struct double_stack *stack;
    stack = double_stack_new(size);
    double value;
    for(int i=0; i < size; i++){
        if(is_operator(expr[i])){
          double op2 = double_stack_pop(stack);
          double op1 = double_stack_pop(stack);
          if((*expr[i]) == '+'){
            value = op1 + op2;
          }
          else if((*expr[i]) == '-'){
            value = op1 - op2;
          }
          else if((*expr[i]) == 'X' || (*expr[i]) == 'x'){
            value = op1 * op2;
          }
          else if((*expr[i]) == '/'){
            value = op1 / op2;
          }
          else value = pow(op1,op2);
          double_stack_push(stack, value);
        }
        else double_stack_push(stack,atof(expr[i]));
    }
    return value;
}

bool is_operator(char* token) {
    if ((*token == '+' || *token == '-' || *token == 'X' || *token == 'x' || *token == '/' || *token == '^') && *(token+1) == '\0') {
      return true;
    }
    return false;
}