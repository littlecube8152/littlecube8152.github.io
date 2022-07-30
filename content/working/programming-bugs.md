---
title: "常見程式的Bug"
date: 2030-02-16T16:15:54+08:00
draft: true
---

 
## 溢位
### int -> long long
注意$10^5$的範圍相乘就會有溢位了，  
不怕MLE之下都開```long long```比較保險。 

### long long -> double
如果涉及距離運算或是其他需要的浮點運算，  
都先把型態轉成```double```以免發生NaN的悲劇。  
  
像是下面的程式碼在座標都是int是不會過的：
```cpp
double dis(pair<long long,long long> p1, pair<long long,long long> p2)
{
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + 
                (p1.second - p2.second) * (p1.second - p2.second));
}
```
  
需要寫成：
```cpp
double dis(pair<long long,long long> p1, pair<long long,long long> p2)
{
    return sqrt(double(p1.first - p2.first) * (p1.first - p2.first) + 
                double(p1.second - p2.second) * (p1.second - p2.second));
}
```

### 乘除順序
在不影響結果之下，
建議先除再乘，避免溢位。  
(當然還是有可能溢位，那就是做法是爛的QAQ)  



## 計算
### 等於
等於一定要記得在判斷式要是「==」  
有些編譯器不會抓出來
### 負數求餘\%
例如下列程式碼：  
```cpp
cout << -2 % 5;
```
會輸出-2而不是3，
所以 ```a % b``` 寫成 ```(a % b + b) % b``` 會比較保險。
### 浮點數比較
絕對要使用誤差，例如下列程式碼：
```cpp
double n = 0;
for (int i = 1; i <= 200000; i++)
{
    n += 0.00001;
    cout << setprecision(0) << i << " " << fixed << setprecision(40) << n << '\n';
}
```
會輸出```100000 0.9999999999980837550594969798112288117409```這種東西，  
也就是說會有誤差，比賽的時候要特別注意要用誤差判定    

<!--## Runtime Error-></!-->



## Memory Limit Exceed
### Segment Fault
例如以下神奇的程式碼：  
```cpp
return 1 << (long long)log2(n);
```
輸入足夠大但$< 2^{50}$的數就會得到MLE  
出錯的原因是因為位移運算溢位了  
因為```1```預設是```int```  
產生Segment Fault而不是直接溢位處理

## 其他
### lesser<T>, greater<T>
放```priority_queue<T>```中，  
```greater<T>```會讓最小的在頂端  
```lesser<T>```會讓最大的在頂端(預設)