#### ? 字符
- 单匹配
```cmd
# 存在文件 a.txt 和 b.txt
$ ls ?.txt
a.txt b.txt
```

- 多个字符匹配
```cmd
# 存在文件 a.txt、b.txt 和 ab.txt
$ ls ??.txt
ab.txt
```

#### * 字符
- *代表任意数量的字符
```cmd
# 存在文件 a.txt、b.txt 和 ab.txt
$ ls *.txt
a.txt b.txt ab.txt

# 输出所有文件
$ ls *
```

- *可以匹配空字符
```cmd
# 存在文件 a.txt、b.txt 和 ab.txt
$ ls a*.txt
a.txt ab.txt
```

#### [...] 模式
- [...]匹配方括号之中的任意一个字符，比如[aeiou]可以匹配五个元音字母
```cmd
# 存在文件 a.txt 和 b.txt
$ ls [ab].txt
a.txt b.txt

$ ls *[ab].txt
ab.txt a.txt b.txt
```

- [start-end]表示一个连续的范围
```cmd
# 存在文件 a.txt、b.txt 和 c.txt
$ ls [a-c].txt
a.txt b.txt c.txt

# 存在文件 report1.txt、report2.txt 和 report3.txt
$ ls report[0-9].txt
report1.txt report2.txt report3.txt
```

#### [^...] 和 [!...]
```cmd
# 存在文件 a.txt、b.txt 和 c.txt
$ ls [^a].txt
b.txt c.txt
```

```cmd
$ echo report[!1-3].txt
report4.txt report5.txt
```

#### {...} 模式
```cmd
$ echo d{a,e,i,u,o}g
dag deg dig dug dog
```

```cmd
$ echo {cat, dog}
cat dog
```

```cmd
# 不存在 a.txt 和 b.txt
$ ls [ab].txt
ls: [ab].txt: No such file or directory

$ ls {a,b}.txt
ls: a.txt: No such file or directory
ls: b.txt: No such file or directory
```

```cmd
$ echo {j{p,pe}g,png}
jpg jpeg png
```

```cmd
$ echo {cat,d*}
cat dawg dg dig dog doug dug
```

#### {start..end} 模式
```cmd
$ echo d{a..d}g
dag dbg dcg ddg

$ echo {11..15}
11 12 13 14 15
```

```cmd
$ echo {a1..3c}
{a1..3c}
```

```cmd
$ echo .{mp{3..4},m4{a,b,p,v}}
.mp3 .mp4 .m4a .m4b .m4p .m4v
```

#### 注意点
- 通配符是先解释，再执行
```cmd
$ ls a*.txt
ab.txt
```

- 通配符不匹配，会原样输出
```cmd
# 不存在 r 开头的文件名
$ echo r*
r*
```
```cmd
$ ls *.csv
ls: *.csv: No such file or directory
```

- 只适用于单层路径
```cmd
$ ls */*.txt
```

- 可用于文件名
```cmd
$ touch 'fo*'
$ ls
fo*
```




