#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100 // Maximum size of the heap

struct Heap
{
   int arr[MAX_SIZE];
   int size;
};

// Function to initialize the heap structure
void initializeHeap(struct Heap *heap)
{
   heap->size = 0;
}

// Function to display the current state of the heap
void printHeap(struct Heap *heap)
{
   for (int i = 0; i < heap->size; i++)
   {
      printf("%d ", heap->arr[i]);
   }
   printf("\n");
}

// Insert an element into the heap
void insert(struct Heap *heap, int value)
{
   if (heap->size == MAX_SIZE)
   {
      printf("Heap overflow\n");
      return;
   }

   heap->arr[heap->size] = value; // Place the new element at the end
   int i = heap->size;
   heap->size++;

   printf("Inserting %d: ", value);
   printHeap(heap);

   // Move up to maintain heap property
   while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i])
   {
      int temp = heap->arr[i];
      heap->arr[i] = heap->arr[(i - 1) / 2];
      heap->arr[(i - 1) / 2] = temp;
      i = (i - 1) / 2;

      printf("Heap after swapping: ");
      printHeap(heap);
   }
}

// Increase the key value of an element at a given index
void increaseKey(struct Heap *heap, int index, int newValue)
{
   if (index >= heap->size || newValue < heap->arr[index])
   {
      printf("Invalid increase operation\n");
      return;
   }

   heap->arr[index] = newValue;
   printf("Increasing key at index %d to %d: ", index, newValue);
   printHeap(heap);

   while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index])
   {
      int temp = heap->arr[index];
      heap->arr[index] = heap->arr[(index - 1) / 2];
      heap->arr[(index - 1) / 2] = temp;
      index = (index - 1) / 2;

      printf("Heap after swapping: ");
      printHeap(heap);
   }
}

// Decrease the key value of an element at a given index
void decreaseKey(struct Heap *heap, int index, int newValue)
{
   if (index >= heap->size || newValue > heap->arr[index])
   {
      printf("Invalid decrease operation\n");
      return;
   }

   heap->arr[index] = newValue;
   printf("Decreasing key at index %d to %d: ", index, newValue);
   printHeap(heap);

   int i = index;
   while (2 * i + 1 < heap->size)
   {
      int largest = i;
      int left = 2 * i + 1;
      int right = 2 * i + 2;

      if (left < heap->size && heap->arr[left] > heap->arr[largest])
         largest = left;

      if (right < heap->size && heap->arr[right] > heap->arr[largest])
         largest = right;

      if (largest == i)
         break;

      int temp = heap->arr[i];
      heap->arr[i] = heap->arr[largest];
      heap->arr[largest] = temp;
      i = largest;

      printf("Heap after swapping: ");
      printHeap(heap);
   }
}

// Function to test the heap
int main()
{
   struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
   initializeHeap(heap);

   insert(heap, 20);
   insert(heap, 15);
   insert(heap, 30);
   insert(heap, 60);
   insert(heap, 40);

   increaseKey(heap, 0, 50);
   increaseKey(heap, 1, 45);
   increaseKey(heap, 2, 65);
   increaseKey(heap, 3, 35);
   increaseKey(heap, 4, 55);

   decreaseKey(heap, 0, 20);
   decreaseKey(heap, 1, 10);
   decreaseKey(heap, 2, 25);
   decreaseKey(heap, 3, 15);
   decreaseKey(heap, 4, 5);

   printf("Final heap: ");
   printHeap(heap);

   // Free the allocated memory
   free(heap);
   return 0;
}