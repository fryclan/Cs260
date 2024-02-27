//node for binary tree
struct BinaryNode
{
    int num;
    struct BinaryNode *left;
    struct BinaryNode *right;
};

typedef struct BinaryNode BinaryNode;

void InOrderTraversal(BinaryNode *current);

int RemoveFromBinaryTree(int num, BinaryNode *current);

BinaryNode * AddToBinaryTree(int num, BinaryNode *current);

void AttachToBinaryTree(BinaryNode *NewTree, BinaryNode *current);
