#include <stdio.h>
#define TABLE_SIZE 7 // Size of the hash table

int hashTable[TABLE_SIZE]; // Hash table array

// Initialize the hash table with -1 to indicate empty slots
void initializeTable()
{
   for (int i = 0; i < TABLE_SIZE; i++)
   {
      hashTable[i] = -1;    
   }
}

// Hash function using modulo division
int hashFunction(int key)
{
   return key % TABLE_SIZE;
}

// Insert function with linear probing
void insert(int key)
{
   int index = hashFunction(key);

   // Linear probing to resolve collision
   for (int i = 0; i < TABLE_SIZE; i++)
   {
      int newIndex = (index + i) % TABLE_SIZE;
      if (hashTable[newIndex] == -1)
      {                             // If slot is empty
         hashTable[newIndex] = key; // Insert key
         printf("Key %d inserted at index %d\n", key, newIndex);
         return;
      }
      else if (i == 0)
      {
         printf("Collision occurred for key %d at index %d\n", key, newIndex);
      }
   }

   // If table is full, print an error
   printf("Hash table is full. Unable to insert key %d\n", key);
}

// Delete function with linear probing
void delete(int key)
{
   int index = hashFunction(key);

   // Linear probing to find the key
   for (int i = 0; i < TABLE_SIZE; i++)
   {
      int newIndex = (index + i) % TABLE_SIZE;
      if (hashTable[newIndex] == key)
      {
         hashTable[newIndex] = -1; // Mark slot as empty
         printf("Key %d deleted from index %d\n", key, newIndex);
         return;
      }
   }

   // If key is not found, print an error
   printf("Key %d not found for deletion\n", key);
}

// Search function with linear probing
void search(int key)
{
   int index = hashFunction(key);

   // Linear probing to find the key
   for (int i = 0; i < TABLE_SIZE; i++)
   {
      int newIndex = (index + i) % TABLE_SIZE;
      if (hashTable[newIndex] == key)
      {
         printf("Key %d found at index %d\n", key, newIndex);
         return;
      }
      if (hashTable[newIndex] == -1)
      {
         break; // Stop searching if we hit an empty slot
      }
   }

   // If key is not found, print an error
   printf("Key %d not found\n", key);
}

// Display function to print the hash table
void displayTable()
{
   for (int i = 0; i < TABLE_SIZE; i++)
   {
      if (hashTable[i] != -1)
      {
         printf("Index %d: %d\n", i, hashTable[i]);
      }
      else
      {
         printf("Index %d: ~\n", i); // '~' denotes an empty slot
      }
   }
}

int main()
{
   initializeTable();

   // Insert keys
   insert(10);
   insert(22);
   insert(31);
   insert(4);
   insert(15);
   insert(28);
   insert(17); // Table is full here

   // Display the hash table after insertions
   printf("\nHash Table after insertions:\n");
   displayTable();

   // Search keys
   search(15); // Found
   search(99); // Not found

   // Delete keys
   delete (28); // Successfully deleted
   delete (99); // Not found

   // Display the hash table after deletions
   printf("\nHash Table after deletions:\n");
   displayTable();

   return 0;
}