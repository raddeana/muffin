#### 包括下面的函数:
- make_heap: 根据指定的迭代器区间以及一个可选的比较函数, 来创建一个heap. O(N)
- push_heap: 把指定区间的最后一个元素插入到heap中. O(logN)
- pop_heap: 弹出heap顶元素, 将其放置于区间末尾. O(logN)
- sort_heap: 堆排序算法, 通常通过反复调用pop_heap来实现. N*O(logN)

#### C ++ 11加入了两个新成员:
- is_heap: 判断给定区间是否是一个heap. O(N)
- is_heap_until: 找出区间中第一个不满足heap条件的位置. O(N)

#### make_heap
STL中的通过make_heap创建的堆，默认是大顶堆(max heap)，即每个非叶子节点元素的值均不"小于"(默认使用<作为比较准则)其左右孩子节点
```cpp
// 1
template <class RandomIt>
void make_heap(RandomIt first, RandomIt last);

// 2
template <class RandomIt, class Compare>
void make_heap(RandomIt first, RandomIt last, Compare comp);
```

#### push_heap
make_heap类似，push_heap也有两个版本，其中有一个版本可以指定堆的比较函数，并且也是以一对迭代器指定的区间来进行操作
```cpp
// 1
template< class RandomIt >
void push_heap( RandomIt first, RandomIt last );

// 2
template< class RandomIt, class Compare >
void push_heap( RandomIt first, RandomIt last, Compare comp );
```

#### pop_heap
```cpp
// 1	
template<class RandomIt>
void pop_heap(RandomIt first, RandomIt last);

// 2
template<class RandomIt, class Compare>
void pop_heap(RandomIt first, RandomIt last, Compare comp);
```

#### sort_heap
sort_heap即经典的堆排序算法，通过每次弹出堆顶直到堆为空，依次被弹出的元素就组成了有序的序列了
STL中的priority_queue即使用heap的这个特性来实现
```cpp
// 1
template <class RandomIt>
void sort_heap(RandomIt first, RandomIt last);

// 2
template <class RandomIt, class Compare>
void sort_heap(RandomIt first, RandomIt last, Compare comp);
```

#### is_heap
```cpp
// (1)	(since C++11)
template <class RandomIt>
bool is_heap(RandomIt first, RandomIt last);

// (2)	(since C++11)
template <class RandomIt, class Compare>
bool is_heap(RandomIt first, RandomIt last, Compare comp);
```

#### is_heap_until
```cpp
// (1)	(since C++11)
template <class RandomIt>
RandomIt is_heap_until(RandomIt first, RandomIt last);

// (2)	(since C++11)
template <class RandomIt, class Compare>
RandomIt is_heap_until(RandomIt first, RandomIt last, Compare comp);
```

#### 总结
- 建堆，make_heap
- 堆操作: 增加元素(push_heap), 删除元素(pop_heap), 排序(sort_heap), 均要求区间已经是一个heap, 并且是与当前操作使用相同的排序准则
- is_heap, is_heap_until当做辅助判断函数来用
- 所有的heap算法操作的区间都需要是随机迭代器组成


