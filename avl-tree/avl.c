#include <stdio.h>
#include <stdlib.h>

// Defining structure for the AVL Tree node
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
struct TreeNode *createNode(int value)
{
   struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
   newNode->value = value;
   newNode->leftChild = NULL;
   newNode->rightChild = NULL;
   newNode->nodeHeight = 1;
   return newNode;
}

// Function to perform right rotation on the tree node
struct TreeNode *rightRotate(struct TreeNode *y)
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
struct TreeNode *leftRotate(struct TreeNode *x)
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
      return createNode(value);

   if (value < node->value)
      node->leftChild = addNode(node->leftChild, value);
   else if (value > node->value)
      node->rightChild = addNode(node->rightChild, value);
   else
      return node;

   node->nodeHeight = 1 + getMax(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
   int balanceFactor = calculateBalanceFactor(node);

   printf("\nPreorder Traversal of the AVL Tree before balancing: ");
   printPreorder(node);

   // Left Left Case
   if (balanceFactor > 1 && value < node->leftChild->value)
      node = rightRotate(node);

   // Right Right Case
   else if (balanceFactor < -1 && value > node->rightChild->value)
      node = leftRotate(node);

   // Left Right Case
   else if (balanceFactor > 1 && value > node->leftChild->value)
   {
      node->leftChild = leftRotate(node->leftChild);
      node = rightRotate(node);
   }

   // Right Left Case
   else if (balanceFactor < -1 && value < node->rightChild->value)
   {
      node->rightChild = rightRotate(node->rightChild);
      node = leftRotate(node);
   }

   printf("\nPreorder Traversal after balancing: ");
   printPreorder(node);

   return node;
}

// Function to find the node with the minimum value in a tree
struct TreeNode *findMinNode(struct TreeNode *node)
{
   struct TreeNode *current = node;
   while (current->leftChild != NULL)
      current = current->leftChild;
   return current;
}

// Function to delete a node from the AVL tree
struct TreeNode *deleteNode(struct TreeNode *root, int value)
{
   if (root == NULL)
      return root;

   if (value < root->value)
      root->leftChild = deleteNode(root->leftChild, value);
   else if (value > root->value)
      root->rightChild = deleteNode(root->rightChild, value);
   else
   {
      if ((root->leftChild == NULL) || (root->rightChild == NULL))
      {
         struct TreeNode *temp = root->leftChild ? root->leftChild : root->rightChild;
         if (temp == NULL)
         {
            temp = root;
            root = NULL;
         }
         else
            *root = *temp;
         free(temp);
      }
      else
      {
         struct TreeNode *temp = findMinNode(root->rightChild);
         root->value = temp->value;
         root->rightChild = deleteNode(root->rightChild, temp->value);
      }
   }

   if (root == NULL)
      return root;

   root->nodeHeight = 1 + getMax(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild));
   int balanceFactor = calculateBalanceFactor(root);

   printf("\nPreorder Traversal before balancing: ");
   printPreorder(root);

   // Left Left Case
   if (balanceFactor > 1 && calculateBalanceFactor(root->leftChild) >= 0)
      root = rightRotate(root);

   // Left Right Case
   else if (balanceFactor > 1 && calculateBalanceFactor(root->leftChild) < 0)
   {
      root->leftChild = leftRotate(root->leftChild);
      root = rightRotate(root);
   }

   // Right Right Case
   else if (balanceFactor < -1 && calculateBalanceFactor(root->rightChild) <= 0)
      root = leftRotate(root);

   // Right Left Case
   else if (balanceFactor < -1 && calculateBalanceFactor(root->rightChild) > 0)
   {
      root->rightChild = rightRotate(root->rightChild);
      root = leftRotate(root);
   }

   printf("\nPreorder Traversal after balancing: ");
   printPreorder(root);

   return root;
}

int main()
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

   // Deleting nodes from the AVL tree
   printf("\nEnter a number to delete from AVL tree (-1 to stop): ");
   scanf("%d", &value);
   while (value >= 0)
   {
      root = deleteNode(root, value);
      printf("\nEnter a number to delete from AVL tree (-1 to stop): ");
      scanf("%d", &value);
   }

   return 0;
}