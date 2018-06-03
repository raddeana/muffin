汇编语言是二进制指令的文本形式，与指令是一一对应的关系

#### 寄存器和内存模型
CPU 本身只负责运算，不负责储存数据。
数据一般都储存在内存之中，CPU 要用的时候就去内存读写数据。
CPU 的运算速度远高于内存的读写速度，为了避免被拖慢，CPU 都自带一级缓存和二级缓存。
CPU 缓存可以看作是读写速度较快的内存
CPU 缓存还是不够快，另外数据在缓存里面的地址是不固定的，CPU 每次读写都要寻址也会拖慢速度。
除了缓存之外，CPU 还自带了寄存器（register），用来储存最常用的数据。
也就是说，那些最频繁读写的数据（比如循环变量），都会放在寄存器里面，CPU 优先读写寄存器，再由寄存器跟内存交换数据

#### 寄存器的种类
- EAX
- EBX
- ECX
- EDX
- EDI
- ESI
- EBP
- ESP

#### 内存模型：Heap
这种因为用户主动请求而划分出来的内存区域，叫做 Heap（堆）。
它由起始地址开始，从低位（地址）向高位（地址）增长。
Heap 的一个重要特点就是不会自动消失，必须手动释放，或者由垃圾回收机制来回收。

#### 内存模型：Stack
Stack 是由内存区域的结束地址开始，从高位（地址）向低位（地址）分配

#### 示例
```c
int add_a_and_b(int a, int b) {
   return a + b;
}

int main() {
   return add_a_and_b(2, 3);
}
```

```
_add_a_and_b:
   push   %ebx
   mov    %eax, [%esp+8] 
   mov    %ebx, [%esp+12]
   add    %eax, %ebx 
   pop    %ebx 
   ret  

_main:
   push   3
   push   2
   call   _add_a_and_b 
   add    %esp, 8
   ret
```

指令：
- push: push指令用于将运算子放入 Stack
- call: call指令用来调用函数
- mov: mov指令用于将一个值写入某个寄存器
- add: add指令用于将两个运算子相加
- pop: pop指令用于取出 Stack 最近一个写入的值
- ret: ret指令用于终止当前函数的执行，将运行权交还给上层函数
