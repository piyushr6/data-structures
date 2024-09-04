#include <stdio.h>
#include <stdlib.h>

struct Queue
{
   int size;
   int front; // front pointer
   int rear;  // rear pointer
   int *arr;  // array to store elements of queue
};

// Function to initialize the queue with a given size
void initialize(struct Queue *q, int s)
{
   q->size = s;
   q->front = -1;                                 // initialize front to -1
   q->rear = 0;                                   // initialize rear to 0
   q->arr = (int *)malloc(q->size * sizeof(int)); // allocate memory for the queue array
}

// Function to add an element to the queue
void enqueue(struct Queue *q, int x)
{
   if (q->rear == q->size)
   {
      printf("The queue is full\n");
   }
   else
   {
      q->arr[q->rear] = x; // Add element to the rear of the queue
      q->rear++;           // Increment the rear index
   }
}

// Function to remove an element from the queue
void dequeue(struct Queue *q)
{
   if (q->rear - 1 == q->front)
   {
      printf("The queue is empty\n");
   }
   else
   {
      q->front++;
   }
}

// Function to get the front element of the queue
int peek(struct Queue *q)
{
   if (q->front == q->rear - 1)
   {
      return -1;
   }
   else
   {
      return q->arr[q->front + 1];
   }
}

// Function to display the elements of the queue
void display(struct Queue *q)
{
   if (q->front == q->rear - 1)
   {
      printf("Queue is empty\n");
      return;
   }

   // Print elements from rear to front
   for (int i = q->rear - 1; i >= q->front + 1; i--)
   {
      printf("%d ", q->arr[i]);
   }

   printf("\n");
}

int main()
{
   int input[] = {5, 8, 1, 7, 4, 2, 9, 6, 3}; // Input array

   // Initialize the first queue (q1) with the size of the input array
   struct Queue *q1 = (struct Queue *)malloc(sizeof(struct Queue));
   int s = 9;
   initialize(q1, s);

   // Enqueue elements into q1 in reverse order of the input array
   for (int i = s - 1; i >= 0; i--)
   {
      enqueue(q1, input[i]);
   }

   printf("Input track is:\n");
   display(q1); // Display the contents of q1

   struct Queue *h1 = (struct Queue *)malloc(sizeof(struct Queue));
   initialize(h1, s);
   struct Queue *h2 = (struct Queue *)malloc(sizeof(struct Queue));
   initialize(h2, s);
   struct Queue *q2 = (struct Queue *)malloc(sizeof(struct Queue));
   initialize(q2, s);

   int req = 1;

   while (req <= s)
   {
      int x = peek(q1);
      int y = peek(h1);
      int z = peek(h2);

      if (x == req) // If the front of q1 is the required element
      {
         dequeue(q1);
         enqueue(q2, x);
         req++;
      }
      else if (y == req)
      {
         dequeue(h1);
         enqueue(q2, y);
         req++;
      }
      else if (z == req)
      {
         dequeue(h2);
         enqueue(q2, z);
         req++;
      }
      else // If none of the queues have the required element at the front
      {

         if (h1->rear == h1->front + 1 || (h1->rear != h1->front + 1 && x > h1->arr[h1->rear - 1]))
         {
            enqueue(h1, x);
            dequeue(q1);
         }
         else
         {
            enqueue(h2, x);
            dequeue(q1);
         }
      }

      printf("h1 : ");
      display(h1);
      printf("h2 : ");
      display(h2);
      printf("output queue : ");
      display(q2);
   }

   printf("\n");
   printf("Final output track:\n");
   display(q2);
   return 0;
}