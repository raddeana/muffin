#### nodejs c/c++ 扩展
Node的插件是动态连接到共享对象上的，可以使用C/C++编写，并能够使用require()语法，使用方法类似于其他的npm模块。
Node插件主要用于提供一个接口，使得Javascript能够使用到C/C++类库。

#### 组件和API
- V8:
  - V8：C++类库，NodeJS可以使用之以提供Javascript实现
  - V8提供了一个机制来创建对象，调用函数等。V8的API文档描述大部分在其头文件v8.h中已经写明，并且能够在线获得
- libuv：
  - 一个C类库，提供Node.js事件循环，其工作线程和所有基于平台的异步行为的实现。 
  - 同时它作为一个跨平台的抽象库，提供简单，类可移植方式访问所有主流操作系统以及许多常见的任务，例如文件系统交互、套接字、定时器和系统事件
- internal class
  - Node.js自身暴露一系列C/C++的API从而插件能够使用——其中最重要的是node::ObjectWrap这个类

#### 静态链接库
- Node.js包含了许多静态链接库，包括OpenSSL
- 这些类库存在于Node.js源码目录下deps/directory中
- 仅有v8和OpenSSL符号是有目的地再暴露，可能会被许多插件使用到

#### hello.cc
```c
#include <node.h>

namespace demo {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void Method (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "hello", Method);
  }

  NODE_MODULE(addon, init)
}  // namespace demo
```

#### binding.gyp
```gyp
{
  'targets': [{
      'target_name': 'addon',
      'sources': [
        'src/hello.cc'
      ],
      'dependencies': []
    }
  ]
}
```

将会在build目录下生成一个Makefile(Unix-like系统)或者一个vcxproj文件(Windows系统)还有一部分其他文件
```cmd
node-gyp configure
```

生成一个编译过的addon.node文件，这个文件会被放在build/Release/目录下
```cmd
node-gyp build
```

引用二进制的C++扩展
```javascript
const addon = require('./build/Release/addon')
// 'world'
console.log(addon.hello())
```
