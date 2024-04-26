---
title: "Linear Programming - Simplex"
date: 2024-04-26T21:24:49+08:00
draft: false
tags: ["tutorial"]
summary: "不負責任亂教 LP"
---

## 前言

我在補掉某場 ICPC 的線性規劃題的時候，把之前亂寫一通的模板貼上去範測原地爆炸，才突然想到之前在寫這個模板的時候，原本的方法只有實作一半而已。因為網路上的模板有的看不懂，有些甚至不是好的，直接亂抄也不怎麼會用，因此開啟了修修線性規劃模板的過程。由於網路上的資源似乎零散或者過於困難，筆者智慧不足無法看懂，幾近崩潰之下終於寫出來了，在這裡試圖用筆者認為較為白話的方式紀錄。

不過筆者的實作稍微複雜，比起其他的模板稍微長一點，不過至少他是對的（吧）。

## LP

LP 就是線性規劃（Linear Programming），會被稱為線性規劃的原因是因為每個不等式都長的像是線性的樣子。例如說

$$
    \begin{array}{rrl}
        \text{maximize} & x + 2y \\\
        \text{subject to} 
        & x + y & \leq 3 \\\
        &    x & \geq 0 \\\
        &    y & \geq 0 
    \end{array}
$$

就是一組 LP，意思是說在 $x + y \leq 3, x \geq 0, y \geq 0$ 的條件下，目標是最大化 $x + 2y$，當然這個大家高中應該都有教，熟悉計算幾何的應該也要知道只有 $x, y$ 的時候該怎麼做。

接下來要介紹的是 LP 的正規形式（Canonical form），長的像是

$$
    \begin{array}{rrl}
        \text{maximize} & \mathbf{c}^\top\mathbf{x} \\\
        \text{subject to} 
        & A\mathbf{x} & \leq \mathbf{b} \\\
        &    \mathbf{x} & \geq 0 \\\
    \end{array}
$$

如果你一時之間看不懂的話，沒關係，這邊只是這樣的意思：

$$
    \begin{array}{rrl}
        \text{maximize} & c_1x_1 + c_2x_2 + \cdots + c_nx_n \\\
        \text{subject to} 
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n & \leq b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n & \leq b_2 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n & \leq b_m \\\
        &   x_i & \geq 0 \\\
    \end{array}
$$

也就是說，$c_i$ 是我們目標的各項係數，$a_{i, j}$ 是第 $i$ 個限制中第 $j$ 項的限制，這些限制加起來不能超過 $b_i$，而且總共有 $m$ 組不同的限制，另外，我們還限制每個變數要大於等於 $0$。

要怎麼把任意的 LP 都寫成正規的形式呢？只需要一些小小的變動。

1. 如果有變數 $x$ 可以是往正負無限跑（unbounded），那我們把他拆成
    $$x = x_+ - x_-$$
2. 如果目標是最小化，那我們可以直接加上一個負號變成最大化。
3. 如果有等號的狀況，拆成大於等於跟小於等於兩個條件。


有了這樣的正規 LP 之後，我們可以一頭栽入解出他的方法了。

## Simplex - Overview

Simplex 演算法的想法就是，二維的 LP 會是一個凸包，三維的 LP 會是 3D 凸包，所有的 LP 都是一個多維凸包（大部分的文獻都說是 polytope，但是多胞形太抽象了），既然這樣，我們就沿著凸包一直往答案變大的地方走下去，要是走不下去不就是結束了嗎？

換句話說，Simplex 其實只是在
- 先找一組合法解
- 一直走路
- 走不到就是最佳解

所以我們先介紹 Simplex Phase II，就是當我們在這個合法解內部的時候，怎麼走到最佳解。接著再介紹 Simplex Phase I 要怎麼走進合法解區域。

## Simplex - Phase II

在這裡，我們假設所有 $b_i \geq 0$，這樣一來 $x_i$ 都為 $0$ 就是一組合法解，我們直接從這裡出發。

Simplex 的想法是，既然大家都是小於等於：
$$
    \begin{array}{rrl}
        \text{maximize} & c_1x_1 + c_2x_2 + \cdots + c_nx_n \\\
        \text{subject to} 
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n & \leq b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n & \leq b_2 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n & \leq b_m \\\
        &   x_i & \geq 0 \\\
    \end{array}
$$
我們可以幫每個不等式補一個假的變數（slack variable）$s_i$，換成
$$
    \begin{array}{rrl}
        \text{maximize} & c_1x_1 + c_2x_2 + \cdots + c_nx_n \\\
        \text{subject to} 
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n + \boxed{s_1} & \boxed=\ b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n + \boxed{s_2} & \boxed=\ b_2 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n + \boxed{s_m} & \boxed=\ b_m \\\
        &   x_i, \boxed{s_j} & \geq 0 \\\
    \end{array}
$$
當然這些變數都要是非負的才會滿足原本的條件。同樣的狀況也可以**對目標函數**做事！也就是說我們開一個答案 $Z$，就可以轉換成
$$
    \begin{array}{rrl}
        \text{maximize} & \boxed{Z} \\\
        \text{subject to} 
        & \boxed{Z-c_1x_1 - c_2x_2 - \cdots - c_nx_n} & \boxed{= 0} \\\
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n + s_1 & = b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n + s_2 & = b_2 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n + s_m & = b_m \\\
        &   x_i, s_j & \geq 0 \\\
    \end{array}
$$
這時候要介紹一個概念：基底變數跟非基底變數（basic variable and non-basic variable）。基底變數可以想成是我們手上握著一組目前的答案，而非基底變數都會是 $0$，如果有學一點點線性代數，就可以想像成非基底是可以自由調整的變數，而我們在解空間內所以全部 $0$ 是一組合法解；而基底變數就是我們手上維持不變的解。在一開始的時候，我們一定是握著 $Z = 0, s_i = b_i$ 的這組基底。

只不過一直握著同一組基底沒有什麼意思，所以 Simplex 剛剛所說的走路就是指我們拿著一個非基底的變數走走看，如果能讓答案變大就走到底，同時原本的基底變數會有一個人離開，而剛剛的非基底變數會有一個人走進去。

聽起來好抽象，我們用一個例子看看。

$$
    \begin{array}{rrl}
        \text{maximize} & 2x + 3y + 4z \\\
        \text{subject to} 
        & 3x + 2y + z & \leq 10 \\\
        & 2x + 5y + 3z & \leq 15 \\\
        &    x,y,z & \geq 0 \\\
    \end{array}
$$

我們先轉換成等式的樣子：
$$
    \begin{array}{rrl}
        \text{maximize} & Z \\\
        \text{subject to} 
        & Z -2x - 3y - 4z   & = 0 \\\
        & 3x + 2y + z + s_1 & = 10 \\\
        & 2x + 5y + 3z + s_2 & =15 \\\
        &    x,y,z,s_1,s_2 & \geq 0 \\\
    \end{array}
$$
現在我們手上的解，也就是基底變數，是 $Z = 0, s_1 = 10, s_2 = 15$。這時候我們嘗試透過 $z$ 去增加答案，$z$ 可以增加多少呢？先不考慮第一列的目標函數，
- 第二列告訴我們 $z \leq 10$。
- 第三列告訴我們 $3z \leq 15 \Rightarrow z \leq 5$

我們直接讓第三列生效（因為他是最緊的限制），這時候 $z = 5$。為了處理這樣的改變，那一列的基底變數 $s_2$ 會被丟出去。此時基底受到 $z$ 的影響要做出改變才能滿足等式，也就是變成 $Z = 20, s_1 = 5, z = 5$。為了方便我們用高斯消去只讓第三列有 $z$，也就是
$$
    \begin{array}{rrl}
        \text{maximize} & Z \\\
        \text{subject to} 
        & Z +\frac 2 3x - \frac {11} 3 y + \frac 4 3 s_2 & = 0 \\\
        & \frac 7 3 x + \frac 1 3 y + s_1 - \frac 1 3 s_2 & = 5 \\\
        & 2x + 5y + 3z + s_2 & = 15 \\\
        &    x,y,z,s_1,s_2 & \geq 0 \\\
    \end{array}
$$
這時候非基底不管怎麼調整都不會變大，因為他們原本是 $0$，一變大 $Z$ 就會變小，換句話說我們達到最佳解了。


這時候你應該會有超級多問題，例如說
 - 為什麼要選 $z$？
 - 為什麼出去的是 $s_2$？
 - 為什麼要忽略第一列？
 - 為什麼可以說找到最佳解了？

沒關係，我第一次也看不懂。以下我們要來介紹我們想維護的一些**更強的性質**，讓演算法的輕鬆順利進行。

### 更多性質

我們選取任意一個非基底變數試圖放進來的時候，可以想像成原本的基底變數應該要做出相應的調整來維持等號的成立。這個非基底變數（範例中的 $z$）變大的時候，如果某個變數會一起變大，那這些變數都沒事，但是如果有變數變小的話，這個變數是不能跑到低於 $0$ 的，因此我們想換進來的變數就會受到這樣的限制。在這個範例中，我們可以顯而易見的發現是 $s_2$，但是還記得調整之後我們做了高斯消去嗎？這是因為我們想要滿足

- 如果一個變數是基底變數，那只可以有一橫列他的係數非 $0$。

這樣的好處是當我們在放進一個非基底變數的時候，不需要透過其他運算就可以輕鬆得到是誰先出去。維護的方法也只需要拿進去基底變數的那一橫列去消去就好。我們把剛剛上面的狀況排好看之後感受一下。
$$
    \begin{array}{rrrrrrrl}
        \text{maximize} & Z \\\
        \text{subject to} 
        & \boxed{Z} & -2x & -3y & -4z & & & = 0 \\\
        & &3x &+ 2y &+ z &\boxed{+ s_1}& & = 10 \\\
        & &2x &+ 5y &+ 3z &&\boxed{+ s_2} & =15 \\\
        & &   x,&y,&z,&s_1,&s_2 & \geq 0 \\\
    \end{array}
$$
$$
    \begin{array}{rrrrrrrl}
        \text{maximize} & Z \\\
        \text{subject to} 
        & \boxed Z &+\frac 2 3x &- \frac {11} 3 y &&&+ \frac 4 3 s_2 & = 0 \\\
        & &\frac 7 3 x &+ \frac 1 3 y &&\boxed{+ s_1} &- \frac 1 3 s_2 & = 5 \\\
        & &2x &+ 5y &\boxed{+ 3z} &&+ s_2 & = 15 \\\
        & &   x,&y,&z,&s_1,&s_2 & \geq 0 \\\
    \end{array}
$$
這時候我們把要離開的變數所對應的列叫做 pivot row，我不知道這個的翻譯是啥，但是如果你學過高斯消去法應該就會知道這是什麼意思。

因為上面的因素，你才不會想要把第一列消掉，一消下去 $Z$ 就變 $0$，整個社會大倒退。所以我們永遠不會選擇第一列。

在第一列就是目標的時候，選擇誰要加入基底變數就相當簡單，如果他在第一行的係數是負的，那增加他 $Z$ 就會變大，也就是我們想要的。但反過來如果他是正的，$Z$ 就會變小，我們的演算法就會倒退，也就是說這樣就會是不好的。

這樣一說其實一開始選 $x, y, z$ 都可以，但是為了實作方便，以及避免不斷繞圈的狀況，進入的變數（entering variable）的選擇就會是選擇第一列係數最小的變數；離開的變數（leaving variable）就會是該直行 $a_{i, j} > 0$ 而 $\dfrac{b_i}{a_{i, j}}$ 最小的列對應的基底變數。如果說全部都是 $a_{i, j} \leq 0$，那就代表說這個變數可以任意大都不會影響條件，這時候就可以 $Z = \infty$，在這個狀況下我們說最大值沒有上界（Unbounded）。
 
這也可以解釋為什麼當找不到負的狀況的時候，我們就抵達最佳解了。

### Implementation

```cpp
struct simplex 
{
    const double inf = 1 / .0, eps = 1e-9;
    int n, m, var[205];
    double A[205][205], B[205], x[205];
    void init(int _n) { n = _n; }
    void equation(vector<double> a, double b)
    {
        for (int i = 0; i < n; i++) A[m][i] = a[i];
        B[m] = b;
        A[m][n + m] = 1, x[n + m] = b, var[m] = n + m;
        ++m;
    }
    double solve(vector<double> c) 
    {
        for (int i = 0; i < n; i++) A[m][i] = -c[i];
        A[m][n + m] = 1, var[m] = n + m;
        while (true)
        {
            int in = min_element(A[m], A[m] + n + m + 1) - A[m];
            if (A[m][in] >= -eps)
                break;
            double bx = inf;
            int piv = -1;
            for (int j = 0; j < m; j++)
                if (eps < A[j][in] && B[j] / A[j][in] <= bx)
                    piv = j, bx = B[j] / A[j][in];
            if (bx == inf) return inf;

            int out = var[piv];
            for (int j = 0; j <= m; j++)
                if (j != piv)
                {
                    x[var[j]] -= bx * A[j][in] / A[j][var[j]];
                    double f = A[j][in] / A[piv][in];
                    for (int k = 0; k <= n + m; k++)
                        A[j][k] -= A[piv][k] * f;
                    B[j] -= B[piv] * f;
                }
            x[out] = 0, x[in] = bx, var[piv] = in;
        }
        return x[n + m];
    }
} lp;
```

在這份程式碼中，我是使用 $x_0, x_1, \ldots, x_{n-1}$ 來代表原始的變數，$x_n, x_{n+1}, \ldots, x_{n+m-1}$ 是代表 slack variable $s_0, s_1, \ldots, s_{n-1}$，而 $Z$ 是被放在最後的 $x_{n+m}$。`while(true)` 裡面做的事就是不斷的選取進入的變數 `in`，然後選取 $\frac{b_i}{a_{i, j}}$ 最小的當作 pivot 之後，就能知道那一行要出去的基底變數 `out` 是誰。如果選不到 pivot 的話，就可以直接斷定答案是 $\infty$。

接著的 `for` 迴圈就是更新基底變數的值、做出高斯消，然後就能替換基底變數了。最後做完的時候 $Z$ 應該要除以該項係數，但是因為 $Z$ 永遠不會離開基底，係數自然就會維持是 $1$ 了。

Phase II 的實作應該相當簡單，讀者可以嘗試先寫出 [UOJ 179 線性規劃](https://uoj.ac/problem/179) 的一、三子題，後面 Phase I 結束就可以做出四個子題（Extra test 需要自己實作小數，但是基本上實際運用場合不太容易有這樣的狀況）。


## Simplex - Phase I

在 Phase I 中要處理的就是我們 Phase II 假設的問題，也就是說我們要勇敢的跨出「$x_i = 0$ 不再是一組解」的狀況。例如說

$$
    \begin{array}{rrl}
        \text{maximize} & x + 2y \\\
        \text{subject to} 
        & x + y & \leq 4 \\\
        & x + y & \geq 2 \\\
        & x - y & \leq 1 \\\
        & x - y & \geq -1 \\\
        & x, y & \geq 0 
    \end{array}
$$
的可行空間會是一個轉了 45 度的正方形，最大值是 $6.5$，但是我們不能再從 $(x, y) = (0, 0)$ 開始了！在另一個例子當中，
$$
    \begin{array}{rrl}
        \text{maximize} & x + 2y \\\
        \text{subject to} 
        & x + y & \leq 2 \\\
        & x + y & \geq 3 \\\
        & x, y & \geq 0 
    \end{array}
$$
甚至沒有任何一組解。Phase I 的目的就是想要找到有沒有這樣的一組解，如果有的話就找出來，剩下的就能交給 Phase II 了！

### 問題轉換

具體來說，我們要怎麼做到這件事呢？假設對於原本的限制，
$$
    \begin{array}{rrl}
        \text{maximize} & Z \\\
        \text{subject to} 
        & Z-c_1x_1 - c_2x_2 - \cdots - c_nx_n & = 0 \\\
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n + s_1 & = b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n + s_2 & = b_2 \\\
        & a_{3,1}x_1 + a_{3,2}x_2 + \cdots + a_{3,n}x_n + s_3 & = b_3 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n + s_m & = b_m \\\
        &   x_i, s_j & \geq 0 \\\
    \end{array}
$$
這時候，**假設只有 $b_2, b_3 < 0$，其他都還是正的**，那我們在選取原本的基底變數的時候，就會窒礙難行，因為我們的起始點 $s_2 = b_2, s_3 = b_3$ 是不合法的。

這時候，我們要做的是在 $b_i < 0$ 的條件**再引入更多變數**（這些稱為 artifical variable），例如說從上面的例子，我們就可以創造 $t_2, t_3$：
$$
    \begin{array}{rrrl}
        % \text{maximize} & Z \\\
        \text{subject to} 
        & Z-c_1x_1 - c_2x_2 - \cdots - c_nx_n & & = 0 \\\
        & a_{1,1}x_1 + a_{1,2}x_2 + \cdots + a_{1,n}x_n + s_1 & & = b_1 \\\
        & a_{2,1}x_1 + a_{2,2}x_2 + \cdots + a_{2,n}x_n + s_2 & \boxed{-t_2} & = b_2 \\\
        & a_{3,1}x_1 + a_{3,2}x_2 + \cdots + a_{3,n}x_n + s_3 & \boxed{-t_3} & = b_3 \\\
        & \vdots \\\
        & a_{m,1}x_1 + a_{m,2}x_2 + \cdots + a_{m,n}x_n + s_m & & = b_m \\\
        &   x_i, s_j, & \boxed{t_k} & \geq 0 \\\
    \end{array}
$$
這樣做的意義在哪裡呢？如果 $t_k$ 都必須要是正的，因為原本都是小於等於的狀況，所以在原本的限制底下就根本沒有解，所以換句話說，**如果我們嘗試最大化 $-t_2-t_3$，就可以得知原本有沒有解！**

讓我們直接來看一個例子。
$$  
    \begin{array}{rrl}
        \text{maximize} & -x -y \\\
        \text{subject to} 
        & x + 2y & \geq 2 \\\
        & 2x + y & \geq 2 \\\
        & x, y & \geq 0 
    \end{array}
$$
轉換成 Simplex 的樣子就是
$$  
    \begin{array}{rrrrrl}
        \text{maximize} & Z \\\
        \text{subject to}
        & Z & +x +y     &           && = 0 \\\ 
        &   & -x - 2y    & +s_1      && = -2 \\\
        &   & -2x - y    & +s_2      && = -2 \\\
        &   &   x, y,   & s_1, s_2  &&\geq 0 
    \end{array}
$$
對於 $b_i$ 是負的條件，我們都補上一個 $t_i$。在這個例子裡是全部都是負的，所以在 Phase I 的一開始會先轉換成
$$  
    \begin{array}{rrrrl}
        \text{maximize} & \boxed{-t_1-t_2} \\\
        \text{subject to}
        % & Z & +x +y     &           && = 0\\ 
        & -x - 2y    & +s_1      & \boxed{-t_1}  & = -2 \\\
        & -2x - y    & +s_2      & \boxed{-t_2}  & = -2 \\\
        &   x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$
然後會重新做一個新的目標函數：
$$  
    \begin{array}{rrrrrl}
        \text{maximize} & \boxed{Z'} \\\
        \text{subject to}
        & Z' &        &           & \boxed{+t_1+t_2} & =  -4 \\\
        && -x - 2y    & +s_1      & -t_1  & = -2 \\\
        && -2x - y    & +s_2      & -t_2  & = -2 \\\
        &&   x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$
這時候我們的基底變數是 $Z' = -4, t_1 = 2, t_2 = 2$。不過我們的目標函數沒辦法得知要調整哪個非基底變數，所以我們先做高斯消去（其實只要代換就好，因為只有第一列要被消掉）。
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' & \boxed{-3x-3y} & \boxed{+s_1+s_2} && = -4 \\\
        && -x - 2y    & +s_1      & -t_1  & = -2 \\\
        && -2x - y    & +s_2      & -t_2  & = -2 \\\
        &&  x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$
進入的變數很顯然就會是選擇 $x, y$ 的其中一個，不過在 Phase II 當中，我們原本說
 - 離開的變數（leaving variable）就會是該直行 $a_{i, j} > 0$ 而 $\frac{b_i}{a_{i, j}}$ 最小的列對應的基底變數。

這件事情壞掉了，理由是因為 Phase II 一開始的基底變數都是 $s_i$，所以過程中保證基底變數那一列的所有的係數都是正的，所以可以直接取得正確的離開變數，所以這邊我的方法是**直接把 $b_i < 0$ 的那一些列都取負**，理論上應該要可以用基底變數的係數處理正負，不過這樣我覺得會更為麻煩。這樣每次替換變數的時候都會保證基底變數的係數非負，然後選取該列的時候 $a_{i, j}$ 必定是正的，所以從頭到尾 $b_i$ 都也會維持是正的。
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' & \boxed{-3x-3y} & \boxed{+s_1+s_2} && = -4 \\\
        && x + 2y    & -s_1      & +t_1  & = 2 \\\
        && 2x + y    & -s_2      & +t_2  & = 2 \\\
        &&  x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$
這時候會選擇進入的變數是 $x$，並且選取第三行，使得出來的變數是 $t_2$，變成
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' & -\frac 3 2y & +s_1-\frac 1 2 s_2 & +\frac 3 2 t_2& = -1 \\\
        && \frac 3 2 y    & -s_1+\frac 1 2s_2      & +t_1-\frac 1 2 t_2  & = 1 \\\
        && 2x + y    & -s_2      & +t_2  & = 2 \\\
        &&  x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$  
基底變成 $Z' = -1, x = 1, t_1 = 1$。

繼續選取進入變數，接下來會選到 $y$ 進入、$t_1$ 離開：
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' &  & & +t_1+t_2& = 0 \\\
        && \frac 3 2 y    & -s_1+\frac 1 2s_2      & +t_1-\frac 1 2 t_2  & = 1 \\\
        && 2x    & +\frac 2 3s_1 -\frac 4 3 s_2      & -\frac 2 3 t_1+\frac 4 3 t_2  & = \frac 4 3 \\\
        &&  x, y,   & s_1, s_2, & t_1, t_2      & \geq 0 
    \end{array}
$$  
基底變成 $Z' = 0, x = 1, y = \frac 2 3$ 並且 Phase I 的 LP 解完了。這時候 $t_1, t_2$ 確實變成了 $0$，所對應的解在原本的狀況也是合法的，所以我們直接把 $t_i$ 這些 artificial variable 都拿掉，並且放回我們原本的目標：
$$  
    \begin{array}{rrrrl}
        \text{maximize} & Z \\\
        \text{subject to}
        & Z & +x +y     &           & = 0 \\\
        && \frac 3 2 y    & -s_1+\frac 1 2s_2       & = 1 \\\
        && 2x    & +\frac 2 3s_1 -\frac 4 3 s_2      & = \frac 4 3 \\\
        &&  x, y,   & s_1, s_2, & \geq 0 
    \end{array}
$$  
這時候的基底是 $Z = \frac 3 5, x = 1, y = \frac 2 3$，不過新的第一列並沒有處理好，含有其他的基底變數，所以先消一下：
$$  
    \begin{array}{rrrrl}
        \text{maximize} & Z \\\
        \text{subject to}
        & Z &  &   +\frac 1 3 s_1+\frac 1 3s_2         & = -\frac 4 3 \\\
        && \frac 3 2 y    & -s_1+\frac 1 2s_2       & = 1 \\\
        && 2x    & +\frac 2 3s_1 -\frac 4 3 s_2      & = \frac 4 3 \\\
        &&  x, y,   & s_1, s_2, & \geq 0 
    \end{array}
$$  
然後我們就已經得到一組最佳解了！因此 Phase II 根本不用跑。只不過這是比較幸運的狀況，事實上 Phase II 還是要乖乖跑。

在 Phase I 中有機會遇到 Unbounded 嗎？很顯然是不可能的，因為答案至多是 $0$，**不過要是遇到解出來的 $Z'$ 非零（或是 artificial variable 有正的），就可以直接斷定無解**，例如說以下這個例子：

$$  
    \begin{array}{rrl}
        \text{maximize} & x \\\
        \text{subject to} 
        & x + y & \leq -1 \\\
        & x, y  & \geq 0
    \end{array}
$$

在 Phase I 就會直接寫出
$$  
    \begin{array}{rrl}
        \text{maximize} & Z' \\\
        \text{subject to} 
        & Z' + x + y + s_1 & = -1 \\\
        & -x - y - s_1 + t_1 & = 1 \\\
        & x, y, s_1, t_1  & \geq 0
    \end{array}
$$
無法進行任何基底的變動，所以已經抵達最佳解，不過 $Z'$ 此時是 $-1$（因為 $t_1 = 1$），就能直接斷定無解。

不過，直接 artificial variable 都拿掉是安全的嗎？有沒有可能 artificial variable 是基底變數？的確是有可能 artificial 是基底變數，但剛剛好是 $0$，在這個狀況就不可以貿然直接拿掉，因為這樣基底變數就會少一個。比如說以下的例子：
$$  
    \begin{array}{rrl}
        \text{maximize} & y \\\
        \text{subject to} 
        & -2x + y & \leq -6 \\\
        & x + y & \leq 3 \\\
        & x, y & \geq 0 
    \end{array}
$$
我們直接轉換成 Phase I 的目標
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' &&& +t_1 & = 0 \\\
        && -2x + y  & +s_1  & -t_1       & = -6 \\\
        && x + y    & +s_2  &           & = 3 \\\
        &&  x, y,   & s_1, s_2, & t_1   & \geq 0 
    \end{array}
$$  
基底是 $Z' = -6, s_2 = 3, t_1 = 6$，轉換成可以跑的形式就會是
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' & -2x + y & + s_1 && = -6 \\\
        && 2x - y  & -s_1  & +t_1       & = 6 \\\
        && x + y    & +s_2  &           & = 3 \\\
        &&  x, y,   & s_1, s_2, & t_1   & \geq 0 
    \end{array}
$$  
接下來鐵定是選擇 $x$ 作為進入變數，這時候基底會有兩種改變方法，其中一種是取代 $s_2$，改變為 $Z' = 0, x = 3, t_1 = 0$：
$$  
    \begin{array}{rrrrrl}
        \text{maximize} &  Z' \\\
        \text{subject to}
        & Z' & + 3y & + s_1 + 2s_2 && = 0 \\\
        &&  - 3y  & -s_1 - 2s_2  & +t_1       & = 0 \\\
        && x + y    & +s_2  &           & = 3 \\\
        &&  x, y,   & s_1, s_2, & t_1   & \geq 0 
    \end{array}
$$  
這時候 Phase I 結束了，也確實有一組合法的解，不過在把 $t_1$ 直接丟掉的時候，**基底變數也被我們丟掉了**！不過這種狀況其實不難處理，因為要是 $t_i$ 是基底，那那一行也可以當作 $s_i$ 是基底，只不過 $s_i$ 變數的係數會是負的，所以重新把這些基底變數換一下並且整列取負就好。值得注意的是這時候其實不消原本的目標函數也不會怎樣，因為這個目標函數很快就會被丟掉並且進入 Phase II，而 Phase I 的目標不可能會出現 $t_i$ 而不出現 $s_i$。

### Summary

Phase I 的目的就是找到一組可行解。

一開始會重新做一個新的目標函數：
$$  
    \begin{array}{rrrrrl}
        \text{maximize} & -t_{i} - t_{j} - t_{k} - \cdots
    \end{array}
$$
目標是對於所有 $b_i$ 是負的情況造一個新的變數（artificial variable），然後想辦法把他們消成 $0$，如果消不到 $0$ 就是不可能。

因為這些 artificial variable 會存在於目標，因此要先各個都消一次，然後又因為這些基底變數的係數是負的，那些列都需要取負。

做完這些調整之後會跟 Phase II 一模一樣，解完之後如果 artificial variable 是基底，那因為同樣的原因要把基底從 $t_i$ 換成對應的 $s_i$，並且係數是負的所以整行要取負。

最後把原本的目標函數放回來，然後消去一下讓基底變數不見就可以用這組可行解繼續 Phase II。

### Implementation
```cpp
const int mxM = 205;
const int mxN = 205 + 2 * mxM;
struct simplex
{
    const double inf = 1 / .0, eps = 1e-9;
    int n, m, k, var[mxN], inv[mxN], art[mxN];
    double A[mxM][mxN], B[mxM], x[mxN];
    void init(int _n) { n = _n, m = 0; }
    void equation(vector<double> a, double b)
    {
        for (int i = 0; i < n; i++)
            A[m][i] = a[i];
        B[m] = b, var[m] = n + m, ++m;
    }
    void pivot(int r, int c, double bx)
    {
        for (int i = 0; i <= m + 1; i++)
            if (i != r && abs(A[i][c]) > eps)
            {
                x[var[i]] -= bx * A[i][c] / A[i][var[i]];
                double f = A[i][c] / A[r][c];
                for (int j = 0; j <= n + m + k; j++)
                    A[i][j] -= A[r][j] * f;
                B[i] -= B[r] * f;
            }
    }
    double phase(int p)
    {
        while (true)
        {
            int in = min_element(A[m + p], A[m + p] + n + m + k + 1) - A[m + p];
            if (A[m + p][in] >= -eps)
                break;
            double bx = inf;
            int piv = -1;
            for (int i = 0; i < m; i++)
                if (A[i][in] > eps && B[i] / A[i][in] <= bx)
                    piv = i, bx = B[i] / A[i][in];
            if (piv == -1)
                return inf;
            int out = var[piv];
            pivot(piv, in, bx);
            x[out] = 0, x[in] = bx, var[piv] = in;
        }
        return x[n + m];
    }
    double solve(vector<double> c)
    {
        auto invert = [&](int r)
        {
            for (int j = 0; j <= n + m; j++)
                A[r][j] *= -1;
            B[r] *= -1;
        };
        k = 1;
        for (int i = 0; i < n; i++)
            A[m][i] = -c[i];
        fill(A[m + 1], A[m + 1] + mxN, 0.0);
        for (int i = 0; i <= m + 1; i++)
            fill(A[i] + n, A[i] + n + m + 2, 0.0), var[i] = n + i, A[i][n + i] = 1;

        for (int i = 0; i < m; i++)
        {
            if (B[i] < 0)
            {
                ++k;
                for (int j = 0; j <= n + m; j++)
                    A[m + 1][j] += A[i][j];
                invert(i);
                var[i] = n + m + k, A[i][var[i]] = 1,
                art[var[i]] = n + i;
            }
            x[var[i]] = B[i];
        }

        phase(1);
        if (*max_element(x + (n + m + 2), x + (n + m + k + 1)) > eps)
            return .0 / .0;
        for (int i = 0; i <= m; i++)
            if (var[i] > n + m)
                var[i] = art[var[i]], invert(i);
        k = 0;
        return phase(0);
    }
} lp;
```
如果我們原本有 $N$ 個變數，然後有 $M$ 個限制，因為每個限制可以有一個 slack variable 跟 artificial variable，再加上兩個目標，所以最多可以有 $N + 2M + 2$ 個變數在跑。

`pivot` 就只是把消去的部份拿出來，而 `phase` 跟上面 Phase II 的消去極為相似，這時候我們把目標放在第 $m$ 列，新的目標放在第 $m + 1$ 列，所以，當在 Phase I 的時候，呼叫 `phase(1)` 用新的目標當作目標函數去找可行解，然後把列都取完負就可以照著跑 Phase II `phase(0)`，因為原本的目標函數被放在第 $m$ 行，所以 Phase I 就會順便做消去了。

`solve` 的一開始就只是初始化，然後把負行紀錄的數量記為 $k$，並且在 Phase I 裡面就能順便用。Phase I 完如果有 artificial variable 非 $0$，回傳 `nan` 代表沒有合法解，然後把該取負的取完就可以回去跑 Phase II 找出最大值了。

理論上因為每個基底變數只會出現在一個等式之中，空間可以不需要多開這 $2M$ 個，不過筆者認為這樣的實作較為麻煩且不好壓 artificial variable + slack variable，就沒有把這邊壓下去了。

## Complexity

Simplex method 的最大敵人之一就是 Klee–Minty cube，在這樣的狀況 worst case 複雜度是 $O(2^N\text{poly}(N, M))$。

什麼？你跟我說我花了這麼久寫出來的模板是指數級的？

很抱歉，這確實是事實，不過在大多數競程跟實際用途，Simplex 跑得相當快，基本上這個模板應該已經足敷使用。

## References

[1] A. Arulandu, "Linear Programming," 2021. Accessed: Apr. 26, 2024. [Online]. Available: https://activities.tjhsst.edu/sct/lectures/2021/2021_03_12_Linear_Programming.pdf

這篇 [1] 有提到一些不只 Simplex 的方法，不過有一些重要比賽題目的暴雷，請讀者自行斟酌要不要閱讀。

[2]
"CME 338 Large-Scale Numerical Optimization - The Primal Simplex Method." Available: http://stanford.edu/class/cme338/notes/notes06-simplex.pdf

看起來很難的文章 [2]，我也看不懂。

[3]
M. Goemans, "18.310A lecture notes - Linear programming," 2015. Available: https://math.mit.edu/~goemans/18310S15/lpnotes310.pdf

MIT 的 lecture note [3]，裡面有很詳細的範例跟除了 Simplex 以外更多的東西，未來有空可能可以從裡面延伸更多關於線性規劃的內容。

[4]
Wikipedia Contributors, “Simplex algorithm,” Wikipedia, Dec. 09, 2019. https://en.wikipedia.org/wiki/Simplex_algorithm

‌英文維基百科 [4]，個人認為寫的很難懂，Phase I 也比較沒有做詳細說明。

[5]
“THE STEPS OF THE SIMPLEX ALGORITHM.” Available: https://www.hec.ca/en/cams/help/topics/The_steps_of_the_simplex_algorithm.pdf

這篇文章 [5] 內容不多，但是有非常淺顯易懂的 Phase II 範例。

[6]
“PHASE 1 SIMPLEX METHOD.” Accessed: Apr. 26, 2024. [Online]. Available: http://www.eng.uwaterloo.ca/~syde05/phase1.pdf

還蠻詳細的 Phase I 說明筆記 [6]。
