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
   while (ptr != NULL)
   {
      printf("Coefficient : %d", ptr->coeff);
      printf("\nPower : %d", ptr->power);
      printf("\n");
      ptr = ptr->next;
   }
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
void insertAtEnd(struct node *p1, int coeff, int power)
{
   struct node *ptr = (struct node *)malloc((sizeof(struct node)));
   ptr->coeff = coeff;
   ptr->power = power;
   struct node *p = p1;

   while (p->next != NULL)
   {
      p = p->next;
   }
   p->next = ptr;
   ptr->next = NULL;
}

int main()
{
   struct node *p1 = (struct node *)malloc(sizeof(struct node));
   struct node *p2 = (struct node *)malloc(sizeof(struct node));

   p1 = createNode(3, 4);
   displayList(p1);
   insertAtEnd(p1, 12, 2);
   displayList(p1);
   insertAtEnd(p1, 10, 0);
   displayList(p1);

   p2 = createNode(5, 3);
   displayList(p2);
   insertAtEnd(p2, 4, 2);
   displayList(p2);
   insertAtEnd(p2, 3, 0);
   displayList(p2);

   struct node *result = (struct node *)malloc(sizeof(struct node));
}