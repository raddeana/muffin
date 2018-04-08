# include<stdbool.h>  
# include<stdlib.h>  
# define maxsize 10
typedef int datatype;
  
//Sequence Stack 实现顺序栈，使用数组来实现  
struct stack  
{  
    datatype *data;  
    int top;  
}
  
typedef struct stack Stack;  
//创建栈
  
int realsize = maxsize;

/**
 * 初始化
 * @param {* Stack} 栈
 * @return void
 */
void init(Stack *s) {  
    // 分配内存
    s->data = (datatype *)malloc(sizeof(datatype)*maxsize);  
    s->top = -1;  
}
  
/**
 * 判断栈是否为空
 * @param {* Stack} 栈
 * @return {bool} 栈是否为空
 */
bool Empty (Stack *s) {
    if (s.top == -1) {
        return true;
    } else {
        return false;  
    }
}  
  
/**
 * 判断栈是否已满了  
 * @param {* Stack} 栈元素
 * @return {bool} 栈是否满了
 */
bool full (Stack *s) {
    if(s.top == realsize - 1) {  
        return true;  
    } else {  
        return false;  
    }  
}  
  
/**
 * 入栈
 * @param {* Stack} 栈指针
 * @param {datatype} 入栈元素
 * @return void
 */
void Push (Stack *s, datatype element) {  
    if(!full()) {  
        s.top ++;
        s.data[s.top] = element;  
    } else {  
        printf("栈满\n");  
    }  
}  
  
/**
 * 出栈
 * @param {* Stack} 栈指针
 * @return void
 */
void Pop (Stack *s) {
    if(!Empty()) {  
        s.top --;  
    } else {  
        printf("栈空\n");  
    }  
}
  
/**
 * 取栈顶元素  
 * @param {* Stack} 栈指针
 * @return void 
 */
datatype Top (Stack *s)  
{  
    if (!Empty()) { 
        return s.data[s.top];  
    } else {  
        printf("栈空\n");  
    }  
}

/**
 * 销毁栈
 * @param {* Stack} 栈指针
 * @return void
 */
void Destroy (Stack *s) {  
    s.top=-1;
}
