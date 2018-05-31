struct chunk {
  char signature[4];
  struct chunk *next;
  int state;
  int size;
}

void *tlsf_create_with_pool(unit8_t * heap_base, size_t heap_size) 
{
  chunk_head = (struct chunk *)heap_base;
  strncpy(chunk_head->signature, "OSEX", 4);
  chunk_head->next = NULL;
  chunk_head->state = FREE;
  chunk_head-size = heap_size;
  return NULL;
}

void *malloc(size_t size)
{
    if(size == 0) {
        return NULL;
    }

    struct chunk* selected; 
    struct chunk* next; 
    void* ret;  //返回的指针ret(return的缩写)

    // 首次适应
    selected = chunk_head;
    while(selected)
    {
        if(selected->state == FREE) 
        {
            // 要分配的内存大小与当前块大小符合
            if(selected->size == (size + sizeof(struct chunk)))
            {
                selected->state = USED;
                ret = ((uint8_t *)selected) + sizeof(struct chunk);
                return ret;
            }
            
            // 找到合适大小的块且为未使用的块
            if(selected->size > size + 2 * sizeof(struct chunk))
            {
                int size_temp = selected->size;
                selected->size = size + sizeof(struct chunk);
                selected->state = USED;

                ret = ((uint8_t *)selected) + sizeof(struct chunk);

                next = (struct chunk*)((uint8_t *)selected + sizeof(struct chunk) + size);
                next->state = FREE;
                next->size = size_temp - selected->size;
                strncpy(next->signature, "OSEX", 4);
                next->next = selected->next;

                selected->next = next;
                return ret;
            }
        }
        
        selected = selected->next;
    }
    
    return NULL;
}

void free(void *ptr)
{
    if(ptr == NULL) {
        return;
    }

    // 得到指针对应的块
    struct chunk *achunk=(struct chunk *)(((uint8_t *)ptr)-sizeof(struct chunk));

    if(strncmp(achunk->signature,"OSEX",4)) {
        return;
    }

    achunk->state = FREE;

    // 合并后一个state为FREE的块
    if(achunk->next != NULL)
    {
        if(achunk->next->state == FREE)
        {
            achunk->size = achunk->size + achunk->next->size;
            achunk->next = achunk->next->next; 
        }
    }

    // 合并前一个state为FREE的块
    if(achunk == chunk_head)
        return;

    struct chunk* before = chunk_head;
    struct chunk* selected = chunk_head->next;
    
    // 找到当前块的前一块指针
    while(selected != achunk)
    {
        before = selected;
        selected = selected->next;
    }
    
    if(before->state == FREE)
    {
        before->size = before->size + achunk->size;
        before->next = achunk->next;
    }
    
    return;
}

void *calloc(size_t num, size_t size)
{
    char* a = malloc(num * size);
    if(a == NULL)
        return NULL;
    int i;
    int j;
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < size; j++)
            a[size * i + j] = 0;
    }
    return a;
}

void *calloc(size_t num, size_t size)
{
    char* a = malloc(num * size);
    if(a == NULL) {
        return NULL;
    }
    
    int i;
    int j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < size; j++)
            a[size * i + j] = 0;
    }
    
    return a;
}

void *realloc(void *oldptr, size_t size)
{   
    //如果oldptr是NULL，该函数等价于malloc(size)
    if(oldptr == NULL)
        return malloc(size);

    // 得到指针对应的块
    struct chunk *achunk=(struct chunk *)(((uint8_t *)oldptr)-sizeof(struct chunk));
    
    // 验证oldptr的有效性
    if(strncmp(achunk->signature,"OSEX",4)) {
        return NULL;
    }

    // 如果size是0，该函数等价于free(oldptr)
    if(size == 0)
    {
        free(oldptr);
        return NULL;
    }
    
    char* a = malloc(size);
    char* b = (char*) oldptr;
    
    if(a == b) {
        return b;
    }

    if(size >= achunk->size) {
        // 如果新内存块比较大，复制整个旧内存块，而且不用初始化多出来的那部分
        int i;
        for( i = 0; i < (achunk->size - sizeof(struct chunk)); i++)
            a[i] = b[i];

        free(b);
        return a;
    } else {
        // 如果新内存块比较小，只复制旧内存块的前面部分
        int i;
        for( i = 0; i < (size - sizeof(struct chunk)); i++)
            a[i] = b[i];
        free(b);
        return a;
    }
}
