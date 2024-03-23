#include"iostream"
#include "list"
#include "queue"
#include "unordered_set"

using namespace std;

class Solution
{
    vector<vector<int>>res;
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        vector<vector<double>>arr;
        for(auto &v: points)
        {
            double x = v[0]; double  y = v[1];
            double dis = sqrt((pow(x,2) + pow(y,2)));
            arr.push_back({dis,x,y});
        }
        partition(arr,0,arr.size() - 1,k);
        return res;
    }

    void partition(vector<vector<double>>&arr,int l,int r,int k)
    {
        srand(time(nullptr));
        int pivot =(int)((rand() / RAND_MAX) * (r - l) + l);
        double  x = arr[pivot][0];
        int i1 = l - 1;
        int i2 = r + 1;
        for (int i = l; i < i2; i++)
        {
            if (arr[i][0] < x)
            {
                swap(arr[i], arr[++i1]);
            } else if (arr[i][0] > x)
            {
                swap(arr[i], arr[--i2]);
                i--;
            }
        }
        int n = arr.size();
        if (k > i1 + 1 && k < i2 + 1)
        {
            for(int i = 0; k; i++,k--)
                res.push_back({(int)arr[i][1], (int)arr[i][2]});
            return;
        }else if(k <= i1 + 1)
            partition(arr,l,i1,k);
        else partition(arr,i2,r,k);
    }
};