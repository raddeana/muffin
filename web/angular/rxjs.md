#### 创建数据流
- 单值：of, empty, never
- 多值：from
- 定时：interval, timer
- 从事件创建：fromEvent
- 从Promise创建：fromPromise
- 自定义创建：create

#### 创建出来的数据流是一种可观察的序列，可以被订阅，也可以被用来做一些转换操作:
- 改变数据形态：map, mapTo, pluck
- 过滤一些值：filter, skip, first, last, take
- 时间轴上的操作：delay, timeout, throttle, debounce, audit, bufferTime
- 累加：reduce, scan
= 异常处理：throw, catch, retry, finally
- 条件执行：takeUntil, delayWhen, retryWhen, subscribeOn, ObserveOn
- 转接：switch

#### 也可以对若干个数据流进行组合:
- concat，保持原来的序列顺序连接两个数据流
- merge，合并序列
- race，预设条件为其中一个数据流完成
- forkJoin，预设条件为所有数据流都完成
- zip，取各来源数据流最后一个值合并为对象
- combineLatest，取各来源数据流最后一个值合并为数组

#### 管道：
- Observable 可观察序列，只出不进
- Observer 观察者，只进不出
- Subject 可出可进的可观察序列，可作为观察者
- ReplaySubject 带回放
- Subscription 订阅关系

#### 简单的订阅示例
```javascript
const diff = moment(createAt).fromNow()

tick() {
  this.diff = moment(createAt).fromNow()
  setTimeout(tick.bind(this), 1000)
}

Observable.interval(1000).subscribe(() => {
  this.diff = moment(createAt).fromNow()
})
```

#### 示例
```javascript
// 挣钱是为了买房，买房是为了赚钱
const house$ = new Subject()
const houseCount$ = house$.scan((acc, num) => acc + num, 0).startWith(0)

// 工资始终不涨
const salary$ = Observable.interval(100).mapTo(2)
const rent$ = Observable.interval(3000)
  .withLatestFrom(houseCount$)
  .map(arr => arr[1] * 5)

// 一买了房，就没现金了
const income$ = Observable.merge(salary$, rent$)
const cash$ = income$
  .scan((acc, num) => {
    const newSum = acc + num

    const newHouse = Math.floor(newSum / 100)
    
    if (newHouse > 0) {
      house$.next(newHouse)
    }

    return newSum % 100
  }, 0)

houseCount$.subscribe(num => console.log(`houseCount: ${num}`))
cash$.subscribe(num => console.log(`cash: ${num}`))
```
