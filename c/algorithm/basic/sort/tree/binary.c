struct TreeNode {
  struct TreeNode *leftPtr;  /* pointer to left subtree */
  int data;                  /* node data */
  struct TreeNode *rightPtr; /* pointer to right subtree */
};

void insertNode(TreeNodePtr *treePtr, int value)
{
  if (*treePtr == NULL) {
    *treePtr = malloc(sizeof(TreeNode));

    if (*treePtr != NULL) {
      (*treePtr) -> data = value;
      (*treePtr) -> leftPtr = NULL;
      (*treePtr) -> rightPtr = NULL;
    } else {
      printf("%d not inserted. No memory available.\n", value);
    }
  } else { 
    if (value < (*treePtr) -> data) {
      insertNode(&((*treePtr)->leftPtr), value);
    } else {
      if (value >(*treePtr) -> data) {
        insertNode(&((*treePtr) -> rightPtr), value);
      } else {
        printf("dup");
      }
    }
  }
}

TreeNode *binaryTreeSereach(TreeNode * const treePtr, int value)
{
  TreeNode *tempPtr = treePtr;

  while (tempPtr != NULL && tempPtr -> data != value)
  {
    if (value > tempPtr->data) {
      tempPtr = tempPtr->rightPtr;
    } else {
      tempPtr = tempPtr->leftPtr;
    }
  }

  return tempPtr;
}
