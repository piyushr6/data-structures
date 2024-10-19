#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
   int value;
   struct TreeNode *leftChild;
   struct TreeNode *rightChild;
   int nodeHeight;
};

// Function to print the tree using preorder traversal
void printPreorder(struct TreeNode *root)
{
   if (root != NULL)
   {
      printf("%d ", root->value);
      printPreorder(root->leftChild);
      printPreorder(root->rightChild);
   }
}

// Function to get the height of the tree
int getNodeHeight(struct TreeNode *node)
{
   if (node == NULL)
      return 0;
   return node->nodeHeight;
}

// Function to get the maximum of two integers
int getMax(int a, int b)
{
   return (a > b) ? a : b;
}

// Allocating memory to tree node
struct TreeNode *initializeNode(int value)
{
   struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));

   newNode->value = value;
   newNode->leftChild = NULL;
   newNode->rightChild = NULL;
   newNode->nodeHeight = 1;

   return newNode;
}

// Function to perform right rotation on the tree node
struct TreeNode *performRightRotation(struct TreeNode *y)
{
   struct TreeNode *x = y->leftChild;
   struct TreeNode *temp = x->rightChild;

   // Perform rotation
   x->rightChild = y;
   y->leftChild = temp;

   // Update heights
   y->nodeHeight = getMax(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;
   x->nodeHeight = getMax(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;

   return x;
}

// Function to perform left rotation on the tree node
struct TreeNode *performLeftRotation(struct TreeNode *x)
{
   struct TreeNode *y = x->rightChild;
   struct TreeNode *temp = y->leftChild;

   // Perform rotation
   y->leftChild = x;
   x->rightChild = temp;

   // Update heights
   x->nodeHeight = getMax(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;
   y->nodeHeight = getMax(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;

   return y;
}

// Function to calculate balance factor
int calculateBalanceFactor(struct TreeNode *node)
{
   if (node == NULL)
      return 0;
   return getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild);
}

// Function to insert a node into the AVL tree
struct TreeNode *addNode(struct TreeNode *node, int value)
{
   if (node == NULL)
      return initializeNode(value);

   if (value < node->value)
      node->leftChild = addNode(node->leftChild, value);
   else if (value > node->value)
      node->rightChild = addNode(node->rightChild, value);
   else
      return node;

   node->nodeHeight = 1 + getMax(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
   int balanceFactor = calculateBalanceFactor(node);

   printf("\nPreorder Traversal before balancing: ");
   printPreorder(node);

   // Left Left Case
   if (balanceFactor > 1 & value < node->leftChild->value)
      return performRightRotation(node);

   // Right Right Case
   if (balanceFactor<-1 & value> node->rightChild->value)
      return performLeftRotation(node);

   // Left Right Case
   if (balanceFactor > 1 & value > node->leftChild->value)
   {
      node->leftChild = performLeftRotation(node->leftChild);
      return performRightRotation(node);
   }

   // Right Left Case
   if (balanceFactor < -1 & value < node->rightChild->value)
   {
      node->rightChild = performRightRotation(node->rightChild);
      return performLeftRotation(node);
   }

   printf("\nPreorder Traversal after balancing: ");
   printPreorder(node);

   return node;
}

void main()
{
   struct TreeNode *root = NULL;
   int value;

   // Inserting nodes into the AVL tree
   printf("Enter a number to insert into AVL tree (-1 to stop): ");
   scanf("%d", &value);
   while (value >= 0)
   {
      root = addNode(root, value);
      printf("\nEnter a number to insert into AVL tree (-1 to stop): ");
      scanf("%d", &value);
   }
}
