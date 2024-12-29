#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node
{
    Node*left;
    Node*right;
    int val;
    int height;
    Node(int val):left(nullptr),right(nullptr),height(1),val(val)
    {
        this->val = val;
    }
};


int getHeight(Node*cur)
{
    if(cur == nullptr)
        return 0;
    return cur->height;
}

int getBalance(Node*cur)
{
    return getHeight(cur->left) - getHeight(cur->right);
}

Node* leftRotate(Node* cur) {
    if (!cur || !cur->right) return cur;

    Node* newHead = cur->right;
    Node* rl = newHead->left;

    newHead->left = cur;
    cur->right = rl;

    cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
    newHead->height = max(getHeight(newHead->left), getHeight(newHead->right)) + 1;

    return newHead;
}

Node* rightRotate(Node* cur) {
    if (!cur || !cur->left) return cur;

    Node* newHead = cur->left;
    Node* lr = newHead->right;

    newHead->right = cur;
    cur->left = lr;

    cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
    newHead->height = max(getHeight(newHead->left), getHeight(newHead->right)) + 1;

    return newHead;
}





Node* insert(Node* cur, int val)
{
    if (cur == nullptr)
    {
        cur = new Node(val);
    } else {
        if (val < cur->val)
            cur->left = insert(cur->left, val);
        else if (val > cur->val)
            cur->right = insert(cur->right, val);
    }
        cur->height = 1 + max(getHeight(cur->left), getHeight(cur->right));
        int balance = getBalance(cur);
        if (balance > 1)
        {
            balance = getBalance(cur->left);
            if (balance == 1)
            {
                cur=  rightRotate(cur);
            } else {
                cur->left = leftRotate(cur->left);
                cur =  rightRotate(cur);
            }
        } else if (balance < -1)
        {
            balance = getBalance(cur->right);
            if (balance == -1)
            {
                cur = leftRotate(cur);
            } else {
                cur->right = rightRotate(cur->right);
                cur =  leftRotate(cur);
            }
    }
    return cur;
}

Node *root;

vector<int>level;
bool complete = true;
bool mustBeLeaf = false;

void levelOrder()
{
    queue<Node*>q;
    q.push(root);
    while(!q.empty())
    {
        int size = q.size();
        while(size-- > 0)
        {
            Node*cur = q.front(); q.pop();
            level.push_back(cur->val);
            if(cur->left != nullptr)
            {
                q.push(cur->left);
                if(mustBeLeaf)
                    complete = false;
            }else
            {
                mustBeLeaf = true;
            }
            
            if(cur->right != nullptr)
            {
                q.push(cur->right);
                if(mustBeLeaf)
                    complete = false;
            }else
            {
                mustBeLeaf = true;
            }
        }
    }
}






int main()
{
    int n;
    cin >> n;
    int val;
    for(int i = 0; i < n; i++)
    {
        cin >> val;
        root = insert(root,val);
    }
    levelOrder();
    cout << level[0];
    for(int i = 1;i < level.size(); i++)
        cout << " " << level[i];
    cout << endl;
    if(complete)
        cout << "YES";
    else cout << "NO";
    
}

