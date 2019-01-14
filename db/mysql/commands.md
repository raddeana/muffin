#### 排序 默认是升序的 多个字段排序 哪个字段排序在前先排序
- select id,name,age,birth from teacher order BY age,birth DESC;
- select id,name,age from teacher order by age ASC;
- select birth from teacher order by birth desc;

#### 列名 as 序号
- select id as 序号,name as 名字,age as 年龄,birth as 生日 from teacher;

#### 列名（空格）序号
- select id 序号,name 名字,age 年龄,birth 生日 from teacher;
- select * from teacher limit 4;

#### 第一页
- select * from teacher limit 0, 4;

#### 第二页
- select * from teacher limit 4, 4;

#### 第三页
- select * from teacher limit 8, 4;

#### 连接字符串
- select CONCAT('a', 'b');
- select concat('fdg', 'fdgdf');
- select concat(name, id) from teacher;

#### 连接字符串后的长度
- select LENGTH(concat('a', 'b'));

#### 替换
- select REPLACE ('abcdefg', 'a', '*');

#### 从第二个开始，后面数五个，包括第二个
- select substring('abcdefghij',2,5);
- update teacher set name=replace(name, '王天一', '**')where id=4;
- select now();
- select date_format(NOW(), '%Y-%m-%d %h:%i:%s');

#### 字符串类型时间转date format类型格式必须与日期时间格式相同，否则返回null
- select str_to_date('2018-08-27 11:24:32', '%Y-%m-%d %h');
- select round(25.6564,2);
- select convert(123, char(2));
- select convert('123', signed);
- alter table teacher add COLUMN score int;
- SELECT * from teacher;
- update teacher set score=90 where age=62;

#### 如果字段值非空，则返回该值，否则返回value
- select name,age,sex,IFNULL(score,‘0’)from teacher;
- SELECT * from sanguo;
#### 如果表名后不添加字段，那么必须插入所有值。
- insert into sanguo values(6,‘周瑜’,45,‘男’,’《三国演义》’);

#### 如果插入部分字段的值，那么必须在表名后面指定插入字段的名字。
- insert into sanguo(name,age,sex)VALUES(‘诸葛亮’,65,‘男’);
#### 备份sanguo表 结构和数据 1.导出备份文件
#### 2.拷贝了表结构 数据 但是约束没有了
- create table sanguo_copy SELECT * from sanguo;
- SELECT * from sanguo_copy;
#### 表必须已经存在
- INSERT INTO sanguo_copy (id,name,age)SELECT id,name,age from sanguo;
- SELECT * from sanguo;
#### 更新多个字段 为保证更新的唯一性 一般使用ID更新
```
update sanguo set name='关平', age=20 where id=1;
UPDATE sanguo set comefrom='三国';
alter table san RENAME sanguo;
SELECT * from sanguo where id=1;
update sanguo set name=‘sb’ where id in (6,7,8);
UPDATE sanguo set age=1 where id<5 and id>3;
SELECT LAST_INSERT_ID();
```
#### delete可以删除部分数据 但是id不会重新开始
```
DELETE from sanguo where id=8;
DELETE FROM sanguo where id in(6,7);
```
#### truncate只能删除全表数据 不能删除部分数据 id从新开始
```
TRUNCATE TABLE sanguo;
```
#### 级联 casecade
#### 级联 删除 如果删除父表中的数据，那么对应子表中数据也删除
```
DELETE from stu WHERE id=3;
SELECT * from sanguo;
SELECT * from stu;
```
#### 级联 更新 如果更新父表中与子表关联的字段数据（id），那么对应子表中关联的字段数据也相应更新
```
update stu set id=5 where id=1;
update stu set id=6 where id=5;
update sanguo set name='傻逼' where id=2;
update stu set name='关羽' WHERE id=6;

select * from student;
select * from student limit 5,5;
select * from student where sex='女' or age=18;
select concat('我叫', name, '，', '今年', age, '岁', '，', '我来自', address) from student;
```
#### 找到名字里含八的
- select * from student where name like concat(’%’,‘八’,’%’);

#### 匹配一个字符
```
select * from student where name like '八';
select * from student where name like '八';
select * from student where name like '%八';
select * from student where name like '八%';
```

#### 查找所有含八的
```
select * from student where name like '%八%';
```
#### 转义字符
```
select * from student where name like '张/' escape '/';
select id,name 姓名 from student where name REGEXP '.';
select * from student where age between 18 and 19;
select * from student where age > 17 and age < 19;
select * from emp;
```
#### 算出本月开发部所发工资
```
select sum(sal) from emp where deptid=1;
```
#### 算出开发部平均工资
```
select round(avg(sal),1) 平均月薪 from emp where deptid=1;
```
#### 算出测试部工资最高的
```
select max(sal+com),ename from emp where deptid=2;
```
#### 算出运维部工资最低的
```
select min(sal+com) from emp where deptid=3;
select count() 总数 from emp;
```
#### 查询每个部门的人数 注 规定select后面出现的字段必须是group by后的字段或者聚合函数
```
select deptid,ename ,count()from emp where 1=1 group by deptid;错误的sql语句
select deptid,count(ename) 人数,SUM(sal+com) 工资总数,MAX(sal+com) 最高工资,
MIN(sal+com) 最低工资,round(avg(sal+com),1) 部门平均工资 from emp where 1=1 group by deptid;
```
#### 针对部门的平均工资 排序 升序
```
select deptid,avg(sal+com) 平均工资 from emp where 1=1 group by deptid order by 平均工资;
```
#### where 针对每条数据 条件
```
select deptid,avg(sal+com) 平均工资 from emp where 1=1 group by deptid order by avg(sal+com);
```
#### 查询每个部门中男女的人数
```
select deptid,sex,count() from emp where 1=1 group by deptid,sex;
group by 结果集 只有两列 deptid cou
where 2：group by 3：having 4：order by
select deptid,count() cou from emp where 1=1 group by deptid having cou>0 order by cou limit 0,2;
select deptid,count(*),avg(sco) from score where sco>60 group by deptid;
```
#### 表连接
```
select empno,ename,sex,DEPT from emp,dept where emp.id=dept.id;
select e.empno,e.ename,e.sex,d.DEPT from emp e,dept d where e.id=d.id;
select e.empno,d.DEPT,c.comfrom from emp e,dept d,come c where e.id=d.id and d.comid=c.comid;
```
#### 内连接 等值连接 表一 表二 匹配数据存在，
```
select d.DEPT,c.comfrom from dept d inner join come c on d.comid=c.comid;
```
#### 自连接
```
select f.id,f.name,t.name pname from t_function f join t_function t on f.id=t.pid;
```
#### 外连接 左外连接 右外连接
#### 左外连接 以左表为主表 通常以左外连接为常用连接
```
select e.ename,e.sex,d.DEPT,s.sco from emp e left join dept d on e.id=d.id left join score s on d.id=s.id;
```

#### 右外连接 以右表为主表
```
select e.ename,e.sex,d.DEPT from emp e right join dept d on e.id=d.id;
```
#### 查询每个部门的员工人数 将部门dept表左连接员工信息表emp
```
select d.id,count(e.id) from dept d
left join emp e on e.deptid=d.id
where d.comid is not null group by d.id
having count(e.id)>0
order by d.id DESC;
```
#### 子查询
```
select id,ename from emp where id in (2,3,4,5,6,7);
select id,ename from emp where id in (select id from emp where id>1);
select d.id,d.DEPT,(select count(*) from emp e where e.deptid=d.id) sum from dept d;
```
