#### 请求参数
```js
fetch(`${url}`, {
  method:
  headers:
  body:
  credentials:
  mode:
  cache：
  redirect:
  referrer:
  referrerPolicy:
  integrity:
})
```

##### method，headers
关于发送方式和请求头

##### body
请求体，或者我们可以狭义的理解为请求所携带的参数

##### credentials
控制请求是否带上 cookie 等机密信息
- omit: 请求不带任何 cookie
- same-origin: 同域请求会带上 cookie
- include: 无论是否跨域都会带上 cookie

##### mode
设置请求方式的标志位
- same-origin
- no-cors
- cors

##### cache
控制 fetch 请求如何和 HTTP 缓存协作的
- default
- no-store
- reload
- no-cache
- force-cache
- only-if-cached

##### redirect
设置请求如果遇到重定向的返回如何响应
- follow: 跟随重定向
- error: 如果 response 是重定向，则报错
- manual: 自定义行为

##### referrer
设置请求 referrer 字段的值

##### referrerPolicy
- Referer 头如何被设置的策略
- 设置请求 referrer 字段的值

##### integrity
设置请求的 subresource integrity


#### 响应
```js
fetch(url, option).then((response) => {
  response.headers
  response.ok
  response.status
  response.statusText
  response.redirected
  response.type
  response.url
  response.arrayBuffer()
  response.blob()
  response.formData()
  response.json()
  response.text()
})
```

##### headers
获取响应的 HTTP 头

##### ok
表示请求成功，即 statsu 在 200-299 之间

##### status, statusText
##### redirected
此标志位表示请求是否被重定向了

##### type
- basic: 常规同域响应
- cors: 合法的跨域响应
- error: 网络错误
- opaque: 用 "no-cors" 请求去获取跨域资源的响应

##### url
响应对应的 url，并且是最终的 url（在重定向后最终的url）
##### arrayBuffer
Ajax 是否能实现获取这些格式的方法，取决于浏览器是否实现了相关类
##### blob, formData, json, text
