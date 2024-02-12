#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_N = 200005;
    int cnt;
    int trie[MAX_N][26];
    int End[MAX_N];
    int fail[MAX_N];
    int box[MAX_N];
    int head[MAX_N];
    int Next[MAX_N];
    int to[MAX_N];
    int times[MAX_N];

    void addEdge(int u, int v)
    {
        Next[++cnt] = head[u];
        head[u] = cnt;
        to[cnt] = v;
    }

    void setFail()
    {
        int cur = 0;
        int l = 0, r = 0;
        for (int i = 0; i < 26; i++)
            if (trie[cur][i] != 0)
                box[r++] = trie[cur][i];
        while (l < r)
        {
            cur = box[l++];
            for (int i = 0; i < 26; i++)
            {
                if (trie[cur][i] == 0)
                {
                    trie[cur][i] = trie[fail[cur]][i];
                }
                else
                {
                    fail[trie[cur][i]] = trie[fail[cur]][i];
                    box[r++] = trie[cur][i];
                }
            }
        }
    }

    void build(vector<string> &dict)
    {
        for (int i = 0; i < dict.size(); i++)
        {
            string s = dict[i];
            int cur = 0;
            for (char ch : s)
            {
                int val = ch - 'a';
                if (trie[cur][val] == 0)
                    trie[cur][val] = ++cnt;
                cur = trie[cur][val];
            }
            End[i] = cur;
        }
    }

    void dfs(int i)
    {
        for (int ei = head[i]; ei != 0; ei = Next[ei])
        {
            int v = to[ei];
            dfs(v);
            times[i] += times[v];
        }
    }

    void match(string content)
    {
        int cur = 0;
        for (int i = 0; i < content.size(); i++)
        {
            int val = content[i] - 'a';
            cur = trie[cur][val];
            times[cur]++;
        }
    }

int main()
{
    string content;
    int n;
    vector<string> arr;
    cin >> n;
    while (n-- > 0)
    {
        string s;
        cin >> s;
        arr.push_back(s);
    }
    cin >> content;
    cnt = 0;
    build(arr);
    setFail();
    match(content);
    int temp = cnt;
    cnt = 0;
    for (int i = 1; i <= temp; i++)
    {
        addEdge(fail[i], i);
    }
    dfs(0);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << times[End[i]] << endl;
    }


}
