#### 邻接列表模型
分层数据无处不在
它可以是博客类别(栏目)，产品层次结构或组织结构
有很多方法来管理MySQL中的层次数据，邻接列表模型可能是最简单的解决方案

#### 术语:
- 电子设备(Electronics)是顶级节点或根节点
- 笔记本电脑，相机和照片，手机和配件(Laptops, Cameras & photo, Phones & Accessories)节点是Electronics节点的子节点
- 反之亦然Electronics节点是Laptops, Cameras & photo, Phones & Accessories节点的父节点
- 叶子节点是没有子节点的节点，例如Laptops，PC，Android，iOS等，而非叶节点是至少有一个子节点的节点
- 一个节点的子孙节点被称为后代节点。一个节点的父节点，祖父节点等也被称为祖先节点

```sql
CREATE TABLE category (
  id int(10) unsigned NOT NULL AUTO_INCREMENT,
  title varchar(255) NOT NULL,
  parent_id int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (parent_id) REFERENCES category (id) 
    ON DELETE CASCADE ON UPDATE CASCADE
);
```

#### 插入数据
```sql
INSERT INTO category(title, parent_id) VALUES('Electronics', NULL);
```

```sql
INSERT INTO category(title, parent_id) VALUES('Laptops & PC', 1);

INSERT INTO category(title, parent_id) VALUES('Laptops', 2);
INSERT INTO category(title, parent_id) VALUES('PC', 2);

INSERT INTO category(title, parent_id) VALUES('Cameras & photo', 1);
INSERT INTO category(title, parent_id) VALUES('Camera', 5);

INSERT INTO category(title, parent_id) VALUES('Phones & Accessories', 1);
INSERT INTO category(title, parent_id) VALUES('Smartphones', 7);

INSERT INTO category(title, parent_id) VALUES('Android', 8);
INSERT INTO category(title, parent_id) VALUES('iOS', 8);
INSERT INTO category(title, parent_id) VALUES('Other Smartphones', 8);

INSERT INTO category(title, parent_id) VALUES('Batteries', 7);
INSERT INTO category(title, parent_id) VALUES('Headsets', 7);
INSERT INTO category(title, parent_id) VALUES('Screen Protectors', 7);
```

#### 查找根节点
```sql
SELECT
    id, title
FROM
    category
WHERE
    parent_id IS NULL;
```

#### 查找节点的直接子节点
```sql
SELECT
    id, title
FROM
    category
WHERE
    parent_id = 1;
```

#### 查找叶节点
```sql
SELECT
    c1.id, c1.title
FROM
    category c1
        LEFT JOIN
    category c2 ON c2.parent_id = c1.id
WHERE
    c2.id IS NULL;
```

#### 查询整个树
```sql
WITH RECURSIVE category_path (id, title, path) AS (
  SELECT id, title, title as path
    FROM category
    WHERE parent_id IS NULL
  UNION ALL
  SELECT c.id, c.title, CONCAT(cp.path, ' > ', c.title)
    FROM category_path AS cp JOIN category AS c
      ON cp.id = c.parent_id
)
SELECT * FROM category_path ORDER BY path;
```

#### 查询子树
```sql
WITH RECURSIVE category_path (id, title, path) AS (
  SELECT id, title, title as path
    FROM category
    WHERE parent_id = 7
  UNION ALL
  SELECT c.id, c.title, CONCAT(cp.path, ' > ', c.title)
    FROM category_path AS cp JOIN category AS c
      ON cp.id = c.parent_id
)

SELECT * FROM category_path ORDER BY path;
```

#### 查询单个路径
```sql
WITH RECURSIVE category_path (id, title, parent_id) AS (
  SELECT id, title, parent_id
    FROM category
    WHERE id = 10 -- child node
  UNION ALL
  SELECT c.id, c.title, c.parent_id
    FROM category_path AS cp JOIN category AS c
      ON cp.parent_id = c.id
)

SELECT * FROM category_path;
```

#### 计算每个节点的级别
```sql
WITH RECURSIVE category_path (id, title, lvl) AS (
  SELECT id, title, 0 lvl
    FROM category
    WHERE parent_id IS NULL
  UNION ALL
  SELECT c.id, c.title,cp.lvl + 1
    FROM category_path AS cp JOIN category AS c
      ON cp.id = c.parent_id
)

SELECT * FROM category_path ORDER BY lvl;
```

#### 删除节点及其后代
```sql
DELETE FROM category WHERE id = 2;
```

#### 删除节点并提升其后子节点
- 将节点的直接子节点的parent_id更新为新父节点的ID
- 删除节点
```sql
UPDATE category SET parent_id = 7 WHERE parent_id = 5;
```

#### 移动子树
```sql
UPDATE category SET parent_id = 7 WHERE id = 5;
```
