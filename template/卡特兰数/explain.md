### 卡特兰数 (Catalan Numbers) 的四种表达式

1. ​**组合数差形式**​  
   $$
   f(n) = \binom{2n}{n} - \binom{2n}{n-1}
   $$

2. ​**组合数除法形式**​  
   $$
   f(n) = \frac{1}{n+1} \binom{2n}{n}
   $$

3. ​**递推关系**​  
   $$
   f(n) = f(n-1) \cdot \frac{4n-2}{n+1}
   $$

4. ​**求和形式**​  
   $$
   f(n) = \sum_{i=0}^{n-1} f(i) \cdot f(n-1-i)
   $$