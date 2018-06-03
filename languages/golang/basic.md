#### Go 语言的基础组成有以下几个部分:
- 包声明
- 引入包
- 函数
- 变量
- 语句 & 表达式
- 注释

#### 关键字
| break | default | func | interface |	select|
| case | defer | go | map | struct|
| chan | else | goto | package | switch|
| const | fallthrough | if | range | type|
| continue | for | import | return | var|

#### 预定义标识符
| append | bool | byte | cap | close | complex | complex64 | complex128 | uint16 |
| copy | false | float32 | float64 | imag | int | int8 | int16 | uint32 |
| int32 | int64 | iota | len | make | new | nil | panic | uint64 |
| print | println | real | recover | string | true | uint | uint8 | uintptr |

#### 数据类型
- 布尔型
布尔型的值只可以是常量 true 或者 false。一个简单的例子：var b bool = true。
- 数字类型
整型 int 和浮点型 float32、float64，Go 语言支持整型和浮点型数字，并且原生支持复数，其中位的运算采用补码。
- 字符串类型:
字符串就是一串固定长度的字符连接起来的字符序列。Go的字符串是由单个字节连接起来的。Go语言的字符串的字节使用UTF-8编码标识Unicode文本。
- 派生类型:
  - 指针类型（Pointer）
  - 数组类型
  - 结构化类型(struct)
  - Channel 类型
  - 函数类型
  - 切片类型
  - 接口类型（interface）
  - Map 类型

#### 变量的定义
```go
var identifier type
v_name = value
var v_name = value
```

#### 语言常量
```go
package main

import "unsafe"
const (
    a = "abc"
    b = len(a)
    c = unsafe.Sizeof(a)
)

func main(){
    println(a, b, c)
}
```

##### iota
```go
package main
import "fmt"

func main() {
  const (
    a = iota   // 0
    b          // 1
    c          // 2
    d = "ha"   // 独立值，iota += 1
    e          // "ha"   iota += 1
    f = 100    // iota +=1
    g          // 100  iota +=1
    h = iota   // 7,恢复计数
    i          // 8
  );

  fmt.Println(a, b, c, d, e, f, g, h, i)
}
```

#### 函数返回多个值
```go
package main
import "fmt"

func swap(x, y string) (string, string) {
   return y, x
}

func main() {
   a, b := swap("Mahesh", "Kumar")
   fmt.Println(a, b)
}
```

#### 变量作用域
- 函数内定义的变量称为局部变量
- 函数外定义的变量称为全局变量
- 函数定义中的变量称为形式参数

#### 声明数组
```go
var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
```

#### 初始化数组
```go
var variable_name [SIZE] variable_type
var balance [10] float32

var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
var balance = [...]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
 
 a = [3][4]int{  
 {0, 1, 2, 3} ,   /*  第一行索引为 0 */
 {4, 5, 6, 7} ,   /*  第二行索引为 1 */
 {8, 9, 10, 11}   /*  第三行索引为 2 */
}
```

#### 访问数组元素
```go
float32 salary = balance[9]
```

#### 指针
```go
package main
import "fmt"

func main() {
   var a int= 20      /* 声明实际变量 */
   var ip *int        /* 声明指针变量 */
   ip = &a            /* 指针变量的存储地址 */
   fmt.Printf("a 变量的地址是: %x\n", &a)
   /* 指针变量的存储地址 */
   fmt.Printf("ip 变量储存的指针地址: %x\n", ip)
   /* 使用指针访问值 */
   fmt.Printf("*ip 变量的值: %d\n", *ip)
}
```

```go
package main
import "fmt"

type Books struct {
   title string
   author string
   subject string
   book_id int
}

func main () {
   var Book1 Books        /* 声明 Book1 为 Books 类型 */
   var Book2 Books        /* 声明 Book2 为 Books 类型 */

   /* book 1 描述 */
   Book1.title = "Go 语言"
   Book1.author = "www.runoob.com"
   Book1.subject = "Go 语言教程"
   Book1.book_id = 6495407

   /* book 2 描述 */
   Book2.title = "Python 教程"
   Book2.author = "www.runoob.com"
   Book2.subject = "Python 语言教程"
   Book2.book_id = 6495700

   /* 打印 Book1 信息 */
   fmt.Printf( "Book 1 title : %s\n", Book1.title)
   fmt.Printf( "Book 1 author : %s\n", Book1.author)
   fmt.Printf( "Book 1 subject : %s\n", Book1.subject)
   fmt.Printf( "Book 1 book_id : %d\n", Book1.book_id)

   /* 打印 Book2 信息 */
   fmt.Printf( "Book 2 title : %s\n", Book2.title)
   fmt.Printf( "Book 2 author : %s\n", Book2.author)
   fmt.Printf( "Book 2 subject : %s\n", Book2.subject)
   fmt.Printf( "Book 2 book_id : %d\n", Book2.book_id)
}
```

#### 语言接口
```go
type interface_name interface {
   method_name1 [return_type]
   method_name2 [return_type]
   method_name3 [return_type]
   method_namen [return_type]
}
```

#### 错误处理
```
type error interface {
    Error() string
}
```
