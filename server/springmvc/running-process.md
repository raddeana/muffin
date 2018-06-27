```seq
DispatcherServlet->DispatcherServlet: doService
DispatcherServlet->HandlerMapping: getHandlerMapping
HandlerMapping-->DispatcherServlet: 返回HandlerMapping
Note left of HandlerMapping: getHandler
HandlerMapping->HandlerExecutionChain: 生成HandlerExecutionChain
HandlerExecutionChain-->HandlerMapping: 返回实例
DispatcherServlet->HandlerInterceptor: 执行拦截preHandler方法
HandlerInterceptor-->DispatcherServlet: N/A
DispatcherServlet->HandlerAdapter: getHandlerAdapter
HandlerAdapter-->DispatcherServlet: 返回实例
DispatcherServlet->HandlerAdapter: handle(执行handle)
HandlerAdapter-->DispatcherServlet: 返回ModelAndView
HandlerAdapter->Handler: 执行
Handler-->HandlerAdapter: 返回ModelAndView
DispatcherServlet->DispatcherServlet: 执行render 渲染函数
```

#### Spring工作流程描述
- 用户向服务器发送请求，请求被Spring 前端控制Servelt DispatcherServlet捕获；
- DispatcherServlet对请求URL进行解析，得到请求资源标识符（URI）。然后根据该URI，调用HandlerMapping获得该Handler配置的所有相关的对象（包括Handler对象以及Handler对象对应的拦截器），最后以HandlerExecutionChain对象的形式返回；
- DispatcherServlet 根据获得的Handler，选择一个合适的HandlerAdapter（附注：如果成功获得HandlerAdapter后，此时将开始执行拦截器的preHandler(...)方法）
- 提取Request中的模型数据，填充Handler入参，开始执行Handler（Controller）；在填充Handler的入参过程中，根据你的配置，Spring将帮你做一些额外的工作；
- HttpMessageConveter： 将请求消息（如Json、xml等数据）转换成一个对象，将对象转换为指定的响应信息
  - 数据转换: 对请求消息进行数据转换；如 String 转换成 Integer、Double 等
  - 数据根式化: 对请求消息进行数据格式化；如将字符串转换成格式化数字或格式化日期等
  - 数据验证: 验证数据的有效性（长度、格式等），验证结果存储到 BindingResult 或 Error 中
- Handler执行完成后，向 DispatcherServlet 返回一个 ModelAndView 对象；
- 根据返回的 ModelAndView，选择一个适合的ViewResolver（必须是已经注册到Spring容器中的ViewResolver）返回给DispatcherServlet；
- ViewResolver 结合 Model 和 View，来渲染视图
- 将渲染结果返回给客户端
