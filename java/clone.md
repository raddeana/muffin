### 浅克隆
- 被复制的类需要实现Clonenable接口（不实现的话在调用clone方法会抛出CloneNotSupportedException异常)， 该接口为标记接口(不含任何方法)
- 覆盖clone()方法，访问修饰符设为public。方法中调用super.clone()方法得到需要的复制对象。（native为本地方法)

```java
class Student implements Cloneable{   
   private int number;     
   public int getNumber() {   
       return number;    
   }     
   public void setNumber(int number) {    
       this.number = number;    
   }   
 
   @Override    
   public Object clone() {  
       Student stu = null;    
       try{    
           stu = (Student)super.clone();    
       }catch(CloneNotSupportedException e) {    
           e.printStackTrace();   
       }    
       return stu;    
   }
}
```

### 深克隆
```java
package abc;    
class Address implements Cloneable {  
   private String add;    
   public String getAdd() {   
       return add;    
   }     
   public void setAdd(String add) {    
       this.add = add;    
   }     
 
   @Override   
   public Object clone() {   
       Address addr = null;    
       try{    
           addr = (Address)super.clone();   
       }catch(CloneNotSupportedException e) {    
           e.printStackTrace();    
       }    
       return addr;    
   }    
}     
 
class Student implements Cloneable{    
   private int number;     
   private Address addr;         
 
   public Address getAddr() {  
       return addr;    
   }   
 
   public void setAddr(Address addr) {    
       this.addr = addr;   
   }   
 
   public int getNumber() {    
       return number;    
   }   
   public void setNumber(int number) {    
       this.number = number;   
   }   
 
   @Override    
   public Object clone() {    
       Student stu = null;    
       try{    
           stu = (Student)super.clone();   //浅复制    
       }catch(CloneNotSupportedException e) {    
           e.printStackTrace();    
       }    
       stu.addr = (Address)addr.clone();   //深度复制    
       return stu;    
   }    
}    
```

##### 序列化
```java

```
