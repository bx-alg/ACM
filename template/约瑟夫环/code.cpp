// 当编号从0开始 时

class Solution
{
public:
    int iceBreakingGame(int num, int target)
    {
        if(num == 1)return 0;
        return (iceBreakingGame(num - 1,target) + target) % num;
    }

};

 
