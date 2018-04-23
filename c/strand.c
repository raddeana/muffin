#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

struct String {
  char* ch;
  int length;
};

bool assignString(String* str, char* chars);
bool destroyString(String* str);
bool clearString(String* str);
void printString(String str);
bool insertString(String* str, String T, int locate);
bool copyString(String* str, String T);
int indexString(String str, String T);

// 给字符串重新赋值
bool assignString (String* str, char* chars){
  if (str->ch) {
    free(str->ch);
  }

  int i;
  char* c;
  for (i = 0, c = chars; *c; c++, i++);//获取字符串长度
  if (!i) { 
    str->ch = NULL; str->length = 0; return true; 
  } else {
    str->ch = (char*)malloc(i*sizeof(char));

    for (int j = 0; j < i; j++){
      str->ch[j] = chars[j];
    }

    str->length = i;
    return true;
  }
}

// 销毁字符串
bool destroyString (String* str){
  if (str) {
    free(str);
    str = NULL;
    return true;
  } else {
    return false;
  }
}

// 清空字符串
bool clearString (String* str){
  while (str->length){
    str->ch[str->length] = NULL;
    str->length --;
  }

  return true;
}

// 打印
void printString(String str){
    if (str.length)
    {
        for (int i = 0; i < str.length;i++)
        {
            printf("%c", str.ch[i]);
            
        }
        printf("\n");
    }
}

// 在原字符串str的第locate个元素前插入子字符串T
bool insertString (String* str, String T, int locate){
    if (locate < 0 || locate > str->length) {
      return false;
    }
    
    if (T.length){
        if (!(str->ch = (char*) {
          realloc(str->ch,(str->length + T.length)*sizeof(char)))) exit(-1);
        }
        
        for (int i = str->length - 1; i >= locate; i--) {
            str->ch[i + T.length] = str->ch[i];
        }
        
        for (int i = 0; i < T.length; i++) {
            str->ch[locate + i] = T.ch[i];
        }
        
        str->length += T.length;
    }
    
    return true;
}

// 把T的值赋给str
bool copyString (String* str, String T){
  if (str->ch) { 
    free(str->ch);
  }
  
  if (!&T) {
    str->ch = NULL;
    str->length = 0;
    return true; 
  } else {
    str->ch = (char*)malloc(T.length*sizeof(char));
    
    for (int i = 0; i < T.length; i++){
      str->ch[i] = T.ch[i];
    }
    
    str->length = T.length;
  }
  return true;
}

// 在原字符串str中搜索子字符串T的位置
// 查找失败返回-1
// 正常返回index为第一次出现T首字符的位置
int indexString (String str, String T) {
  int index = -1;
  int key = 0;
  int Hl = 0;

  if (T.length && str.length >= T.length){
    for (int i = 0; i <= str.length - T.length; i++) {
      if (str.ch[i] == T.ch[key]) {
        key ++;
        Hl ++;

        if (Hl >= T.length) {
          index = i - T.length+1; 
          return index;
        }
      } else {
        Hl = key = 0;
      }

      printf("i=%d, str是%c, T是%c, 核对T的第%d个字符, 已满足字符数%d\n", i, str.ch[i], T.ch[key], key, Hl);
    }
  }

  return index;
}
