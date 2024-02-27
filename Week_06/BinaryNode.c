#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_validation.h"
#include "BinaryNode.h"

BinaryNode * LocateParent(int num, BinaryNode *current)
{
    BinaryNode * RetVal = NULL;
    if (current != NULL)
    {
        if (num == current->num)
        {
            return (BinaryNode *)1;
        }
        else if (num < current->num)
        {
            RetVal = LocateParent(num, current->left);
            if (RetVal == (BinaryNode *)1)
            {
                return current;
            }
            
        }
        else
        {
            RetVal = LocateParent(num, current->right);
            if (RetVal == (BinaryNode *)1)
            {
                return current;
            }
        }
    }
    else
    {
        return NULL;
    }
    return RetVal;
}

void AttachToBinaryTree(BinaryNode *NewTree, BinaryNode *current)
{
    if (current != NULL && NewTree != NULL)
    {
        if (NewTree->num < current->num)
        {
            if(current->left == NULL)
            {
                current->left = NewTree;
            }
            else
            {
                AttachToBinaryTree(NewTree, current->left);
            }
        }
        else
        {
            if(current->right == NULL)
            {
                current->right = NewTree;
            }
            else
            {
                AttachToBinaryTree(NewTree, current->right);
            }
        }
    }
}

BinaryNode * AddToBinaryTree(int num, BinaryNode *current)
{
    if (current != NULL)
    {
        if (num < current->num)
        {
            current->left = AddToBinaryTree(num, current->left);
        }
        else
        {
            current->right = AddToBinaryTree(num, current->right);
        }
    }
    else
    {
        current = malloc(sizeof(BinaryNode));
        current->left = NULL;
        current->right = NULL;
        current->num = num;
    }
    return current;
}


int RemoveFromBinaryTree(int num, BinaryNode *current)
{
    BinaryNode *TempParentNode = LocateParent(num, current);
    if(TempParentNode != NULL)
    {
        if (num < TempParentNode->num)
        {
            BinaryNode *ChildToBeDelete = TempParentNode->left;
            BinaryNode *NewChild = ChildToBeDelete->left;
            BinaryNode *GrandChild = ChildToBeDelete->right;
            TempParentNode->left = NewChild;
            if(GrandChild != NULL)
            {    
                AttachToBinaryTree(GrandChild, TempParentNode);
            }
            free(ChildToBeDelete);
        }
        else
        {
            BinaryNode *ChildToBeDelete = TempParentNode->right;
            BinaryNode *NewChild = ChildToBeDelete->right;
            BinaryNode *GrandChild = ChildToBeDelete->left;
            TempParentNode->right = NewChild;
            if (GrandChild != NULL)
            {
                AddToBinaryTree(GrandChild->num, current);
                if(GrandChild->left != NULL || GrandChild->right != NULL)
                    {
                        AttachToBinaryTree(GrandChild, TempParentNode);
                    }
            }
            free(ChildToBeDelete);
        }
    }
    else
    {
        return 0;
    }
    return 1; 
}

void InOrderTraversal(BinaryNode *current)
{
    if(current != NULL)
    {
        InOrderTraversal(current->left);
        printf("current->value: %d\n", current->num);
        InOrderTraversal(current->right);
    }
}
