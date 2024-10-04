#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // For using isalnum

// Node structure for binary tree
struct node
{
   int data;
   struct node *left;
   struct node *right;
};

// Node structure for expression tree
struct ExprNode
{
   char data;
   struct ExprNode *left;
   struct ExprNode *right;
};

// Stack structure for handling expression tree nodes
struct Stack
{
   struct ExprNode *node;
   struct Stack *next;
};

// Function to create a binary tree node
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

// Function for postorder traversal of binary tree
void postOrder(struct node *p)
{
   if (p == NULL)
      return;
   postOrder(p->left);
   postOrder(p->right);
   printf("%d ", p->data);
}

// Function to count nodes in binary tree
int countNodes(struct node *p)
{
   if (p == NULL)
      return 0;

   int nodes = 1 + countNodes(p->left) + countNodes(p->right);

   return nodes;
}

// Function to count leaf nodes in binary tree
int leafNodes(struct node *p)
{
   if (p == NULL)
      return 0;

   if (p->left == NULL && p->right == NULL)
      return 1;

   int c1 = leafNodes(p->left);
   int c2 = leafNodes(p->right);

   return c1 + c2;
}

// Function to calculate the height of a binary tree node
int height(struct node *n)
{
   if (n == NULL)
      return -1; // Base case: If the node is NULL, the height is -1 (for edges)

   int leftHeight = height(n->left);
   int rightHeight = height(n->right);

   return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to create a new node for the expression tree
struct ExprNode *createExprNode(char data)
{
   struct ExprNode *node = (struct ExprNode *)malloc(sizeof(struct ExprNode));
   node->data = data;
   node->left = NULL;
   node->right = NULL;
   return node;
}

// Function to push expression tree nodes onto the stack
struct Stack *push(struct Stack *top, struct ExprNode *node)
{
   struct Stack *newStackNode = (struct Stack *)malloc(sizeof(struct Stack));
   newStackNode->node = node;
   newStackNode->next = top;
   return newStackNode; // Return the new top of the stack
}

// Function to pop expression tree nodes from the stack
struct Stack *pop(struct Stack *top, struct ExprNode **node)
{
   if (top == NULL)
   {
      printf("Stack underflow\n");
      return NULL;
   }
   *node = top->node;
   struct Stack *temp = top;
   top = top->next;
   free(temp);
   return top; // Return the new top of the stack
}

// Function to create an expression tree from a postfix expression
struct ExprNode *createExpressionTree(char postfix[])
{
   struct Stack *stack = NULL;

   for (int i = 0; postfix[i] != '\0'; i++)
   {
      if (isalnum(postfix[i]))
      {
         struct ExprNode *newNode = createExprNode(postfix[i]);
         stack = push(stack, newNode);
      }
      else
      {
         struct ExprNode *newNode = createExprNode(postfix[i]);

         struct ExprNode *rightNode;
         struct ExprNode *leftNode;
         stack = pop(stack, &rightNode);
         stack = pop(stack, &leftNode);

         newNode->right = rightNode;
         newNode->left = leftNode;

         stack = push(stack, newNode);
      }
   }

   struct ExprNode *root;
   stack = pop(stack, &root);
   return root;
}

// Function for postorder traversal of expression tree
void postOrderExpr(struct ExprNode *p)
{
   if (p == NULL)
      return;
   postOrderExpr(p->left);
   postOrderExpr(p->right);
   printf("%c ", p->data);
}

int main()
{
   struct node *root;
   root = createNode();
   printf("\n");

   // 1. Traversing
   printf("The postorder traversal of the given binary tree is:\n");
   postOrder(root);  
   printf("\n");

   // 2. Nodes
   printf("The number of total nodes are %d\n", countNodes(root));

   // 3. Leaf nodes
   printf("The number of leaf nodes are %d\n", leafNodes(root));

   // 4. Height of the tree
   printf("The height of the tree is %d\n", height(root));

   // 5. Postfix expression
   char postfix[] = "ab+ef*g*-";

   struct ExprNode *exprRoot = createExpressionTree(postfix);

   printf("Postorder traversal of the expression tree: ");
   postOrderExpr(exprRoot);

   return 0;
}