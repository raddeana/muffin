#### Spring Boot
发送邮件是网站的必备功能之一，用户注册验证、忘记密码或者发送营销信息

#### 三大类
- Message 类: 创建和解析邮件的核心 API，用于创建一封邮件，可以设置发件人、收件人、邮件主题、正文信息、发送时间等信息
- Transport 类: 发送邮件的核心 API 类
- Store 类: 接收邮件的核心API类

#### 相关协议
- SMTP 协议: 发送邮件协议
- POP3 协议: 获取邮件协议
- IMAP: 接收信息的高级协议
- MIME: 邮件拓展内容格式：信息格式，附件格式

#### pom 包配置
```xml
<dependencies>
  <dependency> 
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-mail</artifactId>
  </dependency>
</dependencies>
```

#### 配置文件
```conf
spring.mail.host = smtp.163.com //邮箱服务器地址
spring.mail.username = xxx@oo.com //用户名
spring.mail.password = xxyyooo    //密码
spring.mail.default-encoding = UTF-8

//超时时间，可选
spring.mail.properties.mail.smtp.connectiontimeout = 5000  
spring.mail.properties.mail.smtp.timeout = 3000
spring.mail.properties.mail.smtp.writetimeout = 5000
```

```conf
spring.mail.host = smtp.126.com
spring.mail.username = yourEmail@126.com
spring.mail.password = yourPassword
spring.mail.default-encoding = UTF-8
```

```conf
spring.mail.host = smtp.qq.com
spring.mail.username = ityouknow@qq.com
spring.mail.password = yourPassword
spring.mail.default-encoding=UTF-8
```

#### JavaMailSender
```java
@Component
public class MailServiceImpl implements MailService {
  private final Logger logger = LoggerFactory.getLogger(this.getClass());

  @Autowired
  private JavaMailSender mailSender;

  @Value("${spring.mail.username}")
  private String from;

  @Override
  public void sendSimpleMail(String to, String subject, String content) {
    SimpleMailMessage message = new SimpleMailMessage();
    message.setFrom(from);
    message.setTo(to);
    message.setSubject(subject);
    message.setText(content);

    try {
      mailSender.send(message);
      logger.info("简单邮件已经发送。");
    } catch (Exception e) {
      logger.error("发送简单邮件时发生异常！", e);
    }
  }
}
```

- from, 即为邮件发送者
- to, 邮件接收者
- subject, 邮件主题
- content, 邮件的主体

#### 测试
```java
@RunWith(SpringRunner.class)
@Spring BootTest
public class MailServiceTest {
  @Autowired
  private MailService MailService;

  @Test
  public void testSimpleMail() throws Exception {
    mailService.sendSimpleMail("ityouknow@126.com","这是一封简单邮件","大家好，这是我的第一封邮件！");
  }
}
```

#### 富文本邮件
##### 发送 HTML 格式邮件
```java
public void sendHtmlMail(String to, String subject, String content) {
    MimeMessage message = mailSender.createMimeMessage();

  try {
    // true 表示需要创建一个 multipart message
    MimeMessageHelper helper = new MimeMessageHelper(message, true);
    helper.setFrom(from);
    helper.setTo(to);
    helper.setSubject(subject);
    helper.setText(content, true);

    mailSender.send(message);
    logger.info("html邮件发送成功");
  } catch (MessagingException e) {
    logger.error("发送html邮件时发生异常", e);
  }
}
```

##### 发送带附件的邮件
添加多个附件可以使用多条 helper.addAttachment(fileName, file)
```java
public void sendAttachmentsMail(String to, String subject, String content, String filePath){
  MimeMessage message = mailSender.createMimeMessage();

  try {
    MimeMessageHelper helper = new MimeMessageHelper(message, true);
    helper.setFrom(from);
    helper.setTo(to);
    helper.setSubject(subject);
    helper.setText(content, true);

    FileSystemResource file = new FileSystemResource(new File(filePath));
    String fileName = file.getFilename();
    helper.addAttachment(fileName, file);
    // helper.addAttachment("test"+fileName, file);

    mailSender.send(message);
    logger.info("带附件的邮件已经发送。");
  } catch (MessagingException e) {
    logger.error("发送带附件的邮件时发生异常！", e);
  }
}
```

##### 发送带静态资源的邮件
```java
public void sendInlineResourceMail(String to, String subject, String content, String rscPath, String rscId){
  MimeMessage message = mailSender.createMimeMessage();

  try {
    MimeMessageHelper helper = new MimeMessageHelper(message, true);
    helper.setFrom(from);
    helper.setTo(to);
    helper.setSubject(subject);
    helper.setText(content, true);

    FileSystemResource res = new FileSystemResource(new File(rscPath));
    helper.addInline(rscId, res);

    mailSender.send(message);
    logger.info("嵌入静态资源的邮件已经发送");
  } catch (MessagingException e) {
    logger.error("发送嵌入静态资源的邮件时发生异常", e);
  }
}
```

#### 邮件系统
##### pom 中导入 thymeleaf 的包
```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

##### emailTemplate.html
```html
<!DOCTYPE html>
<html lang="zh" xmlns:th="http://www.thymeleaf.org">
  <head>
    <meta charset="UTF-8"/>
    <title>邮件模板</title>
  </head>
  <body>
    您好，感谢您的注册，这是一封验证邮件，请点击下面的链接完成注册，感谢您的支持<br/>
    <a href="#" th:href="@{http://www.ityouknow.com/register/{id}(id=${id}) }">激活账号</a>
  </body>
</html>
```

##### 解析模板并发送
```java
@Test
public void sendTemplateMail() {
  // 创建邮件正文
  Context context = new Context();
  context.setVariable("id", "006");
  String emailContent = templateEngine.process("emailTemplate", context);

  mailService.sendHtmlMail("wherebt@126.com", "主题：这是模板邮件", emailContent);
}
```

##### 发送失败
- 接收到发送邮件请求，首先记录请求并且入库
- 调用邮件发送接口发送邮件，并且将发送结果记录入库
- 启动定时系统扫描时间段内，未发送成功并且重试次数小于 3 次的邮件，进行再次发送
