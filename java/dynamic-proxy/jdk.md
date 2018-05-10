#### class文件简介及加载
```java
package ClassLoader;  

public class Programmer {
  public void code() {
    System.out.println("I'm a Programmer,Just Coding.....");  
  }
}
```

```java
package ClassLoader;  

public class MyClassLoader extends ClassLoader {
  public Class<?> defineMyClass( byte[] b, int off, int len) {  
    return super.defineClass(b, off, len);  
  } 
}  
```

```java
package samples;  
  
import java.io.File;  
import java.io.FileInputStream;  
import java.io.FileNotFoundException;  
import java.io.IOException;  
import java.io.InputStream;  
import java.net.URL;  
  
public class MyTest {  
  
    public static void main(String[] args) throws IOException {  
        // 读取本地的class文件内的字节码，转换成字节码数组  
        File file = new File(".");  
        InputStream  input = new FileInputStream(file.getCanonicalPath()+"\\bin\\samples\\Programmer.class");  
        byte[] result = new byte[1024];  
          
        int count = input.read(result);  
        
        // 使用自定义的类加载器将 byte字节码数组转换为对应的class对象  
        MyClassLoader loader = new MyClassLoader();  
        Class clazz = loader.defineMyClass( result, 0, count);  
        
        // 测试加载是否成功，打印class 对象的名称  
        System.out.println(clazz.getCanonicalName());  
                  
        // 实例化一个Programmer对象  
        Object o= clazz.newInstance();  
        try {  
          // 调用Programmer的code方法  
          clazz.getMethod("code", null).invoke(o, null);  
        } catch (IllegalArgumentException | InvocationTargetException | NoSuchMethodException | SecurityException e) {  
          e.printStackTrace();  
        }  
    }  
}  
```
