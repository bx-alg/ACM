long long comb[1000][1000];  
  for (int i = 0; i <= n; ++i) 
  {
      comb[i][i] = comb[i][0] = 1;            
      if (i==0) continue;
      for (int j = 1; j < i; ++j) 
      {
          comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
      }
  }  