#### 预处理（preprocessing）是将文本替换的过程
> 将所有的#define删除，并且展开所有的宏定义
> 处理所有的条件编译指令，#ifdef #ifndef #endif等，就是带#的那些
> 处理#include，将#include指向的文件插入到该行处
> 删除所有注释
> 添加行号和文件标示，这样的在调试和编译出错的时候才知道是是哪个文件的哪一行
> 保留#pragma编译器指令，因为编译器需要使用它们

#### #define的基本用法
```cpp
#define PI 3.1415
```

```cpp
#define A 32+6
int i = 6*A;
```

#### 重复定义
```cpp
#include "vehicle.h"
#include "car.h"
```

##### 解决方法
###### 使用#ifdef #ifndef #endif
```cpp
#ifndef VEHICLE_H
#define VEHICLE_H
class vehicle{...}
#endif
```
###### 使用#pragma once
在include后面加上 #pragma once
```cpp
#include "vehicle.h"
#pragma once
#include "car.h"
```

#### #define简单函数
```cpp
#define MAX(a, b) a > b ? a : b
```
优点：无视类型
重复计算
```cpp
int i = MAX(7*6, 2);
int i = 7*6 > 2 ? 7*6 : 2;
```

#### #define的高级花式用法
使用 "\"，将 "\" 附在行尾，即可在预处理时将多行合并成一行，既保持了可读性，又能够define成功
```cpp
#define CLASS_DECLARE(c)\
const char* GetName(){\
    return #c;}\ 
static int s_num;\
int attribute1;\
int attribute2
```
当我们在多个类中使用 CLASS_DECLARE() 时，会出现link error
```cpp
#define CLASS_DEFINE(c)\
int c::s_num = 0;\
int c::attribute1 = 0;\
int c::attribute2 = 0
```

```cpp
Car.h
============================
class Car
{
  CLASS_DECLARE(Car);
}

Car.cpp
============================
CLASS_DEFINE(Car);
```

#### 宏定义中#号的花式用法
##### if else 代码块
```cpp
#define VAR 1
#if VAR == 1
//do something
#elif VAR == 2
//do something
#else 
//do something
#endif
```

##### "##" 连接
```cpp
#define HANDLER_WRAPPER(c) \
    static void c ## Wrapper(a) {
      return a;
    }

Class Car {
  HANDLER_WRAPPER(Car);//Car中拥有了CarWrapper()函数
}
```

