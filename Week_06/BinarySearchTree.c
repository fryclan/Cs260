#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_validation.h"
#include "BinaryNode.h"

int main()
{
    int Check = 0;
    int UserInput = 0;
    char UserChar[10] ="";
    char UserCheck[10] = "y";
    BinaryNode *BinaryTree = NULL;
    BinaryTree = AddToBinaryTree(8, BinaryTree);
    BinaryTree = AddToBinaryTree(6, BinaryTree);
    BinaryTree = AddToBinaryTree(5, BinaryTree);
    BinaryTree = AddToBinaryTree(24, BinaryTree);
    BinaryTree = AddToBinaryTree(13, BinaryTree);
    BinaryTree = AddToBinaryTree(2, BinaryTree);
    BinaryTree = AddToBinaryTree(1, BinaryTree);
    BinaryTree = AddToBinaryTree(3, BinaryTree);
    BinaryTree = AddToBinaryTree(4, BinaryTree);
    BinaryTree = AddToBinaryTree(22, BinaryTree);
    BinaryTree = AddToBinaryTree(11, BinaryTree);
    BinaryTree = AddToBinaryTree(55, BinaryTree);
    BinaryTree = AddToBinaryTree(7, BinaryTree);
    printf("do you want to add more to the tree?(yes/no)\n");
    readline_string("%s", UserChar);
    while (UserChar[0] == UserCheck[0])
    {
        printf("what integer you want to add?\n");
        readline_int("%d", &UserInput);
        BinaryTree = AddToBinaryTree(UserInput, BinaryTree);
        printf("do you want to add more to the tree?(yes/no)\n");
        readline_string("%s", UserChar);
    }
    InOrderTraversal(BinaryTree);
    Check = RemoveFromBinaryTree(2, BinaryTree);
    printf("Remove Value Returns: %d\n", Check);
    InOrderTraversal(BinaryTree);
}
