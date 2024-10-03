#include <stdio.h>
#include <stdlib.h>

struct node
{
   int data;
   struct node *left;
   struct node *right;
};

// Recursive function to create a binary tree
struct node *createNode()
{
   int data;
   printf("Data (-1 for no node): ");
   scanf("%d", &data);
   if (data == -1)
      return NULL;

   // Create a new node
   struct node *newNode = (struct node *)malloc(sizeof(struct node));
   newNode->data = data;

   printf("Enter left child %d:\n", data);
   newNode->left = createNode();

   printf("Enter right child %d:\n", data);
   newNode->right = createNode();

   return newNode;
}

// function for postorder traversal
void postOrder(struct node *p)
{
   if (p == NULL)
      return;
   postOrder(p->left);
   postOrder(p->right);
   printf("%d ", p->data);
}

int countNodes(struct node *p)
{
   if (p == NULL)
      return 0;

   int nodes = 1 + countNodes(p->left) + countNodes(p->right);

   return nodes;
}

int leafNodes(struct node *p)
{
   int c1 = 0;
   int c2 = 0;

   if (p == NULL)
      return 0;

   if (p->left == NULL && p->right == NULL)
      return 1;

   c1 = leafNodes(p->left);
   c2 = leafNodes(p->right);

   return c1 + c2;
}

int main()
{
   struct node *root;
   root = createNode();
   printf("\n");

   // 1.traversing
   postOrder(root);
   printf("\n");

   // 2. nodes
   printf("\nThe number of Total nodes are %d", countNodes(root));
   printf("\n");

   // 3. leaf nodes
   printf("\nThe number of Leaf nodes are %d", leafNodes(root));
   printf("\n");
}