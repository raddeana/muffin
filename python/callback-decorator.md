#### 装饰器
装饰器用来实现一种切面功能，即一些函数在调用前都必须实现的功能
n个参数的函数
```python
import functools

def log (func):
  @functools.wraps (func)
  def wrapper (*args, **kwargs):
    print ('call %s():' % func.__name__)
    return func (*args, **kwargs)
  return wrapper

@log
def now ():
  print ('2015-3-25')
```

#### 回调函数
回调函数就是一个通过函数指针调用的函数
```python
def test (num):
  for i in range (num):
    print ('hello, world')

def call (times, funcname):
  return funcname (times)
```
