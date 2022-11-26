---
title: "[Codeforces] Mashup 練習 1"
date: 2021-03-09T23:29:39+08:00
draft: false
tags: ["codeforces"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

選訓上了 希望不要墊底><  

## 1354D - Multiset 
### 題敘
[Link](https://codeforces.com/problemset/problem/1354/D)  
在記憶體限制下實作一個Multiset支援刪除第k項。  

### 想法
用線段樹/BIT，  
可以在上面二分搜，  
注意BIT的二分搜，仔細想一想，可以用BIT的特性做到$\mathcal{O}(\log N)$查詢，  
[AC Code](https://codeforces.com/problemset/submission/1354/109468604)  


## 747E - Comments
### 題敘
[Link](https://codeforces.com/problemset/problem/747/E)  
給定一個留言壓平的序列（格式參考題目），輸出以階層拆解後的樣子。  

### 想法
DFS裸題，稍微想一下就過了。   
[AC Code](https://codeforces.com/problemset/submission/747/109469986)
  





## 1450D - Rating Compression
### 題敘
[Link](https://codeforces.com/problemset/problem/1450/D)  
把原陣列($n$項)**分別**每$k (1 \leq k \leq n)$做最小值成為$n$個新陣列，  
判斷哪些$k$的時候滿足新陣列是$1$到$n - k + 1$的排列，  

### 想法
注意不同位置會被**多個**取最小值的區間涵蓋到，  
例如$1 < k < n$時$1$只能在陣列的兩端，否則會有兩個區間處理後值為$1$，
所以如果當前陣列有解，可以從兩端是否是最小值判斷。  

### 細節
注意特判$k = 1$及$k = n$。  
  
[AC Code](https://codeforces.com/problemset/submission/1450/109495886)
  

## 1172B - Nauuo and Circle
### 題敘
[Link](https://codeforces.com/problemset/problem/1172/B)  
有一顆樹，  
求樹的所有節點都在圓上的等分點的時候，邊不交叉的可能排列數  
輸出$\mod 998244353$。  

### 想法
令根節點(1號點)在最上面，考慮他的子樹分布排列，  
等同於他子節點的排列數$\times$所有子樹可能相乘(因為不同子樹的節點不會交叉)，  
再考慮旋轉圓有$n$種可能。    

### 細節
注意計算子樹的時候除了根節點(1號點)都要把自己加下去排列，  
可以自己推看看。  
  
[AC Code](https://codeforces.com/problemset/submission/1172/109497694)
