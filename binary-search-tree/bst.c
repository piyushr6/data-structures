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

// In-order traversal (Left, Root, Right)
void inOrder(struct node *root)
{
   if (root == NULL)
      return;

   inOrder(root->left);
   printf("%d ", root->data);
   inOrder(root->right);
}

// Pre-order traversal (Root, Left, Right)
void preOrder(struct node *root)
{
   if (root == NULL)
      return;

   printf("%d ", root->data);
   preOrder(root->left);
   preOrder(root->right);
} // Function to find the minimum value in the binary tree
int min(struct node *root)
{
   if (root == NULL)
   {
      printf("Tree is empty.\n");
      return -1; // Indicating an empty tree
   }

   // Keep going left until we find the leftmost leaf
   while (root->left != NULL)
   {
      root = root->left;
   }
   return root->data; // Return the minimum value
}

// Function to find the maximum value in the binary tree
int max(struct node *root)
{
   if (root == NULL)
   {
      printf("Tree is empty.\n");
      return -1; // Indicating an empty tree
   }

   // Keep going right until we find the rightmost leaf
   while (root->right != NULL)
   {
      root = root->right;
   }
   return root->data; // Return the maximum value
}

int search(struct node *root, int data)
{
   if (root->data == data)
      return 1;
   else
   {
      if (data < root->data)
         root = root->left;
      else
         root = root->right;
   }
   return 0;
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

      root = insert(root, data); // Insert the data into the BST
   }

   printf("\nThe preOrder traversal of the tree is: ");
   preOrder(root);

   printf("\nThe inOrder traversal of the tree is: ");
   inOrder(root);

   printf("\nEnter data to be searched:");
   int d;
   scanf("%d", &d);

   if (search(root, d) == 1)
      printf("\nElement found!");
   else
      printf("\nElement not found");

   printf("\n The minimum value in this tree is %d", min(root));
   printf("\n The maximum value in this tree is %d", max(root));

   return 0;
}