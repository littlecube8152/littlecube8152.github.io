---
title: "[Codeforces] 1182E"
description: "Product Oriented Recurrence"
date: 2021-02-03T21:08:39+08:00
draft: false
tags: ["codeforces","math","tutorial"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

矩陣好難:( 

## 題敘

[Link](https://codeforces.com/contest/1182/problem/E)\
對於 $ x \geq 4 $ ， $ f_n = c^{2n-6} f_{n-1} f_{n-2} f_{n-3} $\
給定 $ n, f_1, f_2, f_3, c $，求 $ f_n \mod 10^9 + 7 $。 \
\
$ ( 4 \leq n \leq 10^{18}, 1 \leq f_1, f_2, f_3, c \leq 10^9  ) $ 

## 想法

### TLE
用模仿費式數列DP的方法做的話......總複雜度 $ \mathcal{O}(n) $\
看一下值域，感覺就是會吃爆TLE......

### 快速冪
這裡要用到一個技巧：矩陣快速冪\
把原本的式子拆開，可以分成兩個部份解決\
$ f_n = (c^{2n-6}) \times (f_{n-1} f_{n-2} f_{n-3}) $\
先令 $ a_n, b_n, c_n, p_n $ 代表 $ f_n = c^{p_n} f_1^{a_n} f_2^{b_n} f_3^{c_n} $

#### 解決後半($f_1^{a_n} f_2^{b_n} f_3^{c_n}$)

對於這個部分，有：\
$\begin{cases} a_n = a_{n-1} + a_{n-2} + a_{n-3}\newline b_n = b_{n-1} + b_{n-2} + b_{n-3} \newline c_n = c_{n-1} + c_{n-2} + c_{n-3} \end{cases}$\
\
所以可以用轉移矩陣來做這件事：\
$\begin{bmatrix}
    {1} & {1} & {1} \newline
    {1} & {0} & {0} \newline
    {0} & {1} & {0}  \end{bmatrix}\begin{bmatrix}
    {a_{n-1}}  \newline
    {a_{n-2}}  \newline
    {a_{n-3}}  \end{bmatrix}=\begin{bmatrix}
    {a_{n-1} + a_{n-2} + a_{n-3}}  \newline
    {a_{n-1}}  \newline
    {a_{n-2}}   \end{bmatrix}=\begin{bmatrix}
    {a_{n}}  \newline
    {a_{n-1}}  \newline
    {a_{n-2}}   \end{bmatrix}$

結果：我們可以發現這三個共用一個轉移式，只要把左邊的矩陣用**快速冪**的方式，\
就可以$ \mathcal{O}(\log n) $ 內求得 $ a_n, b_n, c_n $\
\
然而，這個方法有溢位的風險，\
實作上可以每次做完矩陣乘法 mod $10^9 + 6 $，\
原因是因為費馬小定理：\
$ a^p \equiv a \mod p $\
$ a^{p-1} \equiv 1 \mod p $\
\
再透過一次快速冪，我們可以在$\mathcal{O}(\log n)$內得到$f_{n-1} f_{n-2} f_{n-3}$的部分，\
而$c^{2n-6}$呢？ 當然也可以！

#### 解決前半($c^{p_n}$)
先列出他的轉移式：\
$ p_n = 2n-6 + p_{n-1} + p_{n-2} + p_{n-3} $\
\
和前面不一樣的是，轉移式的前面多了變數，\
在轉移矩陣轉移的時候，我們要同時維護$2n-6$，\
可是矩陣好像不能每次+2，每次+2......嗎？\
\
在這個部分，可以增開一維，放一個常數$2$進去，\
常數本身也很好維護，所以轉移矩陣像這樣：\
$   \begin{bmatrix}
    {1} & {1} & {1} & {1} & {1} \newline
    {1} & {0} & {0} & {0} & {0} \newline
    {0} & {1} & {0} & {0} & {0} \newline
    {0} & {0} & {0} & {1} & {1} \newline
    {0} & {0} & {0} & {0} & {1} 
    \end{bmatrix}
    \begin{bmatrix}
    {p_{n-1}}  \newline
    {p_{n-2}}  \newline
    {p_{n-3}}  \newline
    {2(n-1)-6} \newline
    {2}  \end{bmatrix}
    =
    \begin{bmatrix}
    {p_{n-1} + p_{n-2} + p_{n-3} + 2(n-1)-6 + 2}  \newline
    {p_{n-1}}  \newline
    {p_{n-2}}  \newline
    {2(n-1)-6 + 2} \newline
    {2}   \end{bmatrix}
    =
    \begin{bmatrix}
    {p_{n}}  \newline
    {p_{n-1}}  \newline
    {p_{n-2}}  \newline
    {2n-6} \newline
    {2}   \end{bmatrix}$\
\
結果記得隨時mod，不然會溢位，\
再次利用快速冪求得$c^{p_n}$，複雜度$\mathcal{O}(\log n)$

#### 結果
總複雜度$\mathcal{O}(\log n)\$\
應該過的了，不然就是寫錯了(痛苦的Debug時間)

### 其他
似乎可以用原根+BSGS過？\
不過那個我還沒學過，改天學完再來處理這種方法。

## AC Code

### 快速冪
  寫得稍微有點長，不過應該蠻好看懂的(吧？)
  
  ```cpp
    #include <bits/stdc++.h>
    #define ll long long
    #define MOD 1000000007
    using namespace std;

    struct Matrix3
    {
        ll val[3][3] = {{0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0}};
        Matrix3 operator*(Matrix3 m)
        {
            Matrix3 r;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    for (int k = 0; k < 3; k++)
                        r.val[i][j] = (r.val[i][j] + this->val[i][k] * m.val[k][j]) % (MOD - 1);
            return r;
        }
    };

    struct Matrix5
    {
        ll val[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
        Matrix5 operator*(Matrix5 m)
        {
            Matrix5 r;
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    for (int k = 0; k < 5; k++)
                        r.val[i][j] = (r.val[i][j] + this->val[i][k] * m.val[k][j]) % (MOD - 1);
            return r;
        }
    };

    Matrix3 A = {{{1, 1, 1},
                 {1, 0, 0},
                 {0, 1, 0}}};
    Matrix5 B = {{{1, 1, 1, 1, 1},
                  {1, 0, 0, 0, 0},
                  {0, 1, 0, 0, 0},
                  {0, 0, 0, 1, 1},
                  {0, 0, 0, 0, 1}}};
    Matrix3 I3 = {{{1, 0, 0},
                  {0, 1, 0},
                  {0, 0, 1}}};
    Matrix5 I5 = {{{1, 0, 0, 0, 0},
                   {0, 1, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 1, 0},
                   {0, 0, 0, 0, 1}}};

    ll f1, f2, f3, c, n, pf1, pf2, pf3, pc;

    Matrix3 fast_pow3(ll n)
    {
        if (n == 0)
            return I3;
        if (n == 1)
            return A;
        if (n % 2)
            return A * fast_pow3(n - 1);

        Matrix3 HA = fast_pow3(n / 2);
        return HA * HA;
    }

    Matrix5 fast_pow5(ll n)
    {
        if (n == 0)
            return I5;
        if (n == 1)
            return B;
        if (n % 2)
            return B * fast_pow5(n - 1);

        Matrix5 HB = fast_pow5(n / 2);
        return HB * HB;
    }

    ll lfast_pow(ll base, ll n)
    {
        if (n == 0)
            return 1;

        if (n == 1)
            return base;

        if (n % 2)
            return (base * lfast_pow(base, n - 1) % (MOD));

        ll half = lfast_pow(base, n / 2);
        return (half * half) % (MOD);
    }

    int main()
    {
        cin >> n >> f1 >> f2 >> f3 >> c;
        Matrix3 M = fast_pow3(n - 3);
        Matrix5 N = fast_pow5(n - 3);
        pf1 = (M.val[0][2]);
        pf2 = (M.val[0][1]);
        pf3 = (M.val[0][0]);
        pc = (2 * N.val[0][4]) % (MOD - 1);
        cout << (((lfast_pow(f1, pf1) * lfast_pow(f2, pf2)) % (MOD)) * (lfast_pow(f3, pf3) * lfast_pow(c, pc) % (MOD))) % (MOD);
    }
  ```
  
