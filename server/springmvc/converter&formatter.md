#### Converter和Formatter都可以用于将一种对象类型转换成另一种对象类型

#### 编写Converter步骤:
- 编写一个实现了org.springframework.core.convert.converter.Converter接口的Java类
```java
public class MyConverter implements Converter<String,Date> {
                                            //<源类型，目标类型>
    private String dataPattern;
    public MyConverter (String dataPattern) {
      this.dataPattern=dataPattern;
      System.out.println("DataPattern is"+dataPattern);
    }
    
    public Date convert (String s) {
      try {
        SimpleDateFormat simpleDateFormat= new SimpleDateFormat(dataPattern);
        // 设置日期/时间的解析是否不严格，为false表示严格
        simpleDateFormat.setLenient(false);

        return simpleDateFormat.parse(s);
      } catch (ParseException e) {
        e.printStackTrace();
      }

      return null;
    }
}
```
- 在SpringMVC的配置文件中编写一个 ConversionService Bean
```xml
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
- 要给annotation-driven元素的 conversion-service 属性赋 bean 名称
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/mvc
           http://www.springframework.org/schema/mvc/spring-mvc-3.0.xsd">
    <context:component-scan base-package="controller"/>
    <context:component-scan base-package="Service"/>
    <!--
     <mvc:annotation-driven>
       元素注册用于支持基于注解的控制器的请求处理方法的Bean对象。
       详解：https://my.oschina.net/HeliosFly/blog/205343
    -->
    <mvc:annotation-driven conversion-service="conversionService"/>

    <bean id="viewResolver"
          class="org.springframework.web.servlet.view.InternalResourceViewResolver">
      <property name="prefix" value="/WEB-INF/view/"/>
      <property name="suffix" value=".jsp"/>
    </bean>

    <bean id="conversionService" class="org.springframework.context.support.ConversionServiceFactoryBean">
      <property name="converters">
        <list>
          <bean class="converter.MyConverter">
            <constructor-arg type="java.lang.String" value="MM-dd-yyyy"/>
          </bean>
        </list>
      </property>
    </bean>
</beans>
```

#### Formatter就像Converter一样，也是将一种类型转换成另外一种类型。但是，Formatter的源类型必须是String，而Converter则适用于任意的源类型
- 编写一个实现了org.springframework.format.Formatter接口的Java类
```java
public class DateFormatter implements org.springframework.format.Formatter<Date> {
  @Override 
  public Date parse (String s, Locale locale) throws ParseException {
    return null;
  }
  
  @Override 
  public String print (String s, Locale locale) {
    return null;
  }
}
```

- 在SpringMVC的配置文件中编写一个ConversionService Bean
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd             http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/mvc
        http://www.springframework.org/schema/mvc/spring-mvc-3.0.xsd">
  <context:component-scan base-package="controller" />
  <context:component-scan base-package="Service" />
  
  <!--
   <mvc:annotation-driven> 元素注册用于支持基于注解的控制器的请求处理方法的Bean对象
  -->
  <mvc:annotation-driven conversion-service="conversionService"/>

  <bean id="viewResolver" class="org.springframework.web.servlet.view.InternalResourceViewResolver">
    <property name="prefix" value="/WEB-INF/view/"/>
    <property name="suffix" value=".jsp"/>
  </bean>

  <!--需要配置此项来扫描Formatter-->
  <context:component-scan base-package="formatter"/>
  <bean id="formatterConversionService" 
        class="org.springframework.format.support.FormattingConversionServiceFactoryBean">
    <property name="formatters">
      <set>
        <bean class="formatter.DateFormatter">
          <constructor-arg type="java.lang.String" value="MM-dd-yyyy"/>
        </bean>
      </set>
    </property>
  </bean>
</beans>
```
