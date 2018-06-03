#### AOP常见概念
- Cross Cutting Concern: 横切性关注点, 补充我们OOP纵向编写的补充, 可以理解成遍布在系统的处理流程中的, 一种独立的服务
- Aspect: 对我们上面的 Cross Cutting Concern 的一种模块化, 也就是将其封装成一个类
- Advice: 对关注点的具体实现, 在切面的某个特定的连接点（Joinpoint）上执行的动作
- Pointcut: 定义了这个 Adivce 应用到那些 Joinpoint 上
- Jointpoint: 是 Advice 在应用程序上的执行点或者时机, 对Spring来说, 它就是方法调用
- Weave: 将 Advice 应用到 Target Object 上的整个过程叫织入
- Target Object: Advice应用的对象

#### 静态代理和动态代理showing
- 接口: com.qian.subject.Subject – 目标类RealSubject和代理类要实现的接口
- 目标类: com.qian.realsubject.RealSubject
- 静态代理类: com.qian.staticproxy.SubjectStaticProxy 
- 动态代理类: com.qian.dynamicproxy.SubjectDanamicProxy

```java
package com.qian.subject;
/**
 * 实际类RealSubject和代理类要实现的接口；
 * @author Administrator
 */
public interface Subject {
    public void addSub(String name, String password);
    public String findSub(String id);
}
```

```java
package com.qian.realsubject;
import com.qian.subject.*;

/**
 * Subject的实现类，并重写方法
 * @author Administrator
 *
 */
public class RealSubject implements Subject {
    public void addSub(String name, String password) {
        System.out.println("RealSubject.addSub()   "+ name+"  "+ password);
    }
    public String findSub(String id) {
        System.out.println("RealSubject.findSub()  "+ id);
        return "realSubject.findSub()";
    }
}
```

```java
package com.qian.staticproxy;

import com.qian.subject.Subject;

public class SubjectStaticProxy implements Subject {
    // Remark: 拿到实际对象的引用
    private Subject realSubject;
    
    // 这里我们通过构造函数拿到
    public SubjectStaticProxy(Subject realSubject){
        this.realSubject = realSubject;
    }
    
    public void addSub(String name, String password) {
        System.out.println("staticProxy do something before realSubject.add()");
        //调用实际对象的方法
        realSubject.addSub(name, password);
    }
    
    public String findSub(String id) {
        System.out.println("staticProxy do something before realSubject.findSub()");
        return realSubject.findSub(id);
    }
}
```

```java
package com.qian.danamicproxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class SubjectDanamicProxy implements InvocationHandler {
    // 实际要传入的realSubject;
    private Object realSubject;

    public Object getSubjectProxy(Object realSubject){
        this.realSubject = realSubject;
        
        // 都是realSubject的；
        Object proxy = Proxy.newProxyInstance(realSubject.getClass().getClassLoader(), realSubject.getClass().getInterfaces(), this);
        
        // 为了看看这个proxy和invoke(proxy)是否一样
        
        System.out.println("--proxy=Prox.new...() is "+proxy.getClass().getName());
        return proxy;
    }

    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        System.out.println("--proxy in invoke parameters is "+proxy.getClass().getName());
        checkInfo();
        Object result = method.invoke(realSubject, args);       
        return result;
    }

    private void checkInfo(){
        System.out.println("Doing some checking things before method invocation");
    }
}
```

#### Spring实现AOP的方式之Aspectj注解
- aspectj类: com.qian.springaopaspectj.CheckInfoAspect 
- xml文件: applicationContextAspectj.xml
```java
package com.qian.springaopaspectj;

import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;

/**
 * 将 代理类中 都要做得检查操作（横切性关注点模块化）
 * @author Administrator
 */
@Aspect // 对横切性关注点的模块化；
public class CheckInfoAspect {
    // 定义advice应用到那些连接点上，也就是advice在应用程序上自行的点或者时机
    // poincuName()就是给这个poincut起个名；
    @Pointcut("execution(* add*(..)) || execution(* find*(..))")
    private void poincutName(){}

    // advice也就是关注点的具体实现；before在连接点JointPoint的前面使用
    @Before("poincutName()")
    public void checkInfo(){
        System.out.println("Doing some checking things before method invocation");
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xmlns:tx="http://www.springframework.org/schema/tx"
     xmlns:aop="http://www.springframework.org/schema/aop"
     xmlns:context="http://www.springframework.org/schema/context"
     xsi:schemaLocation="
     http://www.springframework.org/schema/beans
     http://www.springframework.org/schema/beans/spring-beans-4.3.xsd
     http://www.springframework.org/schema/context
     http://www.springframework.org/schema/context/spring-context-4.3.xsd
     http://www.springframework.org/schema/tx
     http://www.springframework.org/schema/tx/spring-tx-4.3.xsd
     http://www.springframework.org/schema/aop
     http://www.springframework.org/schema/aop/spring-aop-4.3.xsd">
     
    <!-- 告诉JVM 我们用了aspectj的 annotation -->
    <aop:aspectj-autoproxy></aop:aspectj-autoproxy>
    <bean id="realSubject" class="com.qian.realsubject.RealSubject"/>
    <bean id="checkInfoAspect" class="com.qian.springaopanno.CheckInfoAspect"/>
</beans>
```

#### Spring实现AOP的方式之aop-config
- 目标类: com.qian.realsubject.RealSubject 
- Advice类: com.qian.springaopxml.CheckInfoAspectXml 
- xml文件: applicationContextConfig.xml

```java
package com.qian.springaopxml;

/**
 * 模拟将遍布在系统流程中的检查信息（关注点）模块化成一个Aspect
 * @author Administrator
 */
public class CheckInfoAspectXml {
    public void checkInfo(){
        System.out.println("Doing some checking things before method invocation");
    }
}
```
```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xmlns:tx="http://www.springframework.org/schema/tx"
     xmlns:aop="http://www.springframework.org/schema/aop"
     xmlns:context="http://www.springframework.org/schema/context"
     xsi:schemaLocation="
     http://www.springframework.org/schema/beans
     http://www.springframework.org/schema/beans/spring-beans-4.3.xsd
     http://www.springframework.org/schema/context
     http://www.springframework.org/schema/context/spring-context-4.3.xsd
     http://www.springframework.org/schema/tx
     http://www.springframework.org/schema/tx/spring-tx-4.3.xsd
     http://www.springframework.org/schema/aop
     http://www.springframework.org/schema/aop/spring-aop-4.3.xsd">

    <bean id="realSubjectCGLIB" class="com.qian.realsubject.RealSubjectCGLIB"/>
    <bean id="checkInfoAspectXml" class="com.qian.springaopxml.CheckInfoAspectXml"/>

    <aop:config>
        <aop:aspect id="checkInfoAspectXml" ref="checkInfoAspectXml">
            <aop:pointcut expression="execution(* com.qian.realsubject.RealSubjectCGLIB.add*(..))||execution(* find*(..))" id="pointcut"/>
            <aop:before method="checkInfo" pointcut-ref="pointcut"/>
        </aop:aspect>
    </aop:config>
</beans>
```

#### 当目标类没有继承接口时，我们用CGLIB，并配置aop-config
- 类: com.qian.realsubject.RealSubjectCGLIB 
- Advice类: com.qian.springaopxml.CheckInfoAspectXml 
- xml文件: applicationContextConfigCGLIB.xml
```java
package com.qian.realsubject;

/**
 * 没有实现任何接口，我们用CGLIB来动态代理它
 * @author Administrator
 */
public class RealSubjectCGLIB {
    public void addSub(String name, String password) {
        System.out.println("RealSubject.addSub()   "+ name+"  "+ password);
    }

    public String findSub(String id) {
        System.out.println("RealSubject.findSub()  "+ id);
        return "realSubject.findSub()";
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xmlns:tx="http://www.springframework.org/schema/tx"
     xmlns:aop="http://www.springframework.org/schema/aop"
     xmlns:context="http://www.springframework.org/schema/context"
     xsi:schemaLocation="
     http://www.springframework.org/schema/beans
     http://www.springframework.org/schema/beans/spring-beans-4.3.xsd
     http://www.springframework.org/schema/context
     http://www.springframework.org/schema/context/spring-context-4.3.xsd
     http://www.springframework.org/schema/tx
     http://www.springframework.org/schema/tx/spring-tx-4.3.xsd
     http://www.springframework.org/schema/aop
     http://www.springframework.org/schema/aop/spring-aop-4.3.xsd">
    <bean id="realSubjectCGLIB" class="com.qian.realsubject.RealSubjectCGLIB"/>
    <bean id="checkInfoAspectXml" class="com.qian.springaopxml.CheckInfoAspectXml"/>

    <aop:config>
        <aop:aspect id="checkInfoAspectXml" ref="checkInfoAspectXml">
            <aop:pointcut expression="execution(* com.qian.realsubject.RealSubjectCGLIB.add*(..))||execution(* find*(..))" id="pointcut"/>
            <aop:before method="checkInfo" pointcut-ref="pointcut"/>
        </aop:aspect>
    </aop:config>
</beans>
```

#### Spring实现AOP的方式之POJO
- 目标类: com.qian.realsubject.RealSubjectBean 
- Advice类: com.qian.springaopproxy.RealSubjectBeanHelper –实现了接口 AfterReturningAdvice, MethodBeforeAdvice 
- xml文件: applicationContextProxy.xml

```java
package com.qian.realsubject;

/**
 * 为了说明 CGLIB 和spring 可以在 JDK动态代理和CGLIB切换
 * 定义了一个没有实现任何借口的普通类；
 * @author Administrator
 */
public class RealSubjectBean {
    private String subName;
    private String password;

    public String getSubName() {
        return subName;
    }

    public void setSubName(String subName) {
        this.subName = subName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void addSubBean() {
        System.out.println("RealSubjectBean.addSubBean()   "+ subName+"  "+ password);
    }

    public String findSubBean(String subName) {
        System.out.println("RealSubjectBean.findSubBean()  "+ subName);
        return "realSubjectBean.findSubBean()";
    }
}
```

```xml
package com.qian.springaopproxy;

import java.lang.reflect.Method;

import org.springframework.aop.AfterReturningAdvice;
import org.springframework.aop.MethodBeforeAdvice;

/**
 * 使用spring 典型的动态代理来处理
 * @author Administrator
 */
public class RealSubjectHelper implements AfterReturningAdvice, MethodBeforeAdvice {
    public void before(Method arg0, Object[] arg1, Object arg2) throws Throwable {
        System.out.println(" RealSubjectHelper BeforMehtod: checking information");
    }

    public void afterReturning(Object arg0, Method arg1, Object[] arg2, Object arg3) throws Throwable {
        System.out.println(" RealSubjectHelper AfterMehtod: checking information");
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xmlns:tx="http://www.springframework.org/schema/tx"
     xmlns:aop="http://www.springframework.org/schema/aop"
     xmlns:context="http://www.springframework.org/schema/context"
     xsi:schemaLocation="
     http://www.springframework.org/schema/beans
     http://www.springframework.org/schema/beans/spring-beans-4.3.xsd
     http://www.springframework.org/schema/context
     http://www.springframework.org/schema/context/spring-context-4.3.xsd
     http://www.springframework.org/schema/tx
     http://www.springframework.org/schema/tx/spring-tx-4.3.xsd
     http://www.springframework.org/schema/aop
     http://www.springframework.org/schema/aop/spring-aop-4.3.xsd">

    <!-- (1)  注册Bean RealSubjectBean 和实现了 MethodBeforeAdvice AfterReturningAdvice接口的 RealSubjectHelper-->
    <bean id="realSubjectBean" class="com.qian.realsubject.RealSubjectBean">
        <property name="subName" value="zhangsan"/>
        <property name="password" value="zhangsan123"/>
    </bean>

    <bean id="realSubjectHelper" class="com.qian.springaopproxy.RealSubjectHelper"/>
    
    <!-- (2) 使用正则表达式来表示切点Pointcut 使用类 JdkRegexpMethodPointcut-->
    <bean id="pointcut" class="org.springframework.aop.support.JdkRegexpMethodPointcut">
        <property name="pattern" value=".*find.*"/>
    </bean>

    <!-- (3) 将横切点的具体实现 Advice 和  切点 Pointcut 联合起来 使用类 DefaultPointcutAdvisor-->
    <!--  
    <bean id="pointcutAdvisor" class="org.springframework.aop.support.DefaultPointcutAdvisor">
        <property name="pointcut" ref="pointcut"/>
        <property name="advice" ref="realSubjectHelper"/>
    </bean>
    -->
    <bean id="pointcutAdvisor" class="org.springframework.aop.support.DefaultPointcutAdvisor">
        <constructor-arg name="pointcut" ref="pointcut"/>
        <constructor-arg name="advice" ref="realSubjectHelper"/>
    </bean>

    <!--  (4) 生成目标对象RealSubjectBean的代理对象 使用类  ProxyFactoryBean -->
    <bean id="realSubjectBeanProxy" class="org.springframework.aop.framework.ProxyFactoryBean">
        <!-- 目标对象 target -->
        <property name="target" ref="realSubjectBean"/>
        <!-- 拦截方法 -->
        <property name="interceptorNames">
            <list>
                <value>pointcutAdvisor</value>
            </list>
        </property>
    </bean>
</beans>
```

#### xml简化
```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xmlns:tx="http://www.springframework.org/schema/tx"
     xmlns:aop="http://www.springframework.org/schema/aop"
     xmlns:context="http://www.springframework.org/schema/context"
     xsi:schemaLocation="
     http://www.springframework.org/schema/beans
     http://www.springframework.org/schema/beans/spring-beans-4.3.xsd
     http://www.springframework.org/schema/context
     http://www.springframework.org/schema/context/spring-context-4.3.xsd
     http://www.springframework.org/schema/tx
     http://www.springframework.org/schema/tx/spring-tx-4.3.xsd
     http://www.springframework.org/schema/aop
     http://www.springframework.org/schema/aop/spring-aop-4.3.xsd">

    <!-- (1)  注册Bean RealSubjectBean 和实现了 MethodBeforeAdvice AfterReturningAdvice接口的 RealSubjectHelper-->
    <bean id="realSubjectBean" class="com.qian.realsubject.RealSubjectBean">
        <property name="subName" value="zhangsan"/>
        <property name="password" value="zhangsan123"/>
    </bean>
    <bean id="realSubjectHelper" class="com.qian.springaopproxy.RealSubjectHelper"/>


    <!-- (2) 使用正则表达式来表示切点Pointcut 和 横切点的具体实现Advice自动联合 使用类 RegexpMethodPointcutAdvisor-->
    <bean id="pointcutAdvisor" class="org.springframework.aop.support.RegexpMethodPointcutAdvisor">
        <property name="pattern" value=".*find.*"/>
        <property name="advice" ref="realSubjectHelper"/>
    </bean>

    <!--  (3) 生成目标对象RealSubjectBean的代理对象 使用类自动代理生成器 DefaultAdvisorAutoProxyCreator-->
    <bean id="realSubjectBeanProxy" class="org.springframework.aop.framework.autoproxy.DefaultAdvisorAutoProxyCreator"/>
</beans>
```

#### 最主要的Client类
```java
package com.qian.client;

import com.qian.realsubject.RealSubject;
import com.qian.realsubject.RealSubjectBean;
import com.qian.realsubject.RealSubjectCGLIB;
import com.qian.staticproxy.SubjectStaticProxy;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.qian.danamicproxy.SubjectDanamicProxy;
import com.qian.subject.Subject;

/**
 * Client主测试类
 * @author Administrator
 */
public class Client {

    // 最通俗易懂的办法 但是耦合度太高了
    public static void subjectImpl(){
        Subject subject = new RealSubject();
        subject.addSub("qian", "520");
        subject.findSub("511");
    }

    // 静态代理
    public static void staticProxy(){

        Subject subject = new SubjectStaticProxy(new RealSubject());
        subject.addSub("name", "password");
        subject.findSub("123");
    }

    // 动态代理
    public static void dynamicProxy(){

        Object proxy = new SubjectDanamicProxy().getSubjectProxy(new RealSubject());
        Subject subject = (Subject)proxy;
        subject.addSub("zhangsan", "pass123");
        subject.findSub("134");
    }

    // 使用 Aspectj.jar 和Aspectjweaver.jar 进行注释 推崇
    public static void springaopAspectj(){
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContextAspectj.xml");
        Subject subject = (Subject) context.getBean("realSubject");
        subject.addSub("spring", "aop");
        subject.findSub("1231");
    }

    // 使用spring的aop-config进行配置、推崇
    public static void springaopConfig(){
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContextConfig.xml");
        Subject subject = (Subject) context.getBean("realSubject");
        subject.addSub("spring", "aop");
        subject.findSub("1231");
    }

    // 对没有实现接口的类使用CGLIB 并使用spring的aop-config进行配置
    public static void springaopConfigCGLIB(){
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContextAopConfigCGLIB.xml");
        RealSubjectCGLIB subject = (RealSubjectCGLIB) context.getBean("realSubjectCGLIB");
        subject.addSub("spring", "aop");
        subject.findSub("1231");
    }

    // spring AOP动态代理
    public static void springaopProxy(){
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContextProxy.xml");
        RealSubjectBean subjectBean = (RealSubjectBean) context.getBean("realSubjectBeanProxy");
        subjectBean.addSubBean();
        subjectBean.findSubBean("springaop4");
    }

    // spirng AOP自动进行匹配的动态代理
    public static void springaopProxyV2(){
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContextProxyV2.xml");
        RealSubjectBean subjectBean = (RealSubjectBean) context.getBean("realSubjectBean");
        subjectBean.addSubBean();
        subjectBean.findSubBean("springaop4");
    }
    
    public static void main(String[] args) {
        //subjectImpl();
        //staticProxy();
        //dynamicProxy();
        //springaopConfig();
        //springaopConfigCGLIB();
        //springaopProxy();
        //springaopProxyV2();
    }
}
```

#### pom
```xml
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>springaop</groupId>
  <artifactId>SpringAop</artifactId>
  <version>0.0.1-SNAPSHOT</version>
  
  <dependencies>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-core</artifactId>
        <version>4.3.0.RELEASE</version>
    </dependency>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context</artifactId>
        <version>4.3.0.RELEASE</version>
    </dependency>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-aop</artifactId>
        <version>4.3.0.RELEASE</version>
    </dependency>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-aspects</artifactId>
        <version>4.3.0.RELEASE</version>
    </dependency>
    <dependency>
            <groupId>org.aspectj</groupId>
            <artifactId>aspectjrt</artifactId>
            <version>1.8.5</version>
    </dependency>
    <dependency>
        <groupId>org.aspectj</groupId>
        <artifactId>aspectjweaver</artifactId>
        <version>1.8.5</version>
    </dependency>
    <dependency>
        <groupId>cglib</groupId>
        <artifactId>cglib</artifactId>
        <version>3.2.0</version>
    </dependency>
  </dependencies>
</project>
```
