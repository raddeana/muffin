#### 异常处理语句 try... excpet... finally
```python
def div(a, b):
  try:
    print(a / b)
  except ZeroDivisionError:
    print("Error: b should not be 0 !!")
  except Exception as e:
    print("Unexpected Error: {}".format(e))
  else:
    print('Run into else only when everything goes well')
  finally:
    print('Always run into finally block.')
  
// tests
div(2, 0)
div(2, 'bad type')
div(1, 2)
```

```python
// Mutiple exception in one line
try:
  print(a / b)
except (ZeroDivisionError, TypeError) as e:
  print(e)
   
// Except block is optional when there is finally
try:
  open(database)
finally:
  close(database)
   
// catch all errors and log it
try:
  do_work()
except:    
  // get detail from logging module
  logging.exception('Exception Caught!')

  // get detail from sys.exc_info() method
  error_type, error_value, trace_back = sys.exc_info()
  print(error_value)
  raise
```

- except语句不是必须的，finally语句也不是必须的，但是二者必须要有一个，否则就没有try的意义了
- except语句可以有多个，Python会按except语句的顺序依次匹配你指定的异常，如果异常已经处理就不会再进入后面的except语句
- except语句可以以元组形式同时指定多个异常，参见实例代码
- except语句后面如果不指定异常类型，则默认捕获所有异常，你可以通过logging或者sys模块获取当前异常
- 如果要捕获异常后要重复抛出，请使用raise，后面不要带任何参数或信息
- 不建议捕获并抛出同一个异常，请考虑重构你的代码
- 不建议在不清楚逻辑的情况下捕获所有异常，有可能你隐藏了很严重的问题
- 尽量使用内置的异常处理语句来，替换 try/except 语句，比如 with 语句，getattr() 方法

#### 抛出异常 raise
如果你需要自主抛出异常一个异常，可以使用raise关键字，等同于 C# 和 Java 中的 throw 语句，其语法规则如下
```python
raise NameError("bad name!")
```

#### 自定义异常类型
Python中也可以自定义自己的特殊类型的异常
```python
class SomeCustomException(Exception):
   pass
```

#### 传递异常 re-raise Exception
捕捉到了异常，但是又想重新引发它（传递异常），使用不带参数的raise语句

```python
def f1():
  print (1 / 0)
def f2():
  try:
    f1()
  except Exception as e:
    // don't raise e !!!
    raise
```

#### 使用内置的语法范式代替 try/except
```python
try:
  test = Test()
  name = test.name  // not sure if we can get its name
except AttributeError:
  name = 'default'
```

```python
name = getattr(test, 'name', 'default')
```

- 只处理你知道的异常，避免捕获所有 异常然后吞掉它们
- 抛出的异常应该说明原因，有时候你知道异常类型也猜不出所以然的
- 避免在catch语句块中干一些没意义的事情
- 不要使用异常来控制流程，那样你的程序会无比难懂和难维护
- 如果有需要，切记使用finally来释放资源
- 如果有需要，请不要忘记在处理异常后做清理工作或者回滚操作
