### SpringMVC 框架主要由四个接口组成
- DispatcherServlet
- HandlerMapping
- Controller
- ViewResolver

#### 前端控制器 DispatcherServlet
- 拦截符合特定格式的URL请求
- 初始化DispatcherServlet上下文对应的WebApplicationContext，并与业务层、持久化层建立联系
- 初始化SpringMVC的各个组件，并装配到DispatcherServlet中

```xml
<servlet>
  <servlet-name>springMVC</servlet-name>
  <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
  <init-param>
    <param-name>contextConfigLocation</param-name>
    <param-value>classpath*:/springMVC.xml</param-value>
  </init-param>
  <load-on-startup>1</load-on-startup>
</servlet>
<servlet-mapping>
  <servlet-name>springMVC</servlet-name>
  <url-pattern>/</url-pattern>
</servlet-mapping>
```

- 如果不指定 <param-value> 的值，则默认配置文件为/WEB-INF/<servlet-name>-servlet.xml
- <load-on-startup> 是启动顺序，通常让Servlet跟随Servlet容器一起启动
- <url-pattern> 定义要拦截的URL请求

拦截规则:
- *.xxx, 指定要拦截的特定类型, 最简单实用的方式, 并且不会拦截静态文件
- /, 使用REST风格进行拦截, 但是会导致静态文件被拦截不能正常显示
- /*, 不能像Struts那样使用, 会导致不能访问jsp

#### 处理器映射 HandlerMapping
负责完成请求到控制器的映射。在servlet的配置文件中，进行uri与控制器的映射
SpringMVC默认的处理器映射，直接将uri与实现类进行绑定，书写方便，但是耦合性高
```xml
<bean id="defaultHandlerMapping" class="org.springframework.web.servlet.handler.BeanNameUrlHandlerMapping"/>
<bean name="/hello.html" class="com.demo.ssm.HelloController"></bean>
```

使用SimpleUrlHandlerMapping，将uri与类的id进行绑定，彼此的耦合性低，更加灵活
```xml
<bean id="simpleUrlHandlerMapping" class="org.springframework.web.servlet.handler.SimpleUrlHandlerMapping">
  <property name="urlMap">
    <map>
      <entry key="/hello.html" value-ref="hello"></entry>
    </map>
  </property>
</bean>
<bean id="hello" class="com.demo.ssm.controller.HelloController"></bean>
```

#### 控制器 Controller
负责处理用户请求，完成之后返回ModelAndView对象给前端控制器
```
<bean id="multi" class="com.demo.ssm.controller.MultiController"></bean>
<bean id="simpleUrlHandlerMapping" class="org.springframework.web.servlet.handler.SimpleUrlHandlerMapping">
  <property name="urlMap">
    <map>
      <entry key="/multi-*.html" value-ref="multi"></entry>
    </map>
  </property>
</bean>
<bean id="multiActionController" class="org.springframework.web.servlet.mvc.multiaction.MultiActionController">
  <property name="methodNameResolver" ref="methodNameResolver"></property>
  <property name="delegate">
    <ref bean="multi" />
  </property>
</bean>

<bean id="methodNameResolver" class="org.springframework.web.servlet.mvc.multiaction.PropertiesMethodNameResolver">
  <property name="mappings">
    <props>
      <prop key="/multi-insert.html">insert</prop>
      <prop key="/multi-update.html">update</prop>
    </props>
  </property>
</bean>
```

#### 视图解析器 ViewResolver
负责对ModelAndView对象的解析，并查找对应的View对象

### 工作原理
- 将客户端请求提交给DispatcherServlet
- 根据<servlet-name>servlet.xml的配置，查找HandlerMapping
- 通过HandlerMapping找到处理请求的具体Controller
- Controller调用业务逻辑处理
- 处理完成之后，返回ModelAndView对象给DispatcherServlet
- 通过ViewResolver找到负责显示的具体View
- 由View将结果渲染到客户端

### 常用注解
- @Controller：声明Action组件，负责注册bean到Spring上下文
- @RequestMapping：用于为控制器指定可以处理的url请求
- @RequestParam：用于指定参数的name属性
- @RequestBody：用于读取Request请求的body部分数据
- @ResponseBody：用于将控制器方法返回的对象写入到Response对象的body数据区
- @PathVariable：用于指定url作为参数
- @Resource用于注入，( 由j2ee提供 ) 默认按名称装配
- @Autowired用于注入，(由spring提供) 默认按类型装配
- @ExceptionHandler：用于异常处理的方法
- @ControllerAdvice：用于使控制器成为全局的异常处理类
- @ModelAttribute：用于优先调用被注解的方法，或注解参数中的隐藏对象

### 拦截器
Spring提供了HandlerInterceptor接口和HandlerInterceptorAdapter适配器
- preHandle()，在Action之前执行的预处理，可以进行编码、安全控制等处理
- postHandle()，在生成View之前执行的后处理，调用了Service并返回ModelAndView，但未进行页面渲染，可以修改ModelAndView
- afterCompletion()，最后执行的返回处理，这时已经进行了页面渲染，可以进行日志记录、释放资源等处理

### 异常处理
- 可以在配置文件中设置SimpleMappingExceptionResolver，也可以实现HandlerExceptionResolver接口，编写自己的异常处理
- 通过exceptionMappings属性的配置，可以将不同的异常映射到不同的页面
- 通过defaultErrorView属性的配置，可以为所有异常指定一个默认的异常处理页面
