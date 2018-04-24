#### web.xml 
```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <context-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>/WEB-INF/applicationContext.xml</param-value>
    </context-param>
    <listener>
        <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>
    </listener>

    <servlet>
        <servlet-name>dispatcher</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <load-on-startup>1</load-on-startup>
        <multipart-config>
            <max-file-size>20848820</max-file-size>
            <!--上传内文件的最大容量-->
            <max-request-size>418018841</max-request-size>
            <!--表示多部分HTTP请求允许的最大容量-->
            <file-size-threshold>1048576</file-size-threshold>
            <!--超过这个容量将会被写到磁盘中-->
            <location>/image/</location>
            <!--要将已上传的文件保存到磁盘中的位置-->
        </multipart-config>
    </servlet>

    <servlet-mapping>
        <servlet-name>dispatcher</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
    <!--Spring中文乱码拦截器-->
    <filter>
        <filter-name>setcharacter</filter-name>
        <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
        <init-param>
            <param-name>encoding</param-name>
            <param-value>UTF-8</param-value>
        </init-param>
    </filter>
    <filter-mapping>
        <filter-name>setcharacter</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>
 </web-app>
```

#### bean
```xml
<bean id="MultipartResolver" class="org.springframework.web.multipart.support.StandardServletMultipartResolver">
```

#### Domain：UploadFile
```java
import org.springframework.web.multipart.MultipartFile;
import java.io.Serializable;

public class UploadFile implements Serializable {
    private MultipartFile multipartFile;
    
    public MultipartFile getMultipartFile() {
      return multipartFile;
    }
    
    public void setMultipartFile(MultipartFile multipartFile) {
      this.multipartFile = multipartFile;
    }
}
```

#### Controller: Html5FileUploadController 类
```java
package controller;

import domain.UploadFile;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletRequest;
import java.io.File;

@Controller
public class Html5FileUploadController {
  private static final Log logger = LogFactory.getLog(Html5FileUploadController.class);

  @RequestMapping("/file_upload")
  public void saveFile (HttpServletRequest servletRequest, @ModelAttribute UploadFile file, BindingResult result) {
    MultipartFile multipartFile = file.getMultipartFile();
    String filename = multipartFile.getOriginalFilename();

    try {
      File file1 = new File(servletRequest.getServletContext().getRealPath("/image"),filename);
      multipartFile.transferTo(file1);
      System.out.println("已经写人本地文件:"+file1.getName());
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
```

执行脚本时，第一件事就是为4个变量分配空间: totalFileLength, totalUploaded, fileCount, filesUploaded;

- totalFileLength: 主要用于保存上传文件的总长度
- totalUploaded: 指示目前已经上传的字节数
- fileCount: 包含了要上传的文件数量
- fileUploaded: 指示了已经上传的文件数量
