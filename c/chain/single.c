typedef struct Node
{
  int data;
  struct Node *pNext; 
} NODE, *PNODE;

PNODE createList (void)  
{  
    int len;
    int i;   
    int val;
    PNODE List;  
    PNODE pHead = (PNODE) malloc(sizeof(NODE))
    
    if (NULL == pHead)
    {
        printf("Memory allocation failure")
        exit(-1)
    }
    else
    {   PNODE pTail = pHead
        pHead->pNext = NULL
        
        for(i=0; i < len; i++)
        {
            PNODE p = (PNODE) malloc(sizeof(NODE))
            if(NULL == p)
            {
                printf("Memory allocation failure")
                exit(-1)
            }
            else
            {
                p->data = val
                pTail->pNext = p
                p->pNext = NULL
                pTail = p
            }
        }
    }
    return pHead;  
}  
