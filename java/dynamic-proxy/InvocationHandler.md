#### InvocationHandler角色
- Proxy角色在执行代理业务的时候, 无非是在调用真正业务之前或者之后做一些 "额外" 业务
- 代理类处理的逻辑很简单: 在调用某个方法前及方法后做一些额外的业务
- 换一种思路就是: 在触发（invoke）真实角色的方法之前或者之后做一些额外的业务
- 为了构造出具有通用性和简单性的代理类, 可以将所有的触发真实角色动作交给一个触发的管理器, 让这个管理器统一地管理触发

#### 两种方式
- 一个比较直观的方式, 就是定义一个功能接口, 然后让 Proxy 和 RealSubject 来实现这个接口
- 还有比较隐晦的方式, 就是通过继承

#### JDK的动态代理创建机制
- 获取 RealSubject 上的所有接口列表
- 确定要生成的代理类的类名, 默认为: com.sun.proxy.$ProxyXXXX
- 根据需要实现的接口信息, 在代码中动态创建 该Proxy类的字节码
- 将对应的字节码转换为对应的class对象
- 创建 InvocationHandler 实例 handler, 用来处理Proxy所有方法调用
- Proxy 的 class 对象以创建的 handler 对象为参数，实例化一个proxy对象

```java
newProxyInstance(ClassLoader loader, Class<?>[] interfaces, InvocationHandler h)
```

```java
invoke(Object proxy, Method method, Object[] args)
```

#### JDK Example
##### Test
```java
package com.foo.proxy;  
  
import java.lang.reflect.InvocationHandler;  
import java.lang.reflect.Proxy;  
  
public class Test {
  public static void main(String[] args) {
    ElectricCar car = new ElectricCar();

    // 获取对应的ClassLoader
    ClassLoader classLoader = car.getClass().getClassLoader();

    // 获取ElectricCar 所实现的所有接口
    Class[] interfaces = car.getClass().getInterfaces();

    // 设置一个来自代理传过来的方法调用请求处理器，处理所有的代理对象上的方法调用
    InvocationHandler handler = new InvocationHandlerImpl(car);

    Object o = Proxy.newProxyInstance(classLoader, interfaces, handler);
    Vehicle vehicle = (Vehicle) o;
    vehicle.drive();
    Rechargable rechargeable = (Rechargable) o;
    rechargeable.recharge();
  }
}
```

##### InvocationHandlerImpl
```java
package com.foo.proxy;  
  
import java.lang.reflect.InvocationHandler;  
import java.lang.reflect.Method;  
  
public class InvocationHandlerImpl implements InvocationHandler {
    private ElectricCar car;
    
    public InvocationHandlerImpl(ElectricCar car) {
        this.car=car;
    }
      
    @Override  
    public Object invoke(Object paramObject, Method paramMethod, Object[] paramArrayOfObject) throws Throwable {
        System.out.println("You are going to invoke " + paramMethod.getName() + " ...");
        paramMethod.invoke(car, null);
        System.out.println(paramMethod.getName() + " invocation Has Been finished...");
        return null;
    }
}
```

##### ProxyUtils
```java
package com.foo.proxy;  
  
import java.io.FileOutputStream;  
import java.io.IOException;  
import java.lang.reflect.Proxy;  
import sun.misc.ProxyGenerator;  
  
public class ProxyUtils {
    /* 
     * 将根据类信息 动态生成的二进制字节码保存到硬盘中， 
     * 默认的是clazz目录下 
     * params:clazz 需要生成动态代理类的类 
     * proxyName:为动态生成的代理类的名称 
     */
    public static void generateClassFile(Class clazz, String proxyName) {  
        // 根据类信息和提供的代理类名称，生成字节码  
        byte[] classFile = ProxyGenerator.generateProxyClass(proxyName, clazz.getInterfaces());   
        String paths = clazz.getResource(".").getPath();  
        System.out.println(paths);  
        FileOutputStream out = null;    
          
        try {  
            // 保留到硬盘中  
            out = new FileOutputStream(paths + proxyName + ".class");    
            out.write(classFile);
            out.flush();
        } catch (Exception e) {  
            e.printStackTrace();
        } finally {
            try {
                out.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}  
```


#### cglib 生成动态代理类的机制 ---- 通过类继承
##### Programmer
```java
package dynamic;  
  
public class Programmer { 
  public void code() {
    System.out.println("I'm a Programmer, just Coding.....");  
  }
}
```

##### Hacker
```java
package dynamic;

import java.lang.reflect.Method;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;
/* 
 * 实现了方法拦截器接口 
 */
public class Hacker implements MethodInterceptor {  
    @Override  
    public Object intercept(Object obj, Method method, Object[] args, MethodProxy proxy) throws Throwable {  
        System.out.println("I am a hacker, Let's see what the poor programmer is doing Now...");
        proxy.invokeSuper(obj, args);
        System.out.println("Oh, what a poor programmer .....");
        return null;
    } 
}
```

```java
package dynamic;  
import net.sf.cglib.proxy.Enhancer;

public class Test {
  public static void main(String[] args) {  
    Programmer progammer = new Programmer();  

    Hacker hacker = new Hacker();  

    // cglib 中加强器，用来创建动态代理  
    Enhancer enhancer = new Enhancer();    

    // 设置要创建动态代理的类  
    enhancer.setSuperclass(progammer.getClass());    

    // 设置回调，这里相当于是对于代理类上所有方法的调用，都会调用CallBack，而Callback则需要实行intercept()方法进行拦截  
    enhancer.setCallback(hacker);  
    Programmer proxy = (Programmer)enhancer.create();  
    proxy.code();
  }
}
```

```java
package samples;  
  
import java.lang.reflect.Method;  
import net.sf.cglib.core.ReflectUtils;  
import net.sf.cglib.core.Signature;  
import net.sf.cglib.proxy.Callback;  
import net.sf.cglib.proxy.Factory;  
import net.sf.cglib.proxy.MethodInterceptor;  
import net.sf.cglib.proxy.MethodProxy;  
  
public class Programmer fa7aa2cd extends Programmer implements Factory {
  // Enchaner 传入的 methodInterceptor
  private MethodInterceptor CGLIB$CALLBACK_0;
  
  public final void code() {
    MethodInterceptor tmp4_1 = this.CGLIB$CALLBACK_0;  
    if (tmp4_1 == null) {  
      tmp4_1;  
      CGLIB$BIND_CALLBACKS(this);// 若callback 不为空，则调用methodInterceptor 的intercept()方法  
    }
    
    if (this.CGLIB$CALLBACK_0 != null)  
      return;  
      // 如果没有设置 callback 回调函数, 则默认执行父类的方法  
      super.code();
  }
}  
```

