#### 函数
```python
def foo():
  return 1
```

#### 作用域
```python
a_string = "This is a global variable"
def foo():
  print locals()
print globals() # doctest: + ELLIPSIS
{, 'a_string': 'This is a global variable'}
foo() # 2
{}
```

#### 变量解析规则
```python
a_string = "This is a global variable"
def foo ():
  print a_string # 1
foo ()
// This is a global variable
```

#### 变量生存周期
```python
def foo ():
  x = 1
foo ()
// 1
print x
// Traceback (most recent call last):
// NameError: name 'x' is not defined
```

#### 函数参数
```python
def foo(x):
  print locals()
foo(1)
// {'x': 1}
```

```python
def foo(x, y=0):  // 1
  return x - y
foo(3, 1)         // 2
foo(3)            // 3
// 3
foo()             // 4
// Traceback (most recent call last):
// TypeError: foo() takes at least 1 argument (0 given)
foo(y=1, x=3)     // 5
// 2
```

#### 嵌套函数
```python
def outer ():
  x = 1
  def inner ():
    print(x)   // 1
  inner()      // 2
outer()
// 3
```

#### 函数是python世界里的一级类对象
```python
// all objects in python inherit from a common base class
issubclass (int, object)
// true
def foo ():
  pass
foo.__class__ 
// 1
// <type 'function'>
issubclass(foo.__class__, object)
// true
```

```python
def add (x, y):
  return x + y
def sub (x, y):
  return x - y
def apply (func, x, y): // 1
  return func(x, y)     // 2
apply(add, 2, 1)        // 3
// 4
apply(sub, 2, 1)
// 5
```

```python
def outer():
  def inner():
    print "Inside inner"
return inner 
// 1
foo = outer() 

// 2
foo // doctest:+ELLIPSIS

// <function inner at 0x>
foo()
// Inside inner
```

#### 闭包
```python
def add (x, y):
  return x + y
def sub (x, y):
  return x - y
def apply (func, x, y): // 1
  return func(x, y)     // 2

apply(add, 2, 1)
// 3

apply(sub, 2, 1)
// 1
```

#### 装饰器
```python
def wrapper(func):
  def checker(a, b):    // 1
    if a.x < 0 or a.y < 0:
      a = Coordinate(a.x if a.x > 0 else 0, a.y if a.y > 0 else 0)
    if b.x < 0 or b.y < 0:
      b = Coordinate(b.x if b.x > 0 else 0, b.y if b.y > 0 else 0)
      ret = func(a, b)
    if ret.x < 0 or ret.y < 0:
      ret = Coordinate(ret.x if ret.x > 0 else 0, ret.y if ret.y > 0 else 0)
      return ret
  return checker

add = wrapper(add)
sub = wrapper(sub)

sub(one, two)
// Coord: {'y': 0, 'x': 0}
add(one, three)
// Coord: {'y': 200, 'x': 100}
```

#### 使用 @ 标识符将装饰器应用到函数
```python
@wrapper
def add (a, b):
  return Coordinate(a.x + b.x, a.y + b.y)
```

#### *args and **kwargs
```python
  def one(*args):
    print args # 1
  one()
  // ()
  one(1, 2, 3)
  // (1, 2, 3)
  def two(x, y, *args): # 2
    print x, y, args
  two('a', 'b', 'c')
  // a b ('c',)
```

```python
def add(x, y):
  return x + y
lst = [1, 2]
add(lst[0], lst[1]) // 1
// 3
add(*lst)           // 2
// 3
```

#### 更通用的装饰器
```python
def logger(func):
  def inner(*args, **kwargs):    // 1
    print ("Arguments were: %s, %s" % (args, kwargs))
    return func(*args, **kwargs) // 2
  return inner
```

```python
@logger
def foo1(x, y=1):
  return x * y

@logger
  def foo2():
    return 2

foo1(5, 4)
// Arguments were: (5, 4)
// 20

foo1(1)
// Arguments were: (1,)
// 1

foo2()
// Arguments were: ()
// 2
```
