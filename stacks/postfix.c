#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stack
{
   char *arr; // The string of operators and operands
   int size;  // size of the stack
   int top;   // index of the top element
};

int precedence(char operator)
{
   switch (operator)
   {
   case '+':
   case '-':
      return 1;
   case '*':
   case '/':
      return 2;
   case '^':
      return 3;
   default:
      return -1; // Invalid operator
   }
}

// Function to check whether stack is empty
int stackIsEmpty(struct stack *st)
{
   return st->top == -1;
}

// Function to check whether stack is full
int stackIsFull(struct stack *st)
{
   return st->top == st->size - 1;
}

void push(struct stack *st, char data)
{
   if (stackIsFull(st))
   {
      printf("Stack overflow\n");
      return;
   }
   st->arr[++(st->top)] = data;
}

char pop(struct stack *st)
{
   if (stackIsEmpty(st))
   {
      printf("Stack underflow\n");
      return '\0';
   }
   return st->arr[(st->top)--];
}

void printStack(struct stack *st)
{
   int temp = st->top;
   while (temp != -1)
   {
      printf("%c ", st->arr[temp--]);
   }
   printf("\n");
}

int main()
{
   struct stack *st = (struct stack *)malloc(sizeof(struct stack));

   char infix[] = "a+b-c+d-e-f+g*i";
   printf("Given infix :  a+b-c+d-e-f+g*i \n");
   printf("Corresponding postfix : \n");

   st->size = strlen(infix);
   st->top = -1;
   st->arr = (char *)malloc(st->size * sizeof(char));

   int i = 0;

   while (infix[i] != '\0')
   {
      if (infix[i] >= 'a' && infix[i] <= 'z') // if it is an operand
      {
         printf("%c", infix[i]);
      }
      else if (infix[i] == '(') // case of '('
      {
         push(st, '(');
      }
      else if (infix[i] == ')') // case of ')'
      {
         while (!stackIsEmpty(st) && st->arr[st->top] != '(')
         {
            printf("%c", pop(st));
         }
         pop(st); // pop the '('
      }
      else // case of an operator
      {
         while (!stackIsEmpty(st) && precedence(st->arr[st->top]) >= precedence(infix[i]))
         {
            printf("%c", pop(st));
         }
         push(st, infix[i]);
      }
      printStack(st);
      i++;
   }

   while (!stackIsEmpty(st)) // pop all remaining operators
   {
      printf("%c", pop(st));
   }

   free(st->arr);
   free(st);
   return 0;
}
