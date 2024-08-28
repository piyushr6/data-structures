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

// Function to push contents in stack
void push(struct stack *st, char data)
{
   if (stackIsFull(st))
   {
      printf("Stack overflow\n");
      return;
   }
   st->arr[++(st->top)] = data;
}

// Function to pop contents from stack
char pop(struct stack *st)
{
   if (stackIsEmpty(st))
   {
      printf("Stack underflow\n");
      return '\0';
   }
   return st->arr[(st->top)--];
}

void reverseString(char *str)
{
   int n = strlen(str);
   for (int i = 0; i < n / 2; i++)
   {
      char temp = str[i];
      str[i] = str[n - i - 1];
      str[n - i - 1] = temp;
   }
}

void reverseExpression(char *expr)
{
   reverseString(expr);
   for (int i = 0; i < strlen(expr); i++)
   {
      if (expr[i] == '(')
      {
         expr[i] = ')';
      }
      else if (expr[i] == ')')
      {
         expr[i] = '(';
      }
   }
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
   char infix[] = "a+(b-c)*d+e-(f*(g/h))";
   printf("Infix expression: %s\n", infix);

   struct stack *st = (struct stack *)malloc(sizeof(struct stack));
   st->size = strlen(infix);
   st->top = -1;
   st->arr = (char *)malloc(st->size * sizeof(char));

   char prefix[st->size + 1]; // To store the prefix expression

   reverseExpression(infix);

   int k = 0, i = 0;

   while (infix[i] != '\0')
   {
      if (infix[i] >= 'a' && infix[i] <= 'z') // case of operand
      {
         prefix[k++] = infix[i];
      }
      else if (infix[i] == '(') // case of (
      {
         push(st, '(');
      }
      else if (infix[i] == ')') // case of )
      {
         while (!stackIsEmpty(st) && st->arr[st->top] != '(')
         {
            prefix[k++] = pop(st);
         }
         pop(st); // pop (
      }
      else
      {
         while (!stackIsEmpty(st) && precedence(st->arr[st->top]) > precedence(infix[i]))
         {
            prefix[k++] = pop(st);
         }
         push(st, infix[i]);
      }

      printStack(st); // Print stack after processing each character
      i++;
   }

   while (!stackIsEmpty(st))
   {
      prefix[k++] = pop(st);
      printStack(st);
   } // popping all remaining operators.

   prefix[k] = '\0';

   reverseString(prefix);

   printf("Prefix expression: %s\n", prefix);

   free(st->arr);
   free(st);

   return 0;
}