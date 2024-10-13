#include <stdio.h>
#include <stdlib.h>

// Node structure for the binary search tree
struct node
{
   int data;
   struct node *left;
   struct node *right;
};

// Function to create a new node
struct node *createNewNode(int data)
{
   struct node *newNode = (struct node *)malloc(sizeof(struct node));
   newNode->data = data;
   newNode->left = NULL;
   newNode->right = NULL;
   return newNode;
}

// Function to insert data into the BST
struct node *insert(struct node *root, int data)
{
   // If the tree is empty, return a new node
   if (root == NULL)
   {
      return createNewNode(data);
   }

   // Otherwise, recur down the tree
   if (data < root->data)
   {
      root->left = insert(root->left, data); // Insert into left subtree
   }
   else if (data > root->data)
   {
      root->right = insert(root->right, data); // Insert into right subtree
   }

   return root; // Return the unchanged node pointer
}

// function for inorder traversal
void inOrder(struct node *root)
{
   if (root == NULL)
      return;

   inOrder(root->left);
   printf("%d ", root->data);
   inOrder(root->right);
}

// function for preorder traversal
void preOrder(struct node *root)
{
   if (root == NULL)
      return;

   printf("%d ", root->data);
   preOrder(root->left);
   preOrder(root->right);
}

// Function to find the minimum value in the binary tree
int min(struct node *root)
{
   if (root == NULL)
   {
      printf("Tree is empty.\n");
      return -1; // Indicating an empty tree
   }

   while (root->left != NULL)
   {
      root = root->left;
   }
   return root->data;
}

// Function to find the maximum value in the binary tree
int max(struct node *root)
{
   if (root == NULL)
   {
      printf("Tree is empty.\n");
      return -1;
   }

   while (root->right != NULL)
   {
      root = root->right;
   }
   return root->data;
}

// Function to search for a node in the BST
struct node *search(struct node *root, int data)
{
   if (root == NULL || root->data == data)
      return root; // Return the node if found

   if (data < root->data)
      return search(root->left, data);
   else
      return search(root->right, data);
}

// Function to find the predecessor of a given node
int getPredecessor(struct node *root, int key)
{
   struct node *current = search(root, key);
   if (current == NULL)
      return -1; // Key not found

   if (current->left != NULL)
   {
      return max(current->left);
   }

   struct node *predecessor = NULL;
   struct node *ancestor = root;
   while (ancestor != current)
   {
      if (key > ancestor->data)
      {
         predecessor = ancestor;
         ancestor = ancestor->right;
      }
      else
      {
         ancestor = ancestor->left;
      }
   }
   return (predecessor != NULL) ? predecessor->data : -1;
}

// Function to find the successor of a given node
int getSuccessor(struct node *root, int key)
{
   struct node *current = search(root, key);
   if (current == NULL)
      return -1; // Key not found

   if (current->right != NULL)
   {
      return min(current->right);
   }

   struct node *successor = NULL;
   struct node *ancestor = root;
   while (ancestor != current)
   {
      if (key < ancestor->data)
      {
         successor = ancestor;
         ancestor = ancestor->left;
      }
      else
      {
         ancestor = ancestor->right;
      }
   }
   return (successor != NULL) ? successor->data : -1;
}

// Function to delete a node from the BST
struct node *deleteNode(struct node *root, int key)
{
   if (root == NULL)
   {
      return root;
   }

   if (key < root->data)
   {
      root->left = deleteNode(root->left, key);
   }
   else if (key > root->data)
   {
      root->right = deleteNode(root->right, key);
   }
   else
   {
      if (root->left == NULL)
      {
         struct node *temp = root->right;
         free(root);
         return temp;
      }
      else if (root->right == NULL)
      {
         struct node *temp = root->left;
         free(root);
         return temp;
      }

      int successorValue = min(root->right);
      root->data = successorValue;
      root->right = deleteNode(root->right, successorValue);
   }
   return root;
}

int main()
{
   struct node *root = NULL;
   int data;

   printf("Enter node data (-1 to stop):\n");

   // Keep inserting data until the user enters -1
   while (1)
   {
      printf("Enter data: ");
      scanf("%d", &data);

      if (data == -1)
         break;

      root = insert(root, data);
   }

   printf("\nThe preOrder traversal of the tree is: ");
   preOrder(root);

   printf("\nThe inOrder traversal of the tree is: ");
   inOrder(root);

   printf("\nEnter data to be searched: ");
   int d;
   scanf("%d", &d);

   if (search(root, d) != NULL)
      printf("Element found!");
   else
      printf("Element not found");

   printf("\nThe minimum value in this tree is %d", min(root));
   printf("\nThe maximum value in this tree is %d", max(root));

   printf("\nEnter node for which you want predecessor: ");
   int np;
   scanf("%d", &np);
   getPredecessor(root, np);
   printf("\nThe predecessor of the element is : %d", getPredecessor(root, np));

   printf("\nEnter node for which you want successor: ");
   int sp;
   scanf("%d", &sp);
   printf("\nThe successor of the element is : %d", getSuccessor(root, sp));

   printf("\nEnter the node which you want to delete from the tree:");
   int delnode;
   scanf("%d", &sp);
   deleteNode(root, sp);
   printf("\nNode deleted!!");

   return 0;
}