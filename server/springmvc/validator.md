#### Bean Validation 为 JavaBean 验证定义了相应的元数据模型和 API

#### Bean Validation 中内置的 constraint
- @Null	被注释的元素必须为 null
- @NotNull 被注释的元素必须不为 null
- @AssertTrue	被注释的元素必须为 true
- @AssertFalse 被注释的元素必须为 false
- @Min(value)	被注释的元素必须是一个数字，其值必须大于等于指定的最小值
- @Max(value)	被注释的元素必须是一个数字，其值必须小于等于指定的最大值
- @DecimalMin(value) 被注释的元素必须是一个数字，其值必须大于等于指定的最小值
- @DecimalMax(value) 被注释的元素必须是一个数字，其值必须小于等于指定的最大值
- @Size(max, min)	被注释的元素的大小必须在指定的范围内
- @Digits (integer, fraction)	被注释的元素必须是一个数字，其值必须在可接受的范围内
- @Past	被注释的元素必须是一个过去的日期
- @Future	被注释的元素必须是一个将来的日期
- @Pattern(value)	被注释的元素必须符合指定的正则表达式

####  Hibernate Validator 附加的 constraint
- @Email 被注释的元素必须是电子邮箱地址
- @Length	被注释的字符串的大小必须在指定的范围内
- @NotEmpty	被注释的字符串的必须非空
- @Range 被注释的元素必须在合适的范围内

```
import javax.validation.constraints.Past;
import javax.validation.constraints.Size;
import java.io.Serializable;
import java.util.Date;

public class Product implements Serializable {
  // 实现了这个接口，可以安全的将数据保存到HttpSession中
  private static final long serialVersionUID= 748392348L;

  /**
   * 序列化运行时使用一个称为 serialVersionUID 的版本号与每个可序列化类相关联，该序列号在反序列化过程中用于验证序列化对象的发送者和接收者是否为该对象加载了与序列化兼容的类。如果接收者加载的该对象的类的 serialVersionUID 与对应的发送者的类的版本号不同，则反序列化将会导致 InvalidClassException。可序列化类可以通过声明名为 "serialVersionUID" 的字段（该字段必须是静态 (static)、最终 (final) 的 long 型字段）显式声明其自己的 serialVersionUID：
   */
  private long id;

  // 被注释的元素的大小必须在指定的范围内
  @Size(min = 1, max = 10, message="不能超过十个字符")
  private String name;

  private String description;
  private String price;

  // 被注释的元素必须是一个过去的日期
  @Past
  private Date productionDate;

  public Date getProductionDate() {
    return productionDate;
  }

  public void setProductionDate(Date productionDate) {
    this.productionDate = productionDate;
  }

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getDescription() {
    return description;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public String getPrice() {
    return price;
  }

  public void setPrice(String price) {
    this.price = price;
  }

  public String toString() {
    return "Product{" +
            "id=" + id +
            ", name='" + name + '\'' +
            ", description='" + description + '\'' +
            ", price='" + price + '\'' +
            ", productionDate=" + productionDate +
            '}';
  }
}
```

#### 在要进行验证的控制器参数前加上@Valid
```java
@RequestMapping(value = "/product_save",method = RequestMethod.POST)
public String saveProduct(@Valid @ModelAttribute  Product product, BindingResult bindingResult,Model model) {
  logger.info("saveProduct called");

  if (bindingResult.hasErrors()) {
    List<ObjectError>objectErrors=bindingResult.getAllErrors();
    Iterator<ObjectError> it =objectErrors.iterator();
    while (it.hasNext()) {
      System.out.println(it.next().toString());
    }

    // FieldError fieldError = bindingResult.getFieldError();
    // logger.info("code:"+fieldError.getCode()+",object:"+fieldError.getObjectName()+",field:"+fieldError.getField());
    product.setProductionDate(null);
    model.addAttribute("product",product);
    return "ProductForm";
  }

  model.addAttribute("product",product);
  return "ProductForm";
}
```

#### 调用转换器，来规范日期时间
##### 编译转换器
```java
package converter;

import org.springframework.core.convert.converter.Converter;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;


public class MyConverter implements Converter<String,Date> { // <源类型，目标类型>
    private String dataPattern;
    
    public MyConverter (String dataPattern) {
      this.dataPattern=dataPattern;
      System.out.println("DataPattern is" + dataPattern);
    }
    
    public Date convert (String s) {
      try {
        SimpleDateFormat simpleDateFormat= new SimpleDateFormat(dataPattern);
        simpleDateFormat.setLenient(false);
        //设置日期/时间的解析是否不严格，为false表示严格

        return simpleDateFormat.parse(s);
      } catch (ParseException e) {
        e.printStackTrace();
      }

      return null;
    }
}
```

##### 在SpringMVC的xml文件中配置转换器
```xml
<mvc:annotation-driven conversion-service="conversionService"/>  
<!--【配置转换器】--> 
<bean id="conversionService" class="org.springframework.context.support.ConversionServiceFactoryBean">
  <property name="converters">
    <list>
      <bean class="converter.MyConverter">
        <constructor-arg type="java.lang.String" value="MM-dd-yyyy"/>
      </bean>
    </list>
  </property>
</bean>
```

