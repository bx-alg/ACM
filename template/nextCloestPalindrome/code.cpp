class Solution
{
public:
    string nearestPalindromic(string n)
    {
        string big = nextGreater(n);
        string small = nextSmaller(n);
        if(stoll(big) - stoll(n) < stoll(n) - stoll(small))
            return big;
        return small;
    }

    string nextSmaller(string num)
    {
        int n = num.size();
        string backUp = num;
        for (int i = 0,j =n - 1; i < j;)
        {
            num[j--] = num[i++];
        }
        if(num < backUp)return num;
        int carry = 1;
        for(int i = (n - 1) / 2; i >= 0; i--)
        {
            int d = num[i] - '0' - carry;
            if(d < 0)
            {
                num[i] = '9';
            }else
            {
                num[i] = d + '0';
                carry = 0;
            }
           num[n - i - 1] = num[i];
        }
        if(num[0] == '0' && n > 1)
        {
            return string(n - 1, '9');
        }
        return num;
    }

    string nextGreater(string num)
    {
        int n = num.size();
        string backUp = num;
        for (int i = 0,j =n - 1; i < j;)
        {
            num[j--] = num[i++];
        }
        if(num  > backUp)return num;
        int carry = 1;
        for(int i = (n - 1) / 2; i >= 0; i--)
        {
            int d = num[i] - '0' + carry;
            if(d > 9)
            {
                num[i] = '0';
            }else
            {
                num[i] = d + '0';
                carry = 0;
            }
            num[n - i - 1] =  num[i];
        }
        if(carry == 1)
        {
            string res(n + 1,'0');
            res.back()= res[0] = '1';
            return res;
        }
        return num;
    }


};