#### 类型系统
```
{
  hero {
    name
    appearsIn
  }
}
```
- 特殊的对象root开始
- 选择其上的hero字段
- 对于hero返回的对象，我们选择name和appearsIn字段

#### 类型语言
```
type Character {
  name: String!
  appearsIn: [Episode]!
}
```

#### 参数
```
type Starship {
  id: ID!
  name: String!
  length(unit: LengthUnit = METER): Float
}
```

#### 查询和变更类型
```
schema {
  query: Query
  mutation: Mutation
}
```

#### 标量类型
```
{
  hero {
    name
    appearsIn
  }
}
```

#### 枚举类型
```
enum Episode {
  NEWHOPE
  EMPIRE
  JEDI
}
```

#### 列表和非空
```
type Character {
  name: String!
  appearsIn: [Episode]!
}

query DroidById($id: ID!) {
  droid(id: $id) {
    name
  }
}
```

#### 接口
```
interface Character {
  id: ID!
  name: String!
  friends: [Character]
  appearsIn: [Episode]!
}

query HeroForEpisode($ep: Episode!) {
  hero(episode: $ep) {
    name
    primaryFunction
  }
}
```

#### 联合类型
```
union SearchResult = Human | Droid | Starship

{
  search(text: "an") {
    ... on Human {
      name
      height
    }
    ... on Droid {
      name
      primaryFunction
    }
    ... on Starship {
      name
      length
    }
  }
}
```

#### 输入类型
```
input ReviewInput {
  stars: Int!
  commentary: String
}

mutation CreateReviewForEpisode($ep: Episode!, $review: ReviewInput!) {
  createReview(episode: $ep, review: $review) {
    stars
    commentary
  }
}
```
