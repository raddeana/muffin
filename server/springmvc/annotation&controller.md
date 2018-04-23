#### 基于注解的控制器
处理器映射DefaultAnnotationHandlerMapping和处理器适配器AnnotationMethodHandlerAdapter来开启支持@Controller 和 @RequestMapping注解的处理器

- @Controller: 用于标识是处理器类
- @RequestMapping: 请求到处理器功能方法的映射规则
- @RequestParam: 请求参数到处理器功能处理方法的方法参数上的绑定
- @ModelAttribute: 请求参数到命令对象的绑定
- @SessionAttributes: 用于声明session级别存储的属性，放置在处理器类上，通常列出模型属性（如@ModelAttribute）对应的名称，则这些属性会透明的保存到session中；
- @InitBinder: 自定义数据绑定注册支持，用于将请求参数转换到命令对象属性的对应类型
- @CookieValue：cookie数据到处理器功能处理方法的方法参数上的绑定
- @RequestHeader：请求头（header）数据到处理器功能处理方法的方法参数上的绑定
- @RequestBody：请求的body体的绑定（通过HttpMessageConverter进行类型转换）
- @ResponseBody：处理器功能处理方法的返回值作为响应体（通过HttpMessageConverter进行类型转换）
- @ResponseStatus：定义处理器功能处理方法/异常处理器返回的状态码和原因
- @ExceptionHandler：注解式声明异常处理器
- @PathVariable：请求URI中的模板变量部分到处理器功能处理方法的方法参数上的绑定，从而支持RESTful架构风格的URI

新的@Contoller和@RequestMapping注解支持类:
- 处理器映射RequestMappingHandlerMapping
- 处理器适配器RequestMappingHandlerAdapter组合来代替处理器映射DefaultAnnotationHandlerMapping
- 处理器适配器AnnotationMethodHandlerAdapter
- 提供更多的扩展点

##### 控制器实现
```java
package cn.javass.chapter6.web.controller;  
// 省略import
// 将一个POJO类声明为处理器
@Controller       
// @RequestMapping
public class HelloWorldController {
    // 请求URL到处理器功能处理方法的映射
    @RequestMapping(value = "/hello")
    public ModelAndView helloWorld () {
        // 收集参数
        // 绑定参数到命令对象
        // 调用业务对象
        // 选择下一个页面
        ModelAndView mv = new ModelAndView();
        
        // 添加模型数据 可以是任意的POJO对象  
        mv.addObject("message", "Hello World!");  
        
        // 设置逻辑视图名，视图解析器会根据该名字解析到具体的视图页面  
        mv.setViewName("hello");  
        return mv;
    }
}
```

- 可以通过在一个POJO类上放置@Controller或@RequestMapping，即可把一个POJO类变身为处理器
- @RequestMapping(value = "/hello") 请求URL(/hello) 到处理器的功能处理方法的映射
- 模型数据和逻辑视图名的返回

##### Spring 配置文件 servlet.xml
```xml
<bean class="org.springframework.web.servlet.mvc.method.annotation.RequestMappingHandlerMapping" />  
<!-- 开始的注解 HandlerAdapter -->  
<bean class="org.springframework.web.servlet.mvc.method.annotation.RequestMappingHandlerAdapter" />  
```

##### 视图解析器的配置
使用 org.springframework.web.servlet.view.InternalResourceViewResolve

##### 处理器的配置
```xml
<bean class="cn.javass.chapter6.web.controller.HelloWorldController"/>
```

##### 处理器定义
- @Controller
- @RequestMapping

##### 窄化请求映射
```java
package cn.web.controller;  
@Controller  
@RequestMapping(value="/user")                 // 处理器的通用映射前缀  
public class HelloWorldController2 {  
  @RequestMapping(value = "/hello2")           // 相对于①处的映射进行窄化  
  public ModelAndView helloWorld () {  
    // 省略实现
  }
}
```

##### 请求映射
http请求信息包含六部分信息：
- 请求方法，如GET或POST，表示提交的方式
- URL，请求的地址信息
- 协议及版本
- 请求头信息（包括Cookie信息）
- 回车换行（CRLF）
- 请求内容区（即请求的内容或数据），如表单提交时的参数数据、URL请求参数
