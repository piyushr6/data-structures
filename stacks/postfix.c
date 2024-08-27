#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stack
{
   char *arr;
   int size;
   int top;
};

int precedence(char operator)
{
   switch (operator)
   {
   case '+':
      return 1;
   case '-':
      return 1;
   case '*':
      return 2;
   case '/':
      return 2;
   default:
      return -1; // Invalid operator
   }
}

int stackIsFull(struct stack *st)
{
   if (st->top == st->size - 1)
      return 1;
   else
      return 0;
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
   if (!stackIsFull(st))
   {
      printf("Stack underflow\n");
      return '\0';
   }
   return st->arr[(st->top)--];
}

int main()
{
   // st is stack variable
   struct stack *st = (struct stack *)malloc(sizeof(struct stack));

   char infix[] = "a/b*(c+(d-e))";

   st->size = strlen(infix);
   st->top = -1;
   st->arr = (char *)malloc(st->size * sizeof(char)); // malloc default is void so typecasted to char

   int i = 0;

   while (infix[i] != '\0')
   {
      if (infix[i] >= 97 && infix[i] <= 122)
      {
         printf("%c", infix[i]);
      }
      else
      {
         if (infix[i] == '(')
            push(st, '(');

         else if (infix[i] == ')')
         {
            while (st->arr[st->top] != '(')
            {
               printf("%c", pop(st));
            }
            pop(st); // pop the '('
         }
         else
         {
            while (st->top != -1 && precedence(st->arr[st->top]) >= precedence(infix[i]))
            {
               printf("%c", pop(st));
            }
            push(st, infix[i]);
         }
      }
      i++;
   }

   while (st->top != -1)
   {
      printf("%c", pop(st));
   }

   free(st->arr);
   free(st);
   return 0;
}