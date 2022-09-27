#include "infix.h"

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** infix, int size){
  char** postfix = malloc(sizeof(char*) * size);
  int postfix_index = 0;
  struct double_stack *stack;
  stack = double_stack_new(size);
  for(int i = 0; i < size; i++){
      if(*infix[i] == '('){
        double_stack_push(stack, i);
      }
      else if(is_operator(infix[i])){
        while(tos_is_greater_op(stack, infix[i], infix) && (stack -> top) > 0){
          int op = double_stack_pop(stack);
          postfix[postfix_index] = infix[op];
          postfix_index++;
        }
        double_stack_push(stack, i);
      }
      else if(*infix[i] == ')'){
        while(*infix[(int)stack -> items[stack -> top - 1]] != '('){
          int op = double_stack_pop(stack);
          postfix[postfix_index] = infix[op];
          postfix_index++;
        }
        int op = double_stack_pop(stack);
        assert(*infix[op] == '(');
      }
      else{
          postfix[postfix_index] = infix[i];
          postfix_index++;
      }
  }
  while((stack -> top) > 0){
    int op = double_stack_pop(stack);
    postfix[postfix_index] = infix[op];
    postfix_index++;
  }
  double value = evaluate_postfix_expression(postfix, postfix_index);
  return value;
}

int precedence(char * args){
  int precedence = 0;
  switch(*args){
    case '+':
      precedence = 1;
      break;
    case '-':
      precedence = 1;
      break;
    case 'X':
      precedence = 2;
      break;
    case 'x':
      precedence = 2;
      break;
    case '/':
      precedence = 2;
      break;
    case '^':
      precedence = 3;
      break;
  }
  return precedence;
}

bool tos_is_greater_op(struct double_stack * stack, char * op, char ** infix){
  if(precedence(infix[(int)stack -> items[stack -> top - 1]]) >= precedence(op)){
      return true;
  }
  return false;
}