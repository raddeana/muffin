### 红黑树
- 根结点的颜色是黑色
- 红结点的两个孩子都为黑色
- 根结点的父结点，所有叶子结点都为黑色（在程序中用NIL替换）
- 每个结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点

```cpp
#include <iostream>
using namespace std;
 
#define BK 0 //黑色
#define RD 1 //红色
 
typedef struct __RBTree {
	int key;
	int color;
  
	__RBTree* left;
	__RBTree* right;
	__RBTree* parent;
} RBTree, *pRBTree;
 
// 创建一个结点
pRBTree Build(int key);
 
// 插入一个结点
void Insert(pRBTree& root, pRBTree z);
 
// 插入修正、让其成为一个合法的红黑树
void InsertFixup(pRBTree& root, pRBTree z);
 
// 打印
void Print(pRBTree root);
 
// 左旋转
void LeftRotate(pRBTree& root, pRBTree x);
 
// 右旋转
void RightRotate(pRBTree& root, pRBTree x);
 
// 根结点的父结点，叶子结点的公共子结点
extern pRBTree NIL;
 
int main () {
	NIL->color = BK;
	NIL->parent = NIL->left = NIL->right = NULL;
 
	int array[8] = {11, 2, 1, 7, 5, 8, 14, 15};
	pRBTree root = NIL;
	for (int i = 0; i < 8; ++ i)
		Insert(root, Build(array[i]));
 
	Print(root);
	return 0;
}
 
pRBTree NIL = new RBTree;

/**
 * 构建树
 * @param {int}
 */
pRBTree Build (int key) {
	pRBTree pTmp = new RBTree;

	pTmp->key = key;
	pTmp->parent = NIL;
	pTmp->left = NIL;
	pTmp->right = NIL;
	pTmp->color = RD;

  return pTmp;
}

/**
 * 插入
 * @param {pRBTree} 根节点
 * @param {pRBTree} 插入节点
 */
void Insert (pRBTree& root, pRBTree z) {
	pRBTree pFind = root;
	pRBTree pPos = NIL;
  
	while (pFind != NIL) {
		pPos = pFind;
		if (z->key > pFind->key) {
			pFind = pFind->right;
		} else {
			pFind = pFind->left;
	  }
  }
  
	z->parent = pPos;
	
  if (pPos == NIL) {
		root = z;
	} else if (pPos->key > z->key) {
		pPos->left = z;
	} else {
		pPos->right = z;
  }
  
	InsertFixup(root, z);
}

/**
 * 打印
 * @param {pRBTree} 根节点
 */
void Print (pRBTree root) {
	if (root != NIL) {
		cout << root->key << " " << root->color << endl;
		Print(root->left);
		Print(root->right);
	}
}

/**
 * 左树旋转
 * @param {pRBTree} 根节点
 * @param {pRBTree} 旋转节点
 */
void LeftRotate (pRBTree& root, pRBTree x) {
	pRBTree y = x->right;
	x->right = y->left;
	
	if (y->left != NIL) {
		y->left->parent = x;
  }
	
	y->left = x;
	y->parent = x->parent;
	
	if (x->parent == NIL) {
		root = y;
	} else if (x->parent->left == x) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
  
  x->parent = y;
}

/**
 * 右树旋转
 * @param {pRBTree} 根节点
 * @param {pRBTree} 旋转节点
 */
void RightRotate (pRBTree& root, pRBTree x) {
	pRBTree y = x->left;
	x->left = y->right;
	
	if (y->right != NIL) {
		y->right->parent = x;
	}
  
	y->right = x;
	y->parent = x->parent;
	
	if (x->parent == NIL) {
		root = y;
	} else if (x->parent->left == x) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
  
  x->parent = y;
}
 
void InsertFixup (pRBTree& root, pRBTree z) {
	while (z->parent->color == RD) {
		if (z->parent == z->parent->parent->left) {
			pRBTree y = z->parent->parent->right;
			
      if (y->color == RD) {
				z->parent->color = BK;
				y->color = BK;
				z->parent->parent->color = RD;
        
				z = z->parent->parent;
			} else if (z == z->parent->right) {
				z = z->parent;
				LeftRotate(root, z);
			} else {
				z->parent->color = BK;
				z->parent->parent->color = RD;
				
        RightRotate(root, z->parent->parent);
			}
		} else {
			pRBTree y = z->parent->parent->left;
			if (y->color == RD) {
				z->parent->color = BK;
				y->color = BK;
				z->parent->parent->color = RD;
				z = z->parent->parent;
			} else if (z == z->parent->left) {
				z = z->parent;
				RightRotate(root, z);
			} else {
				z->parent->color = BK;
				z->parent->parent->color = RD;
				LeftRotate(root, z->parent->parent);
			}
		}
	}
  
	root->color = BK;
}
```
