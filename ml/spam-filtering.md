#### 关键字过滤
使用关键字算法，我们可以将真人荷官，六合彩这两个词语加入赌博类别的黑名单，每个类别都维持对应的黑名单表

#### 贝叶斯模型
其实关键字算法已经接近贝叶斯模型的原理了，我们再仔细分析下关键字算法
关键字算法的问题在于只对输入句子中的部分词语进行分析，而没有对输入句子的整体进行分析

#### 数学推导
- P(A) -> A事件发生的概率，例如明天天晴的概率
- P(A|B) -> 条件概率，B事件发生的前提下A事件发生的概率，例如明天天晴而我又没带伞的概率
- P(输入句子) -> 这个句子在训练数据中出现的概率
- P(赌博) -> 赌博类别的句子在训练数据中出现的概率
- P(赌博|输入句子) -> 输入句子是赌博类别的概率（也是我们最终要求的值）
- P(赌博|输入句子) + P(正常|输入句子) = 100%

#### 词袋集合
```python
def _get_vocab_list(self):
    '''
    Get a list contain all unique non stop words belongs to train_data
    Set up:
    self.vocab_list:
        [
            'What', 'lovely', 'day',
            'like', 'gamble', 'love', 'dog', 'sunkist'
        ]
    '''
    vocab_set = set()
    all_train_data = ''.join([v for _, v in self._train_data])
    token = Token(text=all_train_data, lan=self.lan, split=self.split)
    vocab_set = vocab_set | set(token.tokenizer)
    self._vocab_list = list(vocab_set)
```

#### 长度为49的一维向量
```python
def _get_vocab_matrix(self):
    '''
    Convert strings to vector depends on vocal_list
    '''
    array_list = []
    for k, data in self._train_data:
        return_vec = np.zeros(len(self._vocab_list))
        token = Token(text=data, lan=self.lan, split=self.split)
        for i in token.tokenizer:
            if i in self._vocab_list:
                return_vec[self._vocab_list.index(i)] += 1
        array_list.append(return_vec)
    self._matrix_lst = array_list
```

#### numpy的矩阵运算
```python
def _training(self):
    '''
    Native bayes training
    '''
    self._ps_vector = []
    # 防止有词语在其他类别训练数据中没有出现过，最后的P(句子|类别)乘积就会为零，所以给每个词语一个初始的非常小的出现概率，设置vector默认值为1，cal对应为2
    # vector: 默认值为1的一维数组
    # cal: 默认的分母，计算该类别所有有效词语的总数
    # num: 计算P(赌博), P(句子)
    vector_list = [{
        'vector': np.ones(len(self._matrix_lst[0])),
        'cal': 2.0, 'num': 0.0} for i in range(len(self.CLASSIFY))]
    for k, v in enumerate(self.train_data):
        vector_list[v[0]]['num'] += 1
        # vector加上对应句子的词向量，最后把整个向量除于cal，就得到每个词语在该类别的概率。
        # [1, 0, 0, 0, 1, 0, ..., 1, 0, 1] (根据您所选择的...)
        # [0, 1, 1, 0, 0, 0, ..., 0, 0, 0] (奖金将在您完成...)
        #                   +
        # [1, 1, 1, 1, 1, 1, ..., 1, 1, 1] 
        vector_list[v[0]]['vector'] += self._matrix_lst[k]
        vector_list[v[0]]['cal'] += sum(self._matrix_lst[k])
    for i in range(len(self.CLASSIFY)):
        # 每个词语的概率为[2, 2, 2, 1, 2, 1, ..., 2, 1, 2]/cal
        self._ps_vector.append((
            np.log(vector_list[i]['vector']/vector_list[i]['cal']),
            np.log(vector_list[i]['num']/len(self.train_data))))
```

#### 两个概率向量相乘
```python
def _bayes_classify(self):
  '''
  Calculate the probability of different category
  '''
  possibility_vector = []
  log_list = []
  # self._ps_vector: ([-3.44, -3.56, -2.90], 0.4)
  for i in self._ps_vector:
    # 计算每个词语对应概率的乘积
    final_vector = i[0] * self.word_vec
    # 获取对分类器影响度最大的词语
    word_index = np.nonzero(final_vector)
    non_zero_word = np.array(self._vocab_list)[word_index]
    # non_zero_vector: [-7.3, -8]
    non_zero_vector = final_vector[word_index]
    possibility_vector.append(non_zero_vector)
    log_list.append(sum(final_vector) + i[1])
  possibility_array = np.array(possibility_vector)
  max_val = max(log_list)
  for i, j in enumerate(log_list):
    # 输出最大概率的类别
    if j == max_val:
      max_array = possibility_array[i, :]
      left_array = np.delete(possibility_array, i, 0)
      sub_array = np.zeros(max_array.shape)
      # 通过曼哈顿举例，计算影响度最大的词语
      for k in left_array:
        sub_array += max_array - k
      return self._update_category(log_list), \
        sorted(
          list(zip(non_zero_word, sub_array)),
          key=lambda x: x[1], reverse=True)
```
