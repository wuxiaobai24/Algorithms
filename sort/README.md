---
title: sort算法的实现
date:  2017-0918
---

- 实现环境：
  - 	系统：win10
  - 	IDE：vs2015

- 使用方法：

   用vs打开sort文件夹中的sort.sln，编译

  **注意：**需要向main函数传入参数来运行测试。

  ```shell
  ./sort n algorithm count
  # n 		待排数组大小
  # algorithm  排序的算法编号
  # count		 由于使用的最小单位为ms，待排数组过小时，排序时间可能小于1ms，需要设置count来调整，默认为1
  ```

  可选择的排序算法及其对应的序号

  1. bubbleSort
  2. countSort
  3. quickSort
  4. mergeSort
  5. insertionSort
  6. selectSort
  7. shellSort
  8. radixSort
  9. bucketSort
  10. heapSort


