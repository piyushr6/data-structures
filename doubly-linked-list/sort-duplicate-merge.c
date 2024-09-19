#include <stdio.h>
#include <stdlib.h>

// Define Node structure
struct Node
{
   int data;
   struct Node *next;
   struct Node *prev;
};

// Function to create a new node
struct Node *createNode(int data)
{
   struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
   newNode->data = data;
   newNode->next = NULL;
   newNode->prev = NULL;
   return newNode;
}

// Function to insert a node in a sorted order in the doubly linked list
struct Node *sortedInsert(struct Node *head, int data)
{
   struct Node *newNode = createNode(data);
   struct Node *current;

   // Case when the list is empty
   if (head == NULL)
   {
      head = newNode;
   }

   // Case when the new node should be inserted before the head
   else if (head->data >= newNode->data)
   {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
   }

   // Insertion somewhere in the middle or at the end
   else
   {
      current = head;
      while (current->next != NULL && current->next->data < newNode->data)
      {
         current = current->next;
      }
      newNode->next = current->next;
      if (current->next != NULL)
      {
         newNode->next->prev = newNode;
      }
      current->next = newNode;
      newNode->prev = current;
   }
   return head;
}

// Function to remove duplicates from the sorted doubly linked list
void removeDuplicates(struct Node *head)
{
   if (head == NULL)
      return;

   struct Node *current = head;

   while (current->next != NULL)
   {
      if (current->data == current->next->data)
      {
         struct Node *duplicate = current->next;
         current->next = duplicate->next;
         if (duplicate->next != NULL)
         {
            duplicate->next->prev = current;
         }
      }
      else
      {
         current = current->next;
      }
   }
}

// Function to merge two sorted doubly linked lists
struct Node *mergeLists(struct Node *list1, struct Node *list2)
{
   struct Node *mergedList = NULL;

   // Insert nodes from both lists into the new merged list
   while (list1 != NULL)
   {
      mergedList = sortedInsert(mergedList, list1->data);
      list1 = list1->next;
   }
   while (list2 != NULL)
   {
      mergedList = sortedInsert(mergedList, list2->data);
      list2 = list2->next;
   }
   return mergedList;
}

// Function to print the doubly linked list
void displayList(struct Node *head)
{
   while (head != NULL)
   {
      printf("%d ", head->data);
      head = head->next;
   }
   printf("\n");
}

// Main function to demonstrate the operations
int main()
{
   struct Node *list1 = NULL;
   struct Node *list2 = NULL;
   int data;

   // Input for first list
   printf("First list : \n");
   list1 = sortedInsert(list1, 4);
   displayList(list1);
   list1 = sortedInsert(list1, 6);
   displayList(list1);
   list1 = sortedInsert(list1, 1);
   displayList(list1);
   list1 = sortedInsert(list1, 8);
   displayList(list1);
   list1 = sortedInsert(list1, 1);
   displayList(list1);
   list1 = sortedInsert(list1, 6);
   displayList(list1);
   list1 = sortedInsert(list1, 2);
   displayList(list1);
   list1 = sortedInsert(list1, 3);
   displayList(list1);
   list1 = sortedInsert(list1, 9);
   displayList(list1);

   // Input for second list
   printf("Second list : \n");
   list2 = sortedInsert(list2, 7);
   displayList(list2);
   list2 = sortedInsert(list2, 2);
   displayList(list2);
   list2 = sortedInsert(list2, 4);
   displayList(list2);
   list2 = sortedInsert(list2, 3);
   displayList(list2);
   list2 = sortedInsert(list2, 8);
   displayList(list2);
   list2 = sortedInsert(list2, 1);
   displayList(list2);

   struct Node *mergedList = mergeLists(list1, list2);
   printf("Merged sorted list:\n");
   displayList(mergedList);

   printf("Merged sorted list after removing duplicates:\n");
   removeDuplicates(mergedList);
   displayList(mergedList);

   return 0;
}