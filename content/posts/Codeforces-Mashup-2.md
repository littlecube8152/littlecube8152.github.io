---
title: "[Codeforces] Mashup 練習 2"
date: 2021-03-11T08:27:38+08:00
draft: false
tags: ["codeforces"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

提升一下難度就不會了 傷心  
都要靠題解的提示了QwQ 

## 1244E - Minimizing Difference
### 題敘
[Link](https://codeforces.com/problemset/problem/1244/E)  
每一步操作可以把一個數字加1或減1，問操作完全距最小是多少。

### 想法
用map暴搜，  
迭代器超難寫:(  
[AC Code](https://codeforces.com/problemset/submission/1244/109637029)  






## 1370E - Binary Subsequence Rotation
### 題敘
[Link](https://codeforces.com/problemset/problem/1370/E)  
有一個01字串，  
每次可以選一個子序列然後順時針轉一個位置，  
問做到對齊的最小次數。   

### 想法
這題我真的想不到:(  
    
官解是證明每次選取010101010...的字串至少會是最佳解，   
原題就變成了最大連續和  
[AC Code](hhttps://codeforces.com/problemset/submission/1370/109639148)
  





## 895D - String Mark
### 題敘
[Link](https://codeforces.com/problemset/problem/895/D)  
有兩個字串$a$，$b$，
問有多少$a$的排列滿足字典序大於$a$小於$b$。  
輸出$\mod 10^9 + 7$。    

### 想法
分開作小於$a$，小於$b$再相減，  
用DP/排列組合就可以過。   

### 細節
本題時限卡很緊，需要優化。  
(建議可以用階乘反元素處理)    
  
[AC Code](https://codeforces.com/problemset/submission/895/109648882)
  

## 1336C - Kaavi and Magic Spell
### 題敘
[Link](https://codeforces.com/problemset/problem/1336/C)  
有一個空字串A，  
依序把原字串S的前面放到A的頭或尾(不需要放完)，  
有多少**操作順序**使得做出來的A有一個前綴是T。  
輸出$\mod 998244353$。  

### 想法
令$dp[i][j]$表示已經放了$[0..i]$，開頭在$j$，滿足條件的可能，  
每次就只要考慮放前或放後兩種可能就好。  

  
[AC Code](https://codeforces.com/problemset/submission/1172/109497694)
