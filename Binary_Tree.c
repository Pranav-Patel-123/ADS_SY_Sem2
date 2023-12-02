#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

struct node *create()
{
    int x;
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data (-1 for no node): ");
    scanf("%d", &x);
    if (x == -1)
    {
        return NULL;
    }

    newnode->data = x;
    printf("Enter left child of %d: ", x);
    newnode->left = create();
    printf("Enter right child of %d: ", x);
    newnode->right = create();
    return newnode;
}

void preorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void mirrorImage(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Swap left and right subtrees
    struct node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively mirror the left and right subtrees
    mirrorImage(root->left);
    mirrorImage(root->right);
}

int height(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}


void displayLeafNodes(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->data);
        return;
    }

    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

int countNodes(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void levelOrderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Queue for level order traversal
    struct node *queue[100];
    int front = -1, rear = -1;

    // Enqueue the root
    queue[++rear] = root;

    while (front != rear)
    {
        struct node *current = queue[++front];
        printf("%d ", current->data);

        // Enqueue the left child
        if (current->left != NULL)
        {
            queue[++rear] = current->left;
        }

        // Enqueue the right child
        if (current->right != NULL)
        {
            queue[++rear] = current->right;
        }
    }
}

int main()
{
    struct node *root = NULL;
    int choice;

    do
    {
        printf("\nBinary Tree Operations Menu:\n");
        printf("1. Create\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Level Order Traversal\n");
        printf("6. Mirror Image\n");
        printf("7. Height\n");
        printf("8. Leaf Nodes\n");
        printf("9. Count Nodes\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Creating binary tree...\n");
            root = create();
            break;
        case 2:
            printf("Preorder traversal is: ");
            preorder(root);
            printf("\n");
            break;
        case 3:
            printf("Inorder traversal is: ");
            inorder(root);
            printf("\n");
            break;
        case 4:
            printf("Postorder traversal is: ");
            postorder(root);
            printf("\n");
            break;
        case 5:
            printf("Level order traversal is: ");
            levelOrderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Mirroring the binary tree...\n");
            mirrorImage(root);
            printf("Inorder traversal of the mirrored tree is: ");
            inorder(root);
            printf("\n");
            break;
        case 7:
            printf("Height of the binary tree is: %d\n", height(root));
            break;
        case 8:
            printf("Leaf nodes are: ");
            displayLeafNodes(root);
            printf("\n");
            break;
        case 9:
            printf("Number of nodes in the binary tree is: %d\n", countNodes(root));
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}