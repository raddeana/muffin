#### 文件上传主要有两种方式:
- 使用Apache Commons FileUpload元件
- 利用Servlet3.0及其更高版本的内置支持

- commons-fileupload-1.2.2.jar
- commons-io-2.0.1.jar

#### MultipartFile接口
```java
import org.springframework.web.multipart.MultipartFile;

import java.io.Serializable;
import java.util.List;

public class Product implements Serializable {
  // 实现了这个接口，可以安全的将数据保存到HttpSession中
  
  private long id;
  private String name;
  private String description;
  private String price;
  
  // 在 Domain 类中加入 MultipartFile 类型的属性, 用来保存上传的文件
  private List<MultipartFile> images;
  public List<MultipartFile> getImages() {
    return images;
  }

  public void setImages(List<MultipartFile> images) {
    this.images = images;
  }
}
```

#### MultipartFile 接口提供了以下方法:
- byte[]: getBytes() Return the contents of the file as an array of bytes
- String: getContentType() Return the content type of the file
- InputStream: getInputStream()Return an InputStream to read the contents of the file from
- String: getName() Return the name of the parameter in the multipart form
- String: getOriginalFilename()Return the original filename in the client's filesystem
- long: getSize() Return the size of the file in bytes
- boolean: isEmpty() Return whether the uploaded file is empty
- that is, either no file hasbeen chosen in the multipart form or the chosen file has no content
- void: transferTo (File dest) Transfer the received file to the given destination file

```java
import Service.ProductService;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.util.List;

@Controller
public class Controller {
  private static final Log logger = LogFactory.getLog(ProductController.class);

  @RequestMapping(value = "/product_input")
  public String inputProduct (Model model) {
    logger.info("inputProduct called");
    model.addAttribute("product",new Product());
    return "ProductForm";
  }

  @RequestMapping(value = "/product_save", method = RequestMethod.POST)
  public String saveProduct(HttpServletRequest servletRequest, @ModelAttribute Product product, BindingResult bindingResult, Model model) {
    List<MultipartFile> files= product.getImages();
    System.out.println("文件数量是"+files.size());

    if(null != files && files.size() > 0) {
      for (MultipartFile file:files) {
        String fileName = file.getOriginalFilename(); // 获得文件名称
        File imagFile = new File(servletRequest.getServletContext().getRealPath("/image"),fileName);
        
        try {
          file.transferTo(imagFile);                    // 用于将文件写到服务器本地
        } catch (IOException e) {
          e.printStackTrace();
        }
      }
    }

    model.addAttribute("product", product);
    return "ProductDetails";
  }
}
```

#### 配置文件
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="http://www.springframework.org/schema/beans 
       http://www.springframework.org/schema/beans/spring-beans.xsd 
       http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd
       http://www.springframework.org/schema/mvc
       http://www.springframework.org/schema/mvc/spring-mvc-3.0.xsd">
  <context:component-scan base-package="controller" />
  <context:component-scan base-package="Service" />
  
  <!-- <mvc:annotation-driven> 元素注册用于支持基于注解的控制器的请求处理方法的Bean对象 -->
  <mvc:annotation-driven></mvc:annotation-driven>
  <bean id="viewResolver"
        class="org.springframework.web.servlet.view.InternalResourceViewResolver">
    <property name="prefix" value="/WEB-INF/view/" />
    <property name="suffix" value=".jsp" />
  </bean>
  
  <!-- resources 元素指示SpringMVC那些静态资源需要单独处理 -->
  <mvc:resources mapping="/image/**" location="/image/" />
  <bean id="multipartResolver" class="org.springframework.web.multipart.commons.CommonsMultipartResolver">
    <property name="maxUploadSize" value="2000000" />
  </bean>
</beans>
```
