---
title: "[數論] 質數與模運算"
date: 2021-07-29T15:13:11+08:00
draft: false
tags: ["math"]
summary: "笨方塊想學數學被爆揍，燒雞"
---

[2021 Feb 7] 從寒訓整理一些東西出來，不然我好像會跟不上 :(  
[2021 Jun 2] 重新翻修，發現以前寫錯好多;w;  
[2021 Jul 29] 更新一些小細節  
[2021 Aug 16] 修正一些小錯誤與排版  
[2025 Feb 10] 修正排版以及重新敘述眾多數學上模糊或不正確的觀念  


## 質數篩法

### 最基礎的想法
用一個陣列維護當前的質因數個數，最容易想也做容易寫，
實作上**從 3 開始判奇數**及**質數用到 $\sqrt{N}$ 就停止**可以節省一些常數。

<details>
  <summary>Code</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int prime[100000], index = 1;

int main()
{
    //Easy Sieve
    // | Range |  Time  |
    // |-------|--------|
    // |  1e5  |   3 ms |
    // |  1e6  |  76 ms |
    // |  1e7  | 1.5  s |

    prime[0] = 2;
    for (int i = 3; i < 1000000; i += 2)
    {
        bool isprime = true;
        for (int j = 0; prime[j] <= sqrt(i) && isprime; j++)
            if (!(i % prime[j]))
                isprime = false;
        if (isprime)
            prime[index++] = i;
    }
}
```
  
</details>   
  
### 埃式篩法
基本上跟上個做法很像，不過換成：
如果找到一個質數，**把這個質數的所有倍數都標記為不是質數**，
這個算法的優化也跟上一個差不多。

對於 $N$ 個數字，有 $\frac{}{}$ 被 $2$ 篩到，$\frac{}{}$ 被 $3$ 篩到，最後的數列接近：  

$$N \times (\frac{1}{2} + \frac{1}{3} + \frac{1}{5} + \frac{1}{7} + \cdots) = O(N \ln \ln N)$$

時間複雜度約為 $\mathcal{O}(N \log \log N)$。

實作上程式較短，也比較容易壓常數。

<details>
  <summary>Code</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

bitset<100000> notprime = 3;

int main()
{
    //Eratosthenes Sieve
    // | Range |  Time  |
    // |-------|--------|
    // |  1e5  |   1 ms |
    // |  1e6  |  12 ms |
    // |  1e7  | 144 ms |
    // |  4e7  | 630 ms |
    // |  5e7  | 833 ms |
    // |  1e8  | 1.9  s |

    //Pre-compute all 2n except 2
    for (int i = 4; i < 100000; i += 2)
        notprime[i] = 1;

    //Main Program
    for (int i = 3; i < sqrt(100000); i += 2)
        if (!notprime[i])
            for (int j = i * 3; j < 100000; j += i * 2)
                notprime[j] = 1;
}
```
</details>

### 線性篩法
線性篩法的精神是：
如果有一個數是合數，那他就應該**只被篩掉一次**，
如果某個數字 $K = p_1 p_2 p_3 \cdots p_n$，其中 $p_1 \leq p_2 \leq p_3 \leq \cdots \leq p_n$，
我們希望他只被最大的東西篩掉，所以排除自己，最大的就是 $p_2 p_3 \cdots p_n$。

對於每個數 $C = p_1 p_2 p_3 \cdots p_n$，可以篩掉 $p \times p_1 p_2 p_3 \cdots p_n$，
其中 $p \leq p_1$，否則我們篩掉的那個數字有更大的合數因數：$p p_2 p_3 \cdots p_n$。
  
複雜度是 $\mathcal{O}(N)$，由於每個數都只會被篩到一次（或不被篩到）。

<details>
  <summary>Code</summary>

```cpp
#include <bits/stdc++.h>
#define N 20000000
using namespace std;

bitset<N + 1> notprime = 3;
vector<int> prime;

int main()
{
    //Linear Sieve
    // | Range |  Time  |
    // |-------|--------|
    // |  1e5  |   3 ms |
    // |  1e6  |  36 ms |
    // |  1e7  | 362 ms |
    // |  2e7  | 732 ms |
    // |  1e8  | 3.8  s |

    for (int i = 2; i <= N; i++)
    {
        if (!notprime[i])
            prime.emplace_back(i);
        for (auto j : prime)
        {
            if (i * j > N)
                break;
            notprime[i * j] = 1;
            if (!(i % j))
                break;
        }
    }
}
```
</details>

### 質數篩法 + DP
如果在篩掉的時候順便紀錄**是被誰篩掉的**，可以在短時間求得質因數相關問題的解，
如果要遞迴下去做也可以快速的知道其中的兩個因數。

這樣可以做到 $\mathcal{O}(\log C)$ 質因數分解，對於一些問題是很好用的。

對於線性篩，這可以用來建各種積性函數（也就是滿足當 $\gcd(a, b) = 1$，那 $f(ab) = f(a)f(b)$ 的函數）。

### 次線性篩
我不會。

## GCD
### 貝祖定理
對任意的 $a,b,c \in \mathbb{Z}$，則有 $ax+by=c$ 存在整數解 $x, y \Longleftrightarrow \gcd(a,b) \mid c$。

證明：
- $(\Rightarrow)$   
    因為 $\gcd(a,b) \mid a, \gcd(a,b) \mid b$，可以直接把最大公因數提出來。
    所以一定有 $\gcd(a,b) \mid c$。
 
- $(\Leftarrow)$  
    -   我們只需要證明有 $\exists s,t \in \mathbb{Z}$ 使得 $as+bt = \gcd(a,b)$ 就好，
        因為其他的都可以用倍數的方式湊出來。  

        先排掉 $a = b = 0$，這時候顯然只有 $c = 0$ 有解。

        讓集合 $S = \{ax + by > 0 |x , y \in \mathbb{Z}\}$，也就是所有**正的** $a$ 跟 $b$ 的整數線性組合。
        集合 $S$ 不可能是空的（至少有一個元素 $a$ 或 $b$）

        根據良序定理（粗淺的說，整個集合都是整數，可以好好訂出順序抓到最小的東西），
        存在一個最小的 $d = ax' + by' > 0$ 在集合裡面，
        
        萬一 $d$ 不是 $a, b$ 的公因數怎麼辦？沒關係，那我們直接拿去除除看，
        根據除法定理，我們可以寫出 $a = qd + r$，$q$ 是商、$r$ 是餘數所以 $0 \leq r < d$。
        如果沒有整除，那 $d - r = a - (ax' + by') > 0$，也在集合裡面，就跟 $d$ 是最小的元素矛盾了。
        所以 $r = 0$。同樣的事情也會發生在 $b$ 上，因此 $d \mid a, d \mid b$。 
        
        $d$ 是一個公因數，那 $d \mid \gcd(a, b)$，$ax + by = d$ 有解就會直接導致 $ax + by = \gcd(a,b)$ 也有解。


### 擴展歐幾里得方法

如果原式 $ax+by=c$ 有解，可以轉換為：
$bx + (a - kb)y = c$ 有解（由於這樣處理 $\gcd$ 不變，仍然有解）

$k$ 可以取任何我們開心的數字，所以一般來說都是取除法的餘數，這樣遞迴的速度才會是 $O(\log \min (a, b) + 1)$。

這樣遞迴與一開始的式子關係何在呢？因為用除法寫出 $a = qb + r$ 的時候，

$$
    \begin{align*}
        bx' + ry' & = c \\
        bx' + \left(a - b\left\lfloor\frac{a}{b}\right\rfloor\right)y' & = c \\
        bx' + ay' - b\left\lfloor\frac{a}{b}\right\rfloor y' & = c \\
        ay' + b\left(x' - \left\lfloor\frac{a}{b}\right\rfloor y'\right) & = c \\
    \end{align*}
$$  

中間 $a, b$ 其實就是做輾轉相除法的過程，必會遇到其中一項為 $0$ 的情況，可以直接解出來。

求出來的答案是有個 bound 的。注意對於負數要特判，先取絕對值，計算出來再把符號加回去。

<details>
  <summary>Code</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

// Notice the sign of a, b 
void exgcd(int a, int b, int c, int &x, int &y)
{
    if (b == 0)
        x = c / a, y = 0;
    else
    {
        exgcd(b, a % b, c, y, x);
        y -= x * (a / b);
    }
}
```
</details>

## 模運算
如果有兩個數字 $a, b$ 除以 $m$ 的餘數相等，或者比較正式的定義 $m \mid (a-b)$，那就計 $a \equiv b \mod m$。

在這個狀況下，整個集合被稱為 $\mathbb Z/m\mathbb Z$。這個符號是什麼呢？是來自代數結構中 ring 的 quotient ring。
數學上，$m\mathbb Z$ 是這個集合：

$$ m\mathbb Z = \{\ldots, -3m, -2m, -m, 0, m, 2m, 3m, \ldots\} $$

也就是所有整數乘上 $m$。$\mathbb Z/m\mathbb Z$ 裡面的元素長得像是

$$ \mathbb Z/m\mathbb Z = \{0 + m\mathbb Z, 1 + m\mathbb Z, \ldots, (m - 1) + m\mathbb Z \} $$

可以想像「除以 $m$ 的餘數」把整數分成 $m$ 個區域，$0$ 所在的區域都是被 $m$ 整除的，$1$ 所在的區域都是除以 $m$ 餘 $1$ 的數字，他們剛好會是

$$ 1 + m\mathbb Z = \{\ldots, 1 -3m, 1 -2m, 1 -m, 1, 1 + m, 1 + 2m, 1 + 3m, \ldots\} $$

所以說 $1 \equiv 8 \mod 7$，可以寫成 $1 + 7\mathbb Z = 8 + 7\mathbb Z$。
這也是為什麼符號不能單純地用兩槓的等於（這樣有點怪），然後很常使用的題目寫著輸出 $\mod m$ 其實不太正確，
因為技術上來說 $1, 1 + m, 1 - m$ 都是對於答案的餘數是 $1$ 而言正確的答案。

$$ \renewcommand{\cmod}{\operatorname{\%}} $$
因此，對於以下的內容，我們從 C++ 偷了 $a \cmod b$ 這個符號來代表真實意義上的餘數。

### 基本運算
餘數下的運算其實跟一般加減乘有很類似的規則（或精確地說，結構）：

1. $a \equiv b \mod m, c \equiv d \mod m \Longrightarrow a+c \equiv b+d \mod m$
2. $a \equiv b \mod m, c \equiv d \mod m \Longrightarrow ac \equiv bd \mod m$
3. $a \equiv b \mod m \Longrightarrow a^k \equiv b^k \mod m$（$k \in \mathbb Z^+$）
   - 不用任何炸開，用 2. 套數學歸納法就可以了。
4. $ca \equiv cb \mod n \Rightarrow a \equiv b \mod \frac{n}{\gcd(n, c)}$  
    證明：令 $d = \gcd(n, c)$，
    $n \mid c(a-b) \Rightarrow \frac{n}{d} \mid \frac{c}{d}(a-b)$。
    而且 $\gcd(\frac{n}{d}, \frac{c}{d}) = 1$，
    故 $\frac{n}{d} \mid (a-b) \Longrightarrow a \equiv b \mod \frac{n}{d}$

### 模反元素
如果模運算可以除法，那不是很美妙嗎？
在實數底下，可以做除法的核心概念是對於非 $0$ 的元素，都有倒數存在：

$$ a \times \frac a 1 = $$

這樣就可以用「乘上倒數」的方法把他除掉。

在模運算底下，如果存在兩個數 $a, b$ 滿足 $a \times b \equiv 1 \mod m$，
我們稱 $b$ 是 $a$ 的反元素，記為 $a^{-1}$。

在除以任意正整數（$\mathbb Z/m\mathbb Z$）的世界下，不見得每個非零的元素都有反元素，
例如 $\mathbb Z/9\mathbb Z$ 下：

|$a$     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|--------|---|---|---|---|---|---|---|---|
|$a^{-1}$| 1 | 5 |   | 7 | 2 |   | 4 | 8 |

模反元素是可以用擴展歐幾里得算法求出來的！
因為 $ab \equiv 1 \mod m$，那表示 $m \mid (ab - 1)$，也就是有某個整數 $k$ 滿足 $ab - 1 = km$。

可以透過解　$ab + km = 1$，解出的 $b$ 就是反元素。
此時，根據貝祖定理，$\gcd(a, m)$ 是 $1$ 若且唯若反元素是存在的！

另外，如果需要建反元素表，可以用以下推導出的遞迴式：  
$$
    \begin{align*}
        P - i \times \left\lfloor\frac{P}{i}\right\rfloor & = P \cmod i \newline  
        P - i \times \left\lfloor\frac{P}{i}\right\rfloor & \equiv P \cmod i \mod P  \newline  
        P \times i - i \times \left\lfloor\frac{P}{i}\right\rfloor & \equiv P \cmod i \mod P  \newline  
        i \times (P - \left\lfloor\frac{P}{i}\right\rfloor) & \equiv P \cmod i \mod P  \newline  
        i \times (P - \left\lfloor\frac{P}{i}\right\rfloor) (P \cmod i)^{-1} & \equiv 1 \mod P \newline   
        (P - \left\lfloor\frac{P}{i}\right\rfloor) (P \cmod i)^{-1} & \equiv i^{-1} \mod P  \newline  
        i^{-1} & \equiv (P - \left\lfloor\frac{P}{i}\right\rfloor) (P \cmod i)^{-1} \mod P \newline  
    \end{align*}
$$
$P \cmod i$ 會不會沒有反元素？不可能，因為 $\gcd(P, i) = \gcd(P \cmod i, i)$。
這樣就能夠在 $\mathcal{O}(P)$ 內建完反元素表了。 
 
<details>
  <summary>Code</summary>

#### Code
```cpp
#include <bits/stdc++.h>
#define N 9
using namespace std;

int inv[N];

void build_inv()
{
    inv[1] = 1;
    for (int i = 2; i <= N; i++)
        inv[i] = ((N - (N / i)) * inv[N % i]) % N;
}
```
</details>

### 費馬小定理
在質數 $p$ 的 $\mathbb Z/p\mathbb Z$ 下，對於任意整數 $a$ 及質數 $p$，有：
 - $a^{p} = a \mod p$  
 - $a^{p-1} = 1 \mod p$（這個是定理的敘述）  
 - $a^{p-2} = a^{-1} \mod p$  

［證明］  
對於 $a, 2a, 3a, \cdots, (p-1)a$ 在$\mod p$ 下必須一一對應到 $1, 2, 3, \cdots, p-1$，  
否則兩個同樣餘數的相減就可以得到 $a \mid p$ 的矛盾。
連乘之後得到

$$ (p-1)!a^{p-1} \equiv a \times 2a \times \cdots \times (p-1)a \equiv 1 \times 2 \times \cdots \times (p-1) \equiv (p-1)! \mod m \Longrightarrow a^{p-1} \equiv 1 \mod m$$

所以在質數底下，反元素有另一種求法是透過**費馬小定理**。

### 歐拉函數
#### 定義
**歐拉函數** $\varphi(n)$ 的值是在 $1, 2,...,n$ 中與 $n$ 互質的個數。
常用 $\mathbb Z/m\mathbb Z^*$ 代表從 $\mathbb Z/m\mathbb Z$ 中 $n$ 互質的數，
不過事實上這個敘述是很數學上不精確的（記得我們剛剛說 $\mathbb Z/m\mathbb Z$ 裡面的元素都是集合）。

精確來說，$\mathbb Z/m\mathbb Z^*$ 裡面有的元素是 $\mathbb Z/m\mathbb Z$ 裡面可以做「乘除法」的元素。
也就是說，要有反元素，等價於 $\gcd(m, a)$ 的時候，$a + m\mathbb Z$ 會在 $\mathbb Z/m\mathbb Z^*$ 裡面。

不過第一個最基礎的關係是 $\mathbb Z/m\mathbb Z^*$ 有 $\varphi(n)$ 個元素。

#### 計算
求歐拉函數 $\varphi(n)$ 的值，
最暴力的方法是檢查每個 $1 \leq x < n$ 滿足 $\gcd(n, d) \neq 1$，
但這樣太慢了！

事實上，$\varphi(n)$ 是積性的，也就是說對於 $\gcd(m, n) = 1, \varphi(mn) = \varphi(m)\varphi(n)$。

［證明］  
把 $mn$ 個數排成下面的樣子：

$$
    \begin{matrix}
        1 & 2 & 3 & \cdots & m \\
        m + 1 & m + 2 & m + 3 & \cdots & 2m \\
        2m + 1 & 2m + 2 & 2m + 3 & \cdots & 3m \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        (n-1)m + 1 & (n-1)m + 2 & (n-1)m + 3 & \cdots & nm 
    \end{matrix}
$$

每一橫列都有 $\varphi(m)$ 個元素是跟 $m$ 互質的，
而且 $kp + r \equiv r \mod m$，所以有 $\varphi(m)$個直排是與$m$互質的。

每一直排也都有 $\varphi(n)$ 個元素是跟 $n$ 互質的，
因為把每一直排都寫成 $km+r$ 的樣式，每一個必須在$\mod n$ 下一一對應到 $0, 1, ..., n-1$，
否則可以找到 $(k_0 - k_1)m \mid n$，也就是說兩數不互質的矛盾。
所以可以得到有 $\varphi(m)$ 個直排與 $m$ 互質，每排有 $\varphi(n)$ 個元素是跟 $n$ 互質。

因為與 $m, n$ 都互質的元素也會跟 $mn$ 互質，
（否則，它跟 $mn$ 的GCD一定也是 $m$ 或 $n$ 的因數）
得證 $\gcd(m, n) = 1 \Longrightarrow \varphi(mn) = \varphi(m)\varphi(n)$。
  
不過同時可以發現，如果可以把某個數換成質數的乘積，就可以把他們全部乘起來：
$$
    N = {p_1}^{a_1}{p_2}^{a_2}{p_3}^{a_3} \cdots {p_n}^{a_n} \Longrightarrow
    \varphi(N) = \varphi({p_1}^{a_1})\varphi({p_2}^{a_2})\varphi({p_3}^{a_3}) \cdots \varphi({p_n}^{a_n})
$$

如果某數 $M$ 是某個質數 $p$ 的 $k$ 次方，與他不互質的數必定是 $p$ 的倍數，共有 $\frac{M}{p}$ 個，故：

$$\varphi(M) = M - \frac{ M}{ p} = M \times \frac{ p-1}{ p}$$

套在前面的式子可以發現：

$$
    \begin{align*}
    \varphi(N)
    & =     {p_1}^{a_1} \cdot \frac{p_1-1}{p_1} \times
            {p_2}^{a_2} \cdot \frac{p_2-1}{p_2} \times
            {p_3}^{a_3} \cdot \frac{p_3-1}{p_3} \times
            \cdots \times
            {p_n}^{a_n} \cdot \frac{p_n-1}{p_n} \\
    & = N \prod \frac{p-1}{p}
    \end{align*}
$$

如果要同時求很多數字的歐拉函數，也可以用質數篩去蓋出來。

### 中國剩餘定理
#### 定理

方程組
<!-- -->
$$\begin{cases} 
    x \equiv a_1 \mod n_1 \newline
    x \equiv a_2 \mod n_2 \newline
    x \equiv a_3 \mod n_3 \newline
    \vdots \newline
    x \equiv a_k \mod n_k 
    \end{cases}
$$
當所有 $1 \leq i,  j \leq k,  i \neq j$，都有 $n_i, n_j$ 互質時，$x$ 有解。
而且對於 $x' \equiv x \mod n_1n_2\cdots n_k$，$x'$ 也是一組解。

#### 求解
如果方程組只有兩個式子：

$$   
\begin{cases} 
    x \equiv a_1 \mod n_1 \\
    x \equiv a_2 \mod n_2 
\end{cases}
$$
可以化為：
$$
\begin{cases} 
    x = pn_1 + a_1 \\
    x = qn_2 + a_2
\end{cases}
$$
$$pn_1 + a_1 = qn_2 + a_2$$
$$pn_1 - qn_2 = a_2 - a_1$$

由於 $\gcd(n_1 - n_2) = 1$，所以方程式必有解（而且不只一組） 
利用擴展歐幾里得算法解得的 $p, q$ 回推 $x$，
而此時所有 $x + kn_1n_2$ 都是答案。

對於多組方程式的問題，就可以使用分治，
合併時再使用擴展歐幾里得算法。

另一種想法是對於每個式子，都構建一個解 $e_i$ 使得在$\mod n_i$ 下為 $1$，其他為 $0$，
這樣只要把 $a_i e_i$ 加起來就是要求的 $x$。

設 $N = n_1n_2\cdots n_k$，$n_i^* = \frac{N}{n_i}$，
顯然 $e_i$ 為$n_i^*$的倍數，設 $e_i = t_i n_i^*$，
現在要解的方程式就變為 $t_i n_i^* \equiv 1 \mod n_i$。

把原本的方程式化為 $t_i n_i^* + sn_i = 1$
就可以使用擴展歐幾里得算法找出解，
原本要解的 $x$ 就變為 $\sum_{n=1}^{k} a_i e_i$。

或是觀察這個式子 $t_i n_i^* \equiv 1 \mod n_i$：
其實要求的 $t_i$ 就是 $\mod n_i$ 下的模反元素，
不過注意這邊不能直接一起合併為 $1$，因為答案並不是在 $\mod n_i$ 下，
所以要解的 $x$ 就變為 $\sum_{n=1}^{k} a_i t_i n_i^*$，
模反元素可以用遞迴方法求解。

總算法的時間複雜度是 $\mathcal{O}(k \log \max n_i)$。
<details>
  <summary>分治做法的 Code</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> a = {2, 3, 2}, n = {3, 5, 7};

void exgcd(int a, int b, int c, int &x, int &y)
{
    if (b == 0)
        x = c / a, y = 0;
    else
    {
        exgcd(b, a % b, c, y, x);
        y -= x * (a / b);
    }
}

pair<int, int> solve(int L, int R)
{
    if (L == R)
        return make_pair(a[L], n[L]);
    if (L + 1 == R)
    {
        int p, q, N = n[L] * n[R];
        exgcd(n[L], n[R], a[R] - a[L], p, q);
        return make_pair(((p * n[L] + a[L]) % N + N) % N, N);
    }
    pair<int, int> left = solve(L, (L + R) / 2), right = solve((L + R) / 2 + 1, R);
    int p, q, N = left.second * right.second;
    exgcd(left.second, right.second, right.first - left.first, p, q);
    return make_pair(((p * left.second + left.first) % N + N) % N, N);
}

signed main()
{
    cout << solve(0, 2).first;
}
```
</details>

<details>
  <summary>擴展歐幾里得作法的 Code</summary>  

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> a = {2, 3, 2}, n = {3, 5, 7};

void exgcd(int a, int b, int c, int &x, int &y)
{
    if (b == 0)
        x = c / a, y = 0;
    else
    {
        exgcd(b, a % b, c, y, x);
        y -= x * (a / b);
    }
}

signed main()
{
    int N = 1, ans = 0, t, s;
    for (int i = 0; i < n.size(); i++)
        N *= n[i];
    for (int i = 0; i < n.size(); i++)
    {
        exgcd(N / n[i], n[i], 1, t, s);
        ans = (ans + N / n[i] * a[i] * t) % N;
    }
    cout << ans;
}
```
</details>

<!-- ## 組合計數
### 卡塔蘭數
卡塔蘭數有很多定義方法，常見的有這些：  
 - 長度為 $n$ 的合法括號字串  
 - $N \times N$ 的網格上，用右上－左下的主對角線隔開，走在右下那部分，</br>只能往右以及往上，從左下走到右上不穿越主對角線的路徑數  
 - 長度為 $n$ 的 $\\{1,-1\\}$ 數列，任意前綴和非負的組合數  

以下比較常考慮第二個計數方法，  
定義 $C_0 = 1$，  
由於任意 $N \geq 1$ 的時候，方法可以透過 向右 + （$i \times i$ 的方法） + 向上 + （$(n - i - 1) \times (n - i - 1)$ 的方法）構成，  
所以有 $ C_{n + 1}\sum_{i = 0}^{n} C_iC_{n - i}$ 的遞迴關係。  

不過這樣計算 $C_n$ 需要 $O(n^2)$ 的時間，能不能更快？  

觀察到每一個不合法的路徑都會通過主對角線而碰到上面的一條平行線，  
但是把這條路徑對主對角線翻轉會出現太多一樣的路徑對應到同一種合法路徑，  
所以考慮對上移一格的平行線做翻轉，  
由於穿過主對角線表示目前往上多 $1$，而剩下的部分則是往右多 $1$，  
因此翻轉後會是往上多 $2$，走到 $(n - 1, n + 1)$ 的位置，  

{{< figure src="catalan.png" width="700" >}}  

然後對於所有走到 $(n - 1, n + 1)$ 都會通過上移一格的對角線，  
它們一一對應到一條不合法的路徑，而且不合法的路徑只有這些，  
所以卡塔蘭數的一般式就是 $C_n = \binom{2n}{n} - \binom{2n}{n - 1} = \binom{2n}{n} - \frac{n}{n + 1}\binom{2n}{n} =  \frac{1}{n + 1}\binom{2n}{n}$。   -->

<!-- ## Reference
其他還有很多不同的意義以及一般式的證明方法，詳細參考：  
[Wikipedia - Catalan number](https://en.wikipedia.org/wiki/Catalan_number) -->
