# include <stdio.h>
# include <malloc.h>

# define bool int
# define True 1
# define False 0
# define ERROR -1
# define SIZE 100

/**
  - 初始化线性表
  - 删除线性表
  - 判定是否为空表
  - 线性表长度
  - 输出线性表全部元素
  - 按元素位置查找
  - 按元素值查找
  - 插入
  - 删除
  - 在末尾添加值
  - 删除末位置
*/

 typedef struct {
     int data[SIZE];
     int length;
 } seq_list;
 
// 初始化
void initList(seq_list* list) {
    // 分配存储线性表的空间
    list->data = (seq_list*)malloc(sizeof(seq_list));
    list->length = 0;
}

// 销毁线性表
void destroyList(seq_list* list) {
     free(list);
}
 
// 判断是否为空表
bool listEmpty(seq_list* list) {
   // 是空表返回 1， 不是0
   return (list->length == 0);
}
 
// 线性表长度
int listLength(seq_list* list) {
    return (list->length);
}
 
 // 输出线性表
 void dispList(seq_list* list) {
     int i;
     
     for (i=0; i<length; i++){
         printf("%d", list->data[i]);
     }
     
     printf("\n");
 }
 
 // key 位置元素
 int getElem(seq_list* list, int key) {
     int value = ERROR;
     
     if (-1 < key && key < list->length){
         n = list->data[key];
     }
     
     return n;
}
 
// 按值查找, 返回位置
int locateElem(seq_list* list, int value){
     int key = -1;
     int i;
     
     for (i=0; i < list->length; i++){
         if (list->data[i] == value){
             key = i;
             break;
         }
     }
     
     return key;
 }
 
 // 插入 value 到 key 位置
 bool listInsert(seq_list* list, int value, int key) {
    bool n = False;
    int i;
    // 表未满， 位置合法， 才可插入
    if ((list->length < SIZE) && (-1 < key && key < list->length)){
        for (i=list->length; i != key; i--){
            list->data[i+1] = list->data[i]
        }
        list->data[key] = value;
        n = True;
        list->length++;
    }
    
    return n;
}

// 删除 key 位置元素
bool listDelete(seq_list* list, int key){
    int i;
    bool n = False;
    if (-1 < key && key < list->length){
        for (i=key; i<list->length-1; i++){
            list->data[i] = list->data[i+1];
        }
        list->length--;
    }
    
    return n;
}

// 追加元素
bool listAppend(seq_list* list, int value) {
     bool n = Flase;
     // 表未满， 就可以追加
     if (list->length < SIZE){
         list->data[list->length] = value;
         list->length++;
         n = True;
     }
     
     return n;
}

// 删除末尾元素
bool listPop(seq_list* list) {
    bool n = Flase;
    if (list->length != 0){
        list->length--;
    }
}
