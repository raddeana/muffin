#### Kryo入门
```xml
<dependency>
   <groupId>com.esotericsoftware</groupId>
   <artifactId>kryo</artifactId>
   <version>4.0.1</version>
</dependency>
```

```xml
<dependency>
   <groupId>com.esotericsoftware</groupId>
   <artifactId>kryo-shaded</artifactId>
   <version>4.0.1</version>
</dependency>
```

```java
class Student implements Serializable{  
  private String name;
}

public class Main {
  public static void main(String[] args) throws Exception {
    Kryo kryo = new Kryo();
    Output output = new Output(new FileOutputStream("student.db"));
    Student kirito = new Student("kirito");
    kryo.writeObject(output, kirito);
    output.close();
    Input input = new Input(new FileInputStream("student.db"));
    Student kiritoBak = kryo.readObject(input, Student.class);
    input.close();
    assert "kirito".equals(kiritoBak.getName());
  }
}
```
#### 三种读写方式
- 如果知道class字节码，并且对象不为空
```java
kryo.writeObject(output, someObject);
SomeClass someObject = kryo.readObject(input, SomeClass.class);
```
- 如果知道class字节码，并且对象可能为空
```java
kryo.writeObjectOrNull(output, someObject);
SomeClass someObject = kryo.readObjectOrNull(input, SomeClass.class);
```
- 如果实现类的字节码未知，并且对象可能为null
```java
kryo.writeClassAndObject(output, object);
Object object = kryo.readClassAndObject(input);
if (object instanceof SomeClass) {}
```

#### 支持的序列化类型
| boolean | Boolean | byte | Byte | char |
| --------   | -----:  | :----:  | :----:  | :----:  |
| Character | short | Short | int | Integer |
| long | Long | float | Float | double |
| Double | byte[] | String | BigInteger | BigDecimal |
| Collection | Date | Collections.emptyList | Collections.singleton | Map |
| StringBuilder | TreeMap | Collections.emptyMap | Collections.emptySet | KryoSerializable |
| StringBuffer | Class | Collections.singletonList | Collections.singletonMap | Currency |
| Calendar | TimeZone | Enum | EnumSet ||

#### Kryo支持以下的类型
- 枚举
- 集合、数组
- 子类/多态
- 循环引用
- 内部类
- 泛型

#### 线程安全
Kryo是线程不安全的，意味着每当需要序列化和反序列化时都需要实例化一次，或者借助ThreadLocal来维护以保证其线程安全
```java
private static final ThreadLocal<Kryo> kryos = new ThreadLocal<Kryo>() {
   protected Kryo initialValue () {
       Kryo kryo = new Kryo();
       // configure kryo instance, customize settings
       return kryo;
   }
}

// Somewhere else, use Kryo
Kryo k = kryos.get();
```

#### Kryo相关配置参数详解
```java
kryo.setRegistrationRequired(false);//关闭注册行为
kryo.setReferences(true);//支持循环引用
```

#### 常用Kryo工具类
```java
public class KryoSerializer {
   public byte[] serialize(Object obj) {
       Kryo kryo = kryoLocal.get();
       ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
       Output output = new Output(byteArrayOutputStream);
       kryo.writeClassAndObject(output, obj);
       output.close();
       
       return byteArrayOutputStream.toByteArray();
   }

   public <T> T deserialize(byte[] bytes) {
       Kryo kryo = kryoLocal.get();
       ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(bytes);
       Input input = new Input(byteArrayInputStream);
       input.close();
       return (T) kryo.readClassAndObject(input);
   }

   private static final ThreadLocal<Kryo> kryoLocal = new ThreadLocal<Kryo>() {
       @Override
       protected Kryo initialValue() {
           Kryo kryo = new Kryo();
           kryo.setReferences(true);
           kryo.setRegistrationRequired(false);
           return kryo;
       }
   }
}
```

- Kryo的Input和Output接收一个InputStream和OutputStream，Kryo通常完成字节数组和对象的转换，所以常用的输入输出流实现为ByteArrayInputStream/ByteArrayOutputStream
- writeClassAndObject和readClassAndObject配对使用在分布式场景下是最常见的，序列化时将字节码存入序列化结果中，便可以在反序列化时不必要传入字节码信息
- 使用ThreadLocal维护Kryo实例，这样减少了每次使用都实例化一次Kryo的开销又可以保证其线程安全
