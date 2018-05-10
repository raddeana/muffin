#### Hooks
- beforecreate: 可以在这加个loading事件，在加载实例时触发 
- created: 初始化完成时的事件写在这里，如在这结束loading事件，异步请求也适宜在这里调用
- mounted: 挂载元素，获取到DOM节点
- updated: 如果对数据统一处理，在这里写上相应函数
- beforeDestroy: 可以做一个确认停止事件的确认框
- nextTick: 更新数据后立即操作dom


#### nextTick
```javascript
Vue.nextTick(function () {
  // DOM 更新了
})

this.$nextTick(() => {
  // DOM 更新了
})
```
