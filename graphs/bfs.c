#include <stdio.h>
#include <stdlib.h>

// Define structure for a linked list node (each node represents an edge)
struct Node
{
   int city;
   struct Node *next;
};

// Define adjacency list as an array of linked list heads
struct Node *adjacencyList[7];
char *node_names[] = {"Everett", "Seattle", "North Bend", "Olympia", "Centralia", "Spokane", "Portland"};

// Function to create a new node
struct Node *createNode(int city)
{
   struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
   newNode->city = city;
   newNode->next = NULL;
   return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(int src, int dest)
{
   struct Node *newNode = createNode(dest);
   newNode->next = adjacencyList[src];
   adjacencyList[src] = newNode;
}

// Function to build the adjacency list from the adjacency matrix
void buildAdjacencyList(int matrix[7][7])
{
   for (int i = 0; i < 7; i++)
   {
      for (int j = 0; j < 7; j++)
      {
         if (matrix[i][j] == 1)
         {
            addEdge(i, j);
         }
      }
   }
}

// Function to print the adjacency list
void printAdjacencyList()
{
   printf("Adjacency List Representation:\n");
   for (int i = 0; i < 7; i++)
   {
      printf("%s: ", node_names[i]);
      struct Node *temp = adjacencyList[i];
      while (temp != NULL)
      {
         printf("-> %s ", node_names[temp->city]);
         temp = temp->next;
      }
      printf("\n");
   }
}

// BFS function
void bfs(int start)
{
   int queue[7];
   int front = 0, rear = 0;
   int parent[7];
   int distance[7];

   // Initialize distances and parents
   for (int i = 0; i < 7; i++)
   {
      parent[i] = -1;
      distance[i] = -1;
   }

   // Start node setup
   queue[rear++] = start;
   parent[start] = start; // Parent of start node is the node itself
   distance[start] = 0;

   printf("BFS Traversal starting from %s:\n", node_names[start]);

   while (front < rear)
   {
      int current = queue[front++];
      printf("Processing Node: %s\n", node_names[current]);

      // Traverse all neighbors
      struct Node *temp = adjacencyList[current];
      while (temp != NULL)
      {
         int i = temp->city;
         if (distance[i] == -1)
         {
            queue[rear++] = i;
            parent[i] = current;
            distance[i] = distance[current] + 1;
            printf("Visited %s | Parent: %s | Distance: %d\n", node_names[i], node_names[current], distance[i]);
         }
         temp = temp->next;
      }
      printf("\n");
   }

   // Print final distances and parent arrays
   printf("Final Distance and Parent Arrays:\n");
   for (int i = 0; i < 7; i++)
   {
      printf("Node: %s | Distance: %d | Parent: ", node_names[i], distance[i]);
      if (parent[i] == -1)
      {
         printf("None\n");
      }
      else
      {
         printf("%s\n", node_names[parent[i]]);
      }
   }
}

int main()
{
   // Initialize adjacency list with NULLs
   for (int i = 0; i < 7; i++)
   {
      adjacencyList[i] = NULL;
   }

   // Define adjacency matrix
   int matrix[7][7] = {
       {0, 1, 1, 0, 0, 1, 0}, // Everett
       {0, 0, 0, 1, 0, 0, 0}, // Seattle
       {0, 0, 0, 0, 0, 1, 0}, // North Bend
       {0, 0, 0, 0, 1, 0, 1}, // Olympia
       {0, 0, 0, 0, 0, 1, 1}, // Centralia
       {0, 0, 0, 0, 0, 0, 0}, // Spokane
       {0, 0, 0, 0, 0, 0, 0}  // Portland
   };

   // Build adjacency list from the matrix
   buildAdjacencyList(matrix);
   printf("\n");

   printAdjacencyList();
   printf("\n");

   // Perform BFS starting from different nodes
   int start1 = 0; // Start from "Everett" (index 0)
   bfs(start1);

   printf("\n");

   int start2 = 3; // Start from "Olympia" (index 3)
   bfs(start2);

   return 0;
}