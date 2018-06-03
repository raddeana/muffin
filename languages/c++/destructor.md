#### 析构函数
C++ 会自动析构

#### 无析构函数
```cpp
#include <iostream>
#include <string>

using namespace std;

class NoName {
    public:
        NoName():pstring(new std::string), i(0), d(0){}
    private:
        std::string * pstring;
        int i;
        double d;
};
```

#### 析构函数
```cpp
class NoName {
  public:
      NoName(): pstring(new std::string), i(0), d(0){
        cout << "构造函数被调用了！" << endl;
      }
      ~NoName();
}

NoName::~NoName(){
  cout << "析构函数被调用了！" << endl;
}
```

#### 完整代码：析构函数、赋值构造函数、赋值运算符
```cpp
#include <iostream>
#include <string>

using namespace std;

class NoName {
  public:
    NoName(): pstring (new std::string), i(0), d(0) {
      cout << "构造函数被调用了！" << endl;
    }
    
    NoName(const NoName & other);
    ~NoName();

    NoName& operator = (const NoName &rhs);

  private:
    std::string * pstring;
    int i;
    double d;
};

NoName::~NoName () {
  cout << "析构函数被调用了！" << endl;
}

NoName::NoName (const NoName & other) {
  pstring = new std::string;
  *pstring = *(other.pstring);
  
  i = other.i;
  d = other.d;
}

NoName& NoName::operator = (const NoName &rhs) {
  pstring = new std::string;
  *pstring = *(rhs.pstring);
  
  i = rhs.i;
  d = rhs.d;
  return *this;
}
```
