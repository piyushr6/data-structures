#include <stdio.h>
#include <stdlib.h>

struct node
{
   int coeff;
   int power;
   struct node *next;
};

// Function to traverse and display the nodes of linked list
void displayList(struct node *ptr)
{
   printf("\n");
   while (ptr->next != NULL)
   {
      printf("%dx%d+", ptr->coeff, ptr->power);
      ptr = ptr->next;
   }
   printf("%dx%d", ptr->coeff, ptr->power);
}

// creating a new node
struct node *createNode(int coeff, int power)
{
   struct node *ptr = (struct node *)malloc((sizeof(struct node)));

   ptr->coeff = coeff;
   ptr->power = power;
   ptr->next = NULL;

   return ptr;
}

// Fuction to add a node to the linked list
void insertAtEnd(struct node *head, int coeff, int power)
{
   struct node *ptr = (struct node *)malloc((sizeof(struct node)));
   ptr->coeff = coeff;
   ptr->power = power;
   struct node *p = head;

   while (p->next != NULL)
   {
      p = p->next;
   }
   p->next = ptr;
   ptr->next = NULL;
}

void add(struct node *p1, struct node *p2)
{
   struct node *result = NULL;

   while (p1 != NULL && p2 != NULL)
   {
      if (p1->power == p2->power)
      {
         if (result == NULL)
            result = createNode(p1->coeff + p2->coeff, p1->power);
         else
            insertAtEnd(result, p1->coeff + p2->coeff, p1->power);

         p1 = p1->next;
         p2 = p2->next;
      }
      else if (p1->power > p2->power)
      {
         if (result == NULL)
            result = createNode(p1->coeff, p1->power);
         else
            insertAtEnd(result, p1->coeff, p1->power);

         p1 = p1->next;
      }
      else
      {
         if (result == NULL)
            result = createNode(p2->coeff, p2->power);
         else
            insertAtEnd(result, p2->coeff, p2->power);

         p2 = p2->next;
      }
   }

   while (p1 != NULL)
   {
      if (result == NULL)
         result = createNode(p1->coeff, p1->power);
      else
         insertAtEnd(result, p1->coeff, p1->power);

      p1 = p1->next;
   }

   while (p2 != NULL)
   {
      if (result == NULL)
         result = createNode(p2->coeff, p2->power);
      else
         insertAtEnd(result, p2->coeff, p2->power);

      p2 = p2->next;
   }

   displayList(result);
}

int main()
{
   struct node *p1 = (struct node *)malloc(sizeof(struct node));
   struct node *p2 = (struct node *)malloc(sizeof(struct node));

   p1 = createNode(3, 4);
   insertAtEnd(p1, 12, 2);
   insertAtEnd(p1, 10, 0);
   printf("First Expression: ");
   displayList(p1);

   p2 = createNode(5, 3);
   insertAtEnd(p2, 4, 2);
   insertAtEnd(p2, 3, 0);
   printf("\n\nSecond Expression: ");
   displayList(p2);

   // function to perform addition of the 2 expressions

   printf("\n\nResultant after addition of the 2 expressions : ");
   add(p1, p2);
}