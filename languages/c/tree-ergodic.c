#include<malloc.h> 
#define MAXSIZE 100

typedef char dataType;

// 二叉树结构
typedef struct bnode{  
    dataType data;  
    struct bnode *lChild,*rChild;  
} Bnode, *BTree;

/** 
 * 队列结构
 */
typedef struct {  
    BTree data[MAXSIZE];  
    int front, rear;  
} SeqQueue, *PSeqQueue;

/**
 * 栈的结构
 */
typedef struct {  
    BTree data[MAXSIZE];
    int top;
} SeqStack, *PSeqStack;  
  
// 队列的初始化  
PSeqQueue initSeqQueue () {
  PSeqQueue queue;
  queue = (PSeqQueue)malloc(sizeof(SeqQueue));

  if (queue) {
    queue->front = queue->rear = 0;
  }

  return queue;
}

// 判断队列是否为空  
int emptyQueue (PSeqQueue queue) {
  if (queue && queue->front==queue->rear) {
    return 1;
  } else {
    return 0; 
  }  
}

// 入队列  
int pushQueue (PSeqQueue queue, Bnode *node){  
  if ((queue->rear+1) % MAXSIZE == queue -> front){  // 判断队列是否满了  
    return -1;  
  } else {  
    queue->rear = (queue->rear+1)%MAXSIZE;        // 位置为0的地址空间不用，方便判断是否为空  
    queue->data[queue->rear] = node;
    return 1;
  } 
}

// 出队列  
int popQueue (PSeqQueue queue,BTree *node){
  if (emptyQueue(queue)) {
    return -1;
  } else {
    queue->front = (queue->front +1)%MAXSIZE;  
    *node = queue->data[queue->front];  
    return 1;  
  }
}

// 读取队头元素  
int frontQueue (PSeqQueue queue, BTree *node){  
  if (queue->rear == queue->front){  
    return -1;
  } else {
    *node = queue->data[(queue->front+1)%MAXSIZE];  
    return 1;  
  }
}

// 销毁队列  
void destroyQueue (PSeqQueue *queue) {  
  if (*queue) {
    free(*queue);  
    *queue = NULL;  
  }
}

// 栈的初始化  
PSeqStack initStack () {
  PSeqStack stack;
  stack = (PSeqStack)malloc(sizeof(SeqStack));

  if (stack) {
    stack->top = -1;
  }

  return stack;
}

// 判断栈是否为空
int emptyStack (PSeqStack stack) {
  if (stack->top == -1){  
    return 1;  
  } else {
    return 0;  
  }
}

// 入栈  
int pushStack (PSeqStack stack, Bnode *node) {
  if (stack->top == MAXSIZE-1) {
    return 0;
  } else {
    stack->top ++;
    stack->data[stack->top] = node;
    return 1;  
  }
}

// 出栈  
int popStack (PSeqStack stack, BTree *node) {
  if (emptyStack(stack) == 1) {
    return 0;
  } else {
    *node = stack->data[stack->top];
    stack->top --;

    return 1;
  }
}

// 打印元素  
void visit (char ch) {
    printf("%c \t",ch);
}
  
// 二叉树的建立  
BTree createTree () {
  BTree tree;
  dataType str;
  str = getchar();

  if (str == '#') {
    tree = NULL;
  } else {
    tree = (BTree)malloc(sizeof(Bnode));
    tree->data = str;
    tree->lChild = createTree();
    tree->rChild = createTree();
  }

  return tree;
}

// 先序遍历二叉树  
void perOrder (BTree tree) {
  PSeqStack stack;  
  BTree p = tree;  
  stack = initStack();

  while (p || ! emptyStack(stack)) {
    if (p) {
      visit(p->data);
      pushStack(stack,p);
      p = p->lChild;
    } else {
      popStack(stack,&p);
      p = p->rChild;
    }
  }
}

// 中序遍历此二叉树  
void inOrder (BTree tree) {
  PSeqStack stack;
  BTree p = tree;
  stack = initStack();

  while (p || !emptyStack(stack)) {
    if (p) {
      pushStack(stack,p);
      p = p->lChild;
    } else {
      popStack(stack,&p);
      visit(p->data);
      p = p->rChild;
    }
  }
}  
  
// 后序遍历打印元素  
void postOrder (BTree tree) {
  PSeqStack s1,s2;  
  BTree p = tree;
  
  s1 = initStack();  
  s2 = initStack();  

  while (p || !emptyStack(s2)) {  
    if (p) {  
      pushStack(s1,p);  
      pushStack(s2,p);  
      p = p->rChild;  
    } else {  
      popStack(s2,&p);  
      p = p->lChild;  
    }  
  }  
    
  while(!emptyStack(s1)){  
    popStack(s1,&p);  
    visit(p->data);  
  }
}

// 层次遍历二叉树
void levelOrder (BTree tree) {
  BTree p = tree;
  PSeqQueue queue = initSeqQueue();

  if (p) {
    pushQueue(queue, p);

    while (!emptyQueue(queue)) {
      popQueue (queue, &p);
      visit (p->data);

      if (p -> lChild) {
        pushQueue(queue, p->lChild);
      }

      if (p -> rChild) {
        pushQueue(queue, p->rChild);  
      }
    }
  }  
}

// 求二叉树的高度  
int height (BTree tree) {
  int h1, h2;
  
  if (tree == NULL) {
    return 0;  
  } else {
    h1 = height(tree->lChild);  
    h2 = height(tree->rChild);  

    if (h1 > h2) {
      return h1+1;  
    } else {
      return h2+1;  
    }
  }  
}

// 求解二叉树每层节点的个数  
void levelCount (BTree tree, int l, int num[]) {
    if (tree) {
      num[l]++;
      levelCount(tree->lChild,l+1,num);
      levelCount(tree->rChild,l+1,num);
    }  
}

// 求解二叉树节点总数  
int countTree (BTree tree) {  
  int lCount, rCount;

  if (tree == NULL) {
    return 0;  
  }

  lCount = countTree(tree->lChild);
  rCount = countTree(tree->rChild);
  return lCount + rCount + 1;
}
