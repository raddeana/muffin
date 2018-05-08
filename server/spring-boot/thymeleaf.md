#### Thymeleaf 介绍
Thymeleaf 是一款用于渲染 XML/XHTML/HTML 5 内容的模板引擎

#### Thymeleaf 特点
Thymeleaf 是一个跟 Velocity、FreeMarker 类似的模板引擎，它可以完全替代 JSP
- Thymeleaf 在有网络和无网络的环境下皆可运行，即它可以让美工在浏览器查看页面的静态效果，也可以让程序员在服务器查看带数据的动态页面效果
- Thymeleaf 开箱即用的特性
- Thymeleaf 提供 Spring 标准方言和一个与 SpringMVC 完美集成的可选模块，可以快速的实现表单绑定、属性编辑器、国际化等功能

#### 快速上手
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

#### application.properties
```
spring.thymeleaf.cache = false
```

#### Controller
```java
@Controller
public class HelloController {
    @RequestMapping("/")
    public String index(ModelMap map) {
        map.addAttribute("message", "http://www.ityouknow.com");
        return "hello";
    }
}
```

#### 页面布局
```html
<title th:text="${title}!=null?${title}:'Layout'">Layout</title>
```
