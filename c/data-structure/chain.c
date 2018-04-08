/** 
 * 定义链式存储线性表的结构
 */  
typedef struct LNode  
{  
    int data;             // 数据域  
    struct LNode * next;  // 指向下一个节点的指针  
} LNode, *LinkList;

/** 
 * 逆位序输入n个元素的值,建立带表头结点的单链线性表L 
 * @param {LinkList} 指针
 * @param {int} 元素数量 
 * @return void 
 */  
void CreateList (LinkList &L,int n)  
{  
    L = (LinkList) malloc(sizeof(LNode));                 // 先建立一个带头结点的单链表  
    L -> next = NULL;  
    while (n--)  
    {  
        LinkList p = (LinkList) malloc(sizeof(LNode));    // 动态开辟新的结点  
        scanf("%d",&p->data);                             // 输入结点的值  
        p->next = L->next;  
        L->next = p;                                      // 插入到表头  
    }  
}

/** 
 * 查找单链表中第i个位置的值, 如果存在, 将值赋给e并返回OK, 不存在则返回ERROR 
 * @param: {LinkList} 头指针的引用 
 * @param {int} 查找的位置i 
 * @param {int} 引用
 * @return {int} 成功失败
 */ 
Status GetElem (LinkList &L, int i, int &e)  
{  
  LinkList p = L->next;  
  int j = 1;
  
  while (p&&j<i)             //寻找第i个位置  
  {  
      p = p->next;  
      j += 1;  
  }
  
  if (!p||j>i) {
    return ERROR; //i的位置不合法  
  }
    
  e = p->data;
  return OK;  
}

/**
 * 在带头结点的单链线性表L中第i个位置之前插入元素e 
 * @param {& LinkList} 头指针的引用 
 * @param {int} 插入位置
 * @param {int} 
 * @return {int} 
 */  
Status ListInsert(LinkList &L, int i, int e)  
{  
    LinkList p = L;  
    int j = 0;  
    while(p && j < i - 1)   //找到第i-1个位置  
    {  
        p = p->next;  
        j+=1;  
    }  
    if(j>i-1||!p)return ERROR;                        // i的位置不合法时,即i=0或i>Length(L)+1(表长加1)  
    LinkList q=(LinkList) malloc(sizeof(LNode));      // 动态开辟新的结点  
    q->data=e;          // 将e的值赋给新的结点  
    q->next=p->next;  
    p->next=q;          // 在i-1位置之后插入新的结点  
    return OK;
}

/** 
 * 在带头结点的单链线性表L中, 删除第i个元素, 并由e值返回 
 * @param {& LinkList} 头指针的引用 
 * @param {int} 删除元素的位置 
 * @param {int} 
 * @return {int} 
 */  
Status ListDelete (LinkList &L,int i,int &e)  
{  
    LinkList p = L;
    int j = 0;
    while(p && j < i - 1)                           // 找到第i-1个位置  
    {  
        p=p->next;  
        j+=1;  
    }  
    if(j>i-1||!(p->next)) return ERROR;             // 删除的位置不合理  
    LinkList q = p->next;  
    e = q->data;            // 将值赋给e  
    p->next = q->next;      // 删除第i个位置上的值  
    free(q);                // 释放i位置上的空间  
    return OK;
}

/**
 * 已知单链线性表La和Lb的元素按值非递减排列,归并La和Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列 
 * @param {& LinkList} linkList类型指针变量的引用 
 * @param {& LinkList} ```
 * @param {& LinkList} ```
 * @return void
 */  
void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc) {
  LinkList pa = La->next,
           pb = Lb->next,
           pc;
  
  Lc = pc = La;                           // 用La的头结点作为Lc的头结点  
  while(pa&&pb) {
      if(pa->data <= pb->data) {
          pc->next = pa;
          pc = pa;
          pa = pa->next;
      } else {
          pc->next = pb;
          pc = pb;  
          pb = pb->next;  
      }
  }
  
  pc->next = pa ? pa : pb;   // 插入剩余段  
  free(Lb);                  // 释放Lb的头结点  
}
