#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;
typedef int Status;

typedef struct node {
    Elemtype data;
    struct node *next;
} ListNode;


typedef ListNode *LinkList;

// 初始化单链表
void InitList (LinkList L) {
    L->next = NULL;
}

// 创建单链表（尾插法）
void ListCreateTail (LinkList L, int n) {
    int i;
    ListNode *p, *r;

    r = L;
    printf("Input:");
    
    for (i = 1; i <= n; i++) {
        p = (ListNode *)malloc(sizeof(ListNode));
        scanf("%d", &p->data);
        r->next = p;
        r = p;
    }
    
    r->next = NULL;
}


// 创建单链表(头插法)
void ListCreateHead (LinkList L, int n) {
    ListNode *p, *s;
    int i;
    p = L;
    printf("Input:");
    
    for (i = 1; i <= n; i++) {
        s = (ListNode *)malloc(sizeof(ListNode));
        scanf("%d", &s->data);
        s->next = p->next;
        p->next = s;
    }
}

// 判断线性表是否为空
int ListEmpty (LinkList L) {
    if(L->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// 遍历单链表
void ListTra (LinkList L) {
    ListNode *p;
    p = L->next;
    
    while(p) {
        printf("%d ", p->data);
        p = p->next;
    }
    
    printf("\n");
}

// 销毁单链表
void ClearList (LinkList L) {
    ListNode *p, *q;
    p = L->next;
    
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    
    L->next = NULL;
}

// 返回 i 个位置的元素
Status GetElem (LinkList L, int i, Elemtype *e) {
    int j = 1;
    ListNode *p;
    
    if (ListEmpty(L)) {
        return 0;
    }
    
    p = L->next;
    
    while (p && j < i) {
       p = p->next;
       j++;
    }
    
    if(p == NULL && j < i) {
        return 0;
    }
    
    *e = p->data;
}

// 查找元素 e 的位置
int LocateElem (LinkList L, Elemtype e) {
    int i = 1;
    
    if (ListEmpty(L)) {
        return 0;
    }
    
    ListNode *p = L->next;
    while (p->next != NULL && p->data != e) {
        p = p->next;
        i++;
    }
    
    if (p ->next == NULL && p->data != e) {
        return 0;
    } else {
        return i;
    }
}

// 在 i 的位置上插入元素 e
Status ListInsert (LinkList L, int i, Elemtype e) {
    ListNode *p, *s, *r;
    int j = 1;
    if(ListEmpty(L)) {
        return 0;
    }
    
    if (i < 1) {
        return 0;
    }
    
    p = L->next;
    r = L;
    
    while (p->next != NULL && j < i) {
         p = p->next;
         r = r->next;
         j++;
    }
    
    if(p->next == NULL && j != i - 1) {
        return 0;
    }
    
    if(p->next == NULL && j == i - 1) {
        p = p->next;
        r = r->next;
    }
    
    s = (ListNode *)malloc(sizeof(ListNode));
    s->data = e;
    s->next = p;
    r->next = s;
    
    return 1;
}

// 删除第i个位置的元素
Status ListDelete (LinkList L, int i, Elemtype *e) {
    ListNode *p, *r;
    int j = 1;
    if (ListEmpty(L)) {
        return 0;
    }
    
    if (i < 1) {
        return 0;
    }
    
    p = L->next;
    r = L;
    
    while (p->next != NULL && j < i) {
        p = p->next;
        r = r->next;
        j++;
    }
    
    if (p->next == NULL && j != i) {
        return 0;
    }
    
    *e = p->data;
    r->next = p->next;
    free(p);
    
    return 1;
}

// 返回单链表的元素个数
int ListLength (LinkList L) {
    ListNode *p;
    int i = 1;
    
    if(ListEmpty(L)) {
        return 0;
    }
    
    p = L->next;
    while (p->next != NULL) {
        p = p->next;
        i++;
    }
    
    return i;
}

// 将所有在单链表Lb中但不在单链表La中的数据元素插入到La中
void Union (LinkList La, LinkList Lb) {
    int Len_La = ListLength(La), 
        Len_Lb = ListLength(Lb), i, k;
    
    Elemtype e;
    
    for(i = 1; i <= Len_Lb; i++) {
        GetElem(Lb, i, &e);
        
        if(!LocateElem(La, e)) {
            ListInsert(La, ++Len_La, e);
        }
    }
}

// 将单链表La分解成La，Lb两个单链表，La是奇数的元素，Lb是偶数的元素
void Split (LinkList La, LinkList Lb) {
    ListNode *p, *r, *s;
    p = La->next;
    r = La;
    s = Lb;
    
    while(p != NULL) {
        r->next = p;
        r = p;
        p = p->next;
        
        if (p != NULL) {
            s->next = p;
            s = p;
            p = p->next;
        }
    }
    
    r->next = NULL;
    s->next = NULL;
}

// 将递增有序表La，Lb，合并成递增有序表Lc
void MergeList (LinkList La, LinkList Lb, LinkList Lc) {
    ListNode *p, *s, *r;
    p = La->next;
    r = Lb->next;
    s = Lc;
    
    while(p != NULL && r != NULL) {
        if(p->data >= r->data) {
            s->next = r;
            s = r;
            r = r->next;
        } else {
            s->next = p;
            s = p;
            p = p->next;
        }
    }
    
    while (p == NULL && r !=NULL) {
        s->next = r;
        s = r;
        r = r->next;
    }
    
    while (p != NULL && r == NULL) {
        s->next = p;
        s = p;
        p = p->next;
    }
    
    s->next = NULL;
}

// p指向该单链表的任一结点，将p所指向的结点与其后继结点位置交换
void ExchangeNode (LinkList head, ListNode *p) {
    ListNode *s = head->next;
    if (p->next != NULL) {
        if (p == head->next) {
            head->next = p->next;
            p->next = head->next->next;
            head->next->next = p;
        } else {
            while (s->next != p) {
                s = s->next;
            }
            
            s->next = p->next;
            p->next = s->next->next;
            s->next->next = p;
        }
    }
}

// 返回
ListNode* Return (LinkList L, int i) {
    int j = 1;
    ListNode *p;
    
    if(i == 1) {
        return p = L->next;
    }
    
    p = L->next;
    
    while(p->next != NULL && j < i) {
        p = p->next;
        j++;
    }
    
    return p;
}

// 求递增有序的单链表La和Lb的交集Lc，使Lc也递增有序
void Bemixed (LinkList La, LinkList Lb, LinkList Lc) {
    ListNode *p, *r, *s;
    int Len_Lc = 0;
    Elemtype e;
    p = La->next;
    r = Lb->next;
    s = Lc;
    
    while (p != NULL && r != NULL) {
        if(p->data > r->data) {
            r = r->next;
        } else if (p->data == r->data) {
            s->next = p;
            s = p;
            r = r->next;
            p = p->next;
        } else {
            p = p->next;
        }
    }
    
    s->next = NULL;
}
