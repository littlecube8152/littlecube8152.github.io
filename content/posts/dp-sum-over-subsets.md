---
title: "[DP] Sum over Subsets Optimization"
description: "CF 165E, CF 383E, CF 449D, CF 800D"
date: 2021-06-10T09:57:32+08:00
draft: false
tags: ["tutorial"]
summary: "笨方塊想學 SoS DP 優化被爆揍，燒雞"
---


## 問題
Sum over Subsets 要優化的東西長得像是：  

$\displaystyle F_{mask} = \sum_{i\subseteq mask} A_i$

而$mask$表示一個子集（宇集是有$N$個元素的集合）。  

## 優化
### 暴力
我們可以枚舉所有集合，  
再枚舉一次集合，看看是不是要求的那個集合的子集。    
複雜度$\mathcal O(4^N)$。
```cpp
for (int mask = 0; mask < (1 << N); mask++)
    for (int i = 0; i <= mask; i++)
        if ((mask & i) == i)
            F[mask] += A[i];
```
### 優化過的暴力
剛剛的枚舉方法有多枚舉到不是子集的東西，  
那如果直接枚舉需要的子集，  
可以這樣做：  
```cpp
for (int mask = 0; mask < (1 << N); mask++)
    for (int i = mask;; i = ((i - 1) & mask))
    {
        F[mask] += A[i];
        if(i == 0) break;
    }
```
那為什麼這樣是可以的呢？  
假如我把所有子集排序好，  
- 拿掉最低位元
- 把這個位元以下有被集合涵蓋到的都設為 `1`  

直覺的證明是忽略掉原本集合沒有的，當作是二進位減法。  
這樣的複雜度是$\mathcal O(3^N)$，  
證明有排列組合（元素有不在母集、在母集不在子集、在母集也在子集）；      
或是用二項式定理 $\displaystyle\sum_{i = 0}^{N}C^N_i 2^i = 3^N$。  

### 優化
如果一個集合$S$有$n(S)$個元素，  
它會被$2^{N - n(S)}$個集合給算到，  
也就是說，其中顯然有很多是可以優化掉的，  

假設現在要計算的是$F_{mask}$，  
考慮它的第 $i$ 位（1-ordered），  
 - 如果這位是`0`，就可以不用理它，往下計算。   
 - 如果這位是`1`，就需要考慮這個位元在子集中有或沒有：
    - 子集中沒有這個位元的，剛好是$mask \oplus 2^i$計算下一位的結果，  
    - 子集中有這個位元的，往下計算，因為找不到其他值可以涵蓋這部分。  

而 $mask$ 的所有子集只有一個（$mask$本身）在所有的`1`都一樣，  
換句話說，所有的子集的值都**至少要透過 $mask \oplus 2^i$ 得到**，  
而 $mask \oplus 2^i$ 如果要先計算好，只要按照數字遞增枚舉就好，  

這樣只要最後把$A_{mask}$加上去就好，整體來講就是一個DP：  
    
$dp_{mask,\\, i} = \begin{cases}
            dp_{mask,\\, i - 1} & i \notin \text{set of } mask \\\\
            dp_{mask,\\, i - 1} +  dp_{mask \oplus 2^i,\\, i - 1} & i \in \text{set of } mask \\\\
            A_{mask} & i = 0 \\\\
            \end{cases}$  
$ F_{mask} = dp_{mask,\\,N}$  

直覺的寫法：  
```cpp
for (int mask = 0; mask < (1 << N); mask++)
    dp[mask][0] = A[mask];
for (int mask = 0; mask < (1 << N); mask++)
    for (int i = 1; i <= N; i++)
    {
        if (mask & (1 << (i - 1)))
            dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << (i - 1))][i - 1];
        else
            dp[mask][i] = dp[mask][i - 1];
    }
F[mask] = dp[mask][N];
```
但如果把兩個迴圈內外交換，可以壓縮記憶體：  
```cpp
for (int mask = 0; mask < (1 << N); mask++)
    F[mask] = A[mask];

for (int i = 0; i < N; i++)
    for (int mask = 0; mask < (1 << N); mask++)
        if (mask & (1 << i))
            F[mask] += F[mask ^ (1 << i)];
```  
時間複雜度$\mathcal O(N\\,2^N)$。  

## 討論

在Codeforces的[這篇](./#reference)Blog上面有提到這個問題：  
如果有兩個函數：  
$\displaystyle F_{mask} = f\Bigg(\sum_{i \subset mask}G_i\Bigg),\\, G_{mask} = G\Bigg(\sum_{i \subseteq mask}F_i\Bigg)$  
要怎麼計算？  
其實就跟剛剛優化的推導一樣，  
由於$\\,F\\,$需要他的子集（不含本身），$G\\,$需要他的子集（含本身），  
所以不能套用記憶體優化，一次計算完一個$\\,mask$，然後先計算$\\,F\\,$再計算$\\,G\\,$，  
就可以達到$\mathcal O(N\\,2^N)$的複雜度了。  





## 例題 - Codeforces 165E Compatible Numbers    

[Link](https://codeforces.com/contest/165/problem/E)  
有一個長度為$\\,N\\,$的陣列，  
對每個元素都找到有沒有其他元素使得兩個 AND 起來會是 0。  
$N \leq 10^6,\\,1 \leq a_i \leq 4\times 10^6$  

### 觀察
兩個數字 AND 起來是 0 的意思就是他們沒有相同的位元是`1`，  
所以所有可能的數字剛好會是$\displaystyle (2^{\lceil \log_2 \max a_i \rceil} - 1) \oplus a_i$的子集，  

### 實作
就直接取$dp_{mask} = mask$的子集中的任一可能，  
做剛剛提到的 SoS (​Sum ​over ​Subset) 的優化，  
複雜度$\mathcal O(K\\,2^K)$，其中$K = \lceil \log_2 \max a_i \rceil$。  

**[Code](https://codeforces.com/contest/165/submission/119207382)**  







## 類題 - Codeforces 383E Vowels

[Link](https://codeforces.com/contest/383/problem/E)  

給你 $N$ 個長度為 $3$，僅包含a~x（共$24$種字元）的字串，  
定義一個字是合法的表示其中至少有一個字母是母音，  
問對於所有 $2^{24}$ 種可能的母音選擇，有多少字串是合法的。  
答案輸出請平方之後 $\text{XOR}$。  

### 觀察

考慮簡單一點的狀況：如果每個字串都只有一個位元，  
那顯然就是直接做 SoS DP 下去求出 $2^{24}$ 種可能，  

那如果有 $3$ 個字呢？  
問題出在，當子集涵蓋到兩個就會被算到兩次，  
所以可以用排容處理，一樣做 SoS DP。  

**[Code](https://codeforces.com/contest/383/submission/119450351)**  









## 類題 - Codeforces 449D Jzzhu and Numbers    

[Link](https://codeforces.com/contest/449/problem/D)  
有一個長度為$\\,N\\,$的陣列 $a$，  
找到有多少組序列 $1 < i_1 < i_2 < \cdots < i_k$ （$k$ 僅代表序列的長度）且  
$a_{i_1} \text{ AND } a_{i_2} \text{ AND } \cdots \text{ AND } a_{i_k} = 0$。  
輸出$\\!\mod 10^9 + 7$。  

$N \leq 10^6,\\,0 \leq a_i \leq 10^6$  

### 觀察
如果直接照 LIS 的順序枚舉，  
可以令 $dp[i][mask]$ 表示前 $i$ 個元素中，$\text{AND}$ 起來是 $mask$ 的方法數，  
不過這樣複雜度是$\mathcal O(N\\,2^K)$（其中$K = \lceil \log_2 \max a_i \rceil$），  

但題目還有一個性質：  
  - 所求的組合 $\text{AND}$ 起來是 $0$，實際上就是每個位元flip之後 $\text{OR}$ 起來是`111...11`  
  - 令$b_i = \text{NOT }a_i$，  
    當$b_{i_1} \text{ OR }  b_{i_2} \text{ OR } \cdots \text{ OR }  b_{i_k} = mask$，那$b_{i_1},\\,b_{i_2},\\,\cdots,\\, b_{i_k}$ 都是 $mask$ 的submask，  
  - 不過反過來的情況，只能得到$b_{i_1} \text{ OR }  b_{i_2} \text{ OR } \cdots \text{ OR }  b_{i_k}$是 $mask$ 的submask。  

這樣要怎麼知道有多少組合是題目要的？  
把不要的扣掉！

### 實作

對反轉的 $b_i$ 做一次 SoS 之後，  
所得的總和換成 $ 2^{dp_{mask}} - 1$，剛好是所可以形成的組合數，  
要再把submask給排容掉，  
所以，這裡有兩種做法：  
  - 直接對係數做一次 SoS  
  - 直接對 $dp$陣列再做一次 SoS 扣掉  
    證明：
    當我枚舉第 $i$ 個bit的時候，他會涵蓋到 $i - 1$個bit往下的所有組合  
    （因為計算$dp$的順序），  
    所以這樣涵蓋到的剛好是除卻 $mask$ 的所有submask。

**[Code - 計算係數](https://codeforces.com/contest/449/submission/119426175)   [Code - 直接扣dp陣列](https://codeforces.com/contest/449/submission/119426267)**  











## 類題 - Codeforces 800D Varying Kibibits
**註：這題同時也是772D**  


給你一個長度為 $N$ 的整數陣列 $a$，令這個陣列叫做 $T$，  

定義$f(L)$（$L$是一個非空集合）：  
他的值定義為：
  - 加入前導0，補成同樣長度  
  - 把每個位數都取$\min$  
  - 全部都在$10$進位以下。  

例如$f(530,\\,932,\\,81) = f(5\textbf{30},\\,9\textbf{3}2,\\,\textbf{0}81) = 030 = 30$。  

又定義$\displaystyle G(x) = x \cdot \left( \sum_{\begin{matrix} S\subseteq T,\\, \\\\ S\neq\varnothing,\\, \\\\ f(S)=x \\\\ \end{matrix}} \left( \sum_{y\in S}y \right)^2 \mod 10^9+7 \right)$，  
輸出$G(0) \oplus G(1) \oplus G(2) \oplus \cdots \oplus G(999999)$。  
  
$N \leq 10^6,\\, a_i < 10^6$  

### 觀察
跟剛剛[這題](./#類題---codeforces-449d-jzzhu-and-numbers)很像，  

所以觀察原本的式子：  
$\displaystyle G(x) = x \cdot \left( \sum_{\begin{matrix}\varnothing \subset S\subseteq T,\\, \\\\ f(S)=x \\\\ \end{matrix}} \left( \sum_{y\in S}y \right)^2 \mod 10^9+7 \right)$  
如果改成：  
$\displaystyle G'(x) = x \cdot \left( \sum_{\begin{matrix}\varnothing \subset S\subseteq T,\\, \\\\ f(S){\color{yellowgreen}\geq}x \\\\ \end{matrix}} \left( \sum_{y\in S}y \right)^2 \mod 10^9+7 \right)$  
可以發現就是所有位數都大於等於 $x$ 的元素去組合，  
這時候又有：  
$\displaystyle G'(x) = x \cdot 2^{n(U) - 1} \left( \sum_{y\in U}y^2 + \sum_{y_1\in U}\sum_{y_2\in U}y_1y_2 \mod 10^9+7 \right)$  
其中 $\displaystyle U = \arg\max_{\begin{matrix} S \subseteq T \\\\ \forall a_i \in S,\\,\text{each digit of } a_i \geq x\end{matrix}} n(S)$，  
這個式子有點亂，但它的意思是：  
  - $U$ 是所有位數都大於等於 $x$ 的該位數形成的集合，  
  - 所以，它的組合有 $2^{n(U)}$ 種，  
  - 算出來的時候，$a_i^2$ 總共有 $2^{n(U) - 1}$ 個，  
      - 因為每個組合會貢獻 $1$ 個，總共有 除了該元素都有取或不取$ \Rightarrow 2^{n(U) - 1}$ 個集合
  - 每個$a_ia_j$也剛好有 $2^{n(U) - 1}$ 個，
      - 因為每個組合會貢獻 $2$ 個，總共有 除了那兩個元素都有取或不取$ \Rightarrow 2^{n(U) - 2}$ 個集合  

這個東西就是上面所描述的，接著，再由  
$\displaystyle\left(\sum_{i = 1}^{n(U)} a_i \right)^2 =  \sum_{i = 1}^{n(U)} a_i^2 + \sum_{i = 1}^{n(U)}\sum_{j = i + 1}^{n(U)} 2a_ia_j$  
可以額外紀錄$\displaystyle\sum_{i = 1}^{n(U)} a_i^2$湊出上面的結果，  

所以簡單整理一下，總共需要  
  - 紀錄平方和跟總和  $\Rightarrow$ SoS  
  - 將總和平方，湊出函數值
  - 對結果排容，得出答案  $\Rightarrow$ SoS  

注意這裡的 SoS 跟二進位下有些許不同，  
<details>
  <summary>做法</summary>

  當我們要算總和的時候，  
  需要枚舉該位是不是 $9$，  
  從大到小枚舉，這樣我取$1$才能接續取到 $2,\\,3,\\,\cdots,\\,9$。  
  
  當我們要排容的時候，  
  需要枚舉該位是不是 $9$，  
  從小到大枚舉，這樣我取$1$才能留下 $2,\\,3,\\,\cdots,\\,9$，  
  排掉更低位數不合的情況。    
    
</details>

**[Code](https://codeforces.com/contest/800/submission/119512284)**  

## 後記

### Reference  
[Codeforces Blog - SOS Dynamic Programming \[Tutorial\]](https://codeforces.com/blog/entry/45223)  
[A Simple Introduction to SoS(Sum over Subset) Dynamic Programming](https://robert1003.github.io/2020/10/05/dp-sum-over-subset.html)  


還有感謝在Code Community提示我，讓我想出這些題目的所有人。

    