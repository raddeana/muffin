/**
 * 交换
 * @author mulberry
 */

/**
 * 数组元素交换位置
 * @param { int ref } 元素指针1
 * @param { int ref } 元素指针2
 */
void swap (int &ele1, int &ele2) {
  int temp;
  temp = ele1;
  ele1 = ele2;
  ele2 = temp;
} 
