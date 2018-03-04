#### 查询和变更
##### 字段（Fields）
```
{
  hero {
    name
  }
}
{
  hero {
    name
    # 查询可以有备注！
    friends {
      name
    }
  }
}
```
##### 参数（Arguments）
```
{
  human(id: "1000") {
    name
    height
  }
}
```
##### 别名（Aliases）
```
{
  empireHero: hero(episode: EMPIRE) {
    name
  }
  jediHero: hero(episode: JEDI) {
    name
  }
}
```
##### 片段（Fragments）
```
{
  leftComparison: hero(episode: EMPIRE) {
    ...comparisonFields
  }
  rightComparison: hero(episode: JEDI) {
    ...comparisonFields
  }
}

fragment comparisonFields on Character {
  name
  appearsIn
  friends {
    name
  }
}
```
##### 操作名称（Operation name）
```
query HeroNameAndFriends {
  hero {
    name
    friends {
      name
    }
  }
}
```
##### 变量（Variables）
```
query HeroNameAndFriends($episode: Episode) {
  hero(episode: $episode) {
    name
    friends {
      name
    }
  }
}
```
##### 指令（Directives）
```
query HeroNameAndFriends($episode: Episode = "JEDI") {
  hero(episode: $episode) {
    name
    friends {
      name
    }
  }
}

```
##### 变更（Mutations）
```
query Hero($episode: Episode, $withFriends: Boolean!) {
  hero(episode: $episode) {
    name
    friends @include(if: $withFriends) {
      name
    }
  }
}
```
##### 内联片段（Inline Fragments）
```
mutation CreateReviewForEpisode($ep: Episode!, $review: ReviewInput!) {
  createReview(episode: $ep, review: $review) {
    stars
    commentary
  }
}
```
