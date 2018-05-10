#### 动态代理
通过使用动态代理, 我们可以通过在运行时, 动态生成一个持有RealObject、并实现代理接口的Proxy, 同时注入我们相同的扩展逻辑
```java
public class DynamicProxyHandler implements InvocationHandler {
    private Object realObject;

    public DynamicProxyHandler(Object realObject) {
      this.realObject = realObject;
    }

    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
      // 代理扩展逻辑
      System.out.println("proxy do");
      return method.invoke(realObject, args);
    }
}
```

```java
public static void main(String[] args) {
  RealObject realObject = new RealObject();
  Action proxy = (Action) Proxy.newProxyInstance(ClassLoader.getSystemClassLoader(), new Class[]{Action.class}, new DynamicProxyHandler(realObject));
  proxy.doSomething();
}
```

#### 代理三要素：
- 真实对象: RealObject
- 代理接口: Action
- 代理实例: Proxy
