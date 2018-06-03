#### Handler
hanlder(Android 中称为 adapter，以下称 handler) 是 WeexSDK engine 中一个 service 的概念，它可以被 component、module 和其他的 handler 实现中调用

#### Handler 调用细节
- handler 提供了不同 App 和客户端解耦的能力，上层通过 interface(Android) 和 protocol(iOS) 约束方法
- handler 的实现者，只需要实现该 handler 对应的接口声明的方法即可
- 调用者不关注 handler 具体的实现，只通过接口获得需要的数据或者调用对应的 handler 方法
- 每个 protocol(interface) 对应的 handler 在 app 生命周期期间只有一个实例

#### 内置 handler
- navigationHandler
  - WeexSDK 内部提供了一个默认的 navigation 的 handler，该 handler 是在 navigation Module 中调用 push 和 pop 的一些操作时候被调用
- imageLoaderHandler
  - WeexSDK 图片组件需要从一个固定的 URI 中加载资源，这个加载行为也被封装到 image 的 handler 中，所以在接入 WeexSDK 时候，一定得提供图片 load 的handler
- AppMonitorHandler
  - 该 handler 是 WeexSDK 在渲染过程中性能统计，module 调用统计时候会将数据同步到该 handler 中，可以实现该 handler 将对应的数据上传到监控平台做性能的监控
- JSEXceptionHandler
  - JavaScript 在 runtime 可能会发生一些错误，首先由 JavaScript Engine 捕捉，然后抛出到 WeexSDK， WeexSDK 会通过 JSExceptionHandler 通知到外部调用
- URLRewriteHandler
  - image、video、web组件都在加载 URL 的时候会进行 URL 的重写，重写的规则就是由 URLRewriteHandler 提供，在这里 Handler 里面，可以将特定的 URL，重写为本地 URL 或者其他路径
