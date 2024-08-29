#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct queue
{
   int arr[9]; // Array to hold queue elements
   int front;  // Index of the front element
   int rear;   // Index of the rear element
   int size;   // Maximum size of the queue
};

// Function to check if the queue is full
int isQueueFull(struct queue *q)
{
   if (q->rear == q->size - 1)
      return 1;
   else
      return 0;
}

// Function to check if the queue is empty
int isQueueEmpty(struct queue *q)
{
   if (q->front == -1 || q->front > q->rear)
      return 1;
   else
      return 0;
}

// ENQUEUE
void enqueue(struct queue *q, int n)
{
   if (isQueueFull(q))
   {
      printf("Queue is full \n");
      return;
   }

   if (q->front == -1)
      q->front++;

   q->rear++;
   q->arr[q->rear] = n;
}

// DEQUEUE
int dequeue(struct queue *q)
{
   if (isQueueEmpty(q))
   {
      printf("Queue is empty \n");
      return -1;
   }
   if (q->front == q->rear)
   {
      q->front = -1;
      q->rear = -1;
   }

   printf("Queue is empty \n");
   return -1;

   int item = q->arr[q->front];
   q->front++;
   return item;
}

// Function to display the elements in the queue
void displayQueue(struct queue *q)
{
   if (isQueueEmpty(q))
   {
      printf("Queue is empty!\n");
      return;
   }

   printf("Queue: ");
   for (int i = q->front; i <= q->rear; i++)
   {
      printf("\nelement=%d front=%d back = %d", q->arr[i], q->front, q->rear);
      // printf("\n");
   }

   printf("\n");
}

// 5, 8, 1, 7, 4, 2, 9, 6, 3

int main()
{
   struct queue *h1 = (struct queue *)malloc(sizeof(struct queue));
   struct queue *h2 = (struct queue *)malloc(sizeof(struct queue));
   struct queue *input_track = (struct queue *)malloc(sizeof(struct queue));
   struct queue *output_track = (struct queue *)malloc(sizeof(struct queue));

   int inp[9] = {5, 8, 1, 7, 4, 2, 9, 6, 3};

   input_track->front = -1;
   input_track->rear = -1;
   input_track->size = 9;

   for (int i = 0; i < 9; i++)
   {
      enqueue(input_track, inp[i]);
      displayQueue(input_track);
   } // now rear and front both point to 0

   for (int i = 0; i < 9; i++)
   {
      // enqueue(input_track, inp[i]);
      dequeue(input_track);
      displayQueue(input_track);
   } // now rear and front both point to 0

   // displayQueue(input_track);

   for (int i = 0; i < 9; i++)
   {
      // if (input_track->arr[i] == 1)
      // {
      //    enqueue(output_track, input_track->arr[i]);
      // }
      if (input_track->arr[i] < input_track->arr[i + 1])
      {
         enqueue(h1, dequeue(input_track));
         displayQueue(h1);
      }
      else
      {
         enqueue(h2, dequeue(input_track));
         displayQueue(h2);
      }
   }

   displayQueue(h1);
   displayQueue(h2);
}