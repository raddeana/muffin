// *****************************************
// 树的多种结构定义
// *****************************************

#define MAX_TREE_SIZE 100
typedef int TempType;

// ****************************************
// 双亲表示法
// ****************************************
typedef struct PTNode               /* 结点结构*/
{
    TempType data;                  /* 结点数据*/
    int partent;                    /* 双亲位置*/
} PTNode;

typedef struct                            /* 树结构*/
{
    PTNode nodes[MAX_TREE_SISE];          /* 结点数组*/
    int r, n;                             /* 树中根的位置和结点数*/
} PTree;


// ****************************************
// 孩子表示法
// ****************************************
typedef struct CTNode              /* 结点结构*/
{
    TempType child;                /* 结点数据*/
    struct CTNode *next;           /* 下一个孩子结点*/
} *ChildPtr;

typedef struct                     /* 表头结构*/        
{
    TempType data;                 /* 结点数据*/
    ChiledPtr firstChild;          /* 孩子链表头指针*/
} CTBox;

typedef struct                       /* 树结构*/
{
    CTBox nodes[MAX_TREE_SIZE];      /* 结点数组*/
    int r, n;                        /* 树中根的位置和结点数*/
} CTree;

// ****************************************
// 孩子兄弟 表示法
// ****************************************
typedef struct CSNode                                    /* 结点结构*/
{
    TempType data;                                       /* 结点数据*/
    struct CSNode *firstchild, *rigthsib;                /* 第一个孩子结点， 该结点的右兄弟结点*/
} CSNode, *CSTree;

// ****************************************
// 二叉树的二叉链表 表示法
// ****************************************
typedef struct BiTNode                           /* 结点结构*/
{
    TempType data;                               /* 结点数据*/
    struct BiTNode *lchild, *rchild;             /* 左右孩子指针*/
} BiTNode, *BiTree;

// ****************************************
// 线索二叉树 表示法
// ****************************************
typedef enum{Link, Thread} PointerTag;           /* Link表示存储的是孩子结点， Thread表示存储的是前驱后继*/
typedef struct BiThrNode {
    TempType data;                               /* 结点数据*/
    struct BiThrNode *lchild, *rchild;           /* 左右孩子指针*/
    PointerTag LTag;                             /* 左标志*/
    PointerTag RTag;                             /* 右标志*/
} BiThrNode, *BiThrTree;
