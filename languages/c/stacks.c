#define maxsize 100

typedef struct SqStack {
    int data[maxsize];
    int top;
} SqStack;

// 初始化顺序栈
void initSqStack (SqStack *st){  
    st->top = -1;
}

// 判断栈是否为空
int SqStackEmpty (SqStack *st){  
    return (st -> top==-1 ? 1 : 0);  
}

// 进栈
int SqStackPush (SqStack *st, int x){  
    if(st->top == maxsize-1){  
        return 0;  
    }
    
    st -> data[++st->top] = x;  
    return 1;  
}

// 出栈
int SqStackPop(SqStack *st, int *x){  
    if(st -> top ==-1){  
        return 0;  
    }
    
    *x = st -> data[st -> top--];  
    return 1;
}

// ========================== >
typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode;

// 初始化链栈  
void initStack (Lnode *ln) {
    ln=(Lnode *)malloc(sizeof(Lnode));  
    ln->next = NULL;
}

// 判断链栈是否为空  
int StackEmpty(Lnode *ln){  
    return (ln -> next == NULL ? 1 : 0);  
}

// 进栈  
void StackPush(Lnode *ln, int x){  
    Lnode *p;
    p = (Lnode *)malloc(sizeof(Lnode));  
    if(p == NULL){  
        printf("ERROR");  
        exit(0);  
    }  
    p->next = NULL;  
    p->data = x;  
    p->next = ln->next;  
    ln->next = p;  
}

// 出栈  
int StackPop(Lnode *ln, int *x){  
    Lnode *p = ln->next;  
    
    if (p == NULL){  
        return 0;  
    }
    
    *x = p->data;  
    ln->next = p->next;  
    
    free(p);
    return 1;
}
