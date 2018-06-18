#### 知识点
- long long, long, int 的长度： 
  - 32位系统：int（4个字节） long(4个字节) long long(8个字节)
  - 64位系统：int(4个字节) long (8个字节) long long（8个字节）
- 推荐的声明数组的方法： 
  - const int maxn = 100 + 10;
  - int A[maxn];
- c++ 中有bool类型，但是c中没有
- 注意是在c++中提供了“引用”即 &， 表示参数按照传递引用（by reference）的方式传递。
- c语言中的字符串，就是 字符数组
- 对于非string类型的数组 a，求数组的长度的方法： 
  - sizeof(a)/sizeof(a[0]);
  
#### 引用和指针的区别
- 指针：是一个变量，存储的是一个地址
- 引用：和原变量是一个东西，只不过是变量的一个别名而已
- 指针和引用的使用形式：

```cmd
int a = 1; int *p = &a;
int a = 1; int &q = a;
```

- 可以有const指针，但是不能有const引用
- 指针的值可以为NULL，但是引用的值不能为空
- 指针的值在初始化以后可以改变，即其指向的存储单元,但是引用初始化之后就不能在改变了
- sizeof(指针)：得到的是指针变量存储区的大小； sizeof(引用)：得到的是原变量存储区的大小

#### String常用函数
- length()和size()函数的功能是一样的，都是返回当前字符串的长度
- empty()判断字符串是否为空

#### Algorithm常用函数
- min(a,b):返回a,b中的最小值
- sort(a, a+size): 对数组a进行升序排序

#### 不定长数组vector
- vector a就是一个不定长数组。 
  - a.size(): 读取vector的大小
  - a.resize(): 改变vector的大小
  - a.push_back(): 向尾部添加元素
  - a.pop_back(): 删除最后一个元素
  - a.resize(n): 将n以后的元素删除
  - a.resize(n,value): 新分配出的空间用value初始化
  - a.clear(): 清空vector
- vector 是一个模板类，所以需要使用vector< int >a 或者 vector< double >b 这样的方式来声明里面装的元素的类型
- vector<int> a; 类似于一个int a[]数组
```cmd
vector<int> b(5,1);       // 声明一个大小为10，初始值为1的向量
vector<string> aa;

aa.push_back("a");
aa.push_back("b");
aa.push_back("c");
cout << "请输入值"; 

cin >> aa[2];             // 只有当 2号元素已经存在，才能这样用
//cin >> aa[3];  错误 3号元素不存在 

// 遍历的方法 
vector<string>:: iterator iter; 
for (iter = aa.begin(); iter != aa.end(); iter++) {
    cout << *iter << endl;
}

for (int i = 0; i < aa.size(); i++) {
    cout << aa[i] << endl;  //像使用数组一样，使用vector
}

// 常用函数

if(aa.empty()) {
    cout << "向量非空";
} 

vector<int>::iterator iter2 = b.begin();
b.insert(iter2, 1, 3); // 在1号元素的前面插入元素 
b.insert(b.begin(),100);

for (int i = 0; i < b.size(); i++) 
    cout << b[i] << endl;

b.erase(b.begin()+1);  // 将b.begin() + 1位置上的元素擦除 
```

#### 集合set
- 集合中每个元素至多出现一次

#### 映射map
- map就是从键（key）到 值（value）的映射
- 因为重载了[]运算符，map像是数组的 "高级版"

```cmd
map<string, int> name;
name["aa"] = 1;
name["bb"] = 2;
map<string,int>:: iterator iter;

for (iter = name.begin(); iter != name.end(); iter++) {
    cout << iter->first << " " << iter ->second << endl;
}  

cout << name["bb"];      // 输出为 2
cout <<name.count("bb"); // 输出为 1

// 即查看键为bb的键值对是否存在，如果存在，返回为1，如果不在返回为0,同时可以使用下面的方法，当bb不存在的时候，返回的是超过map末端的迭代器
iter = name.find("bb");
if (iter == name.end()) {
    cout << "不存在 ";
}

// 删除某个元素
name.erase("bb");
```

- 注意，参看某个键值对是否存在，一定不要使用下面的方式,因为这样会向map中插入元素
```cmd
cout << name_map["bb"];
```
- map和set都支持insert， find, count 和 remove 操作，并且可以按照从小到大顺序循环遍历其中的元素
- map也被称作是 "关联数组"
