#### 用户进程内存空间
每个进程都有完全属于自己的，独立的，不被干扰的内存空间，被分成几个段(Segment),分别是Text, Data, BSS, Heap, Stack

##### 命令
- top VIRT 各个进程内存空间的大小
- cat/proc/${id}/maps
- pmap –d

