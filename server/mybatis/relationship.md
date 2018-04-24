#### 测试demo
```java
import java.io.InputStream;
import java.util.List;
 
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Before;
import org.junit.Test;
 
import com.ys.bean.Person;
 
public class MyBatisTest {
    SqlSession session;
     
    @Before
    public void beforeLoadXML(){
        //加载 mybatis 配置文件
        InputStream inputStream = MyBatisTest.class.
                getClassLoader().getResourceAsStream("mybatis-configuration.xml");
        //构建sqlSession的工厂
        SqlSessionFactory sqlSessionFactory =
                new SqlSessionFactoryBuilder().build(inputStream);
        //根据 sqlSessionFactory 产生 session
        session = sqlSessionFactory.openSession();
    }
     
    // 根据 pid 查询 person 表中的数据
    @Test
    public void testSelectById(){
        // 这个字符串有 personMapper.xml 文件中 两个部分构成
        // <mapper namespace="com.ys.bean.personMapper"> 的 namespace 的值
        // <select id="selectPersonById" > id 值
        String statement = "com.ys.bean.personMapper"+".selectPersonById";
        Person p = session.selectOne(statement, 1);
        System.out.println(p);
        session.close();
    }
     
    // 查询person 表所有数据
    @Test
    public void testGetAllPerson(){
        String statement = "com.ys.bean.personMapper.getAllPerson";
        List<Person> listPerson = session.selectList(statement);
        System.out.println(listPerson);
        session.close();
    }
     
    // 根据id更新数据
    @Test
    public void updateById(){
        String statement = "com.ys.bean.personMapper.updatePersonById";
        Person p = new Person();
        p.setPid(1);
        p.setPname("aaa");
        p.setPage(11);
        session.update(statement, p);
        session.commit();
        session.close();
    }
     
    // 向 person 表插入一条数据
    @Test
    public void addPerson(){
        String statement = "com.ys.bean.personMapper.addPerson";
        Person p = new Person();
        //由于我们设置了主键的自增长机制，故这里不需要手动设置 pid 的值
        //p.setPid(1);
        p.setPname("add");
        p.setPage(11);
        session.insert(statement, p);
        session.commit();
        session.close();
    }
     
    // 根据 pid 删除person 表中的数据
    @Test
    public void deletePersonById(){
        String statement = "com.ys.bean.personMapper.deletePersonById";
        session.delete(statement, 1);
        session.commit();
        session.close();
         
    }
}
```

#### 注解配置
```xml
package com.ys.annocation;
 
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
 
import com.ys.bean.Person;
 
public interface PersonMapper { 
    @Insert("insert into person(pid,pname,page) values(#{pid},#{pname},#{page})")
    public int add(Person person);
     
    @Select("select * from person where pid = #{pid}")
    public Person getPerson(int pid);
     
    @Update("update person set pname=#{pname},page=#{page} where pid = #{pid}")
    public int updatePerson(Person preson);
    
    @Delete("delete from person where pid=#{pid}")
    public int deletePerson(int pid);
}
```

#### 一对一 基于xml配置
##### Teacher
```java
public class Teacher {
    private int tid;
    private String tname;
    private Classes classes;
     
    public int getTid() {
        return tid;
    }
    
    public void setTid(int tid) {
        this.tid = tid;
    }
    
    public String getTname() {
        return tname;
    }
    
    public void setTname(String tname) {
        this.tname = tname;
    }
    
    public Classes getClasses() {
        return classes;
    }
    
    public void setClasses(Classes classes) {
        this.classes = classes;
    }
    
    @Override
    public String toString() {
        return "Teacher [tid=" + tid + ", tname=" + tname + ", classes=" + classes + "]";
    }
}
```

##### Classes
```java
public class Classes {
    private int cid;
    private String cname;
    private Teacher teacher;
     
    public int getCid() {
        return cid;
    }
    
    public void setCid(int cid) {
        this.cid = cid;
    }
    
    public String getCname() {
        return cname;
    }
    
    public void setCname(String cname) {
        this.cname = cname;
    }
    
    public Teacher getTeacher() {
        return teacher;
    }
    
    public void setTeacher(Teacher teacher) {
        this.teacher = teacher;
    }
    
    @Override
    public String toString() {
        return "Classes [cid=" + cid + ", cname=" + cname + ", teacher=" + teacher + "]";
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
  PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="one.to.one.classesMapper">
    <!--
       嵌套结果：使用嵌套结果映射来处理重复的联合结果的子集，封装联表查询的数据(去除重复的数据)
       select * from classes c, teacher t where c.tid=t.tid and c.tid=#{tid}
     -->
    <select id="getClasses" resultMap="getClassesMap" parameterType="int">
      select * from classes c ,teacher t where c.tid=t.tid and c.tid=#{tid}
    </select>
    
    <resultMap type="one.to.one.Classes" id="getClassesMap">
        <id column="cid" property="cid"/>
        <result column="cname" property="cname"/>
        <association property="teacher" javaType="one.to.one.Teacher">
            <id column="tid" property="tid"></id>
            <result column="tname" property="tname"/>
        </association>
    </resultMap>
    
    <!--
      嵌套结果：使用嵌套结果映射来处理重复的联合结果的子集，封装联表查询的数据(去除重复的数据)
         select * from teacher t,classes c where t.cid = c.cid and t.cid=#{cid}
     -->
    <select id="getTeacher" resultMap="getTeacherMap" parameterType="int">
        select * from teacher t,classes c
            where t.cid = c.cid and t.cid=#{cid}
    </select>
    
    <resultMap type="one.to.one.Teacher" id="getTeacherMap">
        <id column="tid" property="tid"/>
        <result column="tname" property="tname"/>
        <association property="classes" javaType="one.to.one.Classes">
            <id column="cid" property="cid"/>
            <result column="cname" property="cname"/>
        </association>
    </resultMap>
    
    <!-- 把teacher的字段设置进去 -->
    <select id="getClasses2" resultMap="getClassesMap2">
      select * from classes c where c.cid = #{cid}
    </select>
    <resultMap type="one.to.one.Classes" id="getClassesMap2">
      <id column="cid" property="cid"/>
      <result column="cname" property="cname"/>
      <collection property="teacher" column="tid" select="getTeacherCollection">
      </collection>
    </resultMap>
    <select id="getTeacherCollection" resultType="one.to.one.Teacher">
      select tid tid,tname tname from teacher where tid=#{tid}
    </select>
</mapper>
```

#### 一对多, 多对一 基于xml配置
##### Student
```java
public class Student {
    private int sid;
    private String sname;
    private Classes classes;
    
    public int getSid() {
        return sid;
    }
    
    public void setSid(int sid) {
        this.sid = sid;
    }
    
    public String getSname() {
        return sname;
    }
    
    public void setSname(String sname) {
        this.sname = sname;
    }
    
    public Classes getClasses() {
        return classes;
    }
    
    public void setClasses(Classes classes) {
        this.classes = classes;
    }
    
    @Override
    public String toString() {
        return "Student [sid=" + sid + ", sname=" + sname + ", classes=" + classes + "]";
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
  PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="one.to.many.classesMapper">
  <select id="getClasses" resultMap="getClassesMap">
    select * from classes c,student s where s.cid=c.cid and c.cid=#{cid}
  </select>
  <resultMap type="one.to.many.Classes" id="getClassesMap">
    <id column="cid" property="cid"></id>
    <result column="cname" property="cname"/>
    <collection property="students" ofType="one.to.many.Student">
      <id column="sid" property="sid" />
      <result column="sname" property="sname" />
    </collection>
  </resultMap>
</mapper>
```

##### Classes
```java
public class Classes {
    private int cid;
    private String cname;
    private Set<Student> students;
     
    public int getCid() {
        return cid;
    }
    public void setCid(int cid) {
        this.cid = cid;
    }
    public String getCname() {
        return cname;
    }
    public void setCname(String cname) {
        this.cname = cname;
    }
    public Set<Student> getStudents() {
        return students;
    }
    public void setStudents(Set<Student> students) {
        this.students = students;
    }
    @Override
    public String toString() {
        return "Classes [cid=" + cid + ", cname=" + cname + ", students=" + students + "]";
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
  PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="many.to.one.studentMapper">
  <select id="getStudents" resultMap="getStudentMap">
    select * from classes c,student s where s.cid=c.cid and s.sid=#{sid}
  </select>
  <resultMap type="one.to.many.Student" id="getStudentMap">
    <id column="sid" property="sid"></id>
    <result column="sname" property="sname" />
    <association property="classes" javaType="one.to.many.Classes">
      <id column="cid" property="cid" />
      <result column="cname" property="cname" />
    </association>
  </resultMap>
</mapper>
```

#### 多对多  基于xml配置
##### Users
```java
public class Users {
    private int uid;
    private String uname;
    private Set<Groups> groups;
    
    public int getUid() {
        return uid;
    }
    
    public void setUid(int uid) {
        this.uid = uid;
    }
    
    public String getUname() {
        return uname;
    }
    
    public void setUname(String uname) {
        this.uname = uname;
    }
    
    public Set<Groups> getGroups() {
        return groups;
    }
    
    public void setGroups(Set<Groups> groups) {
        this.groups = groups;
    }
    
    @Override
    public String toString() {
        return "User [uid=" + uid + ", uname=" + uname + ", groups=" + groups + "]";
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
  PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="many.to.many.userMapper">
  <!-- 给一个用户 id，查看该用户下的所有用户组信息 -->
  <select id="getUsers" resultMap="getGroupMap">
      select g.gid,g.gname from users_groups ug,groups g
    where ug.group_id=g.gid and ug.user_id=#{uid}
  </select>
  <resultMap type="many.to.many.Groups" id="getGroupMap">
    <id column="gid" property="gid"/>
    <result column="gname" property="gname"/>
    <collection property="users" ofType="many.to.many.Users">
      <id column="uid" property="uid"/>
    <result column="uname" property="uname"/>
    </collection>
  </resultMap>
</mapper>
```

##### Groups
```java
public class Groups {
    private int gid;
    private String gname;
    private Set<Users> users;
    
    public int getGid() {
        return gid;
    }
    
    public void setGid(int gid) {
        this.gid = gid;
    }
    
    public String getGname() {
        return gname;
    }
    
    public void setGname(String gname) {
        this.gname = gname;
    }
    
    public Set<Users> getUsers() {
        return users;
    }
    
    public void setUsers(Set<Users> users) {
        this.users = users;
    }
    
    @Override
    public String toString() {
        return "Group [gid=" + gid + ", gname=" + gname + ", users=" + users + "]";
    }
}
```

##### Users_Groups
```java
public class Users_Groups {
    private Users user;
    private Groups group;
    
    public Users getUser() {
        return user;
    }
    
    public void setUser(Users user) {
        this.user = user;
    }
    
    public Groups getGroup() {
        return group;
    }
    
    public void setGroup(Groups group) {
        this.group = group;
    }
}
```
